#pragma once
class CGOProcess
{
public:
	CGOProcess();
	virtual ~CGOProcess();

public:
	int GOMap[19][19] = { 0 };
	//0:对局未开始，1：黑方，2：白方，3：对局结束
	int flag;
	//步数
	int step;
	//黑棋吃子
	int BlackTaking;
	//白棋吃子
	int WhiteTaking;
	//黑棋用时
	int BlackTime;
	//白棋用时
	int WhiteTime;
	//单步用时
	int stepTime;
	//贴目
	float komi;

	//上一手棋子位置坐标
	int coordinateX1;
	int coordinateY1;

	//当前棋子位置坐标
	int coordinateX2 ;
	int coordinateY2 ;

	
public:
	void GameStart();
	//转换时间
	CString TimeConvert(int seconds);

};

