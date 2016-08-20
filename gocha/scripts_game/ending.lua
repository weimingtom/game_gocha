--
-- EndingScene
--

--[[

文字をいくつか配置?スクロールさせて終わり。

Congraturations!

企画：Makoto Hamanaka

プログラム：Makoto Hamanaka

グラフィック：LEEX

fin.

]]


-- タイトル画面実装
subclass("EndingScene", Actor) {
}

-- コンストラクタ
function EndingScene:ctor(...)
	print("EndingScene:ctor() called")
	EndingScene.super.ctor(self, ...)
end

-- 文字１つを設定
function EndingScene:add_text(text, pre_move_wait)
	local moji = EndingMoji:new()
	local cfg = {}
	cfg.scene = self
	cfg.moji = text
	cfg.pre_move_wait = pre_move_wait
	-- 初期化
	moji:init(cfg)
	self:add_child(moji) -- 画面表示上の親子関係を設定
end

-- 初期化
function EndingScene:init(cfg)

	-- タイトル画面自体を設定
	self:init_null_sprite(0,0,0) -- 画面表示なし
    self.spr:Show(true)
	self.spr:SetScale(1.0,1.0)
    
    -- スーパークラス(Actor)のinitを呼ぶ
    Actor.init(self, cfg)
	

	local center_x = GS.screen_w/2
	
	local mojidata = {
		"Congraturations!",
		"企画：Makoto Hamanaka",
		"プログラム：Makoto Hamanaka",
		"グラフィック：LEEX",
		"fin."
	}
	
	for i,moji in ipairs(mojidata) do
		self:add_text(moji, (i-1) * 180)
	end

end

-- キーイベント処理
function EndingScene:on_keydown(key, is_ctrl, is_alt, is_shift)
	return false
end

-- マウスイベント処理
function EndingScene:on_mouse(evtype, button, x, y)
	if evtype == "down" and button == 1 then
		local p = self.params
		p.is_clicked = true
		return true
	end
	return false
end

-- ステージを終了させる指示を行う
function EndingScene:finish_stage()
	p.is_clicked = true
end

-- Actor削除時に実行される
function EndingScene:on_destroy()

end


-- 状態関数

function EndingScene:state_start(rt)
	return "goto", "state_frame"
end

-- 入力待ち状態
function EndingScene:state_frame(rt)
	local p = self.params
	while true do
		self:wait(1)
		-- マウスクリックイベントがきたらシーン移行状態の関数へ
		if p.is_clicked then
			return "goto", "state_before_change_scene"
		end
	end
end

-- 次のシーンへの移行前
function EndingScene:state_before_change_scene(rt)
	local p = self.params

	self:wait(30)
	
	-- イベントに応じて次のシーンへ移行
	change_scene(GameTitle)
	return "exit"
end









-- タイトル文字実装
subclass("EndingMoji", Actor) {
}

-- コンストラクタ
function EndingMoji:ctor(...)
	print("EndingMoji:ctor() called")
	EndingMoji.super.ctor(self, ...)
	
end

-- 初期化
-- cfg.start_wait : 文字を表示し始めるまでの時間
function EndingMoji:init(cfg)
	self:init_text("ending_moji", cfg.moji, nil, 0, 0, 1000)

	if cfg.scale ~= nil then
        self.spr:SetScale(unpack(cfg.scale))
	end
	if cfg.center ~= nil then
        self.spr:SetCenter(unpack(cfg.center))
	end
	if cfg.pos ~= nil then
		self.spr:MoveTo(unpack(cfg.pos))
    end
	
    -- スーパークラスのinitを呼ぶ
    Actor.init(self, cfg)

	local p = self.params       
	p.x = 0
	p.y = 0
	p.is_clicked = false

	self.spr:Show(false)
end

-- マウスイベントハンドラ
function EndingMoji:on_mouse(evtype, button, x, y)
	return false
end

-- Actor削除時に実行される
function EndingMoji:on_destroy()
end


-- 状態関数

function EndingMoji:state_start(rt)
	print("EndingMoji.funcs.init()")
	
	return "goto", "state_frame"
end

-- 文字の移動
function EndingMoji:state_frame(rt)
	local p = self.params     
	local cfg = self.cfg

	-- 移動前のウエイト
	self:wait(self.cfg.pre_move_wait)
	
	p.x = 100
	p.y = GS.screen_h
	self.spr:Show(true)
	local alpha = 0
	
	for y=GS.screen_h,0,-2 do
		p.y = y
		-- 透明度設定
		local alpha = 1.0
		local half_h = GS.screen_h/2
		if y > GS.screen_h-100 then
			alpha = (GS.screen_h-y)/100
		elseif y < half_h then
			alpha = y/half_h
		end
		self.spr:MoveTo(p.x, p.y)
		self.spr:SetAlpha(alpha)
		self:wait(1)
	end
	return "exit" -- アクター自滅
end