#pragma once


// NameScan ��ȭ �����Դϴ�.

class NameScan : public CDialogEx
{
	DECLARE_DYNAMIC(NameScan)

public:
	NameScan(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~NameScan();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	CString m_Name;
	CString pName;
};
