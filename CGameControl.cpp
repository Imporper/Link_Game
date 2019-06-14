#include "stdafx.h"
#include "CGameControl.h"

#include"LLKDlg.h"

CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

void CGameControl::StartGame()
{
	CGameLogic m_GameLogic;
	m_GameLogic.InitMap(m_graph);
}

void CGameControl::clearMap()
{
	m_graph.ClearGraph();
}

int CGameControl::GetElement(int nRow, int nCol)
{
	
	return m_graph.GetVertex(nRow * MAX_COL + nCol);
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

//���õڶ����㺯��
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

//�����ж�   �����жϺ���
bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM], int & nVexnum)
{

	//�ж�ѡ�еĵ��Ƿ�Ϊͬһ��ͼƬ����Ϊͬһ��ͼƬ��������ͨ
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	//�ж�ͼƬ�Ƿ���ͬ�������ͬ������ͨ
	int	nInfo1 = m_graph.GetVertex(m_ptSelFirst.row * MAX_COL + m_ptSelFirst.col);
	int	nInfo2 = m_graph.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col);

	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
	{
		return false;
	}

	//�ж��Ƿ������ͨ
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		//����
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);


		//����·������
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}

	return false;
}

//�ж��Ƿ��ʤ
bool CGameControl::IsWin()
{
	
	
		// TODO: �ڴ˴����ʵ�ִ���.
		CGameLogic logic;
		if (logic.IsBlank(m_graph) == true) {
			m_graph.ClearGraph(); //����ͼ�ṹ��
			
			return true;
		}
	
		return false;
	
}

//��ʾ��ť����ʵ��
bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM], int & nVexnum)
{
	CGameLogic logic;

	//�ж��Ƿ�Ϊ��
	if (logic.IsBlank(m_graph) == true)
	{
		return false;
	}
	//����һ����Ч����ʾ·��
	if (logic.SearchValidPath(m_graph))
	{
		//����·������
		nVexnum = logic.GetVexPath(avPath);

		return true;
	}
	return false;

}

//ʵ�����Ź���
void CGameControl::Reset(void)
{
	//����ͼ�ж���
	CGameLogic logic;
	logic.ResetGraph(m_graph);
}