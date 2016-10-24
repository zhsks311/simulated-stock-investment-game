#pragma once
#include "afxcmn.h"


// NewsRecord 대화 상자입니다.

class NewsRecord : public CDialogEx
{
	DECLARE_DYNAMIC(NewsRecord)

public:
	NewsRecord(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~NewsRecord();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstNews;
	CStringList date;
	CStringList article;

};
