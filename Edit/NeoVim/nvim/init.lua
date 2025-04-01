-- Set <space> as the leader key
-- See `:help mapleader`
--  NOTE: Must happen before plugins are required (otherwise wrong leader will be used)
vim.g.mapleader = ' '
vim.g.maplocalleader = ' '

-- Install package manager
--    https://github.com/folke/lazy.nvim
--    `:help lazy.nvim.txt` for more info
local lazypath = vim.fn.stdpath 'data' .. '/lazy/lazy.nvim'
if not vim.loop.fs_stat(lazypath) then
  vim.fn.system {
    'git',
    'clone',
    '--filter=blob:none',
    'https://gitee.com/suyelu/lazy.nvim.git',
    '--branch=stable', -- latest stable release
    lazypath,
  }
end

--vim.opt.rtp:prepend(lazypath)
vim.o.runtimepath = lazypath .. ',' .. vim.o.runtimepath
--print(vim.o.runtimepatih)
--nvim_list_runtime_paths(lazypath)
--nvim_get_runtime_file(lazypath)

-- NOTE: Here is where you install your plugins.
--  You can configure plugins using the `config` key.
--
--  You can also configure plugins after the setup call,
--    as they will be available in your neovim runtime.
local base_url = 'https://gitee.com/suyelu'
require('lazy').setup({
  -- NOTE: First, some plugins that don't require any configuration

  -- Git related plugins
  ---'https://gitee.com/suyelu/copilot.vim.git',
  string.format('%s/copilot.vim.git', base_url),
  'https://gitee.com/suyelu/vim-fugitive',
  'https://gitee.com/suyelu/vim-rhubarb',

  -- Detect tabstop and shiftwidth automatically
  --'https://gitee.com/suyelu/vim-sleuth',

  -- NOTE: This is where your plugins related to LSP can be installed.
  --  The configuration is done below. Search for lspconfig to find it below.
  {
    -- LSP Configuration & Plugins
    'https://gitee.com/suyelu/nvim-lspconfig',
    dependencies = {
      -- Automatically install LSPs to stdpath for neovim
      { 'https://gitee.com/suyelu/mason.nvim',  config = true },
      'https://gitee.com/suyelu/mason-lspconfig.nvim',

      -- Useful status updates for LSP
      -- NOTE: `opts = {}` is the same as calling `require('fidget').setup({})`
      { 'https://gitee.com/suyelu/fidget.nvim', tag = 'legacy', opts = {} },

      -- Additional lua configuration, makes nvim stuff amazing!
      'https://gitee.com/suyelu/neodev.nvim',
    },
  },

  {
    -- Autocompletion
    'https://gitee.com/suyelu/nvim-cmp',
    dependencies = {
      string.format('%s/cmp-nvim-lsp', base_url),
      {
        string.format('%s/LuaSnip', base_url),
        build = 'make install_jsregexp',
      },
      string.format('%s/cmp_luasnip', base_url),
      string.format('%s/cmp-buffer', base_url),
      string.format('%s/cmp-path', base_url),
      string.format('%s/cmp-cmdline', base_url),
    },
  },
  {
    string.format('%s/null-ls.nvim.git', base_url),
    dependencies = { string.format('%s/plenary.nvim', base_url) },
  },
  ---  jump anywhere in a document ---
  {
    string.format('%s/hop.nvim', base_url),
    branch = 'v2',
    keys = {
      { '<leader>h', '<Cmd>HopWord<CR>',            mode = 'n', silent = true },
      { '<leader>H', '<Cmd>HopLine<CR>',            mode = 'n', silent = true },
      { '<leader>f', '<Cmd>HopWordCurrentLine<CR>', mode = 'n', silent = true },
    },
  },
-- 屏保
  {string.format('%s/cellular-automaton.nvim', base_url)},
  -- Useful plugin to show you pending keybinds.
  { string.format('%s/which-key.nvim', base_url), opts = {} },
  {
    -- Adds git releated signs to the gutter, as well as utilities for managing changes
    string.format('%s/gitsigns.nvim', base_url),
    opts = {
      -- See `:help gitsigns.txt`
      signs = {
        add = { text = '+' },
        change = { text = '~' },
        delete = { text = '_' },
        topdelete = { text = '‾' },
        changedelete = { text = '~' },
      },
    },
  },

  {
    -- Theme inspired by Atom
    string.format('%s/onedark.nvim', base_url),
    priority = 1000,
    config = function()
      vim.cmd.colorscheme 'onedark'
    end,
  },
  {
    string.format('%s/tokyonight.nvim', base_url),
  },
  {
    string.format('%s/gruvbox.nvim', base_url),
  },

  {
    -- Set lualine as statusline
    string.format('%s/lualine.nvim', base_url),
    -- See `:help lualine.txt`
    dependencies = {
      string.format('%s/nvim-web-devicons', base_url),
    },
  },

  {
    -- Add indentation guides even on blank lines
    string.format('%s/indent-blankline.nvim', base_url),
    -- Enable `lukas-reineke/indent-blankline.nvim`
    -- See `:help indent_blankline.txt`
    main = "ibl",
    opts = {
      --char = '┊',
      --show_trailing_blankline_indent = false,
    },
  },

  -- "gc" to comment visual regions/lines
  { string.format('%s/Comment.nvim', base_url),   opts = {} },

  -- Fuzzy Finder (files, lsp, etc)
  {
    string.format('%s/telescope.nvim', base_url),
    version = '*',
    dependencies = {
      string.format('%s/plenary.nvim', base_url),
    },
  },

  -- Fuzzy Finder Algorithm which requires local dependencies to be built.
  -- Only load if `make` is available. Make sure you have the system
  -- requirements installed.
  {
    string.format('%s/telescope-fzf-native.nvim', base_url),
    -- NOTE: If you are having trouble with this installation,
    --       refer to the README for telescope-fzf-native for more instructions.
    build = 'make',
    cond = function()
      return vim.fn.executable 'make' == 1
    end,
  },

--无法下载
--  {
    -- Highlight, edit, and navigate code
--    string.format('%s/nvim-treesitter', base_url),
--    dependencies = {
--      string.format('%s/nvim-treesitter-textobjects', base_url),
--    },
--    build = ':TSUpdate',
--  },
  {
    string.format('%s/nvim-tree.lua', base_url),
    dependencies = {
      string.format('%s/nvim-web-devicons', base_url),
    },
  },
  {
    string.format('%s/bufferline.nvim', base_url),
    dependencies = {
      string.format('%s/nvim-web-devicons', base_url),
      string.format('%s/vim-bbye', base_url),
    },
  },
  {
    string.format('%s/lualine-lsp-progress', base_url),
  },
  {
    string.format('%s/dashboard-nvim', base_url),
  },
  {
    string.format('%s/project.nvim', base_url),
  },

  -- NOTE: Next Step on Your Neovim Journey: Add/Configure additional "plugins" for kickstart
  --       These are some example plugins that I've included in the kickstart repository.
  --       Uncomment any of the lines below to enable them.
  -- require 'kickstart.plugins.autoformat',
  -- require 'kickstart.plugins.debug',

  -- NOTE: The import below automatically adds your own plugins, configuration, etc from `lua/custom/plugins/*.lua`
  --    You can use this folder to prevent any conflicts with this init.lua if you're interested in keeping
  --    up-to-date with whatever is in the kickstart repo.
  --
  --    For additional information see: https://github.com/folke/lazy.nvim#-structuring-your-plugins
  --
  --    An additional note is that if you only copied in the `init.lua`, you can just comment this line
  --    to get rid of the warning telling you that there are not plugins in `lua/custom/plugins/`.
  { import = 'custom.plugins' },
}, {})

-- [[ Setting options ]]
-- See `:help vim.o`

-- Set highlight on search
vim.o.hlsearch = false
-- 边输入边搜索
vim.o.incsearch = true
-- Make line numbers default
vim.wo.number = true
-- 边输入边搜索
vim.o.incsearch = true
-- 命令行高为2，提供足够的显示空间
vim.o.cmdheight = 2
-- 当文件被外部程序修改时，自动加载
vim.o.autoread = true
vim.bo.autoread = true
vim.g.encoding = 'UTF-8'
--vim.o.fileencoding = 'utf-8'
-- jkhl 移动时光标周围保留8行
vim.o.scrolloff = 8
vim.o.sidescrolloff = 8
-- 使用相对行号
vim.wo.number = true
vim.wo.relativenumber = true
-- 高亮所在行
vim.wo.cursorline = true
-- 高亮所在列
vim.wo.cursorcolumn = true
-- 显示左侧图标指示列
vim.wo.signcolumn = 'yes'
-- 右侧参考线，超过表示代码太长了，考虑换行
vim.wo.colorcolumn = '80'
-- 缩进2个空格等于一个Tab
vim.o.tabstop = 4
vim.bo.tabstop = 4
vim.o.softtabstop = 4
vim.o.shiftround = true
-- >> << 时移动长度
vim.o.shiftwidth = 4
vim.bo.shiftwidth = 4
-- 空格替代tab
vim.o.expandtab = true
vim.bo.expandtab = true
-- 新行对齐当前行
vim.o.autoindent = true
vim.bo.autoindent = true
vim.o.smartindent = true
-- 搜索大小写不敏感，除非包含大写
vim.o.ignorecase = true
vim.o.smartcase = true

-- 禁止折行
vim.wo.wrap = false
-- 光标在行首尾时<Left><Right>可以跳到下一行
vim.o.whichwrap = '<,>,[,]'
-- 允许隐藏被修改过的buffer
vim.o.hidden = true
-- Enable mouse mode
vim.o.mouse = 'a'

-- Sync clipboard between OS and Neovim.
--  Remove this option if you want your OS clipboard to remain independent.
--  See `:help 'clipboard'`
vim.o.clipboard = 'unnamedplus'

-- Enable break indent
vim.o.breakindent = true

-- Save undo history
vim.o.undofile = true

-- Case insensitive searching UNLESS /C or capital in search
vim.o.ignorecase = true
vim.o.smartcase = true
-- 禁止创建备份文件
vim.o.backup = false
vim.o.writebackup = false
vim.o.swapfile = false

-- Keep signcolumn on by default
vim.wo.signcolumn = 'yes'
-- Decrease update time
vim.o.updatetime = 2500
vim.o.timeout = true
vim.o.timeoutlen = 700
-- split window 从下边和右边出现
vim.o.splitbelow = true
vim.o.splitright = true
-- Set completeopt to have a better completion experience
vim.o.completeopt = 'menu,menuone,noselect,noinsert'

-- NOTE: You should make sure your terminal supports this
vim.o.termguicolors = true
-- 不可见字符的显示，这里只把空格显示为一个点
vim.o.list = true
vim.o.listchars = 'space:·'

-- 补全增强
vim.o.wildmenu = true
-- Dont' pass messages to |ins-completin menu|
vim.o.shortmess = vim.o.shortmess .. 'c'
-- 补全最多显示10行
vim.o.pumheight = 10
-- 永远显示 tabline
vim.o.showtabline = 4 --存疑
-- 使用增强状态栏插件后不再需要 vim 的模式提示
vim.o.showmode = false
-- [[ Basic Keymaps ]]

-- Keymaps for better default experience
-- See `:help vim.keymap.set()`
vim.keymap.set("n", "<leader>fml", "<cmd>CellularAutomaton make_it_rain<CR>")
vim.keymap.set({ 'n', 'v' }, '<Space>', '<Nop>', { silent = true })
-- Remap for dealing with word wrap
vim.keymap.set('n', 'k', "v:count == 0 ? 'gk' : 'k'", { expr = true, silent = true })
vim.keymap.set('n', 'j', "v:count == 0 ? 'gj' : 'j'", { expr = true, silent = true })
local map = vim.api.nvim_set_keymap
-- 复用 opt 参数
local opt = { noremap = true, silent = true }

-- Terminal相关
map('n', '<leader>t', ':sp | terminal<CR>', opt)
map('n', '<leader>vt', ':vsp | terminal<CR>', opt)
map('t', '<Esc>', '<C-\\><C-n>', opt)
map('t', '<A-h>', [[ <C-\><C-N><C-w>h ]], opt)
map('t', '<A-j>', [[ <C-\><C-N><C-w>j ]], opt)
map('t', '<A-k>', [[ <C-\><C-N><C-w>k ]], opt)
map('t', '<A-l>', [[ <C-\><C-N><C-w>l ]], opt)

-- visual模式下缩进代码
map('v', '<', '<gv', opt)
map('v', '>', '>gv', opt)
-- 上下移动选中文本
map('v', 'J', ":move '>+1<CR>gv-gv", opt)
map('v', 'K', ":move '<-2<CR>gv-gv", opt)

-- Alt + hjkl  窗口之间跳转
map('n', '<A-h>', '<C-w>h', opt)
map('n', '<A-j>', '<C-w>j', opt)
map('n', '<A-k>', '<C-w>k', opt)
map('n', '<A-l>', '<C-w>l', opt)

-- 左右比例控制
map('n', '<C-Left>', ':vertical resize -2<CR>', opt)
map('n', '<C-Right>', ':vertical resize +2<CR>', opt)
-- 上下比例
map('n', '<C-Down>', ':resize +2<CR>', opt)
map('n', '<C-Up>', ':resize -2<CR>', opt)

-- 大括号补全
map('i', '{<CR>', '{<CR>}<ESC>O', opt)
-- 圆括号补全
map('i', '(', '()<LEFT>', opt)

require('hop').setup()

-- [[ lualine]]

require('lualine').setup {
  options = {
    theme = 'tokyonight',
    component_separators = { left = '|', right = '|' },
    -- https://github.com/ryanoasis/powerline-extra-symbols
    section_separators = { left = ' ', right = '' },
  },
  extensions = { 'nvim-tree', 'toggleterm' },
  sections = {
    lualine_c = {
      'filename',
      {
        'lsp_progress',
        spinner_symbols = { ' ', ' ', ' ', ' ', ' ', ' ' },
      },
    },
    lualine_x = {
      'filesize',
      {
        'fileformat',
        symbols = {
          unix = '', -- e712
          dos = '', -- e70f
          mac = '', -- e711
        },
        -- symbols = {
        -- unix = "LF",
        --  dos = "CRLF",
        --  mac = "CR",
        -- },
      },
      'encoding',
      'filetype',
    },
  },
}

-- [[ Highlight on yank ]]
-- See `:help vim.highlight.on_yank()`
local highlight_group = vim.api.nvim_create_augroup('YankHighlight', { clear = true })
vim.api.nvim_create_autocmd('TextYankPost', {
  callback = function()
    vim.highlight.on_yank()
  end,
  group = highlight_group,
  pattern = '*',
})

-- [[ Configure Telescope ]]
-- See `:help telescope` and `:help telescope.setup()`
require('telescope').setup {
  defaults = {
    mappings = {
      i = {
        ['<C-u>'] = false,
        ['<C-d>'] = false,
      },
    },
  },
}

-- Enable telescope fzf native, if installed
pcall(require('telescope').load_extension, 'fzf')

-- See `:help telescope.builtin`
vim.keymap.set('n', '<leader>?', require('telescope.builtin').oldfiles, { desc = '[?] Find recently opened files' })
vim.keymap.set('n', '<leader><space>', require('telescope.builtin').buffers, { desc = '[ ] Find existing buffers' })
vim.keymap.set('n', '<leader>/', function()
  -- You can pass additional configuration to telescope to change theme, layout, etc.
  require('telescope.builtin').current_buffer_fuzzy_find(require('telescope.themes').get_dropdown {
    winblend = 10,
    previewer = false,
  })
end, { desc = '[/] Fuzzily search in current buffer' })

vim.keymap.set('n', '<leader>sf', require('telescope.builtin').find_files, { desc = '[S]earch [F]iles' })
vim.keymap.set('n', '<leader>sh', require('telescope.builtin').help_tags, { desc = '[S]earch [H]elp' })
vim.keymap.set('n', '<leader>sw', require('telescope.builtin').grep_string, { desc = '[S]earch current [W]ord' })
vim.keymap.set('n', '<leader>sg', require('telescope.builtin').live_grep, { desc = '[S]earch by [G]rep' })
vim.keymap.set('n', '<leader>sd', require('telescope.builtin').diagnostics, { desc = '[S]earch [D]iagnostics' })


--插件无法加载，在此处无法调用
-- [[ Configure Treesitter ]]
-- See `:help nvim-treesitter`
--require('nvim-treesitter.configs').setup {
  -- Add languages to be installed here that you want installed for treesitter
--  ensure_installed = { 'c', 'cpp', 'go', 'lua', 'python', 'rust', 'tsx', 'typescript', 'vimdoc', 'vim' },

  -- Autoinstall languages that are not installed. Defaults to false (but you can change for yourself!)
--  auto_install = true,

--  highlight = { enable = true },
--  indent = { enable = true, disable = { 'python' } },
--  incremental_selection = {
--    enable = true,
--    keymaps = {
--      init_selection = '<c-space>',
--      node_incremental = '<c-space>',
--      scope_incremental = '<c-s>',
--      node_decremental = '<M-space>',
--    },
--  },
--  textobjects = {
--    select = {
--      enable = true,
--      lookahead = true, -- Automatically jump forward to textobj, similar to targets.vim
--      keymaps = {
--        -- You can use the capture groups defined in textobjects.scm
--        ['aa'] = '@parameter.outer',
--        ['ia'] = '@parameter.inner',
--        ['af'] = '@function.outer',
--        ['if'] = '@function.inner',
--        ['ac'] = '@class.outer',
--        ['ic'] = '@class.inner',
--      },
--    },
--    move = {
--      enable = true,
--      set_jumps = true, -- whether to set jumps in the jumplist
--      goto_next_start = {
--        [']m'] = '@function.outer',
--        [']]'] = '@class.outer',
--      },
--      goto_next_end = {
--        [']M'] = '@function.outer',
--        [']['] = '@class.outer',
--      },
--      goto_previous_start = {
--        ['[m'] = '@function.outer',
--        ['[['] = '@class.outer',
--      },
--      goto_previous_end = {
--        ['[M'] = '@function.outer',
--        ['[]'] = '@class.outer',
--      },
--    },
--    swap = {
--      enable = true,
--      swap_next = {
---        ['<leader>a'] = '@parameter.inner',
--      },
--      swap_previous = {
--        ['<leader>A'] = '@parameter.inner',
--      },
--    },
--  },
--}

--local status, nvim_tree = pcall(require, "nvim-tree")
--if not status then
--	vim.notify("没有找到 nvim-tree")
--	return
--end

--require("plugins-config.nvim-tree")
-- Diagnostic keymaps
vim.keymap.set('n', '[d', vim.diagnostic.goto_prev, { desc = 'Go to previous diagnostic message' })
vim.keymap.set('n', ']d', vim.diagnostic.goto_next, { desc = 'Go to next diagnostic message' })
vim.keymap.set('n', '<leader>e', vim.diagnostic.open_float, { desc = 'Open floating diagnostic message' })
vim.keymap.set('n', '<leader>q', vim.diagnostic.setloclist, { desc = 'Open diagnostics list' })

vim.diagnostic.config {
  virtual_text = true,
  signs = true,
  -- 在输入模式下也更新提示，设置为 true 也许会影响性能
  update_in_insert = false,
}
local signs = { Error = '', Warn = '', Hint = '', Info = ' ' }
for type, icon in pairs(signs) do
  local hl = 'DiagnosticSign' .. type
  vim.fn.sign_define(hl, { text = icon, texthl = hl, numhl = hl })
end

-- LSP settings.
--  This function gets run when an LSP connects to a particular buffer.
local on_attach = function(_, bufnr)
  -- NOTE: Remember that lua is a real programming language, and as such it is possible
  -- to define small helper and utility functions so you don't have to repeat yourself
  -- many times.
  --
  -- In this case, we create a function that lets us more easily define mappings specific
  -- for LSP related items. It sets the mode, buffer and description for us each time.
  local nmap = function(keys, func, desc)
    if desc then
      desc = 'LSP: ' .. desc
    end

    vim.keymap.set('n', keys, func, { buffer = bufnr, desc = desc })
  end

  nmap('<leader>rn', vim.lsp.buf.rename, '[R]e[n]ame')
  nmap('<leader>ca', vim.lsp.buf.code_action, '[C]ode [A]ction')

  nmap('gd', vim.lsp.buf.definition, '[G]oto [D]efinition')
  nmap('gr', require('telescope.builtin').lsp_references, '[G]oto [R]eferences')
  nmap('gI', vim.lsp.buf.implementation, '[G]oto [I]mplementation')
  nmap('<leader>D', vim.lsp.buf.type_definition, 'Type [D]efinition')
  nmap('<leader>ds', require('telescope.builtin').lsp_document_symbols, '[D]ocument [S]ymbols')
  nmap('<leader>ws', require('telescope.builtin').lsp_dynamic_workspace_symbols, '[W]orkspace [S]ymbols')

  -- See `:help K` for why this keymap
  nmap('K', vim.lsp.buf.hover, 'Hover Documentation')
  nmap('<C-k>', vim.lsp.buf.signature_help, 'Signature Documentation')

  -- Lesser used LSP functionality
  nmap('gD', vim.lsp.buf.declaration, '[G]oto [D]eclaration')
  nmap('<leader>wa', vim.lsp.buf.add_workspace_folder, '[W]orkspace [A]dd Folder')
  nmap('<leader>wr', vim.lsp.buf.remove_workspace_folder, '[W]orkspace [R]emove Folder')
  nmap('<leader>wl', function()
    print(vim.inspect(vim.lsp.buf.list_workspace_folders()))
  end, '[W]orkspace [L]ist Folders')
  vim.api.nvim_create_autocmd({ 'CursorHold', 'CursorHoldI' },
    { callback = vim.lsp.buf.document_highlight, buffer = bufnr })
  vim.api.nvim_create_autocmd({ 'CursorMoved', 'CursorMovedI' },
    { callback = vim.lsp.buf.clear_references, buffer = bufnr })
  vim.api.nvim_create_autocmd({ 'TextChangedI', 'TextChangedP' },
    { callback = vim.lsp.buf.signature_help, buffer = bufnr })
  -- Create a command `:Format` local to the LSP buffer
  vim.api.nvim_buf_create_user_command(bufnr, 'Format', function(_)
    vim.lsp.buf.format()
  end, { desc = 'Format current buffer with LSP' })
end

-- Enable the following language servers
--  Feel free to add/remove any LSPs that you want here. They will automatically be installed.
--
--  Add any additional override configuration in the following tables. They will be passed to
--  the `settings` field of the server config. You must look up that documentation yourself.
local servers = {
  clangd = {},
  -- gopls = {},
   pyright = {},
  -- rust_analyzer = {},
  -- tsserver = {},

  lua_ls = {
    Lua = {
      workspace = { checkThirdParty = false },
      telemetry = { enable = false },
    },
   },
}
-- Setup neovim lua configuration
require('neodev').setup()

-- nvim-cmp supports additional completion capabilities, so broadcast that to servers
local capabilities = vim.lsp.protocol.make_client_capabilities()
capabilities = require('cmp_nvim_lsp').default_capabilities(capabilities)

-- Ensure the servers above are installed
local mason_lspconfig = require 'mason-lspconfig'

mason_lspconfig.setup {
  ensure_installed = vim.tbl_keys(servers),
}

mason_lspconfig.setup_handlers {
  function(server_name)
    local server_config = {
      capabilities = capabilities,
      on_attach = on_attach,
      settings = servers[server_name],
    }
    -- 如果server_name为clangd,设置--offset-encoding=utf-16
    if server_name == 'clangd' then
      server_config.cmd = {
        'clangd',
        '--offset-encoding=utf-16',
      }
      server_config.init_options = {
        filetypes = { 'c', 'cpp' },
        clangdFileStatus = true,
        usePlaceholders = true,
        completeUnimported = true,
        semanticHighlighting = true,
        --root_dir = mason_lspconfig.util.root_pattern('compile_commands.json', 'compile_flags.txt', '.git'),
        format = {
          style = 'file',
          fallbackStyle = 'llvm',
          columnLimit = 100,
          tabWidth = 4,
          indentWidth = 4,
          SpacesInAngles = true,
        },
        settings = {
          Cpp = {
            tabWidth = 4,
          },
        },
      }
    end
    require('lspconfig')[server_name].setup(server_config)
  end,
}

-- nvim-cmp setup
local cmp = require 'cmp'
local luasnip = require 'luasnip'

luasnip.config.setup {}

cmp.setup {
  snippet = {
    expand = function(args)
      luasnip.lsp_expand(args.body)
    end,
  },
  mapping = cmp.mapping.preset.insert {
    ['<C-d>'] = cmp.mapping.scroll_docs(-4),
    ['<C-f>'] = cmp.mapping.scroll_docs(4),
    ['<C-Space>'] = cmp.mapping.complete {},
    ['<CR>'] = cmp.mapping.confirm {
      behavior = cmp.ConfirmBehavior.Replace,
      select = true,
    },
    ['<Tab>'] = cmp.mapping(function(fallback)
      if cmp.visible() then
        cmp.select_next_item()
      elseif luasnip.expand_or_jumpable() then
        luasnip.expand_or_jump()
      else
        fallback()
      end
    end, { 'i', 's' }),
    ['<S-Tab>'] = cmp.mapping(function(fallback)
      if cmp.visible() then
        cmp.select_prev_item()
      elseif luasnip.jumpable(-1) then
        luasnip.jump(-1)
      else
        fallback()
      end
    end, { 'i', 's' }),
  },
  sources = {
    { name = 'nvim_lsp' },
    -- { name = 'luasnip' },
    --{ name = 'buffer' },
    --{ name = 'path' },
    --{ name = 'cmdline' },
  },
}
-- Set configuration for specific filetype.
cmp.setup.filetype('gitcommit', {
  sources = cmp.config.sources({
    { name = 'git' }, -- You can specify the `git` source if [you were installed it](https://github.com/petertriho/cmp-git).
  }, {
    { name = 'buffer' },
  }),
})

-- Use buffer source for `/` and `?` (if you enabled `native_menu`, this won't work anymore).
cmp.setup.cmdline({ '/', '?' }, {
  mapping = cmp.mapping.preset.cmdline(),
  sources = {
    { name = 'buffer' },
  },
})

-- Use cmdline & path source for ':' (if you enabled `native_menu`, this won't work anymore).
cmp.setup.cmdline(':', {
  mapping = cmp.mapping.preset.cmdline(),
  sources = cmp.config.sources({
    { name = 'path' },
  }, {
    { name = 'cmdline' },
  }),
})

local status, null_ls = pcall(require, 'null-ls')
if not status then
  vim.notify '没有找到 null-ls'
  return
end

local formatting = null_ls.builtins.formatting
local function get_indentation(lang)
  if lang == 'c' or lang == 'cpp' then
    return 4 -- C 和 C++ 使用 4 个空格缩进
  elseif lang == 'python' then
    return 4 -- Python 使用 2 个空格缩进
  else
    return 8 -- 默认使用 2 个空格缩进
  end
end
local current_filetype = vim.bo.filetype
local indent = get_indentation(current_filetype)
local format_opts = {
    tabWidth = 4,
    insertSpaces = true,
}
null_ls.setup {
  debug = true,
  sources = {
    null_ls.builtins.code_actions.gitsigns,
    -- Formatting ---------------------
    --  brew install shfmt
    formatting.shfmt,
    -- StyLua
    formatting.stylua,
    -- frontend
    formatting.prettier.with {
      -- 只比默认配置少了 markdown
      filetypes = {
        'javascript',
        'javascriptreact',
        'typescript',
        'typescriptreact',
        'vue',
        'css',
        'scss',
        'less',
        'html',
        'json',
        'yaml',
        'graphql',
        'c',
        'cpp',
      },
      prefer_local = 'node_modules/.bin',
      args = { '--tab-width', '4' },
    },

    null_ls.builtins.diagnostics.eslint,
    null_ls.builtins.completion.spell,
    -- formatting.fixjson,
    -- formatting.black.with({ extra_args = { "--fast" } }),
  },
  -- 保存自动格式化
  on_attach = function(client)
    --client.offset_encoding = 'utf-16' -- 可能没有用
    if client.server_capabilities.documentFormattingProvider then
      local pos = vim.fn.getpos '.'
      --vim.cmd 'autocmd BufWritePre <buffer> lua vim.lsp.buf.format(format_opts)'
      vim.fn.setpos('.', pos)
    end
  end,
}
--
-- 这里有bug，C语言格式化的时候，会将缩进设置为两个空格
--
-- The line beneath this is called `modeline`. See `:help modeline`
-- vim: ts=2 sts=2 sw=2 et
-- 让nvim回到上次关闭时的位置
local group = vim.api.nvim_create_augroup('jump_last_position', { clear = true })
vim.api.nvim_create_autocmd('BufReadPost', {
  callback = function()
    local row, col = unpack(vim.api.nvim_buf_get_mark(0, '"'))
    if { row, col } ~= { 0, 0 } then
      vim.api.nvim_win_set_cursor(0, { row, 0 })
    end
  end,
  group = group,
})

-- 为源代码添加作者，邮箱，时间等信息
vim.cmd [[
autocmd BufNewFile *.cc,*.cpp,*.[ch],*.sh,*.java,*.go exec ":call SetTitle()"
  """定义函数SetTitle，自动插入文件头
func SetTitle()
    "如果文件类型为.sh文件
    if &filetype == 'sh'
        call setline(1,"\#########################################################################")
        call append(line("."),   "\# File Name:    ".expand("%"))
        call append(line(".")+1, "\# Author:       suyelu")
        call append(line(".")+2, "\# mail:         suyelu@hotmail.com")
        call append(line(".")+3, "\# Created Time: ".strftime("%c"))
        call append(line(".")+4, "\#########################################################################")
        call append(line(".")+5, "\#!/bin/bash")
        call append(line(".")+6, "")
    else
        call setline(1, "/* ************************************************************************")
        call append(line("."),   "    > File Name:     ".expand("%"))
        call append(line(".")+1, "    > Author:        suyelu")
        call append(line(".")+2, "    > mail:          suyelu@hotmail.com")
        call append(line(".")+3, "    > Created Time:  ".strftime("%c"))
        call append(line(".")+4, "    > Description:   ")
        call append(line(".")+5, " ************************************************************************/")
        call append(line(".")+6, "")
    endif
    "如果文件为.c 文件，则插入 #include <stdio.h>这个头文件
   if &filetype == 'c'
     call append(line(".")+7, "#include <stdio.h>")
     call append(line(".")+8, "")
endif
 if &filetype == "cc"
     call append(line(".")+7, "#include <iostream>")
     call append(line(".")+8, "using namespace std;")
  endif
 if &filetype == "cpp"
     call append(line(".")+7, "#include <iostream>")
     call append(line(".")+8, "using namespace std;")
  endif
endfunc
    "新建文件后，自动定位到文件末尾
    autocmd BufNewFile * normal G
]]

vim.cmd [[
autocmd BufNewFile *.h,*.hpp exec ":call AddHHeader()"
func AddHHeader()
    let macro = "_".toupper(substitute(expand("%"), "[/.]", "_", "g"))."_"
    "normal o
    call setline(9, "#ifndef ".macro)
    call setline(10, "#define ".macro)
    call setline(11, "")
    call setline(12, "#endif  // ".macro)
endfunc
  autocmd BufNewfile * normal 11G
]]
