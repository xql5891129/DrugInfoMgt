#pragma once


// REG 对话框

class REG : public CDialogEx
{
	DECLARE_DYNAMIC(REG)

public:
	REG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~REG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString admin;
	CString password;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
