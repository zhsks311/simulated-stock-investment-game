// TradeRecord.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "����.h"
#include "TradeRecord.h"
#include "afxdialogex.h"


// TradeRecord ��ȭ �����Դϴ�.

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

	m_lCol.pszText = _T("�Ÿű���");
	m_lCol.cx = 90;
	m_trade.InsertColumn(0,&m_lCol);

	m_lCol.pszText = _T("����");
	m_lCol.cx = 80;
	m_trade.InsertColumn(1,&m_lCol);


	m_lCol.pszText = _T("�ŷ���");
	m_lCol.cx = 80;
	m_trade.InsertColumn(2,&m_lCol);


	m_lCol.pszText = _T("��¥");
	m_lCol.cx = 80;
	m_trade.InsertColumn(3,&m_lCol);


	m_lCol.pszText = _T("�ݾ�");
	m_lCol.cx = 80;
	m_trade.InsertColumn(4,&m_lCol);


	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST2, m_trade);
}


BEGIN_MESSAGE_MAP(TradeRecord, CDialogEx)
END_MESSAGE_MAP()


// TradeRecord �޽��� ó�����Դϴ�.
