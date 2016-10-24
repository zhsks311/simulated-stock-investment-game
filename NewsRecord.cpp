// NewsRecord.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "윈플.h"
#include "NewsRecord.h"
#include "afxdialogex.h"


// NewsRecord 대화 상자입니다.

IMPLEMENT_DYNAMIC(NewsRecord, CDialogEx)

NewsRecord::NewsRecord(CWnd* pParent /*=NULL*/)
	: CDialogEx(NewsRecord::IDD, pParent)
{

}

NewsRecord::~NewsRecord()
{
}

void NewsRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstNews);

	LV_COLUMN m_lCol;

	m_lCol.mask = LVCF_TEXT | LVCF_WIDTH;

	m_lCol.pszText = _T("날짜");
	m_lCol.cx = 150;
	m_lstNews.InsertColumn(0,&m_lCol);

	m_lCol.pszText = _T("기사");
	m_lCol.cx = 370;
	m_lstNews.InsertColumn(1,&m_lCol);



	///////////////////





	POSITION pos1 = date.GetHeadPosition();
	POSITION pos2 = article.GetHeadPosition();

	int ind=0;
	
	LV_ITEM m_lItem;
	m_lItem.mask = LVIF_TEXT;

	while(pos1)
	{



	m_lItem.pszText = (LPTSTR)(LPCTSTR)date.GetNext(pos1);;
	m_lItem.iItem = ind;		//col
	m_lItem.iSubItem = 0;	//row
	m_lstNews.InsertItem( &m_lItem );


	m_lItem.pszText = (LPTSTR)(LPCTSTR)article.GetNext(pos2);;
	m_lItem.iItem = ind;
	m_lItem.iSubItem = 1;
	m_lstNews.SetItem( &m_lItem );

	ind++;
	}

}


BEGIN_MESSAGE_MAP(NewsRecord, CDialogEx)
END_MESSAGE_MAP()


// NewsRecord 메시지 처리기입니다.

