#pragma once
#include "afxcmn.h"


// NewsRecord ��ȭ �����Դϴ�.

class NewsRecord : public CDialogEx
{
	DECLARE_DYNAMIC(NewsRecord)

public:
	NewsRecord(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~NewsRecord();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstNews;
	CStringList date;
	CStringList article;

};
