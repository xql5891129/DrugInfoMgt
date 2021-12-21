#pragma once


// ADD 对话框

class ADD : public CDialogEx
{
	DECLARE_DYNAMIC(ADD)

public:
	ADD(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ADD();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString dh;
	CString mc;
	CString lb;
	CString gs;
	CString cd;
	CString sj;
	int bzq;
	int dj;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};

typedef struct node
{
	char dh[10];
	char mc[20];
	char lb[10];
	char gs[20];
	char cd[20];
	char sj[20];
	int bzq;
	int dj;
	struct node* prior, * next;
}Node, * DLinklist;

inline DLinklist init(DLinklist h)
{
	h = (Node*)malloc(sizeof(Node));
	h->prior = NULL;
	h->next = NULL;
	return h;
}