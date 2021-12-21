#pragma once


// USE 对话框

class USE : public CDialogEx
{
	DECLARE_DYNAMIC(USE)

public:
	USE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~USE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEnChangeEdit1();
	CListCtrl m_list;
	CString bh;
	CString sj;
	int sl;
	CString yy;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	void list_dispaly2();
	afx_msg void OnBnClickedCancel();
};

typedef struct node2
{
	char bh[10];
	char sj[20];
	char yy[50];
	int sl;
	struct node* prior, * next;
}Node2, * DLinklist2;

inline DLinklist2 init(DLinklist2 h)
{
	h = (Node2*)malloc(sizeof(Node2));
	h->prior = NULL;
	h->next = NULL;
	return h;
}