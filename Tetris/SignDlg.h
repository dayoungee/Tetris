#pragma once


// CSignDlg 대화 상자

class CSignDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSignDlg)

public:
	CSignDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSignDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CString id;
	CString pass;
	char astr[1024];
	size_t CharactersConverted = 0;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
