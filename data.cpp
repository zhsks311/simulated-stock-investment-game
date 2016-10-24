// data.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "����.h"
#include "data.h"
#include "afxdialogex.h"
// MySql ������ ���� �߰��� ���� ����
#include <winsock2.h> 
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "ws2_32.lib")

#define MYSQL_HOST  "localhost"
#define MYSQL_USER  "root"
#define MYSQL_PWD   "1111"
#define MYSQL_DB "assign"
#define MYSQL_PORT 3306
// MySql ������ ���� �߰��� ���� ��


// data ��ȭ �����Դϴ�.

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

	m_lCol.pszText = _T("�����");
	m_lCol.cx = 90;
	m_lstRank.InsertColumn(0,&m_lCol);

	m_lCol.pszText = _T("���簡");
	m_lCol.cx = 80;
	m_lstRank.InsertColumn(1,&m_lCol);


	MYSQL mysql;
	MYSQL_ROW recordSet;	// mysql �� ���� �ô´�.
	MYSQL_RES *m_res; // mysql�� ����� �޾ƿ´�
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql,MYSQL_HOST,MYSQL_USER,MYSQL_PWD,MYSQL_DB, MYSQL_PORT, 0, 0))
	{
		AfxMessageBox(_T("DB ���� ����"),MB_OK);
		exit(1);
	}
	else
	{

		AfxMessageBox(_T("DB ���� ����"),MB_OK);
		if (mysql_query(&mysql,"set names euckr")!= 0)
			MessageBox(_T("fail"));
	}

	// mysql �����ͺ��̽��� user���̺� ���� �߿� host, user ������ ����.

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

		// �� ����

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


// data �޽��� ó�����Դϴ�.
