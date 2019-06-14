// CGameDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include   <mmsystem.h>  
#pragma   comment(lib,   "Winmm.lib")  

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//初始化起始点坐标
	m_ptGameTop.x = 20;
	m_ptGameTop.y = 50;

	//初始化图片元素大小
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * 17;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * 10;

	//初始化图标选中状态
	m_bFirstPoint = true;
	m_bPlaying = false;
}

CGameDlg::~CGameDlg()
{
}

bool CGameDlg::getStatus()
{
	return this->m_bPlaying;
}




BOOL  CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->SetWindowTextW(_T("欢乐连连看　基本模式"));
	InitBackground();
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::InitBackground()
{	// TODO: 在此处添加实现代码.

	//加载BMP图片资源
	HANDLE Backbmp = ::LoadImage(NULL, _T("theme\\picture\\back_ground.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//获得当前对话框的视频内容
	CClientDC dc(this);

	//创建与视频内容兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcBG.SelectObject(Backbmp);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//hu绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
	this->GetDlgItem(IDC_BTN_WIN)->EnableWindow(false);
	//设置窗口大小
	UpdateWindow();
}


void CGameDlg::InitElement(void)
{
	CClientDC dc(this);
	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\Cat.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElm.CreateCompatibleDC(&dc);
	m_dcElm.SelectObject(hBmp);
	HANDLE hMask = ::LoadImageW(NULL, _T("theme\\picture\\Cat_Elem.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);
}

void CGameDlg::OnPaint()
{
	
		CPaintDC dc(this);
		dc.CDC::BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
	
}

void CGameDlg::OnBnClickedBtnStart()
{
	m_gameControl.StartGame();

	//判断是否正在玩游戏
	m_bPlaying = true;
	m_Hit = false;
	this->GetDlgItem(IDC_BTN_Start)->EnableWindow(false);
	this->GetDlgItem(IDC_BTN_WIN)->EnableWindow(true);
	//更新地图
	UpdateMap();

	//更新窗口
	Invalidate(FALSE);
}

void CGameDlg::UpdateWindow(void)
{
	// 调整窗口大小     
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();     
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


void CGameDlg::UpdateMap()
{
		int nTop = m_ptGameTop.y;
		int nLeft = m_ptGameTop.x;
		int nElemW = m_sizeElem.cx;
		int nElemH = m_sizeElem.cy;

		m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
			m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

		for (int i = 0; i < MAX_ROW; i++) {
			for (int j = 0; j < MAX_COL; j++) {
				int nInfo = m_gameControl.GetElement(i, j);       //当前元素图片的数值
				if (nInfo == BLANK)  continue;
				//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElm, 0, m_anMap[i][j] * nElemH, SRCCOPY);

				//将背景与掩码相或，边保留，图像区域为1
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo * nElemH, SRCPAINT);

				//将元素图片相与，边保留，图像区域为元素图片
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElm, 0, nInfo * nElemH, SRCAND);

			}
		}
	}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_Start, &CGameDlg::OnBnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_Tips, &CGameDlg::OnBnClickedBtnTips)
	ON_BN_CLICKED(IDC_BTN_Restart, &CGameDlg::OnBnClickedBtnRestart)
	ON_BN_CLICKED(IDC_BTN_WIN, &CGameDlg::OnBnClickedBtnWin)
	ON_BN_CLICKED(IDC_BTN_OpenMusic, &CGameDlg::OnBnClickedBtnOpenmusic)
	ON_BN_CLICKED(IDC_BTN_CloseMusic, &CGameDlg::OnBnClickedBtnClosemusic)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonUp(nFlags, point);

	if (point.y < m_rtGameRect.top || point.y > m_rtGameRect.bottom || point.x < m_rtGameRect.left || point.x > m_rtGameRect.right)
		return CDialogEx::OnLButtonUp(nFlags, point);
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;

	//列
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (m_bFirstPoint)
	{
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else
	{
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);
		Vertex avPath[MAX_VERTEX_NUM];     //获得路径   
		int nVexnum = 0;      //顶点个数

		//判断是否是相同图片	
		if (m_gameControl.Link(avPath, nVexnum)) {

			//画提示线
			DrawTipLine(avPath, nVexnum);

			//更新地图
			UpdateMap();
		}
		Sleep(200);    //延迟
		InvalidateRect(m_rtGameRect, FALSE); //局部矩形更新

		//判断胜负
		if (m_gameControl.IsWin()&&m_bPlaying==true) {
			MessageBox(_T("\t获胜！"), _T("欢乐连连看　基本模式"));
			m_bPlaying = false;
			this->GetDlgItem(IDC_BTN_Start)->EnableWindow(true); //游戏结束，将【开始游戏】按钮设置为可点击状态

			return;
		}
	}
		m_bFirstPoint = !m_bFirstPoint; //赋反值，区分第二次点击

		CDialogEx::OnLButtonUp(nFlags, point);
}
//绘制点击框
void CGameDlg::DrawTipFrame(int nRow, int nCol) {
	if (m_bPlaying == true&&m_Hit==false) {
		CClientDC dc(this);
		CBrush brush(RGB(233, 43, 43));
		CRect rtTipFrame;
		rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
		rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
		rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
		rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
		dc.FrameRect(rtTipFrame, &brush);
	}
	else return;
}

	//绘制提示线
void CGameDlg::DrawTipLine(Vertex avPath[MAX_VERTEX_NUM], int nVexnum)
{
		//获取DC
		CClientDC dc(this);

		//设置画笔
		CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

		//将画笔选入DC
		CPen* pOldPen = dc.SelectObject(&penLine);

		dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
		//绘制连接线
		for (int i = 0; i < nVexnum - 1; i++)
		{

			dc.LineTo(m_ptGameTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
				m_ptGameTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
		}

		dc.SelectObject(pOldPen);
}

void CGameDlg::OnBnClickedBtnTips()
{
	// TODO: 在此添加控件通知处理程序代码
	//如果没有进行游戏，则返回
	if (m_bPlaying == false)
		return;

	//如果能够连通，绘制提示框和连接线并更新游戏地图
	Vertex avPath[MAX_VERTEX_NUM];     //获得路径
	int nVexnum = 0;      //顶点个数
	if (m_gameControl.Help(avPath, nVexnum))
	{

		//画第一个点的提示框
		DrawTipFrame(avPath[0].row, avPath[0].col);

		//画第一个点的提示框
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);
		
		//画提示线
		DrawTipLine(avPath, nVexnum);
		
			Sleep(200);    //延迟
			m_gameControl.SetFirstPoint(avPath[0].row, avPath[0].col);
			m_gameControl.SetSecPoint(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);
			if (m_gameControl.Link(avPath, nVexnum))
			UpdateMap();	//更新地图

			InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
		
	}
}

//包括已消除的区域进行重排
void CGameDlg::OnBnClickedBtnRestart()
{
	// TODO: 在此添加控件通知处理程序代码
	//调用CGameControl：：ResetGraph();
	m_gameControl.Reset();

	//更新地图，调用UpdateMap(),更新界面显示
	UpdateMap();

	//通知界面重绘
	InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
}


void CGameDlg::OnBnClickedBtnWin()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (m_bPlaying == true)
	{
		
	//重置地图
		m_gameControl.clearMap();
		//更新地图，调用UpdateMap(),更新界面显示
		UpdateMap();

		//通知界面重绘
		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
		m_Hit = true;
		this->GetDlgItem(IDC_BTN_WIN)->EnableWindow(false);
	}
}


void CGameDlg::OnBnClickedBtnOpenmusic()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPlaying==true)
	PlaySound(TEXT("D:\\The Microsoft Sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
}


void CGameDlg::OnBnClickedBtnClosemusic()
{

	// TODO: 在此添加控件通知处理程序代码

	PlaySound(NULL, NULL, SND_FILENAME);
}
