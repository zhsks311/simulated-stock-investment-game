// NameScan.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "����.h"
#include "NameScan.h"
#include "afxdialogex.h"


// NameScan ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(NameScan, CDialogEx)

NameScan::NameScan(CWnd* pParent /*=NULL*/)
	: CDialogEx(NameScan::IDD, pParent)

	, m_Name(_T(""))
{

}

NameScan::~NameScan()
{
}

void NameScan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_edtName, m_Name);
	DDX_Text(pDX, IDC_edtN, m_Name);
}


BEGIN_MESSAGE_MAP(NameScan, CDialogEx)
	ON_BN_CLICKED(IDOK, &NameScan::OnBnClickedOk)
END_MESSAGE_MAP()


// NameScan �޽��� ó�����Դϴ�.


void NameScan::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	pName=m_Name;
	CDialogEx::OnOK();
}
