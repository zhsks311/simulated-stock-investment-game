#pragma once


// NameScan 대화 상자입니다.

class NameScan : public CDialogEx
{
	DECLARE_DYNAMIC(NameScan)

public:
	NameScan(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~NameScan();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	CString m_Name;
	CString pName;
};
