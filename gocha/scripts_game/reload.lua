
local reload_type = ... -- 引数を受け取る


local files = {}               -- リロード対象スクリプトファイル
local reload_funcs = {}        -- リロード後に実行する関数
local reload_funcs_set = {}    -- リロード後に実行する関数の一致チェック用

local is_reload = true -- リロードか、通常ロードか。

if reload_type == "load" then
	-- 通常ロードをここで処理する
	files = {
		"scripts_common/common.lua",
		"scripts_common/class.lua",
		"scripts_common/coroutine.lua",
		"scripts_common/collision.lua",
		"scripts_common/actor.lua",
		"scripts_game/gamestage.lua",
		"scripts_game/gameinit.lua",
		"scripts_game/gamescene.lua",
		"scripts_game/gamefield.lua",
		"scripts_game/char_actor_common.lua",
		"scripts_game/gamechars.lua",
		"scripts_game/gamechars_enemy.lua",
		"scripts_game/weapons.lua",
		"scripts_game/gametitle.lua",
		"scripts_game/ending.lua",
	}
	is_reload = false
elseif reload_type == "chars" then
	-- キャラクターリロード時
	files = {
		"scripts_game/gamescene.lua",
		"scripts_game/gamefield.lua",
		"scripts_game/char_actor_common.lua",
		"scripts_game/gamechars.lua",
		"scripts_game/gamechars_enemy.lua",
		"scripts_game/weapons.lua",
	}
elseif reload_type == "all" then
	-- 全リロード時
    local res, err = pcall( function()
        endfunc()
    end)
    print("error on endfunc() : ", err)
	files = {
		"scripts_common/common.lua",
		"scripts_common/class.lua",
		"scripts_common/coroutine.lua",
		"scripts_common/collision.lua",
		"scripts_common/actor.lua",
		"scripts_game/gamestage.lua",
		"scripts_game/gameinit.lua",
		"scripts_game/gamescene.lua",
		"scripts_game/gamefield.lua",
		"scripts_game/char_actor_common.lua",
		"scripts_game/gamechars.lua",
		"scripts_game/gamechars_enemy.lua",
		"scripts_game/weapons.lua",
		"scripts_game/gametitle.lua",
		"scripts_game/ending.lua",
	}

	-- タイトル画面に戻る
    table.insert(reload_funcs, function() 
        startfunc()
        return true
    end)
else
	return false, "unknown reload type:"..reload_type
end

-- 現状のon_reloadグローバル関数を削除しておく
if rawget(_G, "on_reload") then
    _G.on_reload = nil
end

-- ファイルをロードする
for i,path in ipairs(files) do
	local res = cfunc.DoLuaFile(path)
    local err = cfunc.GetLuaError()
	if not res then
		return false, "script<"..path.."> reload failed : "..(err or "unknown")
	end
	-- リロード後処理関数が新しく定義されていたらリストに加える
	if rawget(_G,"on_reload") and (not reload_funcs_set[_G.on_reload]) then
		table.insert(reload_funcs, on_reload)
		reload_funcs_set[_G.on_reload] = path
	end
	print("script<"..path.."> reload success.")
end

if is_reload then
	-- リロード後処理関数をすべて実行
	-- １つでもfalseを返したらリロードは不成功とする
	for i, func in ipairs(reload_funcs) do
		local res, err = func()
		if res == false then
			return false, "on_reload() of script<"..reload_funcs_set[func].."> failed. :"..err
		end
	end

	-- すべてのクラスのすべてのインスタンスのon_reload()を（あれば）実行する
	exec_class_reload_funcs()

	print("reload/load success!")
end

collectgarbage("collect")

return true, "success"
