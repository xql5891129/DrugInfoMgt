// USE.cpp: 实现文件
//

#include "pch.h"
#include "DrugInfoMgt.h"
#include "USE.h"
#include "afxdialogex.h"
#include"DrugInfoMgtDlg.h"
#include"USE.h"


// USE 对话框
DLinklist2 h, p, s;
CADOConnect use;
IMPLEMENT_DYNAMIC(USE, CDialogEx)

USE::USE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USE_DIALOG, pParent)
	, bh(_T(""))
	, sj(_T(""))
	, sl(0)
	, yy(_T(""))
{

}

USE::~USE()
{
}

void USE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, bh);
	DDX_Text(pDX, IDC_EDIT2, sj);
	DDX_Text(pDX, IDC_EDIT3, sl);
	DDX_Text(pDX, IDC_EDIT4, yy);
}


BEGIN_MESSAGE_MAP(USE, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &USE::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &USE::OnBnClickedCancel)
END_MESSAGE_MAP()


// USE 消息处理程序



void USE::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	LPSTR str;
	UpdateData(true);
	s = (Node2*)malloc(sizeof(Node2));
	str = T2A(bh);
	strcpy_s(s->bh, str);
	str = T2A(sj);
	strcpy_s(s->sj, str);
	str = T2A(yy);
	strcpy_s(s->yy, str);
	s->sl = sl;

	_bstr_t fSql;
	_RecordsetPtr  m_pRecordSet;
	CADOConnect ado;
	CString fsql;
	fsql.Format(_T("select id,usetime,usenumber,reason from Table_2"));
	fSql = (_bstr_t)fsql;
	m_pRecordSet = ado.GetRecordSet(fSql);
	CString name;
	while (!m_pRecordSet->adoEOF || !m_pRecordSet->BOF) {
		name = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("id"));
		if (strcmp((char*)((LPCTSTR)name), (char*)((LPCTSTR)bh)) != 0)
		{
			AfxMessageBox(_T("该药品ID不存在！请检查！"));
			return;
		}
	}
	CString sql;
	CADOConnect use;
	sql.Format(_T("insert into Table_1(id,usetime,usenumber,reason) values('%s','%s','%d','%s')"), bh,sj,sl,yy);
	_bstr_t Sql;
	Sql = (_bstr_t)sql;
	if (!use.ExecuteSQL(Sql))
		AfxMessageBox(_T("入库失败"));
	else
		AfxMessageBox(_T("入库成功"));

	free(s);
}


BOOL USE::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	LONG lStyle;
	CListCtrl* list = (CListCtrl*)GetDlgItem(IDC_LIST1);
	lStyle = GetWindowLong(list->m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT;
	SetWindowLong(list->m_hWnd, GWL_STYLE, lStyle);
	DWORD dwStyle = list->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	list->SetExtendedStyle(dwStyle);
	list->InsertColumn(1, _T("药品代号"), LVCFMT_CENTER, 100);
	list->InsertColumn(2, _T("使用时间"), LVCFMT_CENTER, 100);
	list->InsertColumn(3, _T("使用数量"), LVCFMT_CENTER, 100);
	list->InsertColumn(4, _T("使用原因"), LVCFMT_CENTER, 500);
	list_dispaly2();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void USE::list_dispaly2()
{
	CListCtrl* plist = (CListCtrl*)GetDlgItem(IDC_LIST1);
	plist->SetRedraw(FALSE);
	plist->DeleteAllItems();
	_RecordsetPtr  m_pRecordSet;
	try {
		int i = 0;
		CString sql;
		//m_pRecordSet.CreateInstance(__uuidof(Recordset));
		_bstr_t Sql;
		sql.Format(_T("select id,usetime,usenumber,reason from Table_2"));
		Sql = (_bstr_t)sql;
		//m_pRecordSet->Open((_bstr_t)sql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockPessimistic, adCmdText);
		m_pRecordSet = use.GetRecordSet(Sql);
		while (!m_pRecordSet->adoEOF || !m_pRecordSet->BOF)//遍历返回的每一条记录
		{
			CString str1, str2, str3, str4;
			str1 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("id"));
			str2 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("usetime"));
			str3 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("usenumber"));
			str4 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("reason"));
			str1.TrimRight();
			str2.TrimRight();
			str3.TrimRight();
			str4.TrimRight();
			//删除字符串右边的空格
			plist->InsertItem(i, str1);
			plist->SetItemText(i, 1, str2);
			plist->SetItemText(i, 2, str3);
			plist->SetItemText(i, 3, str4);
			i++;
			m_pRecordSet->MoveNext();
		}
		m_pRecordSet->Close();
	}
	catch (_com_error e)	// 捕捉异常
	{
		m_pRecordSet->Close();
	}

	plist->SetRedraw(TRUE);
	plist->Invalidate();
	plist->UpdateWindow();
}

void USE::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
