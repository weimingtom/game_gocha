--
--  敵キャラのアクター
--

subclass("Enemy1Actor", CharActorCommon) {
	walk_anim_seq = { 0,0,1,1,1,0,0,2,2,2 }, -- 歩行アニメの順序
}

-- コンストラクタ
function Enemy1Actor:ctor(...)
	Enemy1Actor.super.ctor(self, ...)
end

-- 初期化
function Enemy1Actor:init(cfg)
	-- 画像を指定
    self:init_image("enemy_leader", "chr1", 0,0, 20)
    -- 原点位置を設定
    self.spr:SetCenter(64,96)
	
	cfg.speed = cfg.speed or 2
	
	-- スーパークラス（ここではCharActorCommon)の初期化を実行
	Enemy1Actor.super.init(self,cfg)

	-- 各パラメータの初期化
	local p = self.params
	p.attack_wait_count_init = 25 --60                  -- 攻撃ウエイトカウンター初期値
	p.attack_wait_count = p.attack_wait_count_init -- 攻撃ウエイトカウンター
	p.chip_index_base = 8                          -- 画像チップベース番号
    p.is_enemy = true                              -- 敵方かどうか
	self.spr:SetChipIndex(p.chip_index_base)
end

-- 攻撃判定ルーチン
function Enemy1Actor:attack()
	local p = self.params
	-- 攻撃ウエイトが終わったら攻撃できる
	if p.attack_wait_count > 0 then
		p.attack_wait_count = p.attack_wait_count - 1
	end
	if p.attack_wait_count > 0 then
		return false
	end

    -- 指定距離以内の一番近い敵をターゲットする
	if not self:target_nearest_enemy(150) then
		return false
	end

	-- 攻撃発射
	local speed = 15
	local field = GS.scene.field
	-- ターゲットした敵の方向を取得する
	local mx, my = normalize_dir(p.target_pos[1]-p.x, p.target_pos[2]-p.y)
	-- 方向の値に速さを掛けて武器の速度（ベクトル）を得る
	mx = mx * speed
	my = my * speed
	
	-- 武器「刀」を飛ばす
	field:add_weapon(Katana, self, {
		dir = (mx >= 0) and "right" or "left", -- 右向きか、左向きか
		x = p.x, 	            -- 武器の初期座標(X)
		y = p.y,  	            -- 武器の初期座標(Y)
		mx = mx, 	            -- 武器の速度(X)
		my = my,	            -- 武器の速度(Y)
		collision_x_size = 60, 	-- 武器の衝突判定サイズ(X)
		collision_y_size = 80, 	-- 武器の衝突判定サイズ(Y)
		lifetime = 5,           -- 武器の寿命
		damage = 7,            -- 武器のダメージ
		chip_index_base = 4     -- 画像チップのベース番号    
		})

	-- 攻撃ウエイトカウンタを戻す
	p.attack_wait_count = p.attack_wait_count_init
	
	return true
end

-- Actor削除時に実行される
function Enemy1Actor:on_destroy()
	-- フィールドから削除
	self.cfg.field:remove_char(self)
end

------ 状態関数

-- 初期状態（すぐに待機状態へ移行）
function Enemy1Actor:state_start(rt)
	local p = self.params		
	if not self:is_alive() then
		return "goto", "state_dead"
	end
	return "goto", "state_stand"
end

-- 待機状態（すぐに徘徊状態へ移行）
function Enemy1Actor:state_stand(rt)
	local p = self.params		
	return "goto", "state_wander"
end

-- 徘徊状態
-- ややランダムに動き回る。敵を見つけたら攻撃する。
function Enemy1Actor:state_wander(rt)
	local p = self.params
	while true do
		-- ランダムな移動方向を得る
		local dx,dy = get_random_dir()
		p.mx = dx * p.speed;
		p.my = dy * p.speed;
		-- しばらく同じ方向に歩き続ける
		for i=0,30 do
			-- ダメージを受けたらダメージ状態へ移行
			if #(p.damages) > 0 then
				return "goto", "state_damage"
			end
			-- 敵を見つけたら移動状態へ移行
			if self:target_nearest_enemy(300) then
				return "goto", "state_move"
			end
			-- 歩行アニメーション設定
			if p.mx ~= 0 or p.my ~= 0 then
				local len = #self.walk_anim_seq
				p.chip_index_offset = self.walk_anim_seq[(i%len)+1]
			end
			local hit = self:base_motion()
			self:apply_pos()
			self:wait(1)
			-- 攻撃可能なら攻撃モードへ移行
			if self:attack() then
				return "goto", "state_attack"
			end
			if hit then
				break
			end
		end
	end
end

-- 移動状態
function Enemy1Actor:state_move(rt)
	local p = self.params
	local near_distance_pow2 = 60*60 -- 停止する距離（の２乗）
	local max_move_time = 60 -- 移動し続ける最大フレーム時間
	for i=1,max_move_time do
		if #(p.damages) > 0 then
			return "goto", "state_damage"
		end
		self:go_target_pos()
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
		
		-- 指定位置に近づいたらstand状態へ移行
		if self:get_target_pos_distance_pow2() < near_distance_pow2 then
			return "goto", "state_stand"
		end
	end
	-- 一定時間経過したらstand状態へ移行
	return "goto", "state_stand"
end

-- 「攻撃中」状態
-- 攻撃後一定時間固まる。
function Enemy1Actor:state_attack(rt)
	local p = self.params
	-- ５フレームの間停止して待つ
	for i=1,5 do
		p.chip_index_offset = 3
		-- ダメージを受けていたらダメージ状態へ移行
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
-- しばらくの間固まったまま暗転する
function Enemy1Actor:state_damage(rt)
	local p = self.params
	local damage = self:consume_damage_one()
	-- 20フレームの間色が暗くなる
	for i=1,20 do
		self.spr:SetColor(0.2,0.2,0.2)
		self:apply_pos()
		self:wait(1)
	end
	self.spr:SetColor(1.0,1.0,1.0)
	
	-- 死んでいたら死亡状態に移行
	if p.hp == 0 then
		return "goto", "state_dead"
	end
	-- 一定時間経ったらstand状態へ移行
	return "goto", "state_stand"
end

-- 「死んだ」状態
--Enemy1Actor.state_dead = dead_common_coroutine


