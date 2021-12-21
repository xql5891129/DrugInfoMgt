// ADMIN.cpp: 实现文件
//

#include "pch.h"
#include "DrugInfoMgt.h"
#include "ADMIN.h"
#include "afxdialogex.h"
#include"stdafx.h"
#include"DrugInfoMgtDlg.h"
#include"ADD.h"
#include"USE.h"

// ADMIN 对话框
CADOConnect adp,adz;
IMPLEMENT_DYNAMIC(ADMIN, CDialogEx)

ADMIN::ADMIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Admin_DIALOG1, pParent)
	, mc(_T(""))
	, kc(0)
	, new_kc(0)
{

}

ADMIN::~ADMIN()
{
}

void ADMIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, mc);
	DDX_Text(pDX, IDC_EDIT2, kc);
	DDX_Text(pDX, IDC_EDIT3, new_kc);
}


BEGIN_MESSAGE_MAP(ADMIN, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ADMIN::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ADMIN::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &ADMIN::OnBnClickedButton4)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &ADMIN::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON3, &ADMIN::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &ADMIN::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &ADMIN::OnBnClickedButton5)
END_MESSAGE_MAP()


// ADMIN 消息处理程序


BOOL ADMIN::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_rush.CreateSolidBrush(RGB(219, 238, 249));
	
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
	list->InsertColumn(2, _T("药品名称"), LVCFMT_CENTER, 100);
	list->InsertColumn(3, _T("药品类别"), LVCFMT_CENTER, 100);
	list->InsertColumn(4, _T("库存数目"), LVCFMT_CENTER, 100);
	list->InsertColumn(5, _T("出厂公司"), LVCFMT_CENTER, 100);
	list->InsertColumn(6, _T("产地"), LVCFMT_CENTER, 100);
	list->InsertColumn(7, _T("出厂时间"), LVCFMT_CENTER, 100);
	list->InsertColumn(8, _T("保质期（月）"), LVCFMT_CENTER, 100);
	list->InsertColumn(9, _T("单价（元）"), LVCFMT_CENTER, 100);
	list_dispaly1();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void ADMIN::list_dispaly1()
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
		sql.Format(_T("select id,name,type,number,company,producer,time,shelf_life,price from Table_1"));
		Sql = (_bstr_t)sql;
		//m_pRecordSet->Open((_bstr_t)sql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockPessimistic, adCmdText);
		m_pRecordSet = adp.GetRecordSet(Sql);
		while (!m_pRecordSet->adoEOF || !m_pRecordSet->BOF)//遍历返回的每一条记录
		{
			CString str1, str2, str3, str4, str5, str6, str7, str8, str9;
			str1 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("id"));
			str2 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("name"));
			str3 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("type"));
			str4 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("number"));
			str5 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("company"));
			str6 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("producer"));
			str7 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("time"));
			str8 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("shelf_life"));
			str9 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("price"));
			str1.TrimRight();
			str2.TrimRight();
			str3.TrimRight();
			str4.TrimRight();
			str5.TrimRight();
			str6.TrimRight();
			str7.TrimRight();
			str8.TrimRight();
			str9.TrimRight();
			//删除字符串右边的空格
			plist->InsertItem(i, str1);
			plist->SetItemText(i, 1, str2);
			plist->SetItemText(i, 2, str3);
			plist->SetItemText(i, 3, str4);
			plist->SetItemText(i, 4, str5);
			plist->SetItemText(i, 5, str6);
			plist->SetItemText(i, 6, str7);
			plist->SetItemText(i, 7, str8);
			plist->SetItemText(i, 8, str9);
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






void ADMIN::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	ADD add;
	add.DoModal();
}

void ADMIN::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	list_dispaly1();
}


void ADMIN::OnBnClickedButton4()//修改药品库存
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if ( new_kc == NULL )
	{
		MessageBox(_T("修改库存值不能为空！请检查！"), _T("错误"));
		return;
	}
	if (IDYES)
	{
		CString sql;
		_bstr_t Sql;
		sql.Format(_T("update Table_1 set number='%d' where name='%s' "), new_kc, mc);
		Sql = (_bstr_t)sql;
		if (adz.ExecuteSQL(Sql))
			MessageBox(_T("修改成功！"), _T("提示"));
		else
			AfxMessageBox(_T("修改失败！"));
	}
	else
		return;
}


void ADMIN::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CListCtrl* list = (CListCtrl*)GetDlgItem(IDC_LIST1);
	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
	CString str;
	LPSTR str1;
	USES_CONVERSION;
	if (-1 != pNMListView->iItem)
	{
		str = list->GetItemText(pNMListView->iItem, 1);
		mc = str;
		str = list->GetItemText(pNMListView->iItem, 3);
		str1 = T2A(str);
		kc = atof(str1);
		UpdateData(false);
	}
}


void ADMIN::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	USE use;
	use.DoModal();
}


void ADMIN::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CADOConnect aq;
	CString sql1, sql2;
	_bstr_t Sql1, Sql2;
	UpdateData(true);
	if (mc == "")
	{
		MessageBox(_T("所有内容不能为空！请检查！"), _T("错误"));
		return;
	}
	sql1.Format(_T("delete from Table_1 where name='%s'"), mc);
	Sql1 = (_bstr_t)sql1;
	if (aq.ExecuteSQL(Sql1))
	{
		MessageBox(_T("删除成功！"), _T("提示"));
	}
	else
		MessageBox(_T("删除失败！"), _T("提示"));
}


void ADMIN::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}
