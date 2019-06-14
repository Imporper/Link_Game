#pragma once
#include"global.h"
#include"CGraph.h"
/*class CGameLogic
{
public:
	Vertex m_avPath[4];
	int m_nVexNum;
	void Clear(int pGameMap[10][16], Vertex v1, Vertex v2);
	int GetVexPath(Vertex avPath[4]);
	bool LinkInRow(int pGameMap[10][16], Vertex v1, Vertex v2);
	bool LinkInCol(int pGameMap[10][16] , Vertex v1, Vertex v2);
	bool OneCornerLink(int pGameMap[10][16] , Vertex v1, Vertex v2);
	bool LineY(int pGameMap[10][16] , int nRow1, int nRow2, int nCol);
	bool LineX(int pGameMap[10][16], int nRow, int nCol1, int nCol2);
	void PushVertex(Vertex v);
	void PopVertex();
	void ClearStack();
	bool TwoCornerLink(int pGameMap[10][16], Vertex v1, Vertex v2);
	int pGameMap[10][16];
	void InitMap();
	void ReleaseMap(int pGameMap[10][16]);
	bool Link(Vertex avPath[4], int &nVexnum);
	CGameLogic();
	~CGameLogic();*/

class CGameLogic
{
protected:
	Vertex m_avPath[MAX_VERTEX_NUM];    //保存连接路径的起始点、拐点、终点
	int m_anPath[MAX_VERTEX_NUM];		//保存在进行连接判断时所经过的顶点
	int m_nCorner;						//保存路径中的拐点数
	int m_nVexNum;						//表示顶点数

public:

	CGameLogic();
	~CGameLogic(); 
	//初始化游戏地图
	void InitMap(CGraph &graph);

	//生成图的边的数组，更新边
	void UpdateArc(CGraph &graph, int nRow, int nCol);

	//连接判断函数
	bool IsLink(CGraph &graph, Vertex v1, Vertex v2);

	//消子函数
	void Clear(CGraph &graph, Vertex v1, Vertex v2);


	//判断选择的两个顶点是否联通
	bool SearchPath(CGraph &graph, int nV0, int nV1);

	//判断顶点是否已在路径中存在
	bool IsExsit(int nVi);

	//判断拐点的有效性
	bool IsCornor(void);

	//添加一个路径顶点
	void PushVertex(int v);

	//取出一个路径顶点
	void PopVertex();

	//得到路径，返回的是顶点数
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);

	////判断图中顶点是不是全是空
	bool IsBlank(CGraph &graph);

	//提示算法，
	bool SearchValidPath(CGraph &graph);

	//实现图结构的重排
	void ResetGraph(CGraph& graph);
};