#pragma once
#include "afxcmn.h"


// TradeRecord ��ȭ �����Դϴ�.

class TradeRecord : public CDialogEx
{
	DECLARE_DYNAMIC(TradeRecord)

public:
	TradeRecord(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TradeRecord();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG5};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_trade;
};
