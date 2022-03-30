
// TetrisDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Tetris.h"
#include "TetrisDlg.h"
#include "afxdialogex.h"
#include "CBackColor.h"
#include "LoginDlg.h"

#include "CShapeI.h"
#include "CShapeJ.h"
#include "CShapeL.h"
#include "CShapeRect.h"
#include "CShapeS.h"
#include "CShapeT.h"
#include "CShapeZ.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTetrisDlg 대화 상자


CTetrisDlg::CTetrisDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TETRIS_DIALOG, pParent), _next_block(nullptr), _game_state(STATE_BEFORE_LOGIN)
{
	int background = AfxGetApp()->GetProfileInt(_T("Color"), _T("Background"), CTetrisPalette::BG_WHITE);//레지스트리 값 읽기
	_tetris_frame.set_bgcolor((CTetrisPalette::brush_e)background);
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	buttonColor.CreateSolidBrush(RGB(255, 255, 0));
	
	font.CreatePointFont(85, _T("Time New Romans"));

	_pDlg = new CChat;
}

void CTetrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CTetrisDlg, CDialogEx)
	
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDC_BACKCOLOR, &CTetrisDlg::OnBackcolor)
	ON_COMMAND(IDC_MUIT_CHAT, &CTetrisDlg::OnMuitChat)
	ON_COMMAND(IDC_LOGIN, &CTetrisDlg::OnLogin)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTetrisDlg 메시지 처리기

BOOL CTetrisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	initGame();
	_game_state = STATE_BEFORE_LOGIN;
		
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTetrisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CClientDC dc(this);
		CDC BufferDC;
		BufferDC.CreateCompatibleDC(&dc);
		CBitmap bmpBuffer;
		bmpBuffer.CreateCompatibleBitmap(&dc, 600, 349);
		
		CBitmap* pOldBitmap = (CBitmap*)BufferDC.SelectObject(&bmpBuffer);
		
		BufferDC.SelectObject(CTetrisPalette::getInstance()->getPen(CTetrisPalette::WHITE));
		BufferDC.Rectangle(0, 0, 600, 349);

		if (_next_block) _next_block->draw(BufferDC, 10, 31);

		BufferDC.SelectObject(font);
		BufferDC.SetTextAlign(TA_BASELINE | TA_TOP);
		BufferDC.SetBkMode(TRANSPARENT);

		_tetris_frame.draw(BufferDC, 94, 0);

		draw_environment(BufferDC);

		if (STATE_BEFORE_LOGIN == _game_state)
		{
			BufferDC.SelectObject(CTetrisPalette::getInstance()->getPen(CTetrisPalette::BLACK));

			CBrush gameOverBoxColor;
			gameOverBoxColor.CreateSolidBrush(RGB(128, 255, 200));
			BufferDC.SelectObject(gameOverBoxColor);

			BufferDC.Rectangle(111, 120, 261, 190);
			BufferDC.TextOut(115, 155, _T("로그인 해 주세요!"));
		}
		else if (STATE_GAME_WAITING == _game_state)
		{
			BufferDC.SelectObject(CTetrisPalette::getInstance()->getPen(CTetrisPalette::BLACK));

			CBrush gameOverBoxColor;
			gameOverBoxColor.CreateSolidBrush(RGB(128, 255, 200));
			BufferDC.SelectObject(gameOverBoxColor);

			BufferDC.Rectangle(111, 110, 261, 190);
			BufferDC.TextOut(130, 130, _T("Shift 키를 눌러"));
			BufferDC.TextOut(130, 155, _T("게임을 시작해"));
			BufferDC.TextOut(130, 180, _T("주세요!"));
		}
		else if (STATE_GAME_OVER == _game_state)
		{
			BufferDC.SelectObject(CTetrisPalette::getInstance()->getPen(CTetrisPalette::BLACK));

			CBrush gameOverBoxColor;
			gameOverBoxColor.CreateSolidBrush(RGB(128, 255, 200));
			BufferDC.SelectObject(gameOverBoxColor);

			BufferDC.Rectangle(111, 120, 261, 190);
			BufferDC.TextOut(152, 150, _T("Game Over!"));
			CString str;
			str.Format(_T("Score : %d"), score);
			BufferDC.TextOut(152, 170, str);
		}

		dc.BitBlt(0, 0, 600, 349, &BufferDC, 0, 0, SRCCOPY);
		BufferDC.SelectObject(pOldBitmap);
		BufferDC.DeleteDC();

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTetrisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTetrisDlg::nextFrame(void)
{
	int nowDeletedLine = _tetris_frame.takeDeletedLines();
	if (nowDeletedLine)
	{
		deletedLine += nowDeletedLine;
		beDeletingLine -= nowDeletedLine;
		// 라인이 모두 지워지면
		if (beDeletingLine < 1)
		{
			level++;		// 레벨이 올라간다.
			beDeletingLine = 4 + level;

			speed_up();
		}
		if (nowDeletedLine == 0)
		{
			score += level;
		}
		else
		{
			score += 10 + 2 * (nowDeletedLine - 1);
		}
	}

	if (_tetris_frame.no_moving_block())
	{
		if (_tetris_frame.insertBlock(_next_block))
			_next_block = generate_random_block();
		else
		{
			_game_state = STATE_GAME_OVER;
			KillTimer(0);
		}
	}
}

void CTetrisDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (STATE_BEFORE_LOGIN == _game_state)
		return;

	// TODO: Add your message handler code here and/or call default
	if (VK_SHIFT == nChar)
	{
		initGame();
		startGame();
		_game_state = STATE_GAME_PLAYING;
	}
	else if (VK_F2 == nChar)
	{
		puseSound();
	}
	else if (STATE_GAME_PLAYING == _game_state)
	{
		_tetris_frame.on_key_down(nChar);
	}
	Invalidate(FALSE);

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CTetrisDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam != VK_RETURN)
	{
		SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
		return TRUE;
	}
	else

	return CDialog::PreTranslateMessage(pMsg);
}

void CTetrisDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 0)
	{
		_tetris_frame.on_timer();

		nextFrame();

		Invalidate(FALSE);
	}

	CDialog::OnTimer(nIDEvent);
}

void CTetrisDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}

void CTetrisDlg::initGame()
{
	score = 0;
	level = 1;
	delayTime = 500;
	deletedLine = 0;
	beDeletingLine = 5;

	_tetris_frame.initMap();
}

void CTetrisDlg::startGame()
{
	if(STATE_GAME_WAITING == _game_state)
		PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_ASYNC | SND_RESOURCE);

	if (_next_block) delete _next_block;
	_next_block = generate_random_block();

	_tetris_frame.insertBlock(_next_block);
	_next_block = generate_random_block();

	SetTimer(0, delayTime, NULL);
}

void CTetrisDlg::OnBackcolor()
{
	if(STATE_GAME_PLAYING == _game_state)
		KillTimer(0);

	CBackColor dlg;
	if (dlg.DoModal() == IDOK)
	{
		CTetrisPalette::brush_e nIndex = dlg.GetColorIndex();
		_tetris_frame.set_bgcolor(nIndex);
		AfxGetApp()->WriteProfileInt(_T("Color"), _T("Background"), nIndex); //값변경

		Invalidate(false);//화면 업데이트 
	}

	if (STATE_GAME_PLAYING == _game_state)
		SetTimer(0, delayTime, NULL);
}

void CTetrisDlg::puseSound()
{
	PlaySound(NULL, NULL, NULL);
}



void CTetrisDlg::OnMuitChat()
{
	if (_pDlg)
	{
		_pDlg->Create(IDD_CHAT);
		_pDlg->ShowWindow(SW_SHOW);
	}
}

void CTetrisDlg::OnLogin()
{
	CLoginDlg dlg;
	if (IDOK == dlg.DoModal() && dlg.login_success())
	{
		_game_state = STATE_GAME_WAITING;
		Invalidate(FALSE);
	}
}

void CTetrisDlg::speed_up()
{
	if (delayTime > 300)
	{
		delayTime = (int)(delayTime * 0.8);
	}
	if (delayTime < 200 && delayTime <= 300)
	{
		delayTime = (int)(delayTime * 0.85);
	}
	if (delayTime > 100 && delayTime <= 200)
	{
		delayTime = (int)(delayTime * 0.9);
	}
	if ((delayTime * 0.9 != 0) && (delayTime <= 100))
	{
		delayTime = (int)(delayTime * 0.95);
	}
	if (delayTime * 0.9 == 0)
	{
		delayTime = 1;
	}

	SetTimer(0, delayTime, NULL);
}

void CTetrisDlg::draw_environment(CDC& dc)
{
	CString str;

	dc.TextOut(5, 120, _T("Score"));
	str.Format(_T(": %d"), score);
	dc.TextOut(50, 120, str);

	dc.TextOut(5, 140, _T("Level"));
	str.Format(_T(": %d"), level);
	dc.TextOut(50, 140, str);

	dc.TextOut(5, 160, _T("Speed"));
	str.Format(_T(": %d"), (15000 / delayTime));
	dc.TextOut(50, 160, str);

	dc.TextOut(5, 180, _T("Line"));
	str.Format(_T(": %d"), deletedLine);
	dc.TextOut(50, 180, str);

	dc.TextOut(5, 200, _T("Remain"));
	str.Format(_T(": %d"), beDeletingLine);
	dc.TextOut(50, 200, str);

	dc.SelectObject(buttonColor);
	dc.SelectObject(CTetrisPalette::getInstance()->getPen(CTetrisPalette::BLACK));
	dc.Rectangle(12, 235, 82, 272);
	dc.TextOut(17, 250, _T("New Game"));
	dc.TextOut(26, 265, _T("(Shift)"));

	dc.SelectObject(buttonColor);
	dc.SelectObject(CTetrisPalette::getInstance()->getPen(CTetrisPalette::BLACK));
	dc.Rectangle(12, 275, 82, 312);
	dc.TextOut(17, 290, _T("Stop Music"));
	dc.TextOut(26, 305, _T("(F2)"));
}

CShape* CTetrisDlg::generate_random_block()
{
	int blockType = rand() % 7;
	CShape* shape(nullptr);

	switch (blockType)
	{
	case 0:	shape = new CShapeI(CTetrisPalette::BLOCK_0);		break;
	case 1:	shape = new CShapeJ(CTetrisPalette::BLOCK_1);		break;
	case 2:	shape = new CShapeL(CTetrisPalette::BLOCK_2);		break;
	case 3:	shape = new CShapeRect(CTetrisPalette::BLOCK_3);	break;
	case 4:	shape = new CShapeS(CTetrisPalette::BLOCK_4);		break;
	case 5:	shape = new CShapeT(CTetrisPalette::BLOCK_5);		break;
	case 6:	shape = new CShapeZ(CTetrisPalette::BLOCK_6);		break;
	}

	return shape;
}


void CTetrisDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	KillTimer(0);

	if (_next_block) delete _next_block;

	if(_pDlg) delete _pDlg;
}
