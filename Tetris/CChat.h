#pragma once


// CChat 대화 상자

class CChat : public CDialogEx
{
	DECLARE_DYNAMIC(CChat)

public:

	CChat(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CChat();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg
		//virtual BOOL OnInitDialog();
	void OnBnClickedSend();
	CListBox m_List;
	CString m_strMessage;
	afx_msg void OnBnClickedMult();

private:
	char m_connect_flag = 0;
	SOCKET mh_socket = INVALID_SOCKET;
public:
	afx_msg void OnDestroy();
	void AddEventString(const CString ap_string);
	
protected:
	afx_msg LRESULT On25001(WPARAM wParam, LPARAM lParam);
	afx_msg
		//void SendFrameData(SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, char* ap_send_data);
	//void SendFrameData(SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, CString ap_send_data);
	void SendFrameData(SOCKET ah_socket, char a_message_id, unsigned short int a_body_size, char* ap_send_data);
	LRESULT On25002(WPARAM wParam, LPARAM lParam);
public:
	CEdit m_EditId;
};
