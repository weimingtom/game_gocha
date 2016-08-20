
local GS = _G.GS -- ローカル化によるちょっとした高速化

-- x,yで表される２次元ベクトルと方向が同じで長さが１のベクトル値を返す
function normalize_dir(x,y)
	local len = math.sqrt(x*x + y*y)
	if len == 0 then return x,y end
	return x/len,y/len
end

-- ランダムな方向のx,yを返す（ベクトルの長さは１）
function get_random_dir()
	local rad = (math.random() * 3.14159 * 2)
	return math.cos(rad), math.sin(rad)
end



-- 名前に使用する文字
local letters_for_name = {
    "ア","イ","ウ","エ","オ",
    "カ","キ","ク","ケ","コ",
    "ガ","ギ","グ","ゲ","ゴ",
    "サ","シ","ス","セ","ソ",
    "シャ","シュ","ショ",
    "ザ","ジ","ズ","ゼ","ゾ",
    "タ","チ","ツ","テ","ト",
    "ダ","デ","ド",
    "ナ","ニ","ヌ","ネ","ノ",
    "ハ","ヒ","フ","ヘ","ホ",
    "バ","ビ","ブ","ベ","ボ",
    "パ","ピ","プ","ペ","ポ",
    "マ","ミ","ム","メ","モ",
    "ヤ","ユ","ヨ",
    "ラ","リ","ル","レ","ロ",
    "ワ",
}--    "","","","","",

-- 名前に使用する文字（使用率の低いもの）
local letters_for_name_rare = {
    "キャ","キュ","キョ",
    "ギャ","ギュ","ギョ",
    "ジャ","ジュ","ジョ",
    "ヒャ","ヒュ","ヒョ",
    "ビャ","ビュ","ビョ",
    "ピャ","ピュ","ピョ",
    "ミャ","ミュ","ミョ",
    "リャ","リュ","リョ",
	"ヂ","ヅ",
	"ヲ",
}

-- 名前に使用する文字（名前の先頭にはならないもの）
local letters_for_name_nohead = {
    "ッ","ン","ー"
}

-- 一度作った名前を記憶しておく
-- キー：名前文字列
-- 値：true
local exist_names = {}

-- 名前を生成する
-- 既に使われている名前は使わないようにする
function get_new_name()
    do
    --return ""------------------------------------------------------------------ dummy
    end
	while true do
		local name = get_new_name_sub()
		if exist_names[name] == nil then
			exist_names[name] = true
			return name
		end
	end
end

-- ランダムな名前を生成する
function get_new_name_sub()
    local count = math.random(3,5)
	local name = ""
	for i=1,count do
		if i > 1 and math.random() < 0.1 then
			-- 先頭にはならない文字から選択
			name = name .. letters_for_name_nohead[math.random(#letters_for_name_nohead)]
		elseif math.random() < 0.1 then
			-- あまり使われない文字から選択
			name = name .. letters_for_name_rare[math.random(#letters_for_name_rare)]
		else
			-- 通常文字から選択
			name = name .. letters_for_name[math.random(#letters_for_name)]
		end
	end
	return name
end


-- 共通キャラ用アクター実装
subclass("CharActorCommon", Actor) {
}

-- コンストラクタ
function CharActorCommon:ctor(...)
	CharActorCommon.super.ctor(self, ...)

	self.hilight_actor = nil     -- ハイライトアクター
	self.hpbar_bg_actor = nil    -- HPバー背景アクター
	self.hpbar_actor = nil       -- HPバーアクター
	self.hpbar_rest_actor = nil  -- HPバーの残り部分アクター
	self.name_actor = nil		 -- 名前表示用アクター
end

-- 初期化
function CharActorCommon:init(cfg)
	-- パラメータ用テーブルを取り出す
    local p = self.params
	
	-- キャラの名前
	p.name = cfg.name or get_new_name() -- キャラの名前（ランダムな名前になる）

	cfg.scale = cfg.scale or 1.0
	
	-- 座標?速度等
	-- 設定値を優先する
    p.x = cfg.x
    p.y = cfg.y
    p.z = cfg.z or 0
    p.scale = cfg.scale
	p.mx = cfg.mx or 0
	p.my = cfg.my or 0
	p.speed = cfg.speed or 5
	p.z_depth_offset = cfg.z_depth_offset or 100

	-- 衝突判定位置
	p.collision_x_size = cfg.collision_x_size or (128 * 0.5)
	p.collision_y_size = cfg.collision_y_size or (128 * 0.3)
	p.collision_x_offset = cfg.collision_x_offset or 0
	p.collision_y_offset = cfg.collision_y_offset or 0

	-- 画像チップ情報
	p.chip_index_base = 0 -- 画像内キャラチップベース番号
	p.chip_index_offset = 0 -- チップ番号オフセット（現在の姿勢チップとの差分）
	--p.anim_count = 0 -- チップアニメカウント

	-- 敵味方情報
	p.is_enemy = false
	
	-- 射程距離
	p.attack_range = 200
	
	-- ヒットポイント
	p.maxhp = cfg.maxhp or 100
	p.hp = p.maxhp

	-- 攻撃関連
	p.attack_wait_count = 10 -- 攻撃までのウエイト
	p.attack_wait_count_init = 10 -- 攻撃までのウエイト（初期値）
	p.target_pos = nil -- ターゲット位置
	p.user_target_pos = nil -- ユーザー指定のターゲット位置
	
	-- ダメージ
	p.damages = {} -- 受けたダメージのリスト
    
    -- スーパークラスのinitを呼ぶ
    Actor.init(self, cfg)
end

-- 敵かどうかを返す関数
-- 引数がなければ敵か見方か
-- 引数があればそのキャラにとって敵か味方かを返す
function CharActorCommon:is_enemy(act)
	if act == nil then
		return self.params.is_enemy
	end
	return self.params.is_enemy ~= act:is_enemy()
end

-- 生きているかどうか
function CharActorCommon:is_alive()
	return (self.params.hp > 0)
end

-- 指定座標（ローカル）がこのキャラの内部かどうか判定
function CharActorCommon:is_inside(x, y)
	if x > -100 and x < 100 and y > -100 and y < 100 then
		return true
	end
	return false
end

-- ユーザー指定移動ターゲットを設定
function CharActorCommon:set_user_target_pos(x, y)
	local p = self.params
    p.user_target_pos = {x,y}
end

-- 移動ターゲット位置を設定
function CharActorCommon:set_target_pos(x, y)
	local p = self.params
    p.target_pos = {x,y}
end

-- 移動ターゲット位置を削除
function CharActorCommon:reset_target_pos(x, y)
	local p = self.params
    p.target_pos = nil
end

-- 指定位置に移動するよう移動速度を設定
function CharActorCommon:go_target_pos()
	local p = self.params
    if p.target_pos ~= nil then
        local dx = p.target_pos[1] - p.x
        local dy = p.target_pos[2] - p.y
        dx, dy = normalize_dir(dx, dy)
        p.mx = dx * p.speed
        p.my = dy * p.speed
    end
end

-- キャラ位置からターゲット位置までの距離の２乗を返す
function CharActorCommon:get_target_pos_distance_pow2()
	local p = self.params
    if p.target_pos == nil then return 0 end
	return self:get_distance_to_pos_pow2(p.target_pos[1], p.target_pos[2])
end

-- キャラ位置から指定位置(x,y)までの距離の２乗を返す
function CharActorCommon:get_distance_to_pos_pow2(x,y)
	local p = self.params
    local dx = x - p.x
    local dy = y - p.y
    return dx*dx+dy*dy
end

-- キャラのハイライトをON/OFFする
-- 引数はtrue/false (ON/OFF)
function CharActorCommon:hilight(enable)
	local scale = 1.0
	if enable then
		if self.hilight_actor ~= nil then
			-- 既にハイライトがついている
			return
		end
		local hilight = Actor:new()
		hilight:init()
		hilight:init_image("hilight", "effect", 0, 0, 150)
		hilight.spr:SetChipIndex(0)
		hilight.spr:SetScale(scale, scale)
		hilight.spr:SetCenter(64,96)
		self:add_child(hilight) -- 画面表示上の親子関係を設定
		self.hilight_actor = hilight
	else
		if self.hilight_actor ~= nil then
			self.hilight_actor:delete_internal()
			self.hilight_actor = nil
		end
	end
end

-- 名前表示用アクターを作成する
function CharActorCommon:add_name_disp()
	local p = self.params
	local scale = (1.0 / self.params.scale) * 0.5
	local x_offset = -64
	local y_offset = -110

	if self.name_actors == nil then
		self.name_actors = {}
	end
	
	local actor = Actor:new()
	actor:init()
	actor:init_text("name_text1", p.name, nil, x_offset+1, y_offset+1, 160)
	actor.spr:SetScale(scale, scale)
	actor.spr:SetCenter(4,16)
	actor.spr:SetColor(0,0,0)
	self:add_child(actor) -- 画面表示上の親子関係を設定
	table.insert(self.name_actors, actor)

	local actor = Actor:new()
	actor:init()
	actor:init_text("name_text2", p.name, nil, x_offset, y_offset, 161)
	actor.spr:SetScale(scale, scale)
	actor.spr:SetCenter(4,16)
	self:add_child(actor) -- 画面表示上の親子関係を設定
	table.insert(self.name_actors, actor)
end

-- HPバーを作成する
function CharActorCommon:add_hpbar()
	local scale = self.params.scale * 1.0
	local x_offset = -64
	local y_offset = -100
	
	local bg = Actor:new()
	bg:init()
	bg:init_image("hpbar_bg", "effect", x_offset, y_offset, 1060)
	bg.spr:SetChipIndex(1)
	bg.spr:SetScale(scale, scale)
	bg.spr:SetCenter(4,64)
	self:add_child(bg) -- 画面表示上の親子関係を設定
	self.hpbar_bg_actor = bg
	
	local hpbar = Actor:new()
	hpbar:init()
	hpbar:init_image("hpbar", "effect", x_offset, y_offset, 1061)
	hpbar.spr:SetChipIndex(2)
	hpbar.spr:SetScale(0, scale)
	hpbar.spr:SetCenter(0,64)
	self:add_child(hpbar) -- 画面表示上の親子関係を設定
	self.hpbar_actor = hpbar
	
	self:adjust_hpbar()
	
	local hpbar2 = Actor:new()
	hpbar2:init()
	hpbar2:init_image("hpbar_rest", "effect", x_offset + (120 * scale), y_offset, 161)
	hpbar2.spr:SetChipIndex(3)
	hpbar2.spr:SetScale(scale * (120/128), scale)
	hpbar2.spr:SetCenter(128,64)
	self:add_child(hpbar2) -- 画面表示上の親子関係を設定
	self.hpbar_rest_actor = hpbar2
	
	self:adjust_hpbar()
end

-- HPバーの表示を調整
function CharActorCommon:adjust_hpbar()
	local p = self.params
	if self.hpbar_actor == nil or self.hpbar_rest_actor == nil then
		return false
	end
	local scale = p.scale * 1.0
	local scale_max = scale * (120/128)
	local x_scale = scale_max * (p.hp / p.maxhp)
	self.hpbar_actor.spr:SetScale(x_scale, scale)
	self.hpbar_rest_actor.spr:SetScale(scale_max - x_scale, scale)
end

-- HPバーを削除
function CharActorCommon:remove_hpbar()
	if self.hpbar_actor ~= nil then
		self.hpbar_actor:delete_internal()
		self.hpbar_actor = nil
	end
	if self.hpbar_rest_actor ~= nil then
		self.hpbar_rest_actor:delete_internal()
		self.hpbar_rest_actor = nil
	end
	if self.hpbar_bg_actor ~= nil then
		self.hpbar_bg_actor:delete_internal()
		self.hpbar_bg_actor = nil
	end
end

-- マウス処理???不要？
function CharActorCommon:on_mouse(evtype, button, x, y)
	return false
end

-- イベントを捕捉したらtrueを返す
function CharActorCommon:on_click(button, x, y)
	return false
end

-- 衝突判定の範囲を返す
function CharActorCommon:get_collision_rect()
    local p = self.params
	return
		p.x + p.collision_x_offset,             -- x_center
		p.y + p.collision_y_offset,             -- y_center
		p.collision_x_size,    	-- x_size  
		p.collision_y_size    	-- y_size
--		p.x,                    -- x_center
--		p.y,                    -- y_center
--		128 * p.scale * 0.5,    -- x_size  
--		128 * p.scale * 0.3    -- y_size  
	    
end

-- 現在の座標を返す(フィールド上座標）
function CharActorCommon:get_pos()
    local p = self.params
	return p.x, p.y
end


-- 指定アクターまでの位置の差分を返す
function CharActorCommon:pos_diff(actor)
    local p = self.params
    local p2 = actor.params
	local dx = p2.x - p.x
	local dy = p2.y - p.y
	return dx, dy
end

-- 指定位置までの位置の差分を返す
function CharActorCommon:pos_diff_to(x,y)
    local p = self.params
	local dx = x - p.x
	local dy = y - p.y
	return dx, dy
end

-- 指定アクターまでの距離の２乗を返す
-- ルート(math.sqrt)の計算は重いため、最小限とする
function CharActorCommon:pos_distance_pow2(actor)
    local p = self.params
    local p2 = actor.params
	local dx = p2.x - p.x
	local dy = p2.y - p.y
	return (dx*dx + dy*dy)
end

-- 指定位置までの距離の２乗を返す
-- ルート(math.sqrt)の計算は重いため、最小限とする
function CharActorCommon:pos_distance_pow2_to(x,y)
    local p = self.params
	local dx = x - p.x
	local dy = y - p.y
	return (dx*dx + dy*dy)
end

-- 現在位置を適用
function CharActorCommon:apply_pos()
	local p = self.params
	-- 画像チップ番号変更
	-- 右向きなら+4する。
	self.spr:SetChipIndex(p.chip_index_base + p.chip_index_offset + ((p.mx >= 0) and 4 or 0))

	self.spr:MoveTo(p.x, p.y - p.z)
	self.spr:SetZ(p.y + p.z_depth_offset)
    self.spr:SetScale(p.scale, p.scale)
end

-- ダメージ追加
-- （ダメージアニメ中は追加ダメージを受けない）
function CharActorCommon:add_damage(damage)
	local p = self.params
	if self:get_state_name() == "state_damage" then
		return false
	end
	p.damages[#p.damages+1] = damage
	return true
end

-- ダメージを１つ消化
function CharActorCommon:consume_damage_one()
	local p = self.params
	if #p.damages == 0 then
		return nil
	end
	local damage = table.remove(p.damages,1) --テーブルの最初の値を消化する

	-- ダメージ分HPを減らす
	p.hp = p.hp - damage
	if p.hp < 0 then
		p.hp = 0
	end
	self:adjust_hpbar()
	return damage
end

-- 指定アクターとの衝突を回避する
function CharActorCommon:avoid_collision(actor, x,y,w,h)
	local p = self.params
	local x2,y2,w2,h2 = actor:get_collision_rect()
	local x_distance = (w+w2)/2
	local y_distance = (h+h2)/2
	local x_depth = x_distance - math.abs(x2-x)
	local y_depth = y_distance - math.abs(y2-y)
	-- XとYとで、避ける距離が短くて済む方向に避ける
	if x_depth < y_depth then
		local dx = (x2-x > 0) and -x_distance or x_distance
		p.x = x2 + dx
	else
		local dy = (y2-y > 0) and -y_distance or y_distance
		p.y = y2 + dy
	end
end

-- 基本動作
function CharActorCommon:base_motion()
	local p = self.params
	local hit = false

	-- 速度を位置に追加
	p.x = p.x + p.mx
	p.y = p.y + p.my
	-- 画面外に行かないようにする
	if p.x < 0              then hit = true; p.x = 0 end
	if p.x > GS.field_w     then hit = true; p.x = GS.field_w end
	if p.y < GS.field_h_min then hit = true; p.y = GS.field_h_min end
	if p.y > GS.field_h     then hit = true; p.y = GS.field_h end

	-- 地形との衝突判定
	local x,y,w,h = self:get_collision_rect()
	local near_obstacles_count = GS.collision_ground:search_collided_objects(x,y,w,h)
	for i = 0,near_obstacles_count-1 do
		local obs = get_result_actor(i, GS.collision_ground)
		-- 衝突した地形を「避ける」
		self:avoid_collision(obs,x,y,w,h)
		hit = true
	end

	-- 他キャラクターとの衝突判定
	local x,y,w,h = self:get_collision_rect()
	local near_actors_count = GS.collision:search_collided_objects(x,y,w,h)

	for i = 0,near_actors_count-1 do
		local act = get_result_actor(i, GS.collision)
		if act ~= self and act:is_alive() then
			if self:on_char_collision(act,x,y,w,h) then
				hit = true
			end
		end
	end

	return (hit == true)
end

-- キャラとの衝突発生時の動作
-- 通常は衝突したキャラを「避ける」
--（オーバーライドして動作を変更できる）
-- 衝突したらtrueを返す
function CharActorCommon:on_char_collision(act,x,y,w,h)
	-- 「避ける」
	self:avoid_collision(act,x,y,w,h)
	return true
end


-- 範囲内の一番近い敵をターゲットする
function CharActorCommon:target_nearest_enemy(detect_radius)
	--local self = actor
	local x,y = self:get_pos()
	local range = detect_radius
	local near_actors_count = GS.collision:search_collided_objects(x,y,range*2,range*2)

	local nearest_distance = nil  -- 最も近いアクターまでの距離
	local nearest_actor = nil    -- 最も近いアクター
	for i = 0,near_actors_count-1 do
		local act = get_result_actor(i, GS.collision)
		local is_enemy = self:is_enemy(act)
		if act ~= self and is_enemy and act:is_alive() then
			local distance = self:pos_distance_pow2(act)
			if distance < range * range then
				if nearest_distance == nil or distance < nearest_distance then
					nearest_distance = distance
					nearest_actor = act
				end
			end
		end
	end
	-- 最も近いアクターに移動
	if nearest_actor ~= nil then
		-- 範囲内の敵を発見→敵の位置を移動ターゲットにする
		local x,y = nearest_actor:get_pos()
		self:set_target_pos(x,y)
		return true
	end
	return false
end

-- 死亡時の共通ルーチン
--function dead_common_coroutine(self, rt)
function CharActorCommon:state_dead(rt)
	local p = self.params
	p.hp = 0
	local base_x = p.x
	local alpha = 0.6
	local alpha_step = 0.6 / 120
	self:remove_hpbar()
	for i=1,120 do
		-- サインカーブを描いて上へ移動
		p.z = p.z + 1
		p.x = base_x + math.sin(i/20*(3.14159*2)) * 5 
		p.scale = self.cfg.scale * 1.5
		self.spr:SetAlpha(alpha)
		alpha = alpha - alpha_step
		self:apply_pos()
		self:wait(1)
	end
	-- 一定時間経ったらアクター削除
	return "exit"
end

-- 編集モード用
function CharActorCommon:state_edit(rt)
	for i=0,100 do
		self:apply_pos()
		self:wait(1)
	end
	return "goto", "state_edit"
end