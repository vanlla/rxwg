
// CallDlgDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CallDlg.h"
#include "CallDlgDlg.h"
#include "afxdialogex.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCallDlgDlg 对话框



CCallDlgDlg::CCallDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CALLDLG_DIALOG, pParent)
	, m_szInput(_T(""))
	, m_szOutput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCallDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szInput);
	DDX_Text(pDX, IDC_EDIT2, m_szOutput);
}

BEGIN_MESSAGE_MAP(CCallDlgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCallDlgDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CCallDlgDlg::OnViewAsciiCode)
	ON_BN_CLICKED(IDOK3, &CCallDlgDlg::OnViewString)
END_MESSAGE_MAP()


// CCallDlgDlg 消息处理程序
int g_ntst = 10;
void test1()
{
	g_ntst = 5;
}

void tst2()
{
	g_ntst = 2;
}


typedef void(*pFunc)();



struct PointF
{
	float x;
	float y;
};

double CalcPointDist(PointF pt1, PointF pt2)
{
	double x = abs(pt1.x - pt2.x);
	double y = abs(pt1.y - pt2.y);
	double dist = x*x + y*y;
	dist = sqrt(dist);
	return dist;
}

#pragma comment(lib,"RXJH_GameDll.lib")
_declspec(dllimport) void SetDllHookClient();

BOOL CCallDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	PointF p1{-13.375950, 851.205200};
	PointF p2{ 252.496979, 813.753296 };
	float dist = CalcPointDist(p1, p2);


	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetDllHookClient();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCallDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCallDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCallDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCallDlgDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDllHookClient();
}


void CCallDlgDlg::OnViewAsciiCode()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_szOutput.Empty();

	int nLen = m_szInput.GetLength();
	for (int i = 0; i < nLen; i++)
	{
		char szTemp[4] = { 0 };
		byte ch = m_szInput[i];
		sprintf_s(szTemp, 4, "%02x ", ch);
		m_szOutput.Append(szTemp);
	}

	UpdateData(FALSE);
}


void CCallDlgDlg::OnViewString()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_szInput.Empty();
	
	int nLen = m_szOutput.GetLength();
	int i = 0;
	while (i < nLen)
	{
		char mem[4] = { 0 };
		mem[0] = m_szOutput[i];
		mem[1] = m_szOutput[i + 1];
		char ch = (char)strtol(mem, NULL, 16);
		m_szInput.AppendChar(ch);

		i += 3;
	}

	UpdateData(FALSE);
}
