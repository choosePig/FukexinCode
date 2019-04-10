﻿#pragma once


// CdialogWeight 对话框

class CdialogWeight : public CDialogEx
{
	DECLARE_DYNAMIC(CdialogWeight)

public:
	CdialogWeight(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CdialogWeight();
	float weight;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
