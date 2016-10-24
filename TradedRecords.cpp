// TradedRecords.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "윈플.h"
#include "TradedRecords.h"
#include "afxdialogex.h"


// TradedRecords 대화 상자입니다.

IMPLEMENT_DYNAMIC(TradedRecords, CDialogEx)

	TradedRecords::TradedRecords(CWnd* pParent /*=NULL*/)
	: CDialogEx(TradedRecords::IDD, pParent)
{

}

TradedRecords::~TradedRecords()
{
}

void TradedRecords::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstTrade);

	LV_COLUMN m_lCol;

	m_lCol.mask = LVCF_TEXT | LVCF_WIDTH;

	m_lCol.pszText = _T("매매구분");
	m_lCol.cx = 70;
	m_lstTrade.InsertColumn(0,&m_lCol);

	m_lCol.pszText = _T("종목");
	m_lCol.cx = 80;
	m_lstTrade.InsertColumn(1,&m_lCol);


	m_lCol.pszText = _T("거래량");
	m_lCol.cx = 60;
	m_lstTrade.InsertColumn(2,&m_lCol);


	m_lCol.pszText = _T("날짜");
	m_lCol.cx = 120;
	m_lstTrade.InsertColumn(3,&m_lCol);


	m_lCol.pszText = _T("금액");
	m_lCol.cx = 80;
	m_lstTrade.InsertColumn(4,&m_lCol);


	///////////////////





	POSITION pos1 = div.GetHeadPosition();
	POSITION pos2 = stock.GetHeadPosition();
	POSITION pos3 = quantity.GetHeadPosition();
	POSITION pos4 = date.GetHeadPosition();
	POSITION pos5 = price.GetHeadPosition();
	int ind=0;
	
	LV_ITEM m_lItem;
	m_lItem.mask = LVIF_TEXT;
	while(pos1)
	{



	m_lItem.pszText = (LPTSTR)(LPCTSTR)div.GetNext(pos1);;
	m_lItem.iItem = ind;		//col
	m_lItem.iSubItem = 0;	//row
	m_lstTrade.InsertItem( &m_lItem );


	m_lItem.pszText = (LPTSTR)(LPCTSTR)stock.GetNext(pos2);;
	m_lItem.iItem = ind;
	m_lItem.iSubItem = 1;
	m_lstTrade.SetItem( &m_lItem );


	m_lItem.pszText = (LPTSTR)(LPCTSTR)quantity.GetNext(pos3);;
	m_lItem.iItem = ind;
	m_lItem.iSubItem = 2;
	m_lstTrade.SetItem( &m_lItem );

	m_lItem.pszText = (LPTSTR)(LPCTSTR)date.GetNext(pos4);;
	m_lItem.iItem = ind;
	m_lItem.iSubItem = 3;
	m_lstTrade.SetItem( &m_lItem );

	m_lItem.pszText = (LPTSTR)(LPCTSTR)price.GetNext(pos5);;
	m_lItem.iItem = ind;
	m_lItem.iSubItem = 4;
	m_lstTrade.SetItem( &m_lItem );


	ind++;
	}

}


BEGIN_MESSAGE_MAP(TradedRecords, CDialogEx)
END_MESSAGE_MAP()

// TradedRecords 메시지 처리기입니다.
