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
	CGraph m_graph;			//��ʼ��Ϸ��ͼ
	Vertex m_ptSelFirst;	//��һ��ѡ�еĵ�(x��ʾ��)
	Vertex m_ptSelSec;		//�ڶ���ѡ�еĵ�

public:
	//��ʼ��Ϸ����
	void StartGame(void);
	//ͨ��
	void clearMap();
	//���ĳ��ĳ�е�ͼƬ��ź���
	int GetElement(int nRow, int nCol);

	void SetFirstPoint(int nRow, int nCol);             //���õ�һ���㺯��
	void SetSecPoint(int nRow, int nCol);               //���õڶ����㺯��

	//�����жϺ���
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);

	//��ʤ
	bool IsWin();

	//��������ʾ����
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);

	//ʵ�����Ź���
	void Reset(void);



};

