
-- ステージデータ
local stage_data = {
	[1] = {
		miko_count = 1, -- 巫女（味方）の数
		samurai_count = 1, -- 侍（味方）の数
		-- 敵の設定
		enemies = {
			{ class = "Enemy1Actor", count = 5},
		},
		-- 地面の設定
		ground_ratio = { 90, 10 }, -- 地面の構成割合（砂、草）
		-- 障害物の設定
		obstacles = {
			{ type = "rock1", count = 8 },
			{ type = "rock2", count = 2 },
			{ type = "tree", count = 4 },
		},
	},
	[2] = {
		miko_count = 1,
		samurai_count = 2,
		enemies = {
			{ class = "Enemy1Actor", count = 15},
		},
		-- 地面の設定
		ground_ratio = { 70, 30 }, -- 地面の構成割合（砂、草）
		-- 障害物の設定
		obstacles = {
			{ type = "rock1", count = 5 },
			{ type = "rock2", count = 5 },
			{ type = "tree", count = 4 },
		},
	},
	[3] = {
		miko_count = 1,
		samurai_count = 2,
		enemies = {
			{ class = "Enemy1Actor", count = 20},
		},
		-- 地面の設定
		ground_ratio = { 10, 90 }, -- 地面の構成割合（砂、草）
		-- 障害物の設定
		obstacles = {
			{ type = "rock1", count = 2 },
			{ type = "rock2", count = 3 },
			{ type = "tree", count = 10 },
		},
	},
}

-- GameScene用のcfgデータを返す
function get_stage_cfg(stage)
	if stage == #stage_data+1 then
		return true
	end
	local cfg = stage_data[stage]
	cfg.stage = stage
	return cfg
end