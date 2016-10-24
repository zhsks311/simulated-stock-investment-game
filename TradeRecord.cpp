// TradeRecord.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "윈플.h"
#include "TradeRecord.h"
#include "afxdialogex.h"


// TradeRecord 대화 상자입니다.

IMPLEMENT_DYNAMIC(TradeRecord, CDialogEx)

TradeRecord::TradeRecord(CWnd* pParent /*=NULL*/)
	: CDialogEx(TradeRecord::IDD, pParent)
{
}

TradeRecord::~TradeRecord()
{
}

void TradeRecord::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_LIST1, m_trade);

	
	LV_COLUMN m_lCol;

	m_lCol.mask = LVCF_TEXT | LVCF_WIDTH;

	m_lCol.pszText = _T("매매구분");
	m_lCol.cx = 90;
	m_trade.InsertColumn(0,&m_lCol);

	m_lCol.pszText = _T("종목");
	m_lCol.cx = 80;
	m_trade.InsertColumn(1,&m_lCol);


	m_lCol.pszText = _T("거래량");
	m_lCol.cx = 80;
	m_trade.InsertColumn(2,&m_lCol);


	m_lCol.pszText = _T("날짜");
	m_lCol.cx = 80;
	m_trade.InsertColumn(3,&m_lCol);


	m_lCol.pszText = _T("금액");
	m_lCol.cx = 80;
	m_trade.InsertColumn(4,&m_lCol);


	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST2, m_trade);
}


BEGIN_MESSAGE_MAP(TradeRecord, CDialogEx)
END_MESSAGE_MAP()


// TradeRecord 메시지 처리기입니다.
