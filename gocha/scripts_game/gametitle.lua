--
-- GameTitle
--

-- タイトル画面実装
subclass("GameTitle", Actor) {
}

-- コンストラクタ
function GameTitle:ctor(...)
	print("GameTitle:ctor() called")
	GameTitle.super.ctor(self, ...)

    self.buttons = {} -- TitleMojiインスタンスの配列
end

-- ボタン(TitleMoji)１つを設定
function GameTitle:init_button(cfg, on_click_func)
	-- TitleMoji作成
	local button = TitleMoji:new()
	cfg.scene = self
	cfg.on_click = on_click_func -- クリック時のハンドラセット
	-- 初期化
	button:init(cfg)
	self:add_child(button) -- 画面表示上の親子関係を設定
	table.insert(self.buttons, button)
end

-- 初期化
function GameTitle:init(cfg)

	local center_x = GS.screen_w/2
	
	-- タイトル画面のGUI設定
	local gametitle_cfg = {
		titlelogo = {
			class = "TitleMoji",
			moji = "titlelogo",
			x = center_x,
			y = 100,
			scale = {1.0,1.0},
			chipindex = 0,
			chipspan = {8,2},
			center = {256,0},
			pre_move_wait = 0,
		},
		start = {
			class = "TitleMoji",
			moji = "start",
			x = center_x,
			y = 240+32,
			scale = {1.0,1.0},
			chipindex = 16,
			chipspan = {4,1},
			center = {128,0},
			pre_move_wait = 2,
		},
		--[[
		load = {
			class = "TitleMoji",
			moji = "load",
			x = center_x,
			y = 240+64,
			scale = {1.0,1.0},
			chipindex = 24,
			chipspan = {4,1},
			center = {128,0},
			pre_move_wait = 4,
		},
		]]
		exit = {
			class = "TitleMoji",
			moji = "exit",
			x = center_x,
			y = 240+64*2,
			scale = {1.0,1.0},
			chipindex = 32,
			chipspan = {4,1},
			center = {128,0},
			pre_move_wait = 6,
		},	
	}

	-- タイトル画面自体を設定
	self:init_null_sprite(0,0,0) -- 画面表示なし
    self.spr:Show(true)
	self.spr:SetScale(1.0,1.0)
    
    -- スーパークラス(Actor)のinitを呼ぶ
    Actor.init(self, cfg)

	-- 選択結果情報
	self.params.event = nil -- ボタンにより設定。"start" "load" のどれか
	self.params.event_sender = nil -- イベント送信者
	
	-- タイトルロゴ作成
	self:init_button(gametitle_cfg.titlelogo, nil)

	-- START文字作成
	self:init_button(gametitle_cfg.start, function(btn)
		self:set_event("click", "start")
	end)

--[[
	-- LOAD文字作成
	self:init_button(gametitle_cfg.load, function(btn)
		self:set_event("click", "load")
	end)
]]

	-- EXIT文字作成
	self:init_button(gametitle_cfg.exit, function(btn)
		-- EXITが押されたら即ゲーム終了
		cfunc.RequestQuit()
	end)
	
end

-- キーイベント処理
function GameTitle:on_keydown(key, is_ctrl, is_alt, is_shift)
	return false
end

-- マウスイベント処理
function GameTitle:on_mouse(evtype, button, x, y)
	for i,v in ipairs(self.buttons) do
		if v:on_mouse(evtype, button, x, y) == true then
			return true
		end
	end
	return false
end

-- イベントセット
function GameTitle:set_event(ev, moji)
	if self:get_state_name() == "state_frame" then
		self.params.event = ev
		self.params.event_sender = moji
	end
end


-- Actor削除時に実行される
function GameTitle:on_destroy()

end


-- 状態関数

function GameTitle:state_start(rt)
	return "goto", "state_frame"
end

-- 入力待ち状態
function GameTitle:state_frame(rt)
	local p = self.params
	while true do
		self:wait(1)
		-- マウスクリックイベントがきたらシーン移行状態の関数へ
		if p.event == "click" then
			if p.event_sender == "start" or p.event_sender == "load" then
				return "goto", "state_before_change_scene"
			end
		end
	end
end

-- 次のシーンへの移行前
function GameTitle:state_before_change_scene(rt)
	local p = self.params

	-- ボタンの状態を変更して、右のほうに移動して消す
	for i,btn in ipairs(self.buttons) do
		self:wait(3)
		btn:change_routine("state_post_show")
	end
	self:wait(30)
	
	-- イベントに応じて次のシーンへ移行
	if p.event_sender == "start" then
		-- ゲームシーン（ステージ１）を開始
		change_scene(GameScene, {stage = 1, stage_cfg = get_stage_cfg(1)})
	elseif p.event_sender == "load" then
		-- ロードシーンを開始
		--change_scene(GameLoader)
		--change_scene(GameTitle)
		change_scene(EndingScene)
	end
	return "exit"
end


-- タイトル文字実装
subclass("TitleMoji", Actor) {
}

-- コンストラクタ
function TitleMoji:ctor(...)
	print("TitleMoji:ctor() called")
	TitleMoji.super.ctor(self, ...)
	
end

-- 初期化
function TitleMoji:init(cfg)
	self:init_image(cfg.moji, "title", cfg.x, cfg.y)

	if cfg.scale ~= nil then
        self.spr:SetScale(unpack(cfg.scale))
	end
	if cfg.chipspan ~= nil then
        self.spr:SetChipSpan(unpack(cfg.chipspan))
	end
	if cfg.center ~= nil then
        self.spr:SetCenter(unpack(cfg.center))
	end
	if cfg.chipindex ~= nil then
        self.spr:SetChipIndex(cfg.chipindex)
	end
	if cfg.pos ~= nil then
		self.spr:MoveTo(cfg.x, cfg.y)
    end
	
	cfg.randomness = 3
	
    -- スーパークラスのinitを呼ぶ
    Actor.init(self, cfg)

	local p = self.params       
	p.x = self.cfg.x
	p.y = self.cfg.y
	p.is_clicked = false
end

-- マウスカーソルの内側判定用
function TitleMoji:is_inside(x, y)
	if x > -128 and x < 128 and y > 0 and y < 64 then
		return true
	end
	return false
end

-- マウスイベントハンドラ
function TitleMoji:on_mouse(evtype, button, x, y)
	-- 表示前の段階ならばマウスを処理しない
	if self:get_state_name() == "state_pre_show" 
		or self:get_state_name() == "state_post_show" then
		return false
	end
	local p = self.params
	-- ルート座標系からこのスプライトの座標系に変換
	-- （ただしこのスプライトの拡大縮小は計算に使わない）
	local lx, ly = self.spr:TranslateRootToThis(x,y,false) 
	if evtype == "down" then
		if self:is_inside(lx, ly) then
			p.is_clicked = true
			-- cfgのon_clickハンドラを呼ぶ
			if self.cfg.on_click ~= nil then
				self.cfg.on_click(self)
			end
			return true
		end
	elseif evtype == "move" then
		p.is_under_mouse = self:is_inside(lx, ly)
	end
	return false
end

-- Actor削除時に実行される
function TitleMoji:on_destroy()
end


-- 状態関数

function TitleMoji:state_start(rt)
	print("TitleMoji.funcs.init()")
	
	return "goto", "state_pre_show"
end

-- 左から移動して所定位置に来るまでの状態
function TitleMoji:state_pre_show(rt)
	local p = self.params       
	local step = 50
	local pre_move_length = 600
	self.spr:Show(false)
	-- 移動前のウエイト
	self:wait(self.cfg.pre_move_wait)
	self.spr:Show(true)
	-- 左のほうから設定位置まで移動
	for i=-pre_move_length,0,step do
		self.spr:MoveTo(p.x + i, p.y)
		self:wait(1)
	end
	return "goto", "state_frame"
end

-- アクティブ状態を設定
function TitleMoji:set_active(is_active)
	local p = self.params
	p.is_active = is_active
end

-- ボタンとして機能している状態
-- state_post_showに移行するには、外部からchange_routineを行う必要がある
function TitleMoji:state_frame(rt)
	local p = self.params     
	local cfg = self.cfg
	local count = 0
	local scale = 1.0
	local onoff = false
	while true do
		if cfg.moji ~= "titlelogo" then			
			if p.is_active or p.is_under_mouse then
				-- マウス下であれば「ぽよんぽよん」動く
				if not onoff then
					count = 0
					onoff = true
				end
				local ratio = math.sin(count/3.14159)
				scale = ratio * 0.3 + 1.5
			else
				-- マウスから外れていれば、元の大きさにゆっくり戻る
				onoff = false
				if scale < 0.95 then
					scale = scale + 0.05
				elseif scale > 1.05 then
					scale = scale - 0.05
				else
					scale = 1.0
				end
			end
			-- スケール設定
			self.spr:SetScale(scale * cfg.scale[1], scale * cfg.scale[2])
		end
		self.spr:MoveTo(p.x, p.y)
		self:wait(1)
		count = count + 1
	end
end

-- 右へ移動して消えるまでの状態
function TitleMoji:state_post_show(rt)
	local p = self.params       
	local step = 30
	local post_move_length = 600
	self.spr:Show(true)
	for i=0,post_move_length,step do
		local alpha = 1.0 - (i/post_move_length)*2
		if alpha < 0 then alpha = 0 end
		self.spr:MoveTo(p.x + i, p.y)
		self.spr:SetAlpha(alpha)
		self:wait(1)
	end
	self.spr:Show(false)
	return "exit" -- アクター自滅
end

