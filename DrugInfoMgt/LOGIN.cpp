// LOGIN.cpp: 实现文件
//

#include "pch.h"
#include "DrugInfoMgt.h"
#include "LOGIN.h"
#include "afxdialogex.h"
#include"ADMIN.h"
#include"stdafx.h"
#include"DrugInfoMgtDlg.h"

// LOGIN 对话框
CADOConnect ad;

IMPLEMENT_DYNAMIC(LOGIN, CDialogEx)

LOGIN::LOGIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Login_DIALOG, pParent)
	, userName(_T(""))
	, password(_T(""))
{

}

LOGIN::~LOGIN()
{
}

void LOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, userName);
	DDX_Text(pDX, IDC_EDIT2, password);
}


BEGIN_MESSAGE_MAP(LOGIN, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &LOGIN::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &LOGIN::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &LOGIN::OnBnClickedButton1)
END_MESSAGE_MAP()


// LOGIN 消息处理程序


void LOGIN::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_CHECK1) == BST_CHECKED)
	{
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT2);
		pEdit->SetPasswordChar(0);
		SetDlgItemText(IDC_EDIT2, password);
		UpdateData(false);
	}
	else
	{
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT2);
		pEdit->SetPasswordChar('*');
		SetDlgItemText(IDC_EDIT2, password);
		UpdateData(false);
	}
	GetDlgItem(IDC_EDIT2)->SetFocus();
}


void LOGIN::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	static int k = 6;
	CString str;
	UpdateData(true);
	if (userName.IsEmpty())
	{
		MessageBox(_T("用户名不能为空！"), _T("登陆错误"));
		GetDlgItem(IDC_EDIT1)->SetFocus();
		return;
	}
	if (password.IsEmpty())
	{
		MessageBox(_T("用户密码不能为空！"), _T("登陆错误"));
		GetDlgItem(IDC_EDIT2)->SetFocus();
		return;
	}
	CString sql;
	sql.Format(_T("select* from Table_3 where admin='%s' and password='%s'"), userName, password);
	_bstr_t Sql;
	Sql = (_bstr_t)sql;



	_RecordsetPtr m_recordset;
	try
	{
		m_recordset = ad.GetRecordSet(Sql);  //执行查询，获取记录集
		CString str1, str2;
		str1 = (LPCSTR)(_bstr_t)(m_recordset->GetCollect("admin")); //获取管理员账户，密码
		str2 = (LPCSTR)(_bstr_t)(m_recordset->GetCollect("password"));

		//删除字符串右空格
		str1.TrimRight();
		str2.TrimRight();

		if (str1 == userName && str2 == password)
		{

			m_recordset->Close();
			LOGIN::OnOK();
			ADMIN admin;
			admin.DoModal();

		}
		else
		{
			k--;
			str.Format(_T("%d"), k);
			if (k == 0)
			{
				m_recordset->Close();
				MessageBox(_T("已经连续输入六次错误账户或密码！请下次再试"), _T("登录错误"));
				exit(0);
			}
			int m = MessageBox(_T("账号或密码错误，请检查！你还有") + str + _T("次机会，是否重新登录"), _T("登陆错误"), MB_YESNO);
			if (m == IDNO)
			{
				m_recordset->Close();
				LOGIN::OnOK();
			}
			else
			{
				m_recordset->Close();
				GetDlgItem(IDC_EDIT1)->SetFocus();
			}
		}
	}
	catch (...)
	{

		k--;
		str.Format(_T("%d"), k);
		if (k == 0)
		{
			MessageBox(_T("已经连续输入三次错误账户或密码！请下次再试"), _T("登录错误"));
			exit(0);
		}
		int m = MessageBox(_T("账号或密码错误，请检查！你还有") + str + _T("次机会，是否重新登录"), _T("登陆错误"), MB_YESNO);
		if (m == IDNO)
			LOGIN::OnOK();
		else
		{
			m_recordset->Close();
			GetDlgItem(IDC_EDIT1)->SetFocus();
		}


	}
}


void LOGIN::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
