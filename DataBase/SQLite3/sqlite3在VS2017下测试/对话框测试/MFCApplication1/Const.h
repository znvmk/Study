#pragma once

class Const
{
public:
	// 格
	static const int GRID_SIZE = 26; 						// 尺寸

	// 方块
	static const int BLOCK_GRID_COUNT_H = 4; 				// 一个方向由
	static const int BLOCK_GRID_COUNT_V = 4;				// 4*4的格组成

	// 游戏区域
	static const int GAMEBOARD_X = 20; 						// 游戏区域左上角坐标
	static const int GAMEBOARD_Y = 20;
	static const int GAMEBOARD_GRID_COUNT_H = 10; 			// 横向方块数
	static const int GAMEBOARD_GRID_COUNT_V = 20; 			// 纵向方块数
	static const int GAMEBOARD_WIDTH = 
		GRID_SIZE * GAMEBOARD_GRID_COUNT_H;					// 游戏区域宽度
	static const int GAMEBOARD_HEIGHT = 
		GRID_SIZE * GAMEBOARD_GRID_COUNT_V;					// 游戏区域高度
	static const COLORREF GAMEBOARD_COLOR = 
		RGB(255, 255, 255); 								// 游戏区域背景色

	// 预览区域
	static const int PREVIEW_X = GAMEBOARD_X + GAMEBOARD_WIDTH + GRID_SIZE;
	static const int PREVIEW_Y = GAMEBOARD_Y;		 		// 预览区域左上角坐标
	static const int PREVIEW_WIDTH = GRID_SIZE * 5; 		// 预览区域宽度
	static const int PREVIEW_HEIGHT = GRID_SIZE * 5; 		// 预览区域高度
	static const int PREVIEW_COLOR = RGB(255, 255, 255); 	// 预览区域背景色
	
	// 时钟
	static const int TIMER_ID = WM_USER + 1; 				// 时钟 ID
	static const int TIMER_INIT = 1000; 					// 初始时钟间隔，单位毫秒

	// 事件
	static const int UM_SCORE = WM_USER + 2; 				// 得分
	static const int UM_DIFFICULTYUP = WM_USER + 3; 		// 难度增加
	static const int UM_GAMEOVER = WM_USER + 4; 			// 游戏结束

	// 难度
	static const int DIFF_BASE = 5000; 						// 难度基数，每5000分难度增加
	static const int DIFF_MAX = 10;							// 难度最大值

	// 字符串
	static const int STRING_MAX_LEN = 20;					// 字符串最大长度

	// 数据库
	static LPCTSTR DATABASE_FILE;							// 数据库文件名

	// 数据库表
	static LPCTSTR TABLE_USER;								// 用户表名

	// 数据库字段
	static LPCTSTR FIELD_USERNAME;							// 用户名
	static const int MAX_USERNAME_LEN = 10;					// 用户名最大长度（单位：字符）
	static LPCTSTR FIELD_SCORE;								// 最高得分

	// 排行榜的列表控件
	static const int LISTCTRL_COLUMN_WIDTH_RANK = 40;		// “排名”表头的宽度
	static const int LISTCTRL_COLUMN_WIDTH_USERNAME = 140;	// “用户名”表头的宽度
	static const int LISTCTRL_COLUMN_WIDTH_SCORE = 100;		// “得分”表头的宽度

	// 用户
	static const int USER_MAX_COUNT = 10;					// 最大用户数
};
