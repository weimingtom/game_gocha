

subclass("Obstacle", Actor) {
}

-- コンストラクタ
function Obstacle:ctor(...)
	print("Obstacle:ctor() called")
	Obstacle.super.ctor(self, ...)

end

function Obstacle:init(imagename, cfg)
	local p = self.params
	p.x = cfg.x
	p.y = cfg.y
	self:init_image("obstacle", imagename, p.x, p.y, 100 + p.y)
	self.spr:SetScale(cfg.scale, cfg.scale)
    --self.spr:MoveTo(p.x, p.y)

    -- スーパークラスのinitを呼ぶ
	Actor.init(self, cfg)
end

function Obstacle:get_collision_rect()
	return 
		self.cfg.x, 			-- x_center
		self.cfg.y, 			-- y_center
		self.cfg.collision_size_x, 	-- x_size  
		self.cfg.collision_size_y 	-- y_size  
	
end


--
--  GameField
--

subclass("GameField", Actor) {
}

-- コンストラクタ
function GameField:ctor(...)
	print("GameField:ctor() called")
	GameField.super.ctor(self, ...)

	
    self.weapons = {}
    self.char_actors = {} -- Actorクラスの配列
    self.ground_actors = {} -- Actorクラスの配列
    self.obstacles = {} -- Obstacleクラスの配列
    self.width = 640*4
	
	self.hilighted_chars = {} -- ハイライト対象になっているキャラの配列
	self.selected_chr = nil -- 現在選択中のキャラ
end

local tinsert = table.insert

function GameField:init(cfg)
    self:init_null_sprite(0, 0, 1)
	self.spr:SetScale(1.0,1.0)
    
    -- スーパークラスのinitを呼ぶ
    Actor.init(self, cfg)

	self.params = {
		x = 0,
		y =	0,
		mx = -1,
		my = 0,
		speed = 1,
	}
	local p = self.params

	print("GameField init1 : GS.scheduler.actors count = ", #(GS.scheduler.actors));

	-- ステージデータ雛形作りかけ
	local stagedata = {
		chars = {},
		enemies = {},
		map_tile = {},
		obstacles = {},
	}
	
	-- フィールド上のキャラクター作成
	local stage_cfg = self.cfg.stage_cfg
	for i=1,stage_cfg.miko_count do
		self:add_leader(LeaderActor, 
			{type = "miko", x = math.random(50,GS.screen_w-50), y = math.random(100,GS.screen_h-100)})
	end
	for i=1,stage_cfg.samurai_count do
		self:add_leader(LeaderActor, 
			{type = "samurai", x = math.random(50,GS.screen_w-50), y = math.random(100,GS.screen_h-100)})
	end
	
	-- フィールド上の敵キャラクター作成
	for i,enemy_data in ipairs(stage_cfg.enemies) do
		local class = _G[enemy_data.class]
		for i=1,enemy_data.count do
			self:add_enemy(class, 
				{x = math.random(GS.screen_w*1.5,GS.field_w), y = math.random(100,GS.screen_h-100)})
		end
	end
	
	-- 地面作成
	self:create_ground(stage_cfg.ground_ratio)	
	
	-- 障害物作成
	local obstacle_data = {}
	
	-- 存在する障害物タイプ
	local obstacle_types = {["rock1"]=true, ["rock2"]=true, ["tree"]=true}
	
	-- ステージデータにしたがって障害物データ作成
	for i,obs in ipairs(stage_cfg.obstacles) do
		for i=0, obs.count do
			local x = math.random(0, self.width) - 100
			local y = math.random(100, GS.screen_h-100)
			local scale = 1.0 + math.random() * 0.5
			local type = obs.type
			-- 障害物タイプチェック
			if obstacle_types[type] ~= true then
				error("invalid obstacle type :"..tostring(type))
			end
			local obstacle_cfg = {
				x=x,
				y=y,
				scale = scale,
				type = type
			}
			table.insert(obstacle_data, obstacle_cfg)
		end
	end
	for i,cfg in ipairs(obstacle_data) do
		if cfg.type == "rock1" or cfg.type == "rock2" then
			-- 岩を配置
			local obs = Obstacle:new()
			local size = 128
			obs:init("object",{
				x=cfg.x,
				y=cfg.y,
				collision_size_x = size * cfg.scale * 0.6,
				collision_size_y = size * cfg.scale * 0.4,
				scale = cfg.scale,
			})
			obs.spr:SetChipIndex((cfg.type == "rock1") and 0 or 1)
			self:add_child(obs) -- 画面表示上の親子関係を設定
			local basex = 64
			local basey = 80
			obs.spr:SetCenter(basex,basey)
			table.insert(self.obstacles, obs)
		elseif cfg.type == "tree" then
			-- 木を配置
			local obs = Obstacle:new()
			local size = 128
			obs:init("object",{
				x=cfg.x,
				y=cfg.y,
				collision_size_x = size * cfg.scale * 0.6,
				collision_size_y = size * cfg.scale * 0.4,
				scale = cfg.scale,
			})
			obs.spr:SetChipIndex(2)
			obs.spr:SetChipSpan(1,2)
			self:add_child(obs) -- 画面表示上の親子関係を設定
			local basex = 64
			local basey = 128+96
			obs.spr:SetCenter(basex,basey)
			table.insert(self.obstacles, obs)
		end
	end
	
	
end

-- 地面作成
-- グラデーションが自然になるよう自動処理でチップを置いていく。
function GameField:create_ground( ground_ratio )
	local PLAIN, GRASS, WATER = 0, 1, 2

	-- ランダム地形作成
	-- 周囲１セル分余計にデータを作っておく
	local ground_data = {}
	local ground_chip_size = 128
	for y=1,math.ceil(480/ground_chip_size)+2 do
		local line_data = {}
		table.insert(ground_data, line_data)
		for x=1,math.ceil((self.width)/ground_chip_size)+2 do
			local rand100 = math.random(0,100)
			local map_cell = PLAIN
			
			-- 地面構成比の比率で作成
			for i=0,#ground_ratio-1 do
				if rand100 < ground_ratio[i+1] then
					map_cell = i
					break
				end
				rand100 = rand100 - ground_ratio[i+1]
			end
			
			table.insert(line_data, map_cell)
		end
	end
	
	-- 地面アクター設定

	-- 地面の移り変わりのチップを設定する
	local U,D,R,L,UR,UL,DR,DL,CENTER = 1,2,3,4,5,6,7,8,9
	
	-- マップのベースチップ番号
	local map_chip_indexes = {
		[PLAIN] = 3,
		[GRASS] = 5,
		[WATER] = 12,
	}
	
	-- 草のグラデーションの方向と処理用チップ番号の組み合わせ
	local corner_chips = {
		[UR] = 8,
		[UL] = 10,
		[DR] = 0,
		[DL] = 2,
	}
	
	-- x,yで回したときのcellインデックスの順番
	local cells_order = {
		UL,U,UR,L,CENTER,R,DL,D,DR
	}

	-- 指定方向に草が存在したら斜め隣接判定をOFFにするリスト
	local off_list = {
		[U] = {UR,UL},
		[D] = {DR,DL},
		[R] = {UR,DR},
		[L] = {UL,DL},
	}
	
	-- 草グラデーションのチップ番号と対応するグラデーション方向のデータ
	-- 上から順に適用していく。
	local grad_chip_data = {
		{{U,D,L,R}, 5},
		{{U,L}, 7},
		{{U,R}, 11},
		{{D,L}, 15},
		{{D,R}, 14},
		{{U}, 9},
		{{D}, 1},
		{{R}, 4},
		{{L}, 6},
	}

	-- 現在ターゲットにしているセルの周辺状況を一時記録するテーブル
	-- キーは UL,U,UR,L,CENTER,R,DL,D,DR のどれか(1～9)
	local cells = {}


	-- 周囲にある草のカウント
	local function get_adjacent4_count(map_type)
		local count = 0
		for i=1,4 do
			if cells[i] == map_type then
				count = count + 1
			end
		end
		return count
	end
	
	-- 地形データからターゲットセル周辺の状況をcellsテーブルにコピー
	local function load_cells_from_ground(ground_data, cx, cy)
		local index = 1
		for y = -1,1 do
			for x = -1,1 do
				cells[cells_order[index]] = ground_data[cy+y][cx+x]
				index = index + 1
			end
		end
	end
	
	local gradation_targets = {
		{ GRASS, "grass", 1 },
		{ WATER, "water", 100 },
	}
	
	-- 各方向の地形切り替わり用チップを処理
	for x=1,math.ceil((self.width)/ground_chip_size) do
		for y=1,math.ceil(480/ground_chip_size) do
			local cx,cy = x+1,y+1
			
			local map_cell = ground_data[cy][cx]
			local chip_index = map_chip_indexes[map_cell]

			-- この場所のベースのスプライト(Actor)作成
			local actor = Actor:new()
			actor:init()
			actor:init_image("gnd", "ground", (x-1)*ground_chip_size,(y-1)*ground_chip_size, 0)
			actor.spr:SetChipIndex(chip_index)
			self:add_child(actor) -- 画面表示上の親子関係を設定
			table.insert(self.ground_actors, actor)

			for ix,v in ipairs(gradation_targets) do

				-- 現在セルの周辺状況をcellsテーブルに反映
				load_cells_from_ground(ground_data, cx,cy)
			
				local target_maptype, target_image, target_baseheight = unpack(v)
				local grass_count = get_adjacent4_count(target_maptype) --４方向に隣接する草の数

				if map_cell < target_maptype then
					
					-- 横に草のある方向の隣にあたる斜めのグラデーション処理をOFFにする
					for i=1,4 do
						if cells[i] == target_maptype then
							for j,v in ipairs(off_list[i]) do
								cells[v] = 0
							end
						end
					end
				
					-- 草境界のグラデーションのチップを配置
					local add_chips = {}
					
					for i,data in ipairs(grad_chip_data) do
						local target, chip = unpack(data)
						-- 方向の要件をすべて満たしていたらチップを追加。
						-- チップを適用した方向の草はchips内ではOFFにしておく。
						local is_grass_exist = true
						for j,dir in ipairs(target) do
							if cells[dir] ~= target_maptype then
								is_grass_exist = false
								break
							end
						end
						-- 条件に合致
						if is_grass_exist then
							-- チップを追加、対応する方向の草情報をOFFにする
							tinsert(add_chips, chip)
							for j,dir in ipairs(target) do
								cells[dir] = 0
							end
						end
						-- 対処すべき草がもうなければ終了
						grass_count = get_adjacent4_count(target_maptype) 
						if grass_count == 0 then
							break
						end
					end
					
					-- 斜めの草を処理
					for dir,chip in pairs(corner_chips) do
						if cells[dir] == target_maptype then
							tinsert(add_chips, chip)
						end
					end
					
					-- 草グラデーション処理チップを追加
					for i,chip in ipairs(add_chips) do
						local actor = Actor:new()
						actor:init()
						actor:init_image("map_grad", target_image, (x-1)*ground_chip_size,(y-1)*ground_chip_size, target_baseheight+i)
						actor.spr:SetChipIndex(chip)
						self:add_child(actor) -- 画面表示上の親子関係を設定
						table.insert(self.ground_actors, actor)
					end
				end
			end

		end
	end
end

function GameField:on_reload()
    self:change_routine("frame")
end

-- 画面をスクロールさせる
-- ドット数で指定。プラスならフィールド全体が左にスクロール
function GameField:scroll(dx)
	local p = self.params
	p.x = p.x - dx
	local x_min = -(GS.field_w - GS.screen_w)
	if p.x <= x_min then
		p.x = x_min
	end
	if p.x > 0 then
		p.x = 0
	end
end

-- 衝突判定追加（地形）
function GameField:add_ground_collisions(collision)
	for i,v in ipairs(self.obstacles) do
		if GS.use_c_collision then
			collision:add_object(v.id, v:get_collision_rect() )
		else
			collision:add_object(v, v:get_collision_rect() )
		end
	end
end

-- 衝突判定追加（キャラ）
function GameField:add_collisions(collision)
	for i,v in ipairs(self.char_actors) do
		if GS.use_c_collision then
			collision:add_object(v.id, v:get_collision_rect() )
		else
			collision:add_object(v, v:get_collision_rect() )
		end
	end
end

-- 指定位置付近のリーダーキャラを選択する
function GameField:select_char_on_pos(x,y)
	local near_actors_count = GS.collision:search_collided_objects(x,y,50,80)

	local nearest_distance = nil -- 最も近いアクターまでの距離
	local nearest_actor = nil   -- 最も近いアクター
	--for i,act in ipairs(near_actors) do
	for i = 0,near_actors_count-1 do
		local act = get_result_actor(i, GS.collision)
		if act.classname == "LeaderActor" then
			local distance = act:pos_distance_pow2_to(x,y)
			if nearest_distance == nil or distance < nearest_distance then
				nearest_distance = distance
				nearest_actor = act
			end
		end
	end
	-- 一番近いアクター（があれば）選択キャラとする
	if nearest_actor == nil then
	    return false
	end
	self:select_char(nearest_actor)
	return true
end

-- 指定キャラを選択する
function GameField:select_char(actor)
	if actor.classname == "LeaderActor" then
		if self.selected_chr ~= nil then
			self.selected_chr:hilight_team(false)
		end
		actor:hilight_team(true)
		self.selected_chr = actor
	end
end

-- キャラ選択解除
function GameField:clear_char_selection()
	if self.selected_chr ~= nil then
		self.selected_chr:hilight_team(false)
		self.selected_chr = nil
	end
end

-- 選択キャラに移動先を指定
function GameField:set_target_pos_for_selected_chars(lx,ly)
	if self.selected_chr ~= nil then
		self.selected_chr:set_user_target_pos(lx,ly)
	end
	-- 指定座標が画面のやや中にくるようスクロール
	print("set_user_target_pos")
end

-- 選択キャラにコマンドを指定
function GameField:set_command_for_selected_char(command)
	if self.selected_chr ~= nil then
		self.selected_chr:set_command(command)
	end
end

-- 全キャラを停止
function GameField:stop_all_chars()
	for i,act in ipairs(self.char_actors) do
		act:change_routine("state_edit")
	end
end

-- 全キャラを再スタート
function GameField:restart_all_chars()
	for i,act in ipairs(self.char_actors) do
		act:change_routine("state_start")
	end
end
						
-- スクロール値を設定
function GameField:set_scroll_pos(pos)
	local p = self.params
	p.x = - pos * GS.field_w
end

-- スクロールウィンドウの範囲を取得
-- return 左端座標、右端座標
function GameField:get_scroll_window_pos()
	local p = self.params
	return -p.x, (-p.x + GS.screen_w)
end


-- 武器を発射
-- typeは"arrow" "sword"
-- cfgパラメータにはx,y,x_target, y_target, speedを含むテーブルを指定する。
function GameField:add_weapon(class, actor, cfg)
	local p = self.params
	local weapon = class:new()
	cfg.src_actor = actor
	cfg.field = self
	weapon:init(cfg)
	self:add_child(weapon) -- 画面表示上の親子関係を設定
	
	self.weapons[weapon] = true
end

-- キャラを追加
function GameField:add_leader(class, cfg)
	local actor = class:new()
	cfg.field = self
	actor:init(cfg)
	self:add_child(actor) -- 画面表示上の親子関係を設定
	table.insert(self.char_actors, actor)
end

-- 敵を追加
function GameField:add_enemy(class, cfg)
	local actor = class:new()
	cfg.field = self
	actor:init(cfg)
	self:add_child(actor) -- 画面表示上の親子関係を設定
	table.insert(self.char_actors, actor)
end

-- キャラアクターをフィールドから削除
function GameField:remove_char(actor)
    remove_value_from_array(self.char_actors, actor)
    remove_value_from_array(self.hilighted_chars, actor)
    return false
end


function GameField:remove_weapon(weapon)
	self.weapons[weapon] = nil
end

-- 味方キャラの数
function GameField:get_ally_char_count()
	local count = 0
	for i,act in ipairs(self.char_actors) do
		if not act:is_enemy() then
			count = count + 1
		end
	end
	return count
end

-- 敵キャラの数
function GameField:get_enemy_char_count()
	local count = 0
	for i,act in ipairs(self.char_actors) do
		if act:is_enemy() then
			count = count + 1
		end
	end
	return count
end

-- Actor削除時に実行される
function GameField:on_destroy()
end

------ 状態関数

function GameField:state_start(rt)
	print("GameField init2 : GS.scheduler.actors count = ", #(GS.scheduler.actors));
	
	return "goto", "state_frame"
end

function GameField:state_frame(rt)
	local p = self.params
	-- フィールドの左右の動きを制御する
	while true do
		self.spr:MoveTo(p.x, p.y)
		self.cfg.scene.scroller:set_pos(-p.x/GS.field_w)
		self:wait(1)
	end
end





-- スクロールバー実装（フィールド用）
subclass("ScrollBar", Actor) {
}

-- コンストラクタ
function ScrollBar:ctor(...)
	print("ScrollBar:ctor() called")
	ScrollBar.super.ctor(self, ...)


	self.thumb = nil -- スクロールのつまみ用アクター
	self.is_dragging = false -- つまみをドラッグ中かどうか
	self.drag_start_thumb_local_x = nil -- ドラッグ開始時につまみのどこを掴んでいたか
	self.pos = 0
	self.max_value = 1.0
end


function ScrollBar:init(cfg)
	self:init_image("scrollbar", "frame", cfg.x, cfg.y, 1000)
	self.spr:MoveTo(cfg.x, cfg.y)
	self.spr:SetScale(1.0*cfg.scale,1.0*cfg.scale)
	self.spr:SetChipIndex(1 *8)
	self.spr:SetChipSpan(8,1)
	local p = self.params
	p.x = cfg.x
	p.y = cfg.y

	-- スーパークラスのinitを呼ぶ
	Actor.init(self, cfg)

	-- フィールド全体サイズを1.0としたときのスクロール最大値を計算
	local thumb_width_ratio = GS.screen_w / GS.field_w
	self.max_value = 1.0 - thumb_width_ratio

	-- スクロールのつまみ
	local thumb = Actor:new()
	thumb:init()
	thumb:init_image("thumb", "frame", 0, 0,0)
	thumb.spr:SetScale(thumb_width_ratio, 1.0)
	thumb.spr:SetChipIndex(2 *8)
	thumb.spr:SetChipSpan(8,1)
	self:add_child(thumb) -- 画面表示上の親子関係を設定

	self.thumb = thumb

end

-- 更新した値を受け取るハンドラ関数を登録
-- func は function(pos) の形。
function ScrollBar:set_update_pos_func(func)
	self.on_update_pos_func = func
end

function ScrollBar:set_pos(pos)
	pos = (pos<0) and 0 or pos
	pos = (pos>self.max_value) and self.max_value or pos
	self.pos = pos
	self:apply_thumb_pos()
end


-- つまみ位置を正しい場所に動かす
function ScrollBar:apply_thumb_pos()
	self.thumb.spr:MoveTo(self.pos * 512,0)
end

function ScrollBar:is_inside(x, y)
	if x > 0 and x < 512 and y > 0 and y < 64 then
		return true
	end
	return false
end

local function thumb_is_inside(x, y)
	if x > 0 and x < 512 and y > 0 and y < 64 then
		return true
	end
	return false
end


function ScrollBar:on_mouse(evtype, button, x, y)
	local lx, ly = self.spr:TranslateRootToThis(x,y)
	local tx, ty = self.thumb.spr:TranslateRootToThis(x,y)
	if evtype == "down" then
		-- ドラッグ開始判定
		if thumb_is_inside(tx, ty) then
			--self.cfg.scene:set_event("click", self.cfg.moji)
			self.is_dragging = true
			self.drag_start_thumb_local_x = tx
			return true
		end
		if self:is_inside(lx, ly) then
			-- つまみ以外の部分をクリック
			-- スクロール値を求める
			local pos = (lx - 64) / 512
			pos = (pos<0) and 0 or pos
			pos = (pos>self.max_value) and self.max_value or pos
			self.pos = pos
			self:apply_thumb_pos()
			--print("pos=", pos)
			if self.on_update_pos_func ~= nil then
				self.on_update_pos_func(self.pos)
			end
			return true
		end
	elseif evtype == "up" then
		if self.is_dragging then
			self.is_dragging = false
		end
	elseif evtype == "move" then
		--if not thumb_is_inside(lx, ly) then
		--	self.is_dragging = false
		--end
		if self.is_dragging then
			-- つまみの座標をつかんだ位置から逆算する
			local x1,y1 = self.thumb.spr:TranslateThisToParent(self.drag_start_thumb_local_x, 0)
			local x2,y2 = self.thumb.spr:TranslateThisToParent(0, 0)
			local dx = x1-x2
			-- スクロール値を求める
			local pos = (lx-dx) / 512
			pos = (pos<0) and 0 or pos
			pos = (pos>self.max_value) and self.max_value or pos
			self.pos = pos
			self:apply_thumb_pos()
			--print("pos=", pos)
			if self.on_update_pos_func ~= nil then
				self.on_update_pos_func(self.pos)
			end
		end
		--local p = self.params
		--p.is_under_mouse = self:is_inside(lx, ly)
	end
	return false
end

-- Actor削除時に実行される
function ScrollBar:on_destroy()
end

------ 状態関数

function ScrollBar:state_start(rt)
	print("TitleMoji.funcs.init()")
	local p = self.params       
	
	return "goto", "state_frame"
end

function ScrollBar:state_frame(rt)
	local p = self.params       
	while true do
		self.spr:MoveTo(p.x, p.y)
		self:wait(1)
	end
end


