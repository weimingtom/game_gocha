--
--  GameScene
--

-- シーン実装
subclass("GameScene", Actor) {
}

-- コンストラクタ
function GameScene:ctor(...)
	print("GameScene:ctor() called")
	GameScene.super.ctor(self, ...)

    self.field = nil -- フィールドアクター
	self.scroller = nil -- フィールドをスクロールするスクロールバー
	self.buttons = {} -- ボタン各種の配列
	self.mode = "battle" -- 操作モード："battle"または"edit"
	self.cursor_mode = "cursor" -- カーソルのモード（通常の矢印"cursor"か行き先選択"flag"か）
	self.field_scroll_speed = 0 -- フィールドのスクロール量（フレームあたり）
	self.btn_scroll_l = nil -- スクロールボタン（右方向）
	self.btn_scroll_r = nil -- スクロールボタン（左方向）
	self.btn_mode = nil
	self.btn_attack = nil	-- 攻撃ボタン
	self.btn_defence = nil	-- 防御ボタン
	
	self.game_state = "play" -- ゲーム状態："play" "gameover" "stageclear"

end

-- 初期化
function GameScene:init(cfg)

	cfg.stage = cfg.stage or 1

	-- 画像のないスプライトとして設定
	self:init_null_sprite(0, 0, 0)
	self.spr:SetScale(GS.scene_scale, GS.scene_scale)

    -- スーパークラスのinitを呼ぶ
    GameScene.super.init(self, cfg)
	
	--スクロールバー作成
	local scroller = ScrollBar:new()
	scroller:init({x=300, y=480-60, scale=0.5})
	scroller:set_update_pos_func(function(pos)
		self.field:set_scroll_pos(pos)
	end)
	self:add_child(scroller) -- 画面表示上の親子関係を設定
	
	self.scroller = scroller
		
	--「タイトルに戻る」ボタン作成
	local btn = TextButton:new()
	btn:init({x=10, y=480-20, z=110, scale=0.75, text="タイトルに戻る", on_click=function(btn)
		change_scene(GameTitle)
	end})
	self:add_child(btn) -- 画面表示上の親子関係を設定
	table.insert(self.buttons, btn)
	

	--画面フレーム作成
	local frame = Actor:new()
	frame:init()
	frame:init_image("frame_up", "frame", 0, 0, 100)
	frame.spr:SetChipIndex(0)
	frame.spr:SetChipSpan(8,1)
	frame.spr:SetScale(640/512, 1.0)
	self:add_child(frame) -- 画面表示上の親子関係を設定
			
	--画面フレーム作成
	local frame_dn = Actor:new()
	frame_dn:init()
	frame_dn:init_image("frame_down", "frame", 0, 480-64,100)
	frame_dn.spr:SetScale(640/512, 1.0)
	frame_dn.spr:SetChipIndex(7 *8)
	frame_dn.spr:SetChipSpan(8,1)
	self:add_child(frame_dn) -- 画面表示上の親子関係を設定
	
	-- スクロールボタン
	-- cfgにはx,y,w,h,scale,xcenter,ycenterおよびon_click関数
	-- chip_button_up, chip_button_down, chip_mouse_over を指定可能。
	local btn_scroll_l = ImageButton:new()
	btn_scroll_l:init({
		x = 0,
		y = GS.screen_h * 0.4,
		z = 100,
		w = 64,
		h = 64,
		scale = 1.0,
		imagename = "frame",
		xcenter = 0,
		ycenter = 0,
		chip_button_up = 40,
		chip_button_down = 42,
		chip_mouse_over = 41,
		on_click = function()
			self.field_scroll_speed = -55
		end
	})
	self:add_child(btn_scroll_l) -- 画面表示上の親子関係を設定
	table.insert(self.buttons, btn_scroll_l)
	self.btn_scroll_l = btn_scroll_l
	
	
	local btn_scroll_r = ImageButton:new()
	btn_scroll_r:init({
		x = GS.screen_w - 64,
		y = GS.screen_h * 0.4,
		z = 100,
		w = 64,
		h = 64,
		scale = 1.0,
		imagename = "frame",
		xcenter = 0,
		ycenter = 0,
		chip_button_up = 43,
		chip_button_down = 45,
		chip_mouse_over = 44,
		on_click = function()
			self.field_scroll_speed = 55
		end
	})
	self:add_child(btn_scroll_r) -- 画面表示上の親子関係を設定
	table.insert(self.buttons, btn_scroll_r)
	self.btn_scroll_r = btn_scroll_r

	-- モード表示
	local btn_mode = TextButton:new()
	btn_mode:init({x=120, y=GS.screen_h-20, z=110, scale=0.75, text="モード：＊＊＊", 
		on_click = function(btn)
			if self.mode == "battle" then
				self:set_mode("edit")
			else
				self:set_mode("battle")
			end
			-- カーソルのモードを戻す
			self.cursor_mode = "cursor"
			GS.cursor:set_mode("cursor")
		end})
	self:add_child(btn_mode) -- 画面表示上の親子関係を設定
	table.insert(self.buttons, btn_mode)
	self.btn_mode = btn_mode
	self:update_mode_string()

	--フィールド作成
	local field = GameField:new()
	self.field = field
	field:init({scene = self, stage_cfg = cfg.stage_cfg})
	self:add_child(field) -- 画面表示上の親子関係を設定

	-- 攻撃指示ボタン
	local btn_attack = ImageButton:new()
	btn_attack:init({
		x = 16,
		y = GS.screen_h - 96,
		z = 100,
		w = 64,
		h = 64,
		scale = 1.0,
		imagename = "frame",
		xcenter = 0,
		ycenter = 0,
		chip_button_up = 32,
		chip_button_down = 34,
		chip_mouse_over = 33,
		on_click = function()
			self.field:set_command_for_selected_char("attack")
		end
	})
	self:add_child(btn_attack) -- 画面表示上の親子関係を設定
	table.insert(self.buttons, btn_attack)
	self.btn_attack = btn_attack
	
	-- 防御指示ボタン
	local btn_defence = ImageButton:new()
	btn_defence:init({
		x = 16 + 64,
		y = GS.screen_h - 96,
		z = 100,
		w = 64,
		h = 64,
		scale = 1.0,
		imagename = "frame",
		xcenter = 0,
		ycenter = 0,
		chip_button_up = 35,
		chip_button_down = 37,
		chip_mouse_over = 36,
		on_click = function()
			self.field:set_command_for_selected_char("defence")
		end
	})
	self:add_child(btn_defence) -- 画面表示上の親子関係を設定
	table.insert(self.buttons, btn_defence)
	self.btn_defence = btn_defence
	

	-- 衝突判定追加（地形）
	GS.collision_ground:clear()
	self.field:add_ground_collisions(GS.collision_ground)

end

-- モード文字列を更新
function GameScene:update_mode_string()
	if self.mode == "battle" then
		self.btn_mode.spr:SetText("モード：バトル")
	else
		self.btn_mode.spr:SetText("モード：追加　")
	end
end

-- キー押下げハンドラ
function GameScene:on_keyevent(key, is_down, is_ctrl, is_alt, is_shift)
	-- TABを押したらモード切替え
	if key == SDLK_TAB and is_down then
		if self.mode == "battle" then
			self:set_mode("edit")
		else
			self:set_mode("battle")
		end
		return true
	end
	return false
end

-- マウスハンドラ
function GameScene:on_mouse(evtype, button, x, y)
	-- ゲームクリア時の文字アクターにイベントを渡す
	if self.gameclearmoji ~= nil then
		if self.gameclearmoji:on_mouse(evtype, button, x, y) then
			return true
		end
	end
	-- スクロールバーにイベントを渡す
	if self.scroller:on_mouse(evtype, button, x,y) then
		return true
	end
	-- 各ボタンにイベントを渡す
	for i,v in ipairs(self.buttons) do
		if v:on_mouse(evtype, button, x, y) == true then
			return true
		end
	end

	if evtype == "down" then
		-- マウスクリック時の動作
		local lx,ly = self.field.spr:TranslateRootToThis(x,y)
		if self.mode == "battle" then
			if button == 1 then
				-- 左クリック
				-- カーソルモードならキャラを選択
				if self.cursor_mode == "cursor" or self.cursor_mode == "flag"  then
					if self.field:select_char_on_pos(lx,ly) then
						-- キャラ選択成功→行き先選択モードに移行
						self.cursor_mode = "flag"
						GS.cursor:set_mode("flag")
						return true
					else
						-- キャラ選択失敗→カーソルモードに戻る
						self.cursor_mode = "cursor"
						GS.cursor:set_mode("cursor")
						self.field:clear_char_selection()
						return true
					end
				end
				
			elseif button == 3 then
				if self.cursor_mode == "flag" then
					-- 右クリックで行き先を指示
					self.field:set_target_pos_for_selected_chars(lx,ly)
					
					-- 指定ポイントが画面端のほうならちょっとスクロールさせる
					local x1,x2 = self.field:get_scroll_window_pos()
					print(string.format("lx=%3d ly=%3d x1=%3d x2=%3d", lx, ly, x1, x2))
					if lx < x1 + 100 then
						if self.field_scroll_speed == 0 then
							self.field_scroll_speed = -30
						end
					end
					if lx > x2 - 100 then
						if self.field_scroll_speed == 0 then
							self.field_scroll_speed = 30
						end
					end
					return true
				end
			else
			end
		elseif self.mode == "edit" then
			if ly >= 60 and ly <= GS.screen_h-100 then
				if button == 1 then
					-- 50%の確率で侍か巫女を配置
					local leader_type = (math.random()<0.5) and "miko" or "samurai"
					self.field:add_leader(LeaderActor, 
						{type = leader_type, x = lx, y = ly})
					self.field:stop_all_chars()
					return true
				end
				if button == 3 then
					self.field:add_enemy(Enemy1Actor, {x = lx, y = ly})
					self.field:stop_all_chars()
					--return true
				end
			end
		end
	end
	return false
end

function GameScene:pre_schedule()
	GS.collision:clear()
	
	-- 衝突判定追加（キャラ）
	self.field:add_collisions(GS.collision)
end

-- 指定可能なモードのリスト
local available_modes = {["edit"]=true, ["battle"]=true}

-- 現在の操作モードをセット
-- モードが正しくなければfalseを返す
function GameScene:set_mode(mode)
	if available_modes[mode] == nil then
		print("GameScene:set_mode() : bad mode :", mode)
		return false
	end
	self.mode = mode
	self:update_mode_string()
	if self.mode == "battle" then
		self.field:restart_all_chars()
	else
		self.field:stop_all_chars()
	end
	return true
end

-- 現在の操作モードを取得
function GameScene:get_mode()
	return self.mode
end

-- Actor削除時に実行される
function GameScene:on_destroy()
end

-- 状態関数

-- 初期状態
function GameScene:state_start(rt)
	print("GameScene.funcs.init()")
	return "goto", "state_frame"
end

-- 通常状態
function GameScene:state_frame(rt)

	local gamestartmoji = GameClearMoji:new()
	gamestartmoji:init({on_end_func = nil, moji="ステージ"..self.cfg.stage.."スタート！", wait_frame = 120, scale = {3.0, 4.0}, center = {16*4.5, 8}})
	self:add_child(gamestartmoji)

	while true do
		-- フィールドのスクロール制御を行う
		if self.field_scroll_speed ~= 0 then
			self.field:scroll(self.field_scroll_speed)
			
			-- スクロールスピードをだんだん下げて止める
			local is_plus = self.field_scroll_speed > 0
			if is_plus then
				self.field_scroll_speed = self.field_scroll_speed - 5
			else
				self.field_scroll_speed = self.field_scroll_speed + 5
			end
			local is_plus2 = self.field_scroll_speed > 0
			if is_plus ~= is_plus2 then
				self.field_scroll_speed = 0
			end
		end
		
		self:wait(1)
		
		if self.game_state == "play" then
			-- 味方がいない　→　ゲームオーバー
			if self.field:get_ally_char_count() == 0 then
				-- ゲームオーバーの文字を出す
				self.game_state = "gameover"
				self.gameclearmoji = GameClearMoji:new()
				local func = function()
					self:finish_stage()
				end
				self.gameclearmoji:init({on_end_func = func, moji="ゲームオーバー", wait_frame = 3600, scale = {5.0, 8.0}, center = {16*3.5, 8}})
				self:add_child(self.gameclearmoji) -- 画面表示上の親子関係を設定
			-- 敵がいない　→　ステージクリア
			elseif self.field:get_enemy_char_count() == 0 then
				-- ステージクリアの文字を出す
				self.game_state = "stageclear"
				self.gameclearmoji = GameClearMoji:new()
				local func = function()
					self:finish_stage()
				end
				self.gameclearmoji:init({on_end_func = func, moji="ステージ"..self.cfg.stage.."クリア！", wait_frame = 3600, scale = {4.0, 8.0}, center = {16*4, 8}})
				self:add_child(self.gameclearmoji) -- 画面表示上の親子関係を設定
			end
		elseif self.game_state == "stageclear_finish" then
			-- ステージクリア文字表示後の処理
			local next_stage = self.cfg.stage+1
			if get_stage_cfg(next_stage) == true then
				-- 全ステージクリアならばエンディングへ
				change_scene(EndingScene)
			else
				-- 次のステージへ
				change_scene(GameScene, {stage = next_stage, stage_cfg = get_stage_cfg(next_stage)})
			end
		elseif self.game_state == "gameover_finish" then
			-- ゲームオーバー文字表示後の処理
			change_scene(GameTitle)
		end
	end
end

-- ステージを終了させる指示を行う
function GameScene:finish_stage()
	GS.cursor:set_mode("cursor")
	if self.game_state == "gameover" then
		self.game_state = "gameover_finish"
	elseif self.game_state == "stageclear" then
		self.game_state = "stageclear_finish"
	else
		error("GameScene:finish_stage() invalid state to finish:"..tostring(self.game_state))
	end
end


-- GAME OVER/STAGE CLEAR 文字実装
subclass("GameClearMoji", Actor) {
}

-- コンストラクタ
function GameClearMoji:ctor(...)
	print("GameClearMoji:ctor() called")
	GameClearMoji.super.ctor(self, ...)
end

-- 初期化
-- cfg.start_wait : 文字を表示し始めるまでの時間
-- cfg.scene : シーンオブジェクト
-- cfg.wait_frame : クリック待ちフレーム数
function GameClearMoji:init(cfg)
	cfg.x = cfg.x or GS.screen_w/2
	cfg.y = cfg.y or GS.screen_h/2
	self:init_text("game_clear_moji", cfg.moji, nil, cfg.x, cfg.y, 1000)
	if cfg.scale ~= nil then
        self.spr:SetScale(unpack(cfg.scale))
	end
	if cfg.center ~= nil then
        self.spr:SetCenter(unpack(cfg.center))
	end
    -- スーパークラスのinitを呼ぶ
    Actor.init(self, cfg)
	local p = self.params       
	p.x = cfg.x
	p.y = cfg.y
	p.is_clicked = false
end

-- マウスイベントハンドラ
function GameClearMoji:on_mouse(evtype, button, x, y)
	if evtype == "down" and button == 1 then
		local p = self.params
		p.is_clicked = true
		return true
	end
	return false
end

-- Actor削除時に実行される
function GameClearMoji:on_destroy()
end

-- 状態関数
function GameClearMoji:state_start(rt)
	print("GameClearMoji.funcs.init()")	
	return "goto", "state_pre_show"
end

-- 上から移動して所定位置に来るまでの状態
function GameClearMoji:state_pre_show(rt)
	local p = self.params       
	local step = 15
	local pre_move_length = 300
	-- 上のほうから設定位置まで移動
	for i=-pre_move_length,0,step do
		self.spr:MoveTo(p.x, p.y + i)
		self:wait(1)
	end
	return "goto", "state_frame"
end

-- 文字の移動
function GameClearMoji:state_frame(rt)
	local p = self.params
	self.spr:Show(true)
	local alpha = 0
	p.diff_y = 0

	for i=0,self.cfg.wait_frame do
		p.diff_y = math.sin(3.14159 * 2 * (i / 60)) * 20 -- 秒間１振動
		self.spr:MoveTo(p.x, p.y + p.diff_y)
		self:wait(1)
		if p.is_clicked then
			return "goto", "state_post_show"
		end
	end
	return "goto", "state_post_show"
end

-- 下へ移動して消えるまでの状態
function GameClearMoji:state_post_show(rt)
	local p = self.params       
	local cfg = self.cfg       
	local step = 15
	local post_move_length = 600
	self.spr:Show(true)
	for i=0,post_move_length,step do
		local alpha = 1.0 - (i/post_move_length)*2
		if alpha < 0 then alpha = 0 end
		self.spr:MoveTo(p.x, p.y + p.diff_y + i)
		self.spr:SetAlpha(alpha)
		self:wait(1)
	end
	self.spr:Show(false)
	if cfg.on_end_func ~= nil then
		cfg.on_end_func()
	end
	return "exit" -- アクター自滅
end
