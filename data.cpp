// data.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "윈플.h"
#include "data.h"
#include "afxdialogex.h"
// MySql 연동을 위해 추가한 내용 시작
#include <winsock2.h> 
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "ws2_32.lib")

#define MYSQL_HOST  "localhost"
#define MYSQL_USER  "root"
#define MYSQL_PWD   "1111"
#define MYSQL_DB "assign"
#define MYSQL_PORT 3306
// MySql 연동을 위해 추가한 내용 끝


// data 대화 상자입니다.

IMPLEMENT_DYNAMIC(data, CDialogEx)

	data::data(CWnd* pParent /*=NULL*/)
	: CDialogEx(data::IDD, pParent)
{

}

data::~data()
{
}

void data::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_lstRank);

	LV_COLUMN m_lCol;

	m_lCol.mask = LVCF_TEXT | LVCF_WIDTH;

	m_lCol.pszText = _T("종목명");
	m_lCol.cx = 90;
	m_lstRank.InsertColumn(0,&m_lCol);

	m_lCol.pszText = _T("현재가");
	m_lCol.cx = 80;
	m_lstRank.InsertColumn(1,&m_lCol);


	MYSQL mysql;
	MYSQL_ROW recordSet;	// mysql 의 행을 맡는다.
	MYSQL_RES *m_res; // mysql의 결과를 받아온다
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql,MYSQL_HOST,MYSQL_USER,MYSQL_PWD,MYSQL_DB, MYSQL_PORT, 0, 0))
	{
		AfxMessageBox(_T("DB 연결 실패"),MB_OK);
		exit(1);
	}
	else
	{

		AfxMessageBox(_T("DB 연결 성공"),MB_OK);
		if (mysql_query(&mysql,"set names euckr")!= 0)
			MessageBox(_T("fail"));
	}

	// mysql 데이터베이스의 user테이블 정보 중에 host, user 정보를 보자.

		if (mysql_query(&mysql,"select * from players")!= 0)
			MessageBox(_T("fail"));

	m_res=mysql_store_result(&mysql);
	int datafig=0;
	int ind=0;
	datafig=mysql_num_rows(m_res);

	LV_ITEM m_lItem;
	m_lItem.mask = LVIF_TEXT;

	while((recordSet=mysql_fetch_row(m_res))!=NULL)
	{

		// 값 삽입

		m_lItem.pszText = (LPTSTR)(LPCTSTR)recordSet[0];
		m_lItem.iItem = ind;
		m_lItem.iSubItem = 0;
		m_lstRank.InsertItem( &m_lItem );

		m_lItem.pszText =  (LPTSTR)(LPCTSTR)recordSet[1];
		m_lItem.iItem = ind;
		m_lItem.iSubItem = 1;
		m_lstRank.SetItem( &m_lItem );

		ind++;

	}




}


BEGIN_MESSAGE_MAP(data, CDialogEx)
END_MESSAGE_MAP()


// data 메시지 처리기입니다.
