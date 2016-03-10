#pragma once

#include "Resource.h"
#include "Session.h"

// ChatDialog 对话框

class ChatDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ChatDialog)
private:
	Session * session;

public:
	BOOL OnInitDialog();
	ChatDialog();
	ChatDialog(CWnd* pParent ,Session* session);   // 标准构造函数
	virtual ~ChatDialog();

 //对话框数据
	enum { IDD = IDD_CHATDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT HandleNewMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
