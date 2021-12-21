
// DrugInfoMgtDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DrugInfoMgt.h"
#include "DrugInfoMgtDlg.h"
#include "afxdialogex.h"
#include "LOGIN.h"
#include"REG.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CFont m_editFont, m_buttonFont1, m_buttonFont2;
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


// CDrugInfoMgtDlg 对话框



CDrugInfoMgtDlg::CDrugInfoMgtDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRUGINFOMGT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrugInfoMgtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_BUTTON3, m_button2);
	DDX_Control(pDX, IDC_STATIC1, m_static);
}

BEGIN_MESSAGE_MAP(CDrugInfoMgtDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDrugInfoMgtDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDrugInfoMgtDlg::OnBnClickedButton3)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDrugInfoMgtDlg 消息处理程序

BOOL CDrugInfoMgtDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	m_editFont.CreatePointFont(230, _T("楷体"), NULL);
	m_static.SetFont(&m_editFont, true);
	m_static.SetWindowText(_T("失物招领系统"));
	m_buttonFont1.CreatePointFont(50, _T("楷体"), NULL);
	m_button1.SetFont(&m_editFont, true);
	m_buttonFont2.CreatePointFont(50, _T("楷体"), NULL);
	m_button2.SetFont(&m_editFont, true);
	//m_static.SetFaceColor(RGB(213, 241, 251), true);
	//m_button2.SetFaceColor(RGB(200, 120, 251), true);
	m_Brush.CreateSolidBrush(RGB(219, 238, 249));


	
;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDrugInfoMgtDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDrugInfoMgtDlg::OnPaint()
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
		CRect rect;
		CPaintDC dc(this);
		GetClientRect(&rect);
		dc.FillSolidRect(rect, RGB(141, 182, 205));
		dc.FillPath();

		//背景图片 能够自适应窗口
		GetClientRect(&rect);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_IMG);   //IDB_BITMAP_BACKGROUND是你自己的图对应的ID 
		BITMAP bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		//CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDrugInfoMgtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDrugInfoMgtDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	LOGIN login;
	login.DoModal();
}


void CDrugInfoMgtDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	REG reg;
	reg.DoModal();
}


HBRUSH CDrugInfoMgtDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)// 选择对话框    
	{
		return m_Brush;
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_Brush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_BUTTON1)
	{
		pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_Brush;
	}



	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
