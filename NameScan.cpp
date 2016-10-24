// NameScan.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "윈플.h"
#include "NameScan.h"
#include "afxdialogex.h"


// NameScan 대화 상자입니다.

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


// NameScan 메시지 처리기입니다.


void NameScan::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	pName=m_Name;
	CDialogEx::OnOK();
}
