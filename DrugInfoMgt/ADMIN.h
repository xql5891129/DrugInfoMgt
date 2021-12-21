#pragma once


// ADMIN 对话框

class ADMIN : public CDialogEx
{
	DECLARE_DYNAMIC(ADMIN)

public:
	ADMIN(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ADMIN();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Admin_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CBrush m_rush;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	void list_dispaly1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	CString mc;
	int kc;
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	int new_kc;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
};
