#pragma once
#include "afxcmn.h"


// data 대화 상자입니다.

class data : public CDialogEx
{
	DECLARE_DYNAMIC(data)

public:
	data(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~data();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstRank;
};
