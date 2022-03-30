// CBackColor.cpp: 구현 파일
//

#include "pch.h"
#include "Tetris.h"
#include "CBackColor.h"
#include "afxdialogex.h"



// CBackColor 대화 상자

IMPLEMENT_DYNAMIC(CBackColor, CDialogEx)

CBackColor::CBackColor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BACKCOLOR, pParent)
	
	//, p_tetrisDlg(NULL)
{
	//p_tetrisDlg = (CTetrisDlg*)pParent;
}

CBackColor::~CBackColor()
{
}

void CBackColor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, combo);
}


BEGIN_MESSAGE_MAP(CBackColor, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBackColor::OnBnClicked)
	
END_MESSAGE_MAP()

BOOL CBackColor::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowText(_T("배경색 바꾸기"));
	combo.AddString(BACKGROUND_STR_BLUE);                   //텍스트 추가
	combo.AddString(BACKGROUND_STR_PINK);
	combo.AddString(BACKGROUND_STR_WHITE);
	return TRUE;  // return TRUE unless you set the focus to a control

}


// CBackColor 메시지 처리기


void CBackColor::OnBnClicked()
{
	int index = combo.GetCurSel();
	if (-1 < index)
	{
		if (0 == index)
		{
			_bgColor = CTetrisPalette::BG_BLUE;
		}
		else if (1 == index)
		{
			_bgColor = CTetrisPalette::BG_PINK;
		}
		else
		{
			_bgColor = CTetrisPalette::BG_WHITE;
		}
	}

	CDialogEx::OnOK();
}

CTetrisPalette::brush_e CBackColor::GetColorIndex() {

	return _bgColor;
}
