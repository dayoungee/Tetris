// SignDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Tetris.h"
#include "SignDlg.h"
#include "afxdialogex.h"

#include "CSqlWorker.h"


// CSignDlg 대화 상자

IMPLEMENT_DYNAMIC(CSignDlg, CDialogEx)

CSignDlg::CSignDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIGN, pParent)
{

}

CSignDlg::~CSignDlg()
{
}

void CSignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSignDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSignDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSignDlg 메시지 처리기


void CSignDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_SIGN_ID, id);   //ID에디트창의 Value변수를 id에 저장
	GetDlgItemText(IDC_SIGN_PASS, pass);  //Pass에디트창의 Value변수를 pass저장
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
	CSqlWorker::sql_value_e res = sql.regist_member(id, pass);

	if (CSqlWorker::SQL_RETURN_SUCCESS != res)
	{
		if (CSqlWorker::SQL_CONNECT_FAILED == res)
		{
			AfxMessageBox(_T("데이터베이스 연결에 실패하였습니다."));
		}
		else if (CSqlWorker::SQL_ID_DUPLICATED == res)
		{
			AfxMessageBox(_T("중복되는 아이디가 있습니다."));
		}
		else
		{
			AfxMessageBox(_T("알 수 없는 이유로 가입이 되지 않습니다."));
		}

		return;
	}
	*/
	CDialogEx::OnOK();
}

BOOL CSignDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowText(_T("회원가입"));
	return TRUE;  // return TRUE unless you set the focus to a control

}
