#pragma once
#include "afxcmn.h"


// TradeRecord 대화 상자입니다.

class TradeRecord : public CDialogEx
{
	DECLARE_DYNAMIC(TradeRecord)

public:
	TradeRecord(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TradeRecord();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG5};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_trade;
};
