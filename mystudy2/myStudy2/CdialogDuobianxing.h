#pragma once


// CdialogDuobianxing 对话框

class CdialogDuobianxing : public CDialogEx
{
	DECLARE_DYNAMIC(CdialogDuobianxing)

public:
	CdialogDuobianxing(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CdialogDuobianxing();
	int nn=4;
	bool filled = false;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_nn;
	CButton m_filled;
};
