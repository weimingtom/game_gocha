--
--  WeaponActorCommon  : 武器アクター共通クラス
-- 

subclass("WeaponActorCommon", Actor) {
}

-- コンストラクタ
function WeaponActorCommon:ctor(...)
	WeaponActorCommon.super.ctor(self, ...)
end

-- cfg.src_actorには攻撃主のアクターを入れておくこと。
function WeaponActorCommon:init(cfg)
    local p = self.params
    p.x = cfg.x
    p.y = cfg.y
    p.z = cfg.z or 0
    p.scale = cfg.scale or 1.0
	p.mx = cfg.mx or 0
	p.my = cfg.my or 0
	p.speed = cfg.speed or 5
	p.z_depth_offset = cfg.z_depth_offset or 100
	
	-- 衝突判定位置
	p.collision_x_size = cfg.collision_x_size or 128
	p.collision_y_size = cfg.collision_y_size or 128
	p.collision_x_offset = cfg.collision_x_offset or 0
	p.collision_y_offset = cfg.collision_y_offset or 0
	
	-- 武器の速度?寿命
	p.speed = cfg.speed or 20
	p.lifetime = cfg.lifetime or 60
	
	-- ダメージ
	p.damage = cfg.damage or 10

	-- 画像チップ情報
	p.chip_index_base = cfg.chip_index_base or 0 -- 画像内キャラチップベース番号
	p.chip_index_offset = 0 -- チップ番号オフセット（現在の姿勢チップとの差分）
	--p.anim_count = 0 -- チップアニメカウント

	-- 敵味方情報
	p.is_enemy = false

    -- スーパークラスのinitを呼ぶ
    Actor.init(self, cfg)
end

-- 衝突判定の範囲を返す
function WeaponActorCommon:get_collision_rect()
    local p = self.params
	return
		p.x + p.collision_x_offset,             -- x_center
		p.y + p.collision_y_offset,             -- y_center
		p.collision_x_size,    	-- x_size  
		p.collision_y_size    	-- y_size
end

-- 指定アクターまでの距離の２乗を返す
-- ルート(math.sqrt)の計算は重いため、最小限とする
function WeaponActorCommon:pos_distance_pow2(actor)
    local p = self.params
    local p2 = actor.params
	local dx = p2.x - p.x
	local dy = p2.y - p.y
	return (dx*dx + dy*dy)
end

-- 矢と衝突している中で一番近い敵を見つける
function WeaponActorCommon:get_nearest_hit_enemy()
	local x,y,w,h = self:get_collision_rect()
	local collision = GS.collision
	-- 衝突しているアクターのリストを得る
	local near_actors_count = collision:search_collided_objects(x,y,w,h)

	local nearest_distance = nil
	local nearest_actor = nil
	local src_actor = self.cfg.src_actor
	for i = 0,near_actors_count-1 do
		local act = get_result_actor(i, collision)
		-- リーダーには当たらない
		if self:is_hit_target(act) then
			-- 最短距離の相手を覚えておく
			local distance = self:pos_distance_pow2(act)
			if nearest_distance == nil or distance < nearest_distance then
				nearest_distance = distance
				nearest_actor = act
			end
		end
	end
	return nearest_actor
end

-- 指定キャラアクターが攻撃対象かどうかを返す
-- （オーバーライド可能）
function WeaponActorCommon:is_hit_target(act)
	-- このゲームではリーダーは無敵のため、弾は通過する
	if act.classname == "LeaderActor" then
		return false
	end
	local src_actor = self.cfg.src_actor
	return act ~= self and act:is_alive() and src_actor:is_enemy(act)
end

-- 現在位置を適用
function WeaponActorCommon:apply_pos()
	local p = self.params
	self.spr:MoveTo(p.x, p.y - p.z)
	self.spr:SetZ(p.y + p.z_depth_offset)
    self.spr:SetScale(p.scale, p.scale)
end

-- 指定アクターにダメージを与える
function WeaponActorCommon:do_damage(target_actor)
    local p = self.params
    target_actor:add_damage(p.damage)
end

-- Actor削除時に実行される
function WeaponActorCommon:on_destroy()
	self.cfg.field:remove_weapon(self)
end


--
--  Arrow
--

-- 矢クラス
subclass("Arrow", WeaponActorCommon) {}

-- コンストラクタ
function Arrow:ctor(...)
	Arrow.super.ctor(self, ...)

end

-- 初期化
function Arrow:init(cfg)
	self:init_image("arrow", "weapon", cfg.x, cfg.y, 20)
	self.spr:SetScale(0.5,0.5)
    self.spr:SetCenter(100,150)
	self.spr:SetOpType(cclass.SpriteNode.OP_ADD)
	
	cfg.scale = 1.0
	
	local p = self.params
    cfg.z = 5
    
    -- スーパークラスのinitを呼ぶ
    Arrow.super.init(self, cfg)

	p.z_depth_offset = 150 -- 通常より手前に表示する
	
	p.chip_index_base = 2
	self.spr:SetChipIndex(p.chip_index_base)

end

------ 状態関数

function Arrow:state_start(rt)
	return "goto", "state_move"
end

-- 弾丸移動時
function Arrow:state_move(rt)
	local p = self.params
	for i=1,p.lifetime do
		-- 着弾していればダメージを与え、着弾後状態へ移行
		local nearest_hit_enemy = self:get_nearest_hit_enemy()
		if nearest_hit_enemy ~= nil then
			self:do_damage(nearest_hit_enemy)
			return "goto", "state_after_hit"
		end
		p.x = p.x + p.mx
		p.y = p.y + p.my
		self:apply_pos()
		self:wait(1)
	end
	return "exit"
end

-- ヒット後のアニメ
function Arrow:state_after_hit(rt)
	local p = self.params
	local orig_scale = p.scale
	local alpha = 1.0
	-- 30フレーム移動して消滅する
	for i=1,30 do
		p.x = p.x + p.mx
		p.y = p.y + p.my
		p.scale = orig_scale * (0.5 - i * 0.01)
		self.spr:SetAlpha(alpha)
		alpha = alpha - (1.0/30)
		self:apply_pos()
		self:wait(1)
	end
	return "exit"
end






--
--  Katana
--

-- 刀クラス
subclass("Katana", WeaponActorCommon) {}

-- コンストラクタ
function Katana:ctor(...)
	Katana.super.ctor(self, ...)
end

-- 初期化
function Katana:init(cfg)
	self:init_image("katana", "weapon", cfg.x, cfg.y, 20)
	self.spr:SetScale(1.0,1.0)
    self.spr:SetCenter(64,80)
	self.spr:SetOpType(cclass.SpriteNode.OP_ADD)
	local p = self.params
    cfg.z = 5
    
    -- スーパークラスのinitを呼ぶ
    Katana.super.init(self, cfg)

	p.z_depth_offset = 120 -- 通常より手前に表示する
	
	--p.mx = (cfg.dir == "right") and 10 or -10
	p.chip_index_offset = (cfg.dir == "right") and 1 or 0
	self.spr:SetChipIndex(p.chip_index_base + p.chip_index_offset)
end

------ 状態関数

function Katana:state_start(rt)
	local p = self.params
	local prepare_time = 3
	for i=1,prepare_time do
		self.spr:SetAlpha(1.0 * i / (prepare_time+1))
		p.x = p.x + p.mx
		p.y = p.y + p.my
		self:apply_pos()
		self:wait(1)
	end
	return "goto", "state_move"
end

-- 弾丸移動時
function Katana:state_move(rt)
	local p = self.params
	--local cfg = self.cfg
	p.alpha = 1.0
	for i=1,p.lifetime do
		-- 着弾していればダメージを与え、着弾後状態へ移行
		local nearest_hit_enemy = self:get_nearest_hit_enemy()
		if nearest_hit_enemy ~= nil then
			self:do_damage(nearest_hit_enemy)
			return "goto", "state_after_hit"
		end
		p.alpha = 1.0 - i * 0.01
		self.spr:SetAlpha(p.alpha)
		p.x = p.x + p.mx
		p.y = p.y + p.my
		self:apply_pos()
		self:wait(1)
	end
	return "exit"
end

-- ヒット後のアニメ
function Katana:state_after_hit(rt)
	local p = self.params
	local orig_scale = p.scale
	-- 透明度を増して消滅する
	local frame_count = 7
	for i=1,frame_count do
		--p.x = p.x + ((p.mx > 0) and 1 or -1)
		self.spr:SetAlpha(p.alpha)
		p.alpha = p.alpha - (1.0/frame_count)
		if p.alpha < 0 then 
			p.alpha = 0
		end
		self:apply_pos()
		self:wait(1)
	end
	return "exit"
end

--
--  Ofuda
--

-- お札？クラス
subclass("Ofuda", WeaponActorCommon) {}

-- コンストラクタ
function Ofuda:ctor(...)
	Ofuda.super.ctor(self, ...)
end

-- 初期化
function Ofuda:init(cfg)
	self:init_image("Ofuda", "weapon", cfg.x, cfg.y, 20)
	self.spr:SetScale(1.0,1.0)
    self.spr:SetCenter(64,80)
	self.spr:SetOpType(cclass.SpriteNode.OP_ADD)
	local p = self.params
    cfg.z = 5
    
    -- スーパークラスのinitを呼ぶ
    Ofuda.super.init(self, cfg)

	p.z_depth_offset = 120 -- 通常より手前に表示する
	
	--p.mx = (cfg.dir == "right") and 10 or -10
	p.chip_index_offset = 0 --(cfg.dir == "right") and 1 or 0
	self.spr:SetChipIndex(p.chip_index_base + p.chip_index_offset)
end

------ 状態関数

function Ofuda:state_start(rt)
	local p = self.params
	local prepare_time = 2
	for i=1,prepare_time do
		self.spr:SetAlpha(1.0 * i / (prepare_time+1))
		p.x = p.x + p.mx
		p.y = p.y + p.my
		self:apply_pos()
		self:wait(1)
	end
	return "goto", "state_move"
end

-- 弾丸移動時
function Ofuda:state_move(rt)
	local p = self.params
	--local cfg = self.cfg
	p.alpha = 1.0
	for i=1,p.lifetime do
		-- 着弾していればダメージを与え、着弾後状態へ移行
		local nearest_hit_enemy = self:get_nearest_hit_enemy()
		if nearest_hit_enemy ~= nil then
			self:do_damage(nearest_hit_enemy)
			return "goto", "state_after_hit"
		end
		p.alpha = 1.0 - i * 0.01
		self.spr:SetAlpha(p.alpha)
		p.x = p.x + p.mx
		p.y = p.y + p.my
		self:apply_pos()
		self:wait(1)
	end
	return "exit"
end

-- ヒット後のアニメ
function Ofuda:state_after_hit(rt)
	local p = self.params
	local orig_scale = p.scale
	-- 透明度を増して消滅する
	local frame_count = 15
	for i=1,frame_count do
		--p.x = p.x + ((p.mx > 0) and 1 or -1)
		self.spr:SetAlpha(p.alpha)
		p.alpha = p.alpha - (1.0/frame_count)
		if p.alpha < 0 then 
			p.alpha = 0
		end
		self:apply_pos()
		self:wait(1)
	end
	return "exit"
end


