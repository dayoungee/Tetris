#pragma once
//#include "TetrisFrame.h"
//#include "TetrisDlg.h"
// CBackColor 대화 상자

#include "CTetrisPalette.h"

#define BACKGROUND_STR_BLUE		_T("파랑색")
#define BACKGROUND_STR_PINK		_T("핑크색")
#define BACKGROUND_STR_WHITE	_T("흰색")

class CBackColor : public CDialogEx
{
	DECLARE_DYNAMIC(CBackColor)

public:
	CBackColor(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBackColor();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BACKCOLOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	virtual BOOL OnInitDialog();

protected:

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked();
	CTetrisPalette::brush_e GetColorIndex();

private:
	CComboBox combo;
	CTetrisPalette::brush_e _bgColor;
};
