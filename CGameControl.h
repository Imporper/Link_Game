#pragma once
#include "CGameLogic.h"
#include"global.h"
#include "CGraph.h"
/*class CGameControl
{
public:
	static int s_nRows;
	static int s_nCols;
	static int s_nPicNum;
	void StartGame(void);
	int GetElement(int nRow, int nCol);
	Vertex m_svSelFst;
	Vertex m_svSelSec;
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[4], int &nVexnum);
	CGameControl();
	~CGameControl();
};*/



class CGameControl
{
public:
	CGameControl();
	~CGameControl();

protected:
	CGraph m_graph;			//初始游戏地图
	Vertex m_ptSelFirst;	//第一次选中的点(x表示列)
	Vertex m_ptSelSec;		//第二次选中的点

public:
	//开始游戏函数
	void StartGame(void);
	//通关
	void clearMap();
	//获得某行某列的图片编号函数
	int GetElement(int nRow, int nCol);

	void SetFirstPoint(int nRow, int nCol);             //设置第一个点函数
	void SetSecPoint(int nRow, int nCol);               //设置第二个点函数

	//连接判断函数
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);

	//获胜
	bool IsWin();

	//帮助、提示方法
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);

	//实现重排功能
	void Reset(void);



};

