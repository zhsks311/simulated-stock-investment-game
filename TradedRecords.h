#pragma once
#include "afxcmn.h"


// TradedRecords ��ȭ �����Դϴ�.

class TradedRecords : public CDialogEx
{
	DECLARE_DYNAMIC(TradedRecords)

public:
	TradedRecords(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TradedRecords();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstTrade;
	CStringList div;
	CStringList stock;
	CStringList quantity;
	CStringList date;
	CStringList price;


};
