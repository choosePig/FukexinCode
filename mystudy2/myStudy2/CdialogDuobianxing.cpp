// CdialogDuobianxing.cpp: 实现文件
//

#include "stdafx.h"
#include "myStudy2.h"
#include "CdialogDuobianxing.h"
#include "afxdialogex.h"


// CdialogDuobianxing 对话框

IMPLEMENT_DYNAMIC(CdialogDuobianxing, CDialogEx)

CdialogDuobianxing::CdialogDuobianxing(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_nn(_T(""))
{

}

CdialogDuobianxing::~CdialogDuobianxing()
{
}

void CdialogDuobianxing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITnn, m_nn);
	DDX_Control(pDX, IDC_RADIOfilled, m_filled);
}


BEGIN_MESSAGE_MAP(CdialogDuobianxing, CDialogEx)
	ON_BN_CLICKED(IDOK, &CdialogDuobianxing::OnBnClickedOk)
END_MESSAGE_MAP()


// CdialogDuobianxing 消息处理程序


void CdialogDuobianxing::OnBnClickedOk()
{
	CString m_count;
	GetDlgItemText(IDC_EDITnn, m_count);
	nn = _ttoi(m_count);
	if (((CButton *)GetDlgItem(IDC_RADIOfilled))->GetCheck())
	{
		filled = true;
	}
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
