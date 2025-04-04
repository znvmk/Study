"1.Startup-编辑启动时需要添加的一些配置
"2.General-通用配置
"3.Lang&Encoding-语言和编码
"4.GUI-界面
"5.Format-基本的代码格式
"6.Keymap-通用的快捷键
"7.Plugin-插件相关（包括当前插件相关配置和快捷键等）
"8.File-文件处理
"9.Function-vimrcl里面常用的方法
"10.Display-显示相关


"2.General-通用配置

"去掉讨厌的有关vi一致性模式，避免以前版本的一些bug和局限
set nocompatible
"从不备份
set nobackup
set noswapfile
" 历史记录数
set history=1024
set autochdir
" 允许backspace和光标键跨越行边界(不建议)
"set whichwrap = b,s,'<,>,h,l,[,]
set nobomb
" 使回格键（backspace）正常处理indent, eol, start等
set backspace=indent,eol ",start whichwrp+=<,>,[,]
"Vim的默认寄存器和系统的剪切板共享
set clipboard+=unnamed
"设置Alt键不映射到菜单栏
set winaltkeys=no
set backspace=2	"backspace键失效问题



"3.Lang&Encoding-语言和编码
set fileencodings=utf-8,gbk2312,gbk,gb18030,cp936,ucs-bom
set fencs=utf-8,ucs-bom,shift-jis,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8
set fileencoding=utf-8

"4.GUI-界面

"1.设定启动窗口
winpos 400 0       " 设定窗口位置
set lines=45 columns=75    " 设定窗口大小
"2.不显示工具/菜单栏
set guioptions-=T
set guioptions-=m
set guioptions-=L
set guioptions-=r
set guioptions-=b
" 使用内置 tab 样式而不是 gui
set guioptions-=e
set nolist
set listchars=tab:▶\ ,eol:¬,trail:·,extends:>,precedes:<
set guifont=Inconsolata:h12:cANSI
set go=             " 不要图形按钮
"3.菜单语言设置
set langmenu=zh_CN.UTF-8
set helplang=cn
"4.文本设置
set shortmess=atI   " 启动的时候不显示那个援助乌干达儿童的提示
set nu              " 显示行号
set guifont=Courier_New:h10:cANSI   " 设置字体
syntax on           " 语法高亮
syntax enable
autocmd InsertLeave * se nocul  " 用浅色高亮当前行
autocmd InsertEnter * se cul    " 用浅色高亮当前行
set ruler           " 显示标尺
set showcmd         " 输入的命令显示出来，看的清楚些
set cmdheight=1     " 命令行（在状态行下）的高度，设置为1
set scrolloff=3     " 光标移动到buffer的顶部和底部时保持3行距离
set novisualbell    " 不要闪烁(不明白)
set statusline=%F%m%r%h%w\ [FORMAT=%{&ff}]\ [TYPE=%Y]\ [POS=%l,%v][%p%%]\ %{strftime(\"%d/%m/%y\ -\ %H:%M\")}   "状态行显示的内容
" 我的状态行显示的内容（包括文件类型和解码）
set statusline=%F%m%r%h%w\ [FORMAT=%{&ff}]\ [TYPE=%Y]\ [POS=%l,%v][%p%%]\ %{strftime(\"%d/%m/%y\ -\ %H:%M\")}
set statusline=[%F]%y%r%m%*%=[Line:%l/%L,Column:%c][%p%%]
set laststatus=2    " 启动显示状态行(1),总是显示状态行(2)
" 命令行（在状态行下）的高度，默认为1，这里是2
set cmdheight=2
set cursorline              " 突出显示当前行
" 高亮显示匹配的括号
set showmatch
" 匹配括号高亮的时间（单位是十分之一秒）
set matchtime=1
" 在被分割的窗口间显示空白，便于阅读
set fillchars=vert:\ ,stl:\ ,stlnc:\
" 高亮显示普通txt文件（需要txt.vim脚本）
au BufRead,BufNewFile *  setfiletype txt
"5.vim文件折叠方式为marker
set fdm=marker
set foldenable      " 允许折叠
set foldmethod=manual   " 手动折叠
set foldmethod=indent
set background=dark "背景使用黑色
" 显示中文帮助
if version >= 603
    set helplang=cn
	set encoding=utf-8

endif



"6.设置配色方案
"colorscheme murphy
colorscheme 0
"字体
if (has("gui_running"))
   set guifont=Bitstream\ Vera\ Sans\ Mono\ 10
endif
"分割出来的窗口位于当前窗口的右/下边
set splitright
set splitbelow
"Format-基本的代码格式
" 自动缩进
set autoindent
set cindent
" Tab键的宽度
set tabstop=4
" 统一缩进为4
set softtabstop=4
set expandtab
set shiftwidth=4
" 不要用空格代替制表符
set noexpandtab
" 在行和段开始处使用制表符
set smarttab
"Keymap-通用的快捷键
let mapleader=","
map <S-Insert>        "+gP
map <leader>tn :tabnew<cr>
map <leader>tc :tabclose<cr>
map <leader>th :tabp<cr>
map <leader>tl :tabn<cr>
"新建标签
map <M-F2> :tabnew<CR>
"列出当前目录文件
map <F3> :tabnew .<CR>
"打开树状文件目录
map <C-F3> \be
" 映射全选+复制 ctrl+a
map <C-A> ggVGY
map! <C-A> <Esc>ggVGY
map <F12> gg=G
"C，C++ 按F5编译运行
map <F5> :call CompileRunGcc()<CR>
func! CompileRunGcc()
    exec "w"
    if &filetype == 'c'
        exec "!g++ % -o %<"
        exec "! ./%<"
    elseif &filetype == 'cpp'
        exec "!g++ % -o %<"
        exec "! ./%<"
    elseif &filetype == 'java'
        exec "!javac %"
        exec "!java %<"
    elseif &filetype == 'sh'
        :!./%
    endif
endfunc

"C,C++的调试
map <F8> :call Rungdb()<CR>
func! Rungdb()
    exec "w"
    exec "!g++ % -g -o %<"
    exec "!gdb ./%<"
endfunc
" 打开当前目录 windows
map <leader>ex :!start explorer %:p:h<CR>
" 打开当前目录CMD
map <leader>cmd :!start<cr>
" 打印当前时间
map <F3> a<C-R>=strftime("%Y-%m-%d %a %I:%M %p")<CR><Esc>
nmap <leader>w :w!<cr>
nmap <leader>f :find<cr>
nmap <leader>s :source $VIM/_vimrc<cr>
nmap <leader>e :e $VIM/_vimrc<cr>
" 移动分割窗口
nmap <C-j> <C-W>j
nmap <C-k> <C-W>k
nmap <C-h> <C-W>h
nmap <C-l> <C-W>l
" 复制当前文件/路径到剪贴板
nmap ,fn :let @*=substitute(expand("%"), "/", "\\", "g")<CR>
nmap ,fp :let @*=substitute(expand("%:p"), "/", "\\", "g")<CR>



" 正常模式下 alt+j,k,h,l 调整分割窗口大小
nnoremap <M-j> :resize +5<cr>
nnoremap <M-k> :resize -5<cr>
nnoremap <M-h> :vertical resize -5<cr>
nnoremap <M-l> :vertical resize +5<cr>
"去空行
nnoremap <F2> :g/^\s*$/d<CR>
"比较文件
nnoremap <C-F2> :vert diffsplit
nnoremap vv ^vg_
nnoremap <F2> :setlocal number!<cr>
nnoremap <leader>w :set wrap!<cr>
" 设置切换Buffer快捷键"
nnoremap <C-left> :bn<CR>
nnoremap <C-right> :bp<CR>
imap <C-v> "+gP
" 插入模式移动光标 alt + 方向键
inoremap <M-j> <Down>
inoremap <M-k> <Up>
inoremap <M-h> <left>
inoremap <M-l> <Right>
" IDE like delete
inoremap <C-BS> <Esc>bdei
" 转换当前行为大写
inoremap <C-u> <esc>mzgUiw`za


" 命令模式下的行首尾
cnoremap <C-a> <home>
cnoremap <C-e> <end>
cmap <C-V>        <C-R>+
cmap <S-Insert>        <C-R>+

" 选中状态下 Ctrl+c 复制
vmap <C-c> "+y
vnoremap <BS> d
vnoremap <C-C> "+y
vnoremap <C-Insert> "+y

"8.File-文件处理

"新建.c,.h,.sh,.java文件，自动插入文件头
autocmd BufNewFile *.cpp,*.[ch],*.sh,*.java exec ":call SetTitle()"
""定义函数SetTitle，自动插入文件头
func SetTitle()
    "如果文件类型为.sh文件
    if &filetype == 'sh'
        call setline(1,"\#########################################################################")
        call append(line("."), "\# File Name: ".expand("%"))
        call append(line(".")+1, "\# Author: zn")
        call append(line(".")+2, "\# mail: zn@163.com")
        call append(line(".")+3, "\# Created Time: ".strftime("%c"))
        call append(line(".")+4, "\#########################################################################")
        call append(line(".")+5, "\#!/bin/bash")
        call append(line(".")+6, "")
    else
        call setline(1, "/*************************************************************************")
        call append(line("."), "    > File Name: ".expand("%"))
        call append(line(".")+1, "    > Author: zn")
        call append(line(".")+2, "    > Mail: zn@163.com ")
        call append(line(".")+3, "    > Created Time: ".strftime("%c"))
        call append(line(".")+4, " ************************************************************************/")
        call append(line(".")+5, "")
    endif
    if &filetype == 'cpp'
        call append(line(".")+6, "#include <iostream>")
        "call append(line(".")+7, "using namespace std;")
        call append(line(".")+8, "")
    endif
    if &filetype == 'c'
        call append(line(".")+6, "#include <stdio.h>")
        call append(line(".")+7, "")
    endif
    "新建文件后，自动定位到文件末尾
    autocmd BufNewFile * normal G
endfunc

"搜索忽略大小写
set ignorecase
"搜索逐字符高亮
set hlsearch
set incsearch
" 侦测文件类型
filetype on
" 为特定文件类型载入相关缩进文件
filetype indent on
"自动保存
set autowrite
" 在处理未保存或只读文件的时候，弹出确认
set confirm
"自动补全
:inoremap ( ()<ESC>i
:inoremap ) <c-r>=ClosePair(')')<CR>
:inoremap { {<CR>}<ESC>O
:inoremap { {}<ESC>i
:inoremap } <c-r>=ClosePair('}')<CR>
:inoremap [ []<ESC>i
:inoremap ] <c-r>=ClosePair(']')<CR>
:inoremap " ""<ESC>i
:inoremap ' ''<ESC>i
:inoremap [ []<LEFT>

function! ClosePair(char)
    if getline('.')[col('.') - 1] == a:char
        return "\<Right>"
    else
        return a:char
    endif
endfunction
" 设置当文件被改动时自动载入
set autoread
" quickfkix模式
autocmd FileType c,cpp map <buffer> <leader><space> :w<cr>:make<cr>
"代码补全
set completeopt=preview,menu
" 为C程序提供自动缩进
set smartindent
"打开文件类型检测, 加了这句才可以用智能补全
set completeopt=longest,menu
"make 运行
:set makeprg=g++\ -Wall\ \ %
set magic                   " 设置魔术
set statusline=\ %<%F[%1*%M%*%n%R%H]%=\ %y\ %0(%{&fileformat}\ %{&encoding}\ %c:%l/%L%)\
" 设置在状态行显示的信息
set foldcolumn=0
set foldlevel=3
set foldenable              " 开始折叠
" 不要使用vi的键盘模式，而是vim自己的
" 去掉输入错误的提示声音
set noeb
"行内替换
set gdefault
" 保存全局变量
set viminfo+=!
" 带有如下符号的单词不要被换行分割
set iskeyword+=_,$,@,%,#,-
" 字符间插入的像素行数目
set linespace=0
" 增强模式中的命令行自动完成操作
set wildmenu
" 可以在buffer的任何地方使用鼠标（类似office中在工作区双击鼠标定位）
set mouse=a
set selection=exclusive
set selectmode=mouse,key
" 通过使用: commands命令，告诉我们文件的哪一行被改变过
set report=0
" 光标移动到buffer的顶部和底部时保持3行距离
set scrolloff=2


" CTags的设定
"let Tlist_Sort_Type = "name"    " 按照名称排序
"let Tlist_Use_Right_Window = 1  " 在右侧显示窗口
"let Tlist_Compart_Format = 1    " 压缩方式
"let Tlist_Exist_OnlyWindow = 1  " 如果只有一个buffer，kill窗口也kill掉buffer
"let Tlist_File_Fold_Auto_Close = 0  " 不要关闭其他文件的tags
"let Tlist_Enable_Fold_Column = 0    " 不要显示折叠树
"iautocmd FileType java set tags+=D:\tools\java\tags
"autocmd FileType h,cpp,cc,c set tags+=D:\tools\cpp\tags
"let Tlist_Show_One_File=1            "不同时显示多个文件的tag，只显示当前文件的
"设置tags
"set tags=tags
"默认打开Taglist
"let Tlist_Auto_Open=1
" Tag list (ctags)
"let Tlist_Ctags_Cmd = '/usr/bin/ctags'
"let Tlist_Show_One_File = 1 "不同时显示多个文件的tag，只显示当前文件的
"let Tlist_Exit_OnlyWindow = 1 "如果taglist窗口是最后一个窗口，则退出vim
"let Tlist_Use_Right_Window = 1 "在右侧窗口中显示taglist窗口
" minibufexpl插件的一般设置
"let g:miniBufExplMapWindowNavVim = 1
"let g:miniBufExplMapWindowNavArrows = 1
"let g:miniBufExplMapCTabSwitchBufs = 1
"let g:miniBufExplModSelTarget = 1

"Plugin-插件相关（包括当前插件相关配置和快捷键等）
"设置插件
"filetype plugin on		"允许插件
"filetype plugin indent on
"let Tlist_Show_One_File=1
"let Tlist_Exit_OnlyWindow=1
"let g:winManagerWindowLayout='FileExplorer|TagList'
"nmap wm :WMToggle<cr>
" 将Vundle插件的目录添加到gvim的运行时变量中
"set rtp+=$VIM/Vundle.vim/
"vundle start
"set nocompatible " be iMproved, required
"filetype off                  " required，不要关闭，否则关键字高亮失效
"filetype plugin indent on    " required

"添加、启动插件
"call vundle#begin('$USERPROFILE/.vim/bundle/')	" required
"查看所有插件：BundleList，添加插件：BundleInstall，更新插件：BundleUpdate，查找插件：BundleSearch
"Plugin 'VundleVim/Vundle.vim'
"Plugin 'scrooloose/nerdtree'
"Plugin 'jistr/vim-nerdtree-tabs'
"call vundle#end()            " required

"设置插件快捷键
"autocmd vimenter * NERDTree
"map <F2> :NERDTreeToggle<CR>
"设置插件属性
" 显示行号
"let NERDTreeShowLineNumbers=1
"let NERDTreeAutoCenter=1
" 是否显示隐藏文件
"let NERDTreeShowHidden=1
" 设置宽度
"let NERDTreeWinSize=21
" 在终端启动vim时，共享NERDTree
"let g:nerdtree_tabs_open_on_console_startup=1
" 忽略一下文件的显示
"let NERDTreeIgnore=['\.pyc','\~$','\.swp']
" 显示书签列表
"let NERDTreeShowBookmarks=1


