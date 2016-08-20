

--
--  リーダーキャラのアクター
--

subclass("LeaderActor", CharActorCommon) {
	walk_anim_seq = { 0,0,1,1,1,0,0,2,2,2 }, -- 歩行アニメの順序
}

-- コンストラクタ
function LeaderActor:ctor(...)
	LeaderActor.super.ctor(self, ...)
end

function LeaderActor:init(cfg)
	local imagename = "chr1"
	if cfg.type == "samurai" then
		-- 侍
		imagename = "chr1"
	elseif cfg.type == "miko" then
		-- 巫女
		imagename = "chr2"
	else
		error("bad cfg.type : "..tostring(cfg.type));
	end
    self:init_image("chars", imagename, 0,0, 20)
    self.spr:SetCenter(64,96)
    --self.spr:SetScale(1.5,1.5)

	local p = self.params
    cfg.scale = 1.0
	cfg.speed = cfg.speed or 4
	CharActorCommon.init(self,cfg)

	p.attack_wait_count_init = 20 --80
	p.attack_wait_count = p.attack_wait_count_init
	p.chibis = {}

	-- コマンド： "attack"（攻撃モード） または "defence"（防御モード）
	p.command = "defence"
	
	-- チビキャラを追加
	for i=1,5 do
		local rad = (i/10) * 2 * 3.14159
		self:add_chibi(p.x + math.cos(rad) * 30, p.y + math.sin(rad) * 30)
	end
	
	-- 名前表示をつける
	self:add_name_disp()

	-- 攻撃?防御表示
	local scale = (1.0 / self.params.scale) * 0.25
	local command_actor = Actor:new()
	command_actor:init()
	command_actor:init_image("command", "frame", 24, -88, 150)
	command_actor.spr:SetChipIndex(32)
	command_actor.spr:SetScale(scale, scale)
	command_actor.spr:SetCenter(0,0)
	self:add_child(command_actor) -- 画面表示上の親子関係を設定
	self.command_actor = command_actor
	
	self:adjust_command_icon()

end

-- 移動ターゲット位置を設定
function LeaderActor:set_target_pos(x, y)
	local p = self.params
    p.target_pos = {x,y}
end

-- 移動ターゲット位置を削除
function LeaderActor:reset_target_pos(x, y)
	local p = self.params
    p.target_pos = nil
end

-- チビキャラを指定位置に追加
function LeaderActor:add_chibi(x, y)
	local p = self.params
	local chibi = ChibiActor:new()
	local field = self.cfg.field
	chibi:init{ type = self.cfg.type, x = x, y = y, leader = self, field = field}
	field:add_child(chibi) -- 画面表示上の親子関係を設定
	table.insert(field.char_actors, chibi)
	table.insert(p.chibis, chibi)
end


-- 攻撃判定ルーチン
function LeaderActor:attack()
	local p = self.params
	-- 攻撃ウエイトが終わったら攻撃できる
	if p.attack_wait_count > 0 then
		p.attack_wait_count = p.attack_wait_count - 1
	end
	if p.attack_wait_count > 0 then
		return false
	end

    -- 一番近い敵をターゲットする
	if not self:target_nearest_enemy(300) then
		return false
	end

	-- 攻撃発射
	local speed = 15
	local field = self.cfg.field
	local mx, my = normalize_dir(p.target_pos[1]-p.x, p.target_pos[2]-p.y)
	mx = mx * speed
	my = my * speed
	if self.cfg.type == "samurai" then
		-- 侍なら刀エフェクト
		field:add_weapon(Katana, self, {
			dir = (mx >= 0) and "right" or "left",     -- 右向きか、左向きか
			x = p.x,                                   -- 武器の初期座標(X)
			y = p.y,                                   -- 武器の初期座標(Y)
			mx = mx,                                   -- 武器の速度(X)
			my = my,                                   -- 武器の速度(Y)
			collision_x_size = 60 * self.cfg.scale,    -- 武器の衝突判定サイズ(X)
			collision_y_size = 80 * self.cfg.scale,    -- 武器の衝突判定サイズ(Y)
			lifetime = 5,                              -- 武器の寿命
			damage = 3,                                -- 武器のダメージ
			chip_index_base = 0	})                     -- 画像チップのベース番号    
	else
		-- 巫女なら光の玉
		field:add_weapon(Ofuda, self, {
			x = p.x,                                   -- 武器の初期座標(X)
			y = p.y,                                   -- 武器の初期座標(Y)
			mx = mx,                                   -- 武器の速度(X)
			my = my,                                   -- 武器の速度(Y)
			collision_x_size = 30 * self.cfg.scale,    -- 武器の衝突判定サイズ(X)
			collision_y_size = 30 * self.cfg.scale,    -- 武器の衝突判定サイズ(Y)
			lifetime = 15,                              -- 武器の寿命
			damage = 2,                                -- 武器のダメージ
			chip_index_base = 2	})                     -- 画像チップのベース番号    
	end

	-- 攻撃ウエイトカウンタを戻す
	p.attack_wait_count = p.attack_wait_count_init
	
	-- そのままだと移動してしまうのでターゲットをリセット
	p.target_pos = nil
	
	return true
end

-- チーム全体のハイライトをON/OFFする
function LeaderActor:hilight_team(onoff)
	local p = self.params
	self:hilight(onoff)
	for i,act in ipairs(p.chibis) do
		act:hilight(onoff)
	end
end

function LeaderActor:remove_chibi(child)
	local p = self.params
	remove_value_from_array(p.chibis, child)
end

-- Actor削除時に実行される
function LeaderActor:on_destroy()
	self.cfg.field:remove_char(self)
end

-- キャラとの衝突発生時の動作
function LeaderActor:on_char_collision(act,x,y,w,h)
	-- チビはあたり判定から除外する
	if act.classname ~= "ChibiActor" then
		self:avoid_collision(act,x,y,w,h)
		return true
	end
	return false
end

-- コマンドをセット
-- command : "attack" （攻撃）
--         : "defence" （防御）
function LeaderActor:set_command(command)
	local p = self.params
	print("set_command : ",command)
	if command == "attack" or command == "defence" then
		p.command = command
		self:adjust_command_icon()
	end
end

-- コマンド表示アイコンを更新
function LeaderActor:adjust_command_icon()
	if self.command_actor == nil then
		return 
	end
	local actor = self.command_actor
	local p = self.params
	if p.command == "attack" then
		actor.spr:SetChipIndex(32) -- 攻撃アイコンチップ番号
	else
		actor.spr:SetChipIndex(35) -- 防御アイコンチップ番号
	end
end

------ 状態関数

function LeaderActor:state_start(rt)
	local p = self.params		
	if not self:is_alive() then
		return "goto", "state_dead"
	end
	return "goto", "state_move"
end

-- 待機状態
function LeaderActor:state_stand(rt)
	local p = self.params		
	return "goto", "state_stand_normal"
end

-- 通常待機状態
-- 近づいたら攻撃
-- 一定フレームごとにstand状態に戻る
function LeaderActor:state_stand_normal(rt)
	local p = self.params
	for i=1,100 do
		-- 子分がいなくなると親分は終わり
		if #(p.chibis) == 0 then
			return "goto", "state_dead"
		end
		p.mx = 0
		p.my = 0
		if p.command == "attack" then
			if self:target_nearest_enemy(300) then
				return "goto", "state_move"
			end
		end
		-- 強制移動モード
		if p.user_target_pos ~= nil then
			return "goto", "state_move_force"
		end
		-- 移動ターゲットが設定されていたら移動
		if p.target_pos ~= nil then
			return "goto", "state_move"
		end
		self:base_motion()
		self:apply_pos()
		self:wait(1)
		-- 攻撃可能なら攻撃モードへ移行
		if self:attack() then
			return "goto", "state_attack"
		end
	end
	return "goto", "state_stand"
end

-- 強制移動モード（ユーザーによる移動先指定）
function LeaderActor:state_move_force(rt)
	local p = self.params
	local near_distance_pow2 = 60*60 -- 停止する距離（の２乗）
	local max_move_time = 300 -- 移動し続ける最大フレーム時間
	for i=1,max_move_time do
		-- 子分がいなくなると親分は終わり
		if #(p.chibis) == 0 then
			return "goto", "state_dead"
		end
		p.target_pos = p.user_target_pos
		self:go_target_pos()
		-- 歩行アニメーション設定
		p.chip_index_offset = self.walk_anim_seq[(i%4)+1]
		self:base_motion()
		self:apply_pos()
		self:wait(1)
		
		-- 指定位置に近づいたらstand状態へ移行
		if self:get_target_pos_distance_pow2() < near_distance_pow2 then
			self:reset_target_pos()
			p.user_target_pos = nil
			return "goto", "state_stand"
		end
	end
	-- ターゲットに達していないが時間切れで一旦終了
	p.user_target_pos = nil
	return "goto", "state_stand"
end


-- 通常移動モード
function LeaderActor:state_move(rt)
	local p = self.params
	local near_distance_pow2 = 60*60 -- 停止する距離（の２乗）
	local max_move_time = 60 -- 移動し続ける最大フレーム時間
	for i=1,max_move_time do
		-- 子分がいなくなると親分は終わり
		if #(p.chibis) == 0 then
			return "goto", "state_dead"
		end
		-- 強制移動モード
		if p.user_target_pos ~= nil then
			return "goto", "state_move_force"
		end
		self:go_target_pos()
		-- 歩行アニメーション設定
		p.chip_index_offset = self.walk_anim_seq[(i%4)+1]
		self:base_motion()
		self:apply_pos()
		self:wait(1)
		-- 攻撃可能なら攻撃モードへ移行
		if self:attack() then
			return "goto", "state_attack"
		end
		
		-- 指定位置に近づいたらstand状態へ移行
		if self:get_target_pos_distance_pow2() < near_distance_pow2 then
			self:reset_target_pos()
			return "goto", "state_stand"
		end
	end
	return "goto", "state_stand"
end

-- 「攻撃中」状態
-- 攻撃後一定時間固まる。
function LeaderActor:state_attack(rt)
	local p = self.params
	for i=1,5 do
		p.chip_index_offset = 3
		
		-- 子分がいなくなると親分は終わり
		if #(p.chibis) == 0 then
			return "goto", "state_dead"
		end
		self:apply_pos()
		self:wait(1)
	end
	p.chip_index_offset = 0

	-- 一定時間経ったらstand状態へ移行
	return "goto", "state_stand"
end
    
-- 「死んだ」状態
--LeaderActor.state_dead = dead_common_coroutine


--
--  チビキャラのアクター
--

subclass("ChibiActor", CharActorCommon) {
	walk_anim_seq = { 0,0,1,1,1,0,0,2,2,2 }, -- 歩行アニメの順序
}

-- コンストラクタ
function ChibiActor:ctor(...)
	ChibiActor.super.ctor(self, ...)
end


function ChibiActor:init(cfg)
	local imagename = "chr1"
	if cfg.type == "samurai" then
		-- 侍
		imagename = "chr1"
		cfg.maxhp = 100
	elseif cfg.type == "miko" then
		-- 巫女
		imagename = "chr2"
		cfg.maxhp = 50
	else
		error("bad cfg.type : "..tostring(cfg.type));
	end

    self:init_image("chars", imagename, 0,0, 20)
    self.spr:SetCenter(64,96)
    --self.spr:SetScale(0.6,0.6)

	local p = self.params
    cfg.scale = 0.6

	CharActorCommon.init(self,cfg)

	p.attack_wait_count_init = 40 --130
	p.attack_wait_count = p.attack_wait_count_init
	p.leader = cfg.leader -- リーダー	

	-- HPバーをつける
	self:add_hpbar()
	-- 名前表示をつける
	self:add_name_disp()
end

-- 攻撃判定ルーチン
function ChibiActor:attack()
	local p = self.params
	-- 攻撃ウエイトが終わったら攻撃できる
	if p.attack_wait_count > 0 then
		p.attack_wait_count = p.attack_wait_count - 1
	end
	if p.attack_wait_count > 0 then
		return false
	end

    -- 一番近い敵をターゲットする
	if not self:target_nearest_enemy(300) then
		return false
	end

	-- 攻撃発射
	local speed = 10
	local field = self.cfg.field
	local mx, my = normalize_dir(p.target_pos[1]-p.x, p.target_pos[2]-p.y)
	mx = mx * speed
	my = my * speed
	if self.cfg.type == "samurai" then
		-- 侍なら刀エフェクト
		field:add_weapon(Katana, self, {
			dir = (mx >= 0) and "right" or "left",     -- 右向きか、左向きか
			x = p.x,                                   -- 武器の初期座標(X)
			y = p.y,                                   -- 武器の初期座標(Y)
			mx = mx,                                   -- 武器の速度(X)
			my = my,                                   -- 武器の速度(Y)
			collision_x_size = 60 * self.cfg.scale,    -- 武器の衝突判定サイズ(X)
			collision_y_size = 80 * self.cfg.scale,    -- 武器の衝突判定サイズ(Y)
			lifetime = 5,                              -- 武器の寿命
			damage = 4,                                -- 武器のダメージ
			chip_index_base = 0	})                     -- 画像チップのベース番号    
	else
		-- 巫女なら光の玉
		field:add_weapon(Ofuda, self, {
			x = p.x,                                   -- 武器の初期座標(X)
			y = p.y,                                   -- 武器の初期座標(Y)
			mx = mx,                                   -- 武器の速度(X)
			my = my,                                   -- 武器の速度(Y)
			collision_x_size = 30 * self.cfg.scale,    -- 武器の衝突判定サイズ(X)
			collision_y_size = 30 * self.cfg.scale,    -- 武器の衝突判定サイズ(Y)
			lifetime = 15,                              -- 武器の寿命
			damage = 2,                                -- 武器のダメージ
			chip_index_base = 2	})                     -- 画像チップのベース番号    
	end

	-- 攻撃ウエイトカウンタを戻す
	p.attack_wait_count = p.attack_wait_count_init
	
	-- そのままだと移動してしまうのでターゲットをリセット
	p.target_pos = nil
	
	return true
end

-- Actor削除時に実行される
function ChibiActor:on_destroy()
	local p = self.params
	if p.leader ~= nil then
		p.leader:remove_chibi(self)
	end
	self.cfg.field:remove_char(self)
end

------ 状態関数

function ChibiActor:state_start(rt)
	local p = self.params
	p.speed = 10
	if not self:is_alive() then
		return "goto", "state_dead"
	end
	return "goto", "state_follow"
end

function ChibiActor:state_stand(rt)
	return "goto", "state_move"
end

-- 自由移動
function ChibiActor:state_move(rt)
	local p = self.params
	p.speed = 8
	p.mx = (p.mx>0) and p.speed or -p.speed;
	p.my = (p.my>0) and p.speed or -p.speed;
	for i=1,10000 do
		if #(p.damages) > 0 then
			return "goto", "state_damage"
		end
		if self:pos_distance_pow2(p.leader) > (100*100) then
			return "goto", "state_goleader"
		end
		
		-- 歩行アニメーション設定
		if p.mx ~= 0 or p.my ~= 0 then
			local len = #self.walk_anim_seq
			p.chip_index_offset = self.walk_anim_seq[(i%len)+1]
		end
		self:base_motion()
		self:apply_pos()
		self:wait(1)
		-- 攻撃可能なら攻撃モードへ移行
		if self:attack() then
			return "goto", "state_attack"
		end
	end
	return "goto", "state_move"
end

-- リーダーの近くに戻るモード
function ChibiActor:state_goleader(rt)
	local p = self.params
	p.speed = 10
	
	for i=1,10000 do
		if #(p.damages) > 0 then
			return "goto", "state_damage"
		end
		local distance2 = self:pos_distance_pow2(p.leader)
		if distance2 < (80*80) then
			return "goto", "state_follow"
		end
		local dx, dy = normalize_dir(self:pos_diff(p.leader))
		p.mx = dx * p.speed
		p.my = dy * p.speed
		
		-- 遠すぎる場合はやむをえずリーダーの近くまでワープする
		if distance2 > (200*200) then
			local ddx,ddy = self:pos_diff(p.leader)
			p.mx = ddx - dx * 30
			p.my = ddy - dy * 30
		end
		
		-- 歩行アニメーション設定
		if p.mx ~= 0 or p.my ~= 0 then
			local len = #self.walk_anim_seq
			p.chip_index_offset = self.walk_anim_seq[(i%len)+1]
		end
		self:base_motion()
		self:apply_pos()
		self:wait(1)
	end
	return "goto", "state_move"
end

-- リーダーについていくモード
function ChibiActor:state_follow(rt)
	local p = self.params
	p.speed = 10
	for i=1,10000 do
		if #(p.damages) > 0 then
			return "goto", "state_damage"
		end
		local distance2 = self:pos_distance_pow2(p.leader)
		if distance2 > (150*150) then
			return "goto", "state_goleader"
		end
		--local dx, dy = normalize_dir(self:pos_diff(p.leader))
		-- リーダーと同じ移動を行う
		p.mx = p.leader.params.mx
		p.my = p.leader.params.my
		
		-- 歩行アニメーション設定
		if p.mx ~= 0 or p.my ~= 0 then
			local len = #self.walk_anim_seq
			p.chip_index_offset = self.walk_anim_seq[(i%len)+1]
		end
		self:base_motion()
		self:apply_pos()
		self:wait(1)
		-- 攻撃可能なら攻撃モードへ移行
		if self:attack() then
			return "goto", "state_attack"
		end
	end
	return "goto", "state_move"
end


-- 「攻撃中」状態
-- 攻撃後一定時間固まる。
function ChibiActor:state_attack(rt)
	local p = self.params
	for i=1,5 do
		p.chip_index_offset = 3
		if #(p.damages) > 0 then
			return "goto", "state_damage"
		end
		self:apply_pos()
		self:wait(1)
	end
	p.chip_index_offset = 0
	-- 一定時間経ったらstand状態へ移行
	return "goto", "state_stand"
end


-- 「ダメージを受けた」状態
function ChibiActor:state_damage(rt)
	local p = self.params
	if #p.damages == 0 then
		print(" #p.damages == 0 ")
	end
	local damage = self:consume_damage_one()
	print("damage : ", damage, "#damages=", #p.damages)
	for i=1,20 do
		self.spr:SetColor(0.2,0.2,0.2)
		self:apply_pos()
		self:wait(1)
	end
	self.spr:SetColor(1.0,1.0,1.0)
	-- 一定時間経ったら別の状態へ移行
	if p.hp == 0 then
		return "goto", "state_dead"
	end
	return "goto", "state_follow"
end

-- 「死んだ」状態
--ChibiActor.state_dead = dead_common_coroutine





