// CdialogWeight.cpp: 实现文件
//

#include "stdafx.h"
#include "myStudy2.h"
#include "CdialogWeight.h"
#include "afxdialogex.h"


// CdialogWeight 对话框

IMPLEMENT_DYNAMIC(CdialogWeight, CDialogEx)

CdialogWeight::CdialogWeight(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CdialogWeight::~CdialogWeight()
{
}

void CdialogWeight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CdialogWeight, CDialogEx)
	ON_BN_CLICKED(IDOK, &CdialogWeight::OnBnClickedOk)
END_MESSAGE_MAP()


// CdialogWeight 消息处理程序


void CdialogWeight::OnBnClickedOk()
{
	CString m_weight;
	GetDlgItemText(IDC_EDITweight, m_weight);
	weight = _ttoi(m_weight);

	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
