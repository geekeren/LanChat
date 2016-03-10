#pragma once
#include <vector>
#include "User.h"
#include "Message.h"
#include "Session.h"
#include "SessionManager.h"
#include <WinSock2.h>
#define WM_LISTCHANGE_MESSAGE WM_MY_MESSAGE +1
//数据管理类，将来自网络数据层的数据进行处理解析为业务模型
class DataManager 
{
private :
	//别人给你发消息的服务
	SOCKET MsgServer;

	//服务发现 ,用于发现局域网内安装了同一软件的主机
	SOCKET SeiviceDiscoverServer;

	//存储在局域网内安装了同一软件的主机用户
	vector<User*>* Users;
	//vector<User*>* Users;

	static DataManager* m_pSingleInstance;
	DataManager();
	~DataManager();

public:
	static  DataManager* getInstance();
	void startMsgServer();
	//连接上某个人、主机
	SOCKET connectToUser(User);

	//开启服务发现服务
	void startDiscoverServer();
	//处理同软件发现服务
	virtual void handleServiceDiscoverMsg(Message);
	//处理通信时的信息
	virtual void handleMessage(Message);
	//发送消息
	bool sendMsg(User, Message,SOCKET);

	//处理消息
	void handleMsg(); 


	
	vector<User>& getOnLanUsers();
	 void scanOnLanUsers();

};

