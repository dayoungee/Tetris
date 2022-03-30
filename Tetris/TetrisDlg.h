
// TetrisDlg.h: 헤더 파일
//
#pragma once

#include "TetrisFrame.h"
#include "CChat.h"


#define NEXT_BLOCK_PIXEL_START_X	10
#define NEXT_BLOCK_PIXEL_START_Y	31

#define FRAME_PIXEL_START_X
#define FRAME_PIXEL_START_Y

#define FRAME_PIXEL_SIZE_X
#define FRAME_PIXEL_SIZE_Y


#define STATE_BEFORE_LOGIN		0
#define STATE_GAME_WAITING		1
#define STATE_GAME_PLAYING		2
#define STATE_GAME_OVER			3



// CTetrisDlg 대화 상자
class CTetrisDlg : public CDialogEx
{
// 생성입니다.
public:
	CTetrisFrame _tetris_frame;
	CTetrisDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TETRIS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBackcolor();
	afx_msg void OnMuitChat();
	afx_msg void OnLogin();
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()

	void nextFrame(void);
	void initGame();
	void startGame();
	void speed_up();
	void draw_environment(CDC& dc);
	CShape* generate_random_block();
	void puseSound();

private:
	int beDeletingLine;
	int deletedLine;
	int delayTime;
	int level;
	int score;

	CFont font;
	CBrush buttonColor;
	
	HKEY m_hRegkey;

	CShape* _next_block;
	int _game_state;
	CChat* _pDlg;

};
