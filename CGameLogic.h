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
	Vertex m_avPath[MAX_VERTEX_NUM];    //��������·������ʼ�㡢�յ㡢�յ�
	int m_anPath[MAX_VERTEX_NUM];		//�����ڽ��������ж�ʱ�������Ķ���
	int m_nCorner;						//����·���еĹյ���
	int m_nVexNum;						//��ʾ������

public:

	CGameLogic();
	~CGameLogic(); 
	//��ʼ����Ϸ��ͼ
	void InitMap(CGraph &graph);

	//����ͼ�ıߵ����飬���±�
	void UpdateArc(CGraph &graph, int nRow, int nCol);

	//�����жϺ���
	bool IsLink(CGraph &graph, Vertex v1, Vertex v2);

	//���Ӻ���
	void Clear(CGraph &graph, Vertex v1, Vertex v2);


	//�ж�ѡ������������Ƿ���ͨ
	bool SearchPath(CGraph &graph, int nV0, int nV1);

	//�ж϶����Ƿ�����·���д���
	bool IsExsit(int nVi);

	//�жϹյ����Ч��
	bool IsCornor(void);

	//���һ��·������
	void PushVertex(int v);

	//ȡ��һ��·������
	void PopVertex();

	//�õ�·�������ص��Ƕ�����
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);

	////�ж�ͼ�ж����ǲ���ȫ�ǿ�
	bool IsBlank(CGraph &graph);

	//��ʾ�㷨��
	bool SearchValidPath(CGraph &graph);

	//ʵ��ͼ�ṹ������
	void ResetGraph(CGraph& graph);
};