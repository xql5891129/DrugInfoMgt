// REG.cpp: 实现文件
//

#include "pch.h"
#include "DrugInfoMgt.h"
#include "REG.h"
#include "afxdialogex.h"
#include"DrugInfoMgtDlg.h"


// REG 对话框

IMPLEMENT_DYNAMIC(REG, CDialogEx)

REG::REG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTER_DIALOG, pParent)
	, admin(_T(""))
	, password(_T(""))
{

}

REG::~REG()
{
}

void REG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, admin);
	DDX_Text(pDX, IDC_EDIT3, password);
}


BEGIN_MESSAGE_MAP(REG, CDialogEx)
	ON_BN_CLICKED(IDOK, &REG::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &REG::OnBnClickedCancel)
END_MESSAGE_MAP()


// REG 消息处理程序


void REG::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sql, str;
	CADOConnect ado;
	_bstr_t Sql, fSql, FSql;
	_RecordsetPtr  m_pRecordSet;
	UpdateData(true);
	if (admin == "" || password == "" )
		MessageBox(_T("请输入完整注册信息！"), _T("提示"));

	else
	{
		if (admin.GetLength() >= 6 && admin.GetLength() <= 10 && password.GetLength() >= 6 && password.GetLength() <= 10)
		{
			CString fsql;
			fsql.Format(_T("select admin,password from Table_3"));
			fSql = (_bstr_t)fsql;
			m_pRecordSet = ado.GetRecordSet(fSql);
			CString name;
			while (!m_pRecordSet->adoEOF || !m_pRecordSet->BOF) {
				name = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("admin"));
				if (strcmp((char*)((LPCTSTR)name), (char*)((LPCTSTR)admin))==0)
				{
					AfxMessageBox(_T("该用户名账号已存在！请检查！"));
					return;
				}
			}
			int k = MessageBox(_T("注册成功！是否返回登录"), _T("提示"), MB_YESNO);
			if (k == IDYES)
				CDialogEx::OnCancel();
		}
		else
			MessageBox(_T("注册用户名和密码需在6-10位，请仔细检查！"), _T("提示"));

	}
}


void REG::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
