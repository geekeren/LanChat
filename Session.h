#pragma once

//class ClientSocket;
#include "user.h"
#include "message.h"
#include "socket/MyserverSocket.h"
#include <vector>

class ChatDialog;
class Session
{

	
public:
	bool isOnline;
	User m_user;
	//ClientSocket m_clientSocket;
	vector<Message> messageList;
	ChatDialog* chatDialog;
	ClientSocket *client;

	Session(User);
	void setOnline(bool);
	void setDialog(ChatDialog*);
	~Session();
};

