// 윈플Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "윈플.h"
#include "윈플Dlg.h"
#include "NewsRecord.h"
#include "TradeRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int a;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	a = 0;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// C윈플Dlg 대화 상자




C윈플Dlg::C윈플Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C윈플Dlg::IDD, pParent)
	, m_News1(_T(""))
	, m_News2(_T(""))
	, m_News3(_T(""))
	, m_News4(_T(""))
	, m_News5(_T(""))

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void C윈플Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_lstStock, m_lstStock);
	DDX_Control(pDX, IDC_lstBough, m_lstMyStock);
	DDX_Control(pDX, IDC_SpinPurchase, m_spin1);
	DDX_Control(pDX, IDC_SpinSell, m_spin2);
	//  DDX_Text(pDX, IDC_News1, m_New1);
	DDX_Text(pDX, IDC_News1, m_News1);
	DDX_Text(pDX, IDC_News2, m_News2);
	DDX_Text(pDX, IDC_News3, m_News3);
	DDX_Text(pDX, IDC_news4, m_News4);
	DDX_Text(pDX, IDC_news5, m_News5);
	
}

BEGIN_MESSAGE_MAP(C윈플Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//	ON_NOTIFY(NM_CLICK, IDC_lstStock, &C윈플Dlg::OnClickLstStocks)
	ON_BN_CLICKED(IDC_btnBuy, &C윈플Dlg::OnBnClickedBuy)
	ON_BN_CLICKED(IDC_btnSell, &C윈플Dlg::OnBnClickedSell)
	ON_NOTIFY(NM_CLICK, IDC_lstStock, &C윈플Dlg::OnClickLststock)
	ON_NOTIFY(NM_CLICK, IDC_lstBough, &C윈플Dlg::OnNMClickLstMyStock)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_btnbnew, &C윈플Dlg::OnBnClickedbtnbnew)
	ON_BN_CLICKED(IDC_btnHtry, &C윈플Dlg::OnBnClickedbtnhtry)
END_MESSAGE_MAP()


// C윈플Dlg 메시지 처리기

BOOL C윈플Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.


	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//순서대로
	//내 주식 젤 밑 가리킬 변수
	//시장의 주식 선택한 위치, 내 주식 선택한 위치, 현재가 임시변수, 시장 거래량 임시변수, 내 보유량.

	
	checkMouseClick_Sell=false;//false 일 때 클릭 안한 상태 -> 판매버튼 안 되도록 핮자.
	checkMouseClick_Buy=false;//false 일 때 클릭 안한 상태 -> 구매 버튼 안 되도록 하자/
	mSelIndex=0;
	stockIndex=-1;
	myStockIndex=-1;
	curPrice=0;
	mQuantity=0;
	m_Quantity=0;

	randNews[0]=0;
	randNews[1]=0;
	randNews[2]=0;
	randNews[3]=0;
	randNews[4]=0;

	m_spin1.SetRange(0,1000000);
	m_spin2.SetRange(0,1000000);

	LV_COLUMN m_lCol;

	m_lCol.mask = LVCF_TEXT | LVCF_WIDTH;

	m_lCol.pszText = _T("종목명");
	m_lCol.cx = 90;
	m_lstStock.InsertColumn(0,&m_lCol);

	m_lCol.pszText = _T("현재가");
	m_lCol.cx = 80;
	m_lstStock.InsertColumn(1,&m_lCol);

	m_lCol.pszText = _T("전일대비(%)");
	m_lCol.cx = 100;
	m_lstStock.InsertColumn(2,&m_lCol);

	m_lCol.pszText = _T("거래량");
	m_lCol.cx = 95;
	m_lstStock.InsertColumn(3,&m_lCol);//CListStock의 목록

	m_lCol.pszText = _T("종목명");
	m_lCol.cx = 100;
	m_lstMyStock.InsertColumn(0,&m_lCol);

	m_lCol.pszText = _T("보유량");
	m_lCol.cx = 90;
	m_lstMyStock.InsertColumn(1,&m_lCol);

	m_lCol.pszText = _T("구매날짜");
	m_lCol.cx = 130;
	m_lstMyStock.InsertColumn(2,&m_lCol);

	m_lCol.pszText = _T("매입가");
	m_lCol.cx = 110;
	m_lstMyStock.InsertColumn(3,&m_lCol);

	m_lCol.pszText = _T("현재가");
	m_lCol.cx = 110;
	m_lstMyStock.InsertColumn(4,&m_lCol);

	m_lCol.pszText = _T("평가손익");
	m_lCol.cx = 100;
	m_lstMyStock.InsertColumn(5,&m_lCol);

	m_lCol.pszText = _T("수익률");
	m_lCol.cx = 100;
	m_lstMyStock.InsertColumn(6,&m_lCol);//cListMyStock의 목록
	// 값 삽입


	// MySql 접속
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

	int ind=0;

	// 쿼리 요청	
	if (mysql_query(&mysql,"select * from stock")!= 0)
		MessageBox(_T("fail"));

	m_res=mysql_store_result(&mysql);
	stockfig=mysql_num_rows(m_res);
	stockId.SetSize(stockfig);

	LV_ITEM m_lItem;
	m_lItem.mask = LVIF_TEXT;

	while((recordSet=mysql_fetch_row(m_res))!=NULL)
	{

		// 값 삽입

		m_lItem.pszText = (LPTSTR)(LPCTSTR)recordSet[1];
		m_lItem.iItem = ind;
		m_lItem.iSubItem = 0;
		m_lstStock.InsertItem( &m_lItem );

		m_lItem.pszText =  (LPTSTR)(LPCTSTR)recordSet[2];
		m_lItem.iItem = ind;
		m_lItem.iSubItem = 1;
		m_lstStock.SetItem( &m_lItem );

		// 비어 있는 열의 값 추가(2번째)
		m_lItem.pszText = _T("0");
		m_lItem.iItem = ind;
		m_lItem.iSubItem = 2;
		m_lstStock.SetItem( &m_lItem );

		m_lItem.pszText =  (LPTSTR)(LPCTSTR)recordSet[3];
		m_lItem.iItem = ind;
		m_lItem.iSubItem = 3;
		m_lstStock.SetItem( &m_lItem );

		stockId[ind]=_wtol( CA2W(recordSet[0]));
		ind++;

	}

	//데이터베이스에서 뉴스정보 가져와 저장하자!
	// 쿼리 요청	
	if (mysql_query(&mysql,"select * from news")!= 0)
		MessageBox(_T("fail"));

	m_res=mysql_store_result(&mysql);
	newsfig=mysql_num_rows(m_res);
	newsId.SetSize(newsfig);  //
	newsMin.SetSize(newsfig);
	newsMax.SetSize(newsfig);
	newsArticle.SetSize(newsfig);
	int increased=0;
	while((recordSet=mysql_fetch_row(m_res))!=NULL)
	{
		newsId[increased]=_wtol( CA2W(recordSet[0]));
		newsMin[increased]=_wtol( CA2W(recordSet[2]));
		newsMax[increased]=_wtol( CA2W(recordSet[3]));
		newsArticle[increased]=(LPTSTR)(LPCTSTR)recordSet[1];
		increased++;
	}
	//데이터 베이스 종료
	mysql_close(&mysql);

	//오늘 날짜 구해서 스테틱 텍스트에 삽입
	ctTime = CTime::GetCurrentTime();
	today.Format(_T("%04d년 %02d월 %02d일"),ctTime.GetYear(),ctTime.GetMonth(),ctTime.GetDay());
	GetDlgItem(IDC_News)->SetWindowText(today);

	//랜덤으로 뉴스 발생
	srand((unsigned int)time(NULL));
	randNews[0]=rand()%newsfig;
	randNews[1]=rand()%newsfig;
	randNews[2]=rand()%newsfig;
	randNews[3]=rand()%newsfig;
	randNews[4]=rand()%newsfig;

	//중복되는 숫자 없애기.
	for (int j=0;j<4;j++)
	{
		for(int i=j+1;i<5;i++)
		{
			if(randNews[j]==randNews[i])
			{
				randNews[i]=rand()%newsfig;
				j=-1;
				break;
			}
		}
	}


	//뉴스창에 뉴스 띄우기
	UpdateData(TRUE);
	m_News1=newsArticle[randNews[0]];
	m_News2=newsArticle[randNews[1]];
	m_News3=newsArticle[randNews[2]];
	m_News4=newsArticle[randNews[3]];
	m_News5=newsArticle[randNews[4]];
	UpdateData(FALSE);
	setNewsDlg(today,newsArticle[randNews[0]]);
	setNewsDlg(today,newsArticle[randNews[1]]);
	setNewsDlg(today,newsArticle[randNews[2]]);
	setNewsDlg(today,newsArticle[randNews[3]]);
	setNewsDlg(today,newsArticle[randNews[4]]);

	//타이머.
	SetTimer(200, 5000, NULL);
	SetTimer(100, 60000, NULL); 


	start=clock();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

	

void C윈플Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.


void C윈플Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR C윈플Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C윈플Dlg::OnClickLstStocks(NMHDR *pNMHDR, LRESULT *pResult)
{

}

void C윈플Dlg::OnClickLststock(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	stockIndex = pNMItemActivate->iItem;
	if(stockIndex >= 0 && stockIndex < m_lstStock.GetItemCount())
	{
		sName=m_lstStock.GetItemText(stockIndex,0);
		curPrice=_wtol( CA2W(m_lstStock.GetItemText(stockIndex,1)));

		mQuantity=_wtol( CA2W(m_lstStock.GetItemText(stockIndex,3)));
		checkMouseClick_Buy=true;
	}

	*pResult = 0;	
}


void C윈플Dlg::OnBnClickedBuy()
{

	if(checkMouseClick_Buy==true)
	{
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//시장의 거래량부터 늘리자.
		CString bQuantity;//구매량을 임시 저장할 문자열변수
		CString str_cash;
		long temp;//그 문자열 변수를 숫자로서 저장할 변수
		bool check=0;
		//구매량 받아옴
		GetDlgItem(IDC_edtBNum)->GetWindowText(bQuantity);
		//숫자로 변환
		temp=_wtol( CA2W(bQuantity));
		if(temp==0)
			MessageBox(_T("구매량이 0입니다."));
		else
		{
			//거래량에 추가
			mQuantity=mQuantity+temp;
			//사용 용도 끝나서 재활용함. 현재 추가된 거래량 저장함
			bQuantity.Format(_T("%d"),mQuantity);
			//남은 현금 깎자.

			l_cash=getCash();
			l_cash-=curPrice*temp;
			if(l_cash>=0)
			{
				check=1;
				str_cash.Format(_T("%ld"),l_cash);
				GetDlgItem(IDC_Cash)->SetWindowText(str_cash);
			}
			else
				MessageBox(_T("현금이 부족하다."));
			//시장 목록에 저장.
			if(check==1){
				m_lstStock.SetItemText(stockIndex,3,bQuantity);
				LV_ITEM m_lItem;
				m_lItem.pszText = (LPTSTR)(LPCTSTR)sName;
				m_lItem.iItem = mSelIndex;	//col
				m_lItem.iSubItem = 0;//row
				m_lstMyStock.InsertItem( &m_lItem );
				//내 주식에 저장
				SetMyStock(temp);

			}

			checkMouseClick_Buy=false;
		}
	}
	else
		MessageBox(_T("구매할 종목을 선택해 주세요."));
}


void C윈플Dlg::OnNMClickLstMyStock(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	myStockIndex = pNMItemActivate->iItem;
	if(myStockIndex >= 0 && myStockIndex < m_lstMyStock.GetItemCount())
	{
		m_sName=m_lstMyStock.GetItemText(myStockIndex,0);
		myPrice=_wtol( CA2W(m_lstMyStock.GetItemText(myStockIndex,4)));
		myQuantity=_wtol( CA2W(m_lstMyStock.GetItemText(myStockIndex,1)));
		boughtPrice=_wtol( CA2W(m_lstMyStock.GetItemText(myStockIndex,3)));
		checkMouseClick_Sell=true;
	}
	*pResult = 0;
}

void C윈플Dlg::OnBnClickedSell()
{

	if(checkMouseClick_Sell==true)
	{

		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString sQuantity;//판매량 임시 저장할 문자열변수
		long temp;//그 문자열 변수를 숫자로서 저장할 변수

		GetDlgItem(IDC_edtSNum)->GetWindowText(sQuantity);

		//숫자로 변환

		temp=_wtol( CA2W(sQuantity));	//판매할 양
		if(temp==0)
			MessageBox(_T("판매량이 0입니다."));
		else
		{
			//거래량에 추가
			myQuantity=myQuantity-temp;
			//사용 용도 끝나서 재활용함. 현재 추가된 거래량 저장함
			sQuantity.Format(_T("%ld"),myQuantity);
			//현재 금액 관리.
			CString cash;
			CString prop_str;

			//만약 판매할 량과 보유량이 같다면
			if(myQuantity==0)
			{
				m_lstMyStock.DeleteItem(myStockIndex);
				mSelIndex--;

			}
			else if(myQuantity>0)
			{
				m_lstMyStock.SetItemText(myStockIndex,1,sQuantity);
			}
			else if(myQuantity<0)
				MessageBox(_T("판매하려는 수량이 보유량보다 많습니다."));

			//현금 가져오기.
			GetDlgItem(IDC_Cash)->GetWindowText(cash);
			l_cash=_wtol( CA2W(cash))+myPrice*temp;
			cash.Format(_T("%ld"),l_cash);
			GetDlgItem(IDC_Cash)->SetWindowText(cash);

			//차액 적용해서 자산 바꾸기
			long tempQuantity=0;
			long tempPrice=0;
			long tempSum=0;
			for(int i=0;i<mSelIndex;i++)
			{
				tempPrice=_wtol( CA2W(m_lstMyStock.GetItemText(i,4)));
				tempQuantity=_wtol( CA2W(m_lstMyStock.GetItemText(i,1)));
				tempSum+=tempPrice*tempQuantity;

			}
			cash.Format(_T("%ld"),l_cash+tempSum);
			GetDlgItem(IDC_prop)->SetWindowText(cash);

			setTradeDlg(_T("판매"),m_sName,temp,today,myPrice);

			checkMouseClick_Sell=false;
			isFinished();
		}
	}

	else
		MessageBox(_T("판매할 종목을 선택해 주세요."));
}


void C윈플Dlg::SetMyStock(long quantity)
{
	CString temp;
	CString mName;
	CString p;
	long mPrice=0;
	int index=0;
	bool check=0;
	long mQuantity=0;
	LV_ITEM m_lItem;
	m_lItem.mask = LVIF_TEXT;

	for(int i=0;i<=m_lstMyStock.GetItemCount();i++)
	{	
		if(sName.Compare(m_lstMyStock.GetItemText(i,0))==0)
		{
			index=i;
			check=1;
			mPrice=_wtoi( CA2W(m_lstMyStock.GetItemText(i,3)));
			mQuantity=_wtoi( CA2W(m_lstMyStock.GetItemText(i,1)));

		}
	}
	setTradeDlg(_T("구입"),sName,quantity,today,curPrice);
	if(check&&curPrice==mPrice)
	{
		//보유량
		temp.Format(_T("%ld"),quantity+mQuantity);

		m_lItem.pszText = (LPTSTR)(LPCTSTR)temp;
		m_lItem.iItem = index;
		m_lItem.iSubItem = 1;
		m_lstMyStock.SetItem( &m_lItem );

		// 금일
		m_lItem.pszText = (LPTSTR)(LPCSTR)today;
		m_lItem.iItem = index;
		m_lItem.iSubItem = 2;
		m_lstMyStock.SetItem( &m_lItem );

		//매입가
		temp.Format(_T("%ld"),curPrice);

		m_lItem.pszText = (LPTSTR)(LPCTSTR)temp;
		m_lItem.iItem = index;
		m_lItem.iSubItem = 3;
		m_lstMyStock.SetItem( &m_lItem );

		//현재가
		m_lItem.pszText = (LPTSTR)(LPCTSTR)temp;
		m_lItem.iItem = index;
		m_lItem.iSubItem = 4;
		m_lstMyStock.SetItem( &m_lItem );

		temp.Format(_T("0"));

		//
		//평가손익
		m_lItem.pszText =  (LPTSTR)(LPCTSTR)temp;
		m_lItem.iItem = index;
		m_lItem.iSubItem = 5;
		m_lstMyStock.SetItem( &m_lItem );

		//수익률
		long profit=_wtoi( CA2W(temp));
		temp.Format(_T("%f"),(profit/curPrice)*100);

		m_lItem.pszText = (LPTSTR)(LPCTSTR)temp;
		m_lItem.iItem = index;
		m_lItem.iSubItem = 6;
		m_lstMyStock.SetItem( &m_lItem );
	}
	else
	{

		m_lItem.pszText = (LPTSTR)(LPCTSTR)sName;
		m_lItem.iItem = mSelIndex;		//col
		m_lItem.iSubItem = 0;	//row
		m_lstMyStock.InsertItem( &m_lItem );

		temp.Format(_T("%ld"),quantity);

		m_lItem.pszText = (LPTSTR)(LPCTSTR)temp;
		m_lItem.iItem = mSelIndex;
		m_lItem.iSubItem = 1;
		m_lstMyStock.SetItem( &m_lItem );

		// 비어 있는 열의 값 추가(2번째)
		m_lItem.pszText = (LPTSTR)(LPCSTR)today;
		m_lItem.iItem = mSelIndex;
		m_lItem.iSubItem = 2;
		m_lstMyStock.SetItem( &m_lItem );

		temp.Format(_T("%ld"),curPrice);

		m_lItem.pszText = (LPTSTR)(LPCTSTR)temp;
		m_lItem.iItem = mSelIndex;
		m_lItem.iSubItem = 3;
		m_lstMyStock.SetItem( &m_lItem );

		m_lItem.pszText = (LPTSTR)(LPCTSTR)temp;
		m_lItem.iItem = mSelIndex;
		m_lItem.iSubItem = 4;
		m_lstMyStock.SetItem( &m_lItem );

		temp.Format(_T("0"));

		// 비어 있는 열의 값 추가(2번째)
		m_lItem.pszText =  (LPTSTR)(LPCTSTR)temp;
		m_lItem.iItem = mSelIndex;
		m_lItem.iSubItem = 5;
		m_lstMyStock.SetItem( &m_lItem );

		long profit=_wtoi(CA2W(temp));
		temp.Format(_T("%f"),(profit/curPrice)*100);

		m_lItem.pszText = (LPTSTR)(LPCTSTR)temp;
		m_lItem.iItem = mSelIndex;
		m_lItem.iSubItem = 6;
		m_lstMyStock.SetItem( &m_lItem );
		mSelIndex++;
	}


}



void C윈플Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString str,tempsum;
	int sum=0;
	CString temp;
	int price=0;
	int affection=0;
	float balancer=1.0;//10만원 이상 주식은 변동이 10배가격에서 되도록 하자.

	if(nIDEvent==100)
	{
			srand((unsigned int)time(NULL));
		randNews[0]=rand()%newsfig;
		randNews[1]=rand()%newsfig;
		randNews[2]=rand()%newsfig;
		randNews[3]=rand()%newsfig;
		randNews[4]=rand()%newsfig;

		//날짜 하루 올리자!
		CTimeSpan tsAddTime(1,0,0,0);
		ctTime+=tsAddTime;
		today.Format(_T("%04d년 %02d월 %02d일"),ctTime.GetYear(),ctTime.GetMonth(),ctTime.GetDay());
		GetDlgItem(IDC_News)->SetWindowText(today);
		

		//중복되는 숫자 없애기.
		for (int j=0;j<4;j++)
		{
			for(int i=j+1;i<5;i++)
			{
				if(randNews[j]==randNews[i])
				{
					randNews[i]=rand()%newsfig;
					j=-1;
					break;
				}
			}
		}

		//뉴스창에 뉴스 띄우기
		UpdateData(TRUE);
		m_News1=newsArticle[randNews[0]];
		m_News2=newsArticle[randNews[1]];
		m_News3=newsArticle[randNews[2]];
		m_News4=newsArticle[randNews[3]];
		m_News5=newsArticle[randNews[4]];
		UpdateData(FALSE);
		//뉴스내역에 추가하자!
		setNewsDlg(today,newsArticle[randNews[0]]);
		setNewsDlg(today,newsArticle[randNews[1]]);
		setNewsDlg(today,newsArticle[randNews[2]]);
		setNewsDlg(today,newsArticle[randNews[3]]);
		setNewsDlg(today,newsArticle[randNews[4]]);


	}
	else if(nIDEvent==200)
	{

		int randtemp=0;
		CString cName;
		long value=0;
		long quantity=0;

		for(int i=0;i<stockfig;i++)
		{	
			price=_wtol( CA2W(m_lstStock.GetItemText(i,1)));
			cName=m_lstStock.GetItemText(i,0);
			if(price>=5000000)
				balancer=10;
			for(int j=0;j<5;j++)
			{
				if(newsId[randNews[j]]==1)
					randtemp+=getRand(newsMin[randNews[j]],newsMax[randNews[j]])*balancer;
				else if(newsId[randNews[j]]==stockId[i])
					randtemp+=getRand(newsMin[randNews[j]],newsMax[randNews[j]])*balancer;
			}
			price+=randtemp;
			temp.Format(_T("%ld"),price);
			m_lstStock.SetItemText(i,1,temp);


			//내 주식에 있는 주식들 현재가, 평가손익, 수익률 변경해주기.
			long bPrice=0;
			for(int j=0;j<m_lstMyStock.GetItemCount();j++)
				if(cName.Compare(m_lstMyStock.GetItemText(j,0))==0)
				{
					temp.Format(_T("%ld"),price);
					m_lstMyStock.SetItemText(j,4,temp);
					quantity=_wtol( CA2W(m_lstMyStock.GetItemText(j,1)));
					//매입가 가져오자.
					bPrice=_wtol( CA2W(m_lstMyStock.GetItemText(j,3)));
					//평가손익 계산.
					temp.Format(_T("%ld"),price*quantity-bPrice*quantity);
					m_lstMyStock.SetItemText(j,5,temp);
					//수익률 계산
					temp.Format(_T("%.2lf %%"),((double)price/bPrice-1)*100);
					m_lstMyStock.SetItemText(j,6,temp);

					value+=price*quantity;

				}
		}

		long cash=getCash();
		temp.Format(_T("%ld"),cash+value);
		GetDlgItem(IDC_prop)->SetWindowText(temp);

		randtemp=0;
	}

	CDialog::OnTimer(nIDEvent);
}

int C윈플Dlg::getRand(int min,int max)
{
	int random=0;
	srand((unsigned int)time(NULL));
	while(1)
	{

		random=rand()%4000-2000;
		if(random>=min&&random<=max)
			break;
	}
	return random;
}

void C윈플Dlg::OnBnClickedbtnbnew()
{
	
	nr.DoModal();
}

void C윈플Dlg::OnBnClickedbtnhtry()
{
	tr.DoModal();
}

long C윈플Dlg::getCash()
{
	long a=0;
	CString str_cash;

	GetDlgItem(IDC_Cash)->GetWindowText(str_cash);
	a=_wtol( CA2W(str_cash));

	return a;
}

void C윈플Dlg::isFinished()
{
	long cash=getCash();
	CString temp;
	if(cash>=500000)
	{
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;//끝시간시작을초
		temp.Format(_T("%.2lf"),duration);
		MessageBox(_T("목표치를 다 채우셨습니다.\n게임이 끝났습니다!\n소요 시간 : ")+temp);
		takeName.DoModal();


		//데이터베이스 연동!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
		MYSQL mysql;
	
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

		// 쿼리 요청	
		CString querry;
		querry.Format(_T("insert into players values('%s','%lf')"),takeName.pName,duration);
		MessageBox(querry);
		if (mysql_query(&mysql,querry)!= 0)
			MessageBox(_T("fail"));

		m_res=mysql_store_result(&mysql);

		//쿼리 끝
		dt.DoModal();
		exit(1);
	}
}

void CAboutDlg::OnBnClickedOk()
{

	CDialog::OnOK();
}

void C윈플Dlg::setTradeDlg(CString div, CString stock, long quantity, CString date, long price)
{
	CString temp;

	tr.div.AddTail(div);

	tr.stock.AddTail(stock);

	temp.Format(_T("%ld"),quantity);
	tr.quantity.AddTail(temp);

	tr.date.AddTail(date);

	temp.Format(_T("%ld"),price);
	tr.price.AddTail(temp);
}

void C윈플Dlg::setNewsDlg(CString date,CString article)
{

	nr.date.AddTail(date);
	nr.article.AddTail(article);

}