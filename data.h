#pragma once
#include "afxcmn.h"


// data ��ȭ �����Դϴ�.

class data : public CDialogEx
{
	DECLARE_DYNAMIC(data)

public:
	data(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~data();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstRank;
};
