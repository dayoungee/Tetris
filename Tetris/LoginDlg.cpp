// LoginDlg.cpp: 구현 파일
//
#pragma comment(lib,"libmySQL.lib")

#include "pch.h"
#include "Tetris.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "TetrisDlg.h"
#include "SignDlg.h"

#include "CSqlWorker.h"



// CLoginDlg 대화 상자

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent), _login_success(false)
	
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	
	ON_BN_CLICKED(IDC_SIGN, &CLoginDlg::OnBnClickedSign)
END_MESSAGE_MAP()


// CLoginDlg 메시지 처리기


void CLoginDlg::OnBnClickedOk()
{
	CString id, pass;
	GetDlgItemText(IDC_ID, id);   //ID에디트창의 Value변수를 id에 저장
	GetDlgItemText(IDC_PASS, pass);  //Pass에디트창의 Value변수를 pass저장
	/*
	if (0 == id.GetLength())    //에디트창의 길이를 구해서 검사를 하는부분
	{
		AfxMessageBox(_T("ID를 입력해주세요"));
		return;
	}
	else if (0 == pass.GetLength())  //에디트창의 길이를 구해서 검사를 하는부분
	{
		AfxMessageBox(_T("패스워드를 입력해주세요"));
		return;
	}

	CSqlWorker sql;
	CSqlWorker::sql_value_e res = sql.login(id, pass);

	if (CSqlWorker::SQL_RETURN_SUCCESS != res)
	{
		if (CSqlWorker::SQL_CONNECT_FAILED == res)
		{
			AfxMessageBox(_T("데이터베이스 연결에 실패하였습니다."));
		}
		else if (CSqlWorker::SQL_LOGIN_FAILED == res)
		{
			AfxMessageBox(_T("아이디 비번이 틀렸습니다."));
		}
		else
		{
			AfxMessageBox(_T("알 수 없는 이유로 로그인 할 수 없습니다."));
		}

		return;
	}
	
	AfxMessageBox(_T("로그인 성공"));
	*/

	_login_success = true;

	CDialogEx::OnOK();
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowText(_T("로그인"));
	return TRUE;  // return TRUE unless you set the focus to a control

}



void CLoginDlg::OnBnClickedSign()
{
	CSignDlg dlg;
	dlg.DoModal();
}
