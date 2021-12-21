// ADD.cpp: 实现文件
//

#include "pch.h"
#include "DrugInfoMgt.h"
#include "ADD.h"
#include "afxdialogex.h"
#include"DrugInfoMgtDlg.h"


// ADD 对话框
DLinklist h, p, s;
IMPLEMENT_DYNAMIC(ADD, CDialogEx)

ADD::ADD(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_DIALOG, pParent)
	, dh(_T(""))
	, mc(_T(""))
	, lb(_T(""))
	, gs(_T(""))
	, cd(_T(""))
	, sj(_T(""))
	, bzq(0)
	, dj(0)
{

}

ADD::~ADD()
{
}

void ADD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, dh);
	DDX_Text(pDX, IDC_EDIT2, mc);
	DDX_Text(pDX, IDC_EDIT3, lb);
	DDX_Text(pDX, IDC_EDIT4, gs);
	DDX_Text(pDX, IDC_EDIT5, cd);
	DDX_Text(pDX, IDC_EDIT6, sj);
	DDX_Text(pDX, IDC_EDIT7, bzq);
	DDX_Text(pDX, IDC_EDIT8, dj);
}


BEGIN_MESSAGE_MAP(ADD, CDialogEx)
	ON_BN_CLICKED(IDOK, &ADD::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ADD::OnBnClickedCancel)
END_MESSAGE_MAP()


// ADD 消息处理程序

//, dh,mc,lb,gs,cd,sj,bzq,dj
void ADD::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	LPSTR str;
	UpdateData(true);
	s = (Node*)malloc(sizeof(Node));
	str = T2A(dh);
	strcpy_s(s->dh, str);
	str = T2A(mc);
	strcpy_s(s->mc, str);
	str = T2A(lb);
	strcpy_s(s->lb, str);
	str = T2A(gs);
	strcpy_s(s->gs, str);
	str = T2A(cd);
	strcpy_s(s->cd, str);
	str = T2A(sj);
	strcpy_s(s->sj, str);
	s->bzq = bzq;
	s->dj = dj;



	CString sql;
	CADOConnect adq;
	sql.Format(_T("insert into Table_1(id,name,type,company,number,producer,time,shelf_life,price) values('%s','%s','%s','%s','%d','%s','%s','%d','%d')"),dh, mc, lb, gs, 0, cd, sj, bzq, dj );
	_bstr_t Sql;
	Sql = (_bstr_t)sql;
	if (!adq.ExecuteSQL(Sql))
		AfxMessageBox(_T("入库失败"));
	else
		AfxMessageBox(_T("入库成功"));

	free(s);
}


void ADD::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
