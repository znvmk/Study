nvim_tree.setup({
  sort_by = "case_sensitive",
	-- 是否显示 git 状态
	git = {
		enable = true,
	},
	-- 过滤文件
	filters = {
		dotfiles = true, -- 过滤 dotfile
		custom = { "node_modules" }, -- 其他过滤目录
	},
  view = {
	-- 文件浏览器展示位置，左侧：left, 右侧：right
	side = "left",
	-- 行号是否显示
	number = false,
	relativenumber = false,
	signcolumn = "yes", -- 显示图标
	width = 30,
  },
  renderer = {
    group_empty = true,
  },
})
