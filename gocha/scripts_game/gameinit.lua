-- Lua ごちゃ WARS
--

print("Hello!from gameinit.lua");

collectgarbage("setpause", 105)
collectgarbage("setstepmul", 1000)
collectgarbage("collect")

--
--  GS : GameSystem
--

global "GS"

GS = {
	scheduler = nil,                      -- スケジューラー
	imageloader = cfunc.GetImageLoader(), -- 画像ローダー
	drawsystem = cfunc.GetDrawSystem(),   -- 描画システム
	scene = nil,            -- 現在のシーン（アクター）
	cursor = nil,           -- カーソル用アクター
	collision = nil,        -- 衝突判定インスタンス（キャラ）
	collision_ground = nil, -- 衝突判定インスタンス（地形）
}

local GS = GS

-- 開始処理
function startfunc()

	GS.scene_scale = 1.0

	-- フィールドサイズなどを決定
	GS.screen_w = 640
	GS.screen_h = 480
	GS.field_w = GS.screen_w * 4
	GS.field_h = 400
	GS.field_h_min = 80
	
	math.randomseed(os.time())

    GS.routinepool = RoutinePool:new()
    GS.routinepool:init(50)

	-- 画像をロード
    GS.imageloader:AddSurfaceByFileName("ground", "gocha_map1.png", 128,128,4);
    GS.imageloader:AddSurfaceByFileName("grass", "gocha_grass.png", 128,128,4);
    GS.imageloader:AddSurfaceByFileName("water", "gocha_water.png", 128,128,4);
    GS.imageloader:AddSurfaceByFileName("object", "gocha_mapobj1.png", 128,128,4);
    GS.imageloader:AddSurfaceByFileName("title", "title.png", 64,64,8);
    GS.imageloader:AddSurfaceByFileName("effect", "effect.png", 128,128,4);
    --GS.imageloader:AddSurfaceByFileName("weapon", "weapon.png", 200,200,2);
    GS.imageloader:AddSurfaceByFileName("chr1", "gocha_chr1.png", 128,128,4);
    GS.imageloader:AddSurfaceByFileName("chr2", "gocha_chr2.png", 128,128,4);
    GS.imageloader:AddSurfaceByFileName("frame", "frame.png", 64,64,8);
    GS.imageloader:AddSurfaceByFileName("weapon", "gocha_weapon.png", 128,128,4);

	GS.scheduler = Scheduler:new()

	-- 最初はタイトル画面シーンを設定する
    GS.scene = GameTitle:new()
    GS.scene:init()
	GS.scene:add_sprite_to_drawsystem(GS.drawsystem)
	
	GS.next_scene = nil
	GS.next_scene_cfg = nil
    
    GS.cursor = CursorActor:new()
    GS.cursor:init()
	
	GS.use_c_collision = false
	
	if GS.use_c_collision then
		-- キャラ用衝突判定マップ
		GS.collision = cclass.CollisionDetector()
		GS.collision:init(GS.field_w, GS.field_h, 64,64)
		-- 地形用衝突判定マップ
		GS.collision_ground = cclass.CollisionDetector()
		GS.collision_ground:init(GS.field_w, GS.field_h, 32,32)
	else
		-- キャラ用衝突判定マップ
		GS.collision = CollisionDetector:new()
		GS.collision:init(GS.field_w, GS.field_h, 64,64)
		-- 地形用衝突判定マップ
		GS.collision_ground = CollisionDetector:new()
		GS.collision_ground:init(GS.field_w, GS.field_h, 64,64)
	end
	
	-- ランダムな名前を作るテスト
	for i=1,100 do
		print("新しい名前:",get_new_name())
	end
	
end

-- C言語で書いた衝突判定結果をLua版と同様に変換する関数
local tinsert = table.insert
function get_c_collision_result_to_lua(count, collision_obj)
	local actors = {}
	for i=0,count-1 do
		local actor = Actor.get_actor_by_id(collision_obj:get_result(i))
		tinsert(actors, actor);
	end
	return actors
end

-- Lua版でもC言語版でも結果リストの指定インデックスのActorオブジェクトを返す
function get_result_actor(index, collision_obj)
	if GS.use_c_collision then
		return Actor.get_actor_by_id(collision_obj:get_result(index))
	else
		return collision_obj:get_result(index)
	end
end


function endfunc()
	if GS.scene ~= nil then
		GS.scheduler:delete_actor(GS.scene)
	end
	if GS.cursor ~= nil then
		GS.scheduler:delete_actor(GS.cursor)
	end
	--GS.scheduler:process_deleted_actors()	
	GS.scheduler:schedule()	
	GS.cursor = nil
	GS.scene = nil
end

-- シーンを変更
function change_scene(scene_class, ...)
	GS.next_scene_class = scene_class
	GS.next_scene_cfg = {...}
end


-- フレームの進行処理
function framefunc()
	-- シーン移行の場合
	if GS.next_scene_class ~= nil then
		if GS.scene ~= nil then
			GS.scheduler:delete_actor(GS.scene)
		end
		GS.scheduler:process_deleted_actors()
		GS.scene = GS.next_scene_class:new()
		GS.scene:init(unpack(GS.next_scene_cfg))
		GS.scene:add_sprite_to_drawsystem(GS.drawsystem)
		GS.next_scene_class = nil
		GS.next_scene_cfg = nil
	end

	if GS.scene == nil then
		return "no scene"
	end
	
	-- マウスカーソル位置取得
	local x,y = cfunc.GetMousePos()
	if GS.cursor ~= nil then
		GS.cursor.params.x = x
		GS.cursor.params.y = y
	end

	-- 衝突判定クリア
	if GS.collision ~= nil then
		GS.collision:clear()
	end
	
	-- シーンごとのスケジューラー前処理
	if GS.scene.pre_schedule ~= nil then
		GS.scene:pre_schedule()
	end
	
	-- スケジューラー処理
	GS.scheduler:schedule()	

	-- シーンごとのスケジューラー後処理
	if GS.scene.post_schedule ~= nil then
		GS.scene:post_schedule()
	end
	
	return "ok"
end

-- キー入力イベントハンドラ
function on_keyevent(key, is_down, is_ctrl, is_alt, is_shift)
	-- キー情報をモニタリング（デバッグ用）
	print("on_keydown(key=",key, " is_ctrl=", is_ctrl, " is_alt=", is_alt, " is_shift=", is_shift, ")")
	
	if is_down then
		-- 特殊機能
		-- F1 : キャラ部分リロード
		-- F2 : 全スクリプトリロード
		-- F9 : 実行情報出力
		if key == SDLK_F1 then
			cfunc.ReloadLuaFiles("chars")
			return
		end
		if key == SDLK_F2 then
			cfunc.ReloadLuaFiles("all")
			return
		end
		if key == SDLK_F9 then
			print("GC count = ",collectgarbage("count"))
			print("F9 pressed")
			analyze_instances()
			SDL.SDL_Delay(5000)
			return
		end
	end
	
	-- イベントをシーンに投げる
	if GS.scene ~= nil and GS.scene.on_keyevent ~= nil then
		GS.scene:on_keyevent(key, is_down, is_ctrl, is_alt, is_shift)
	end
end

-- マウスイベントハンドラ
function on_mouseevent(evtype, button, x, y)
	-- マウス情報をモニタリング（デバッグ用）
	if evtype == "down" then
		print("mousedown(button=",button, " x=", x, " y=", y, ")")
	elseif evtype == "up" then
		print("mouseup(button=",button, " x=", x, " y=", y, ")")
	end

	-- イベントをシーンに投げる
	if GS.scene ~= nil then
		GS.scene:on_mouse(evtype, button, x, y)
	end
end






-- テキストボタンクラス
subclass("TextButton", Actor) {
}

-- コンストラクタ
function TextButton:ctor(...)
	print("TextButton:ctor() called")
	TextButton.super.ctor(self, ...)

end

-- cfgにはx,y,text,scale,およびon_clickを指定可能。
function TextButton:init(cfg)
    cfg.x = cfg.x or 0
	cfg.y = cfg.y or 0
	cfg.z = cfg.z or 0
	cfg.text = cfg.text or "XXXXX"
	cfg.scale = cfg.scale or 1.0
	local fontsize = 24
	self:init_text("textbutton", cfg.text, nil, cfg.x, cfg.y, cfg.z)
	cfg.w = string.len(cfg.text) * fontsize * cfg.scale * 0.5
	cfg.h = fontsize * cfg.scale
	self.spr:SetScale(cfg.scale, cfg.scale)
    self.spr:MoveTo(cfg.x, cfg.y)

    -- スーパークラスのinitを呼ぶ
    Actor.init(self, cfg)
	
	local p = self.params
	
	p.is_clicked = false
end

function TextButton:get_cookie()
	return self.cfg.cookie
end

function TextButton:is_inside(x, y)
	if x >= 0 and x < self.cfg.w and y >= 0 and y < self.cfg.h then
		return true
	end
	return false
end


function TextButton:on_mouse(evtype, button, x, y)
	local p = self.params
	local lx, ly = self.spr:TranslateRootToThis(x,y)
	if evtype == "down" then
		if self:is_inside(lx, ly) then
			-- cfgのon_clickハンドラを呼ぶ
			if self.cfg.on_click ~= nil then
				self.cfg.on_click(self)
			end
			p.is_clicked = true
			return true
		end
	elseif evtype == "move" then
		p.is_under_mouse = self:is_inside(lx, ly)
	end
	return false
end

-- Actor削除時に実行される
function TextButton:on_destroy()
end


-- 状態関数

function TextButton:state_start(rt)
	print("TextButton.funcs.init()")
	self.params = {
		x = self.cfg.x,
		y = self.cfg.y,
	}
	local p = self.params       
	
	return "goto", "state_frame"
end

function TextButton:state_frame(rt)
	local p = self.params       
	while true do
		if p.is_clicked then
			return "goto", "state_clicked"
		end
		local x_offset = p.is_under_mouse and 2 or 0
		local y_offset = p.is_under_mouse and 2 or 0
		p.x = self.cfg.x + x_offset
		p.y = self.cfg.y + y_offset
		self.spr:MoveTo(p.x, p.y)
		self:wait(1)
	end
end
	
function TextButton:state_clicked(rt)
	local p = self.params   
	for i=1,10 do
		local x_offset = 4 - i * 0.2
		local y_offset = 4 - i * 0.2
		p.x = self.cfg.x + x_offset
		p.y = self.cfg.y + y_offset
		self.spr:MoveTo(p.x, p.y)
		self:wait(1)
	end
	p.is_clicked = false
	return "goto", "state_frame"
end


-- 画像ボタンクラス
subclass("ImageButton", Actor) {
}

-- コンストラクタ
function ImageButton:ctor(...)
	print("ImageButton:ctor() called")
	ImageButton.super.ctor(self, ...)

end


-- cfgにはx,y,z,w,h,imagename, scale,xcenter,ycenterおよびon_click関数
-- chip_button_up, chip_button_down, chip_mouse_over を指定可能。
function ImageButton:init(cfg)
    cfg.x = cfg.x or 0
	cfg.y = cfg.y or 0
	cfg.z = cfg.z or 0
	cfg.scale = cfg.scale or 1.0
	cfg.imagename = cfg.imagename or ""
	self:init_image("imagebutton", cfg.imagename, nil, cfg.x, cfg.y, cfg.z)
	cfg.w = cfg.w or 64
	cfg.h = cfg.h or 64
	self.spr:SetScale(cfg.scale, cfg.scale)
    self.spr:MoveTo(cfg.x, cfg.y)
	self.spr:SetChipIndex(cfg.chip_button_up)
	cfg.xcenter = cfg.xcenter or 0
	cfg.ycenter = cfg.ycenter or 0
	self.spr:SetCenter(cfg.xcenter, cfg.ycenter)

    -- スーパークラスのinitを呼ぶ
    Actor.init(self, cfg)
	
	-- 実行時状態(params)設定
	local p = self.params
	p.x = self.cfg.x
	p.y = self.cfg.y
	p.is_clicked = false
	p.is_under_mouse = false
end

function ImageButton:get_cookie()
	return self.cfg.cookie
end

function ImageButton:is_inside(x, y)
	if x >= 0 and x < self.cfg.w and y >= 0 and y < self.cfg.h then
		return true
	end
	return false
end


function ImageButton:on_mouse(evtype, button, x, y)
	local p = self.params
	local lx, ly = self.spr:TranslateRootToThis(x,y)
	if evtype == "down" then
		if self:is_inside(lx, ly) then
			-- cfgのon_clickハンドラを呼ぶ
			if self.cfg.on_click ~= nil then
				self.cfg.on_click(self)
			end
			p.is_clicked = true
			return true
		end
	elseif evtype == "move" then
		p.is_under_mouse = self:is_inside(lx, ly)
	end
	return false
end

-- Actor削除時に実行される
function ImageButton:on_destroy()
end


-- 状態関数

function ImageButton:state_start(rt)
	print("ImageButton.funcs.init()")
	
	return "goto", "state_frame"
end

function ImageButton:state_frame(rt)
	local p = self.params
	local cfg = self.cfg
	while true do
		if p.is_clicked then
			return "goto", "state_clicked"
		end
		self.spr:MoveTo(p.x, p.y)
		local index = cfg.chip_button_up
		if p.is_under_mouse and cfg.chip_mouse_over ~= nil then
			index = cfg.chip_mouse_over
		end
		self.spr:SetChipIndex(index)
		self:wait(1)
	end
end
	
function ImageButton:state_clicked(rt)
	local p = self.params   
	local cfg = self.cfg
	for i=1,8 do
		if cfg.chip_button_down == nil then
			local x_offset = 4 - i * 0.2
			local y_offset = 4 - i * 0.2
			p.x = self.cfg.x + x_offset
			p.y = self.cfg.y + y_offset
			self.spr:MoveTo(p.x, p.y)
		end
		local index = cfg.chip_button_down or cfg.chip_button_up
		self.spr:SetChipIndex(index)
		self:wait(1)
	end
	p.is_clicked = false
	return "goto", "state_frame"
end


-- マウスカーソル
subclass("CursorActor", Actor) {
}

-- コンストラクタ
function CursorActor:ctor(...)
	print("CursorActor:ctor() called")
	CursorActor.super.ctor(self, ...)

end

function CursorActor:init(cfg)	
	self:init_image("cursor", "frame", 0,0,1000)
	self.spr:SetScale(1.0,1.0)
	self.spr:SetCenter(0,0)
	self.spr:SetChipIndex(6*8 +0)
	self:add_sprite_to_drawsystem(GS.drawsystem)
	self:set_mode("cursor")

	-- スーパークラスのinitを呼ぶ
	Actor.init(self, cfg)

	self.params = {x = 0, y = 0}
end

-- 画像切り替え
-- modeは"cursor"か"flag"のどちらか
function CursorActor:set_mode(mode)
	if mode == "cursor" then
		self.spr:SetChipIndex(6*8 +0)
		self.spr:SetCenter(0,0)
	else
		self.spr:SetChipIndex(6*8 +1)
		self.spr:SetCenter(0,64)
	end
end

-- Actor削除時に実行される
function CursorActor:on_destroy()
end

function CursorActor:state_start(rt)
	return "goto", "state_frame"
end
	
function CursorActor:state_frame(rt)
	local p = self.params
	while true do
		self.spr:MoveTo(p.x, p.y)
		self:wait(1)
	end
end

