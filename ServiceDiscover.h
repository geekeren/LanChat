#pragma once
#include "DataManager.h"
class ServiceDiscover
{
private:

	int  _udp_serversocket;
	int _udp_socket;
	int  _udp_port;
	sockaddr_in  add;
	sockaddr_in _serveradd;
	
public:
	DataManager* delegate;
	ServiceDiscover(DataManager*);
	void upd_socketIitiollize();
	void StartResponseService();//同软件主机,回复服务
	void StartAskLiveService();//询问安装同软件主机
	bool close();

	~ServiceDiscover();

	friend UINT Response(LPVOID);
	friend UINT AskLive(LPVOID);
};

