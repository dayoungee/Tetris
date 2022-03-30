// CChat.cpp: 구현 파일
//

#include "pch.h"
#include "Tetris.h"
#include "CChat.h"
#include "afxdialogex.h"


// CChat 대화 상자

IMPLEMENT_DYNAMIC(CChat, CDialogEx)

CChat::CChat(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT, pParent)
	, m_strMessage(_T(""))
{

}

CChat::~CChat()
{
}

void CChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHAT_LIST, m_List);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strMessage);
	DDX_Control(pDX, IDC_EDIT_ID, m_EditId);
}


BEGIN_MESSAGE_MAP(CChat, CDialogEx)
	ON_BN_CLICKED(IDC_SEND, &CChat::OnBnClickedSend)
	ON_BN_CLICKED(IDC_MULT, &CChat::OnBnClickedMult)
	ON_WM_DESTROY()
	ON_MESSAGE(25001, &CChat::On25001)
	
	ON_MESSAGE(25002, &CChat::On25002)
END_MESSAGE_MAP()




void CChat::OnBnClickedSend()
{
	CString str;
	GetDlgItemText(IDC_EDIT_TEXT, str);
	size_t CharactersConverted = 0;

	
	
	if (m_connect_flag == 2)
	{
		SendFrameData(mh_socket, 1, str.GetLength() + 1, LPSTR(LPCTSTR(str)));
	}
}


void CChat::OnBnClickedMult()
{
	mh_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in srv_addr;
	memset(&srv_addr, 0, sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	srv_addr.sin_port = htons(18000);
	WSAAsyncSelect(mh_socket, m_hWnd, 25001, FD_CONNECT);
	m_connect_flag = 1;
	AddEventString(_T("서버에 접속중입니다."));
	connect(mh_socket, (LPSOCKADDR)&srv_addr, sizeof(srv_addr));
	
}


void CChat::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (mh_socket != INVALID_SOCKET)
	{
		closesocket(mh_socket);
		mh_socket = INVALID_SOCKET;
	}
}

void CChat::AddEventString(CString ap_string)
{
	while (m_List.GetCount() > 500)
	{
		m_List.DeleteString(0);
	}
	int index = m_List.InsertString(-1, ap_string);
	m_List.SetCurSel(index);

}


afx_msg LRESULT CChat::On25001(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam))
	{
		m_connect_flag = 0;
		closesocket(mh_socket);
		mh_socket = INVALID_SOCKET;
		AddEventString(_T("서버접속에 실패하였습니다."));
	}
	else
	{
		m_connect_flag = 2;
		WSAAsyncSelect(mh_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
		AddEventString(_T("서버에 접속하였습니다"));
	}

	return 0;
}

//void CChat::SendFrameData()

void CChat::SendFrameData(SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, char* ap_send_data)
{
	char* p_send_data = new char[4 + a_body_size];
	*p_send_data = 27;
	*(p_send_data + 1) = a_message_id;
	*(unsigned short*)(p_send_data + 2) = a_body_size;
	memcpy(p_send_data + 4, ap_send_data, a_body_size);
	
	CString str;
	GetDlgItemText(IDC_EDIT_ID, str);

	send(ah_socket, p_send_data, a_body_size + 4, 0);
//	send(ah_socket, str, sizeof(str), 0);
	delete[] p_send_data;
}


afx_msg LRESULT CChat::On25002(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTEVENT(lParam) == FD_READ)
	{
		if (WSAGETSELECTEVENT(lParam) == FD_READ)
		{
			WSAAsyncSelect(wParam, m_hWnd, 25002, FD_CLOSE);

			char key;
			recv(wParam, &key, 1, 0);
			if (key == 27)
			{
				char message_id;
				recv(wParam, &message_id, 1, 0);
				unsigned short int body_size;
				recv(wParam, (char*)&body_size, 2, 0);

				char* p_body_data = NULL;
				if (body_size > 0)
				{
					p_body_data = new char[body_size];

					int total = 0, x;
					int retry = 0;
					while (total < body_size) {
						x = recv(wParam, p_body_data + total, body_size - total, 0);
						if (x == SOCKET_ERROR) break;
						total = total + x;
						if (total < body_size)
						{
							Sleep(50);
							retry++;
							if (retry > 5) break;
						}
					}
				}
				
				if (message_id == 1)
				{
					AddEventString(p_body_data);
				}
				if (p_body_data != NULL) delete[] p_body_data;

				WSAAsyncSelect(wParam, m_hWnd, 25002, FD_READ | FD_CLOSE);
			}
		}
	}
	else
	{
		closesocket(wParam);
		/*CString str;
		for (int i = 0; i < MAX_USER_COUNT; i++)
		{
			if (m_user_list[i].h_socket == wParam)
			{
				m_user_list[i].h_socket = INVALID_SOCKET;
				str.Format(_T("사용자가 종료했습니다. : %s"), m_user_list[i].ip_address);
				AddEventString(str);
				break;
			}
		}*/
	}
	return 0;
}
