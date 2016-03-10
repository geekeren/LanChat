#pragma once

#include "Resource.h"
#include "Session.h"

// ChatDialog �Ի���

class ChatDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ChatDialog)
private:
	Session * session;

public:
	BOOL OnInitDialog();
	ChatDialog();
	ChatDialog(CWnd* pParent ,Session* session);   // ��׼���캯��
	virtual ~ChatDialog();

 //�Ի�������
	enum { IDD = IDD_CHATDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT HandleNewMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
