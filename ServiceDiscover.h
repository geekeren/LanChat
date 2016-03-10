#pragma once
#include <WinSock2.h>
#include "message.h"
#include "DataManager.h"
#include "user.h"
#include "json\json.h"
#pragma comment (lib ,"lib_json.lib")

#pragma comment (lib ,"ws2_32.lib")

using namespace std;

class ServiceDiscover
{
private:
	DataManager * delegate;
	int  _udp_server;
	int  _udp_socket;
	int  _udp_port;
	sockaddr_in  _client_add;
	sockaddr_in _server_add;
	vector<User *> users;
public:

	ServiceDiscover(DataManager *);
	void upd_socketIitiollize();
	void StartResponseService();//同软件主机,回复服务
	void StartAskLiveService();//询问安装同软件主机
	void  ServiceDiscover::GetMsgFormBuffer(Message *, char *);
	bool close();
	string GetMyLocalIpAddress();
	~ServiceDiscover();

	friend DWORD WINAPI Response(LPVOID);
	friend DWORD WINAPI AskLive(LPVOID);
};

