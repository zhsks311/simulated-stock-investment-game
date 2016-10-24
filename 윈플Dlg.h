// 윈플Dlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include<afx.h>
#include <atlstr.h>
#include <time.h>	//시간계산을위해time.h헤더를추가함!!
#include"NameScan.h"
#include "data.h"
#include "TradedRecords.h"
#include "NewsRecord.h"
#include<cstdlib>
// C윈플Dlg 대화 상자
class C윈플Dlg : public CDialog
{
// 생성입니다.
public:
	C윈플Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickLstStocks(NMHDR *pNMHDR, LRESULT *pResult);
	int stockIndex;
	int myStockIndex;
	int mSelIndex;
	CString sName;
	CString m_sName;
	long curPrice, mQuantity,m_Quantity; //시장 클릭시 저장시킬 변수
	long myPrice, myQuantity,my_Quantity,boughtPrice;	//내 주식 클릭시 저장시킬 변수
	long l_prop,l_cash;
	CListCtrl m_lstStock;
	CListCtrl m_lstMyStock;
	CSpinButtonCtrl m_spin1;
	CSpinButtonCtrl m_spin2;
	afx_msg void OnBnClickedBuy();
	afx_msg void OnBnClickedSell();
	void SetMyStock(long quantity);
	afx_msg void OnClickLststock(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickLstMyStock(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

//	CString m_New1;
	CString m_News1;
	CString m_News2;
	CString m_News3;
	CString m_News4;
	CString m_News5;
	CString m_Date;
	CString temp1[5];
   //CMapStringToString NewsInfo[6];
   CUIntArray newsId;
   CUIntArray stockId;
   CUIntArray newsMin;
   CUIntArray newsMax;
   CStringArray newsArticle;
   int newsfig,stockfig;
   int newssort;
   int newskey;
   afx_msg void OnBnClickedbtnbnew();
   afx_msg void OnBnClickedbtnhtry();
   int getRand(int min,int max);
   	int randNews[5];
	long getCash();
	bool checkMouseClick_Buy;
	bool checkMouseClick_Sell;
	void isFinished();
	void setTradeDlg(CString div, CString stock, long quantity, CString date, long price);
	void setNewsDlg(CString date,CString article);
	clock_t start,finish;
	double duration;
	NameScan takeName;
	data dt;
	TradedRecords tr;
	NewsRecord nr;
	CString today;
	CTime ctTime;
};

