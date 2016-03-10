
#include <string>
#include <iostream>

#include "stdafx.h"
#include "ServiceDiscover.h"

using namespace std;

ServiceDiscover::ServiceDiscover(DataManager * delegate)
:_udp_socket(-1), _udp_port(8082)
{
	this->delegate = delegate;
	upd_socketIitiollize();
}

ServiceDiscover::~ServiceDiscover()
{
	close();
}

void ServiceDiscover::upd_socketIitiollize(){
	WSADATA wsdata;
	//启动SOCKET库，版本为2.0  
	if (WSAStartup(0x0202, &wsdata) != 0){
		printf("startup is failed\n");
		return;
	}
	////询问socket
	_client_add.sin_family = AF_INET;
	_client_add.sin_addr.s_addr = htons(INADDR_ANY);
	_client_add.sin_port = htons(0);

	this->_udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (this->_udp_socket == INVALID_SOCKET){
		printf("udp socket 初始化错误\n");
		return;
	}
	///设置为广播
	int opt = 1;
	int ret = setsockopt(this->_udp_socket, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt));
	if (ret != 0){
		printf("udp socket 初始化错误\n");
		return;
	}
	///设置非阻塞
	u_long optt = 1;
	int iResult = ioctlsocket(this->_udp_socket, FIONBIO, &optt);
	if (iResult != NO_ERROR){
		printf("ioctlsocket failed with error: %ld\n", iResult);
		return;
	}

	/////////////////////消息返回socket
	_server_add.sin_family = AF_INET;
	_server_add.sin_addr.s_addr = htons(INADDR_ANY);
	_server_add.sin_port = htons(this->_udp_port);

	this->_udp_server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (this->_udp_server == INVALID_SOCKET){
		printf("udp server socket 初始化错误\n");
		return;
	}

	if ((setsockopt(this->_udp_server, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt))) != 0){
		printf("server socket 初始化错误\n");
		return;
	}

	iResult = ioctlsocket(this->_udp_server, FIONBIO, &optt);
	if (iResult != NO_ERROR){
		printf("ioctlsocket failed with error: %ld\n", iResult);
		return;
	}

	if (bind(this->_udp_server, (sockaddr *)&(this->_server_add), sizeof(sockaddr_in)) != 0){
		printf("bind failed\n");
		return;
	}
}



bool ServiceDiscover::close(){
	WSACleanup();
	return false;
}

DWORD WINAPI AskLive(LPVOID pM){
	ServiceDiscover*  that = (ServiceDiscover*)pM;
	sockaddr_in  addto;

	message message;
	message.time = CTime::GetCurrentTime();
	message.msg_type = msg_type_event;
	message.content = "0";
	message.FromID = inet_addr((that->GetMyLocalIpAddress()).c_str());///ip_addr
	message.ToID = 0;
	message.myWPragam = 0;
	char *msg = NULL;
	message.MsgTobuffer(&msg);

	ZeroMemory(&(addto), sizeof(addto));
	(addto).sin_family = AF_INET;
	(addto).sin_addr.s_addr = INADDR_BROADCAST;
	(addto).sin_port = htons(that->_udp_port);
	int nlen = sizeof(addto);
	(that->users).clear();
	while (1){
		int ret = sendto(that->_udp_socket, msg, (int)strlen(msg), 0, (sockaddr *)&(addto), nlen);

		if (ret < 0)
		{
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK){
				Sleep(2000);
			}
			else{
				break;
			}
		}

		DWORD k = ::GetTickCount();
		long beginTime = k / 1000; // se为秒
		long endTime = beginTime + 20;

		while (beginTime < endTime){

			char buf[256];
			ZeroMemory(buf, 256);
			int handle = that->_udp_socket;
			int re = recvfrom(that->_udp_socket, buf, 256, 0, (sockaddr *)&(addto), &nlen);
			if (re>0){
				buf[re] = '\0';
				Message msg;
				that->GetMsgFormBuffer(&msg, buf);
			//	unsigned long id = msg.FromID;
			//	User * user = new User(id);
			//	that->users.push_back(user);
				msg.msg_type = msg_type_error;
				that->delegate->handleServiceDiscoverMsg(msg);
			}
			else{
				int err = WSAGetLastError();
				if (err == WSAEWOULDBLOCK){
					Sleep(2000);
				}
				else{
					break;
				}
				beginTime = ::GetTickCount() / 1000;
			}
			Sleep(2000);
		}
		
	//	that->delegate->notifyUserListChanged(&(that->users));
		Sleep(10000);
	}

	free(msg);
}

DWORD WINAPI Response(LPVOID pM){

	ServiceDiscover* that = (ServiceDiscover*)pM;
	sockaddr_in from;

	int nAddrLen = sizeof(from);
	while (1)
	{
		char buf[256];
		ZeroMemory(&from, nAddrLen);
		int ret = recvfrom(that->_udp_server, buf, 256, 0, (struct sockaddr FAR *)&from, (int FAR *)&nAddrLen);
		if (ret > 0){
			char * buffer = (char*)malloc(ret + 1);
			memcpy(buffer, buf, ret);
			buffer[ret] = '\0';
			message msg;
			that->GetMsgFormBuffer(&msg, buffer);
			that->delegate->handleServiceDiscoverMsg(msg);
			free(buffer);

			message message;
			message.time = CTime::GetCurrentTime();
			message.msg_type = msg_type_event;
			message.content = "0";
			message.FromID = inet_addr((that->GetMyLocalIpAddress()).c_str());///ip_addr
			message.ToID = 0;
			message.myWPragam = 0;

			char* sendbuf = NULL;
			message.MsgTobuffer(&sendbuf);
			int send = sendto(that->_udp_server, sendbuf, strlen(sendbuf), 0, (struct sockaddr FAR *)&from, nAddrLen);
			free(sendbuf);
			ZeroMemory(buf, 256);
		}
		else{
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK){
				Sleep(2000);
			}
			else{
				break;
			}
		}

	}
	return NULL;
}


string ServiceDiscover::GetMyLocalIpAddress()
{
	char local[255] = { 0 };
	gethostname(local, sizeof(local));
	hostent* ph = gethostbyname(local);
	if (ph == NULL)
		return "";
	in_addr addr;
	memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr)); // 这里仅获取第一个ip  
	string localIP;
	localIP.assign(inet_ntoa(addr));
	return localIP;
}
void  ServiceDiscover::GetMsgFormBuffer(Message * msg, char * buffer){
	///	string smsg = "{\"msg_type\":2}";
	string getMsg(buffer);
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(getMsg, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
	{
		//std::stringstream strValue;


		msg->msg_type = root["msg_type"].asInt();  // 访问节点，upload_id = "UP000000"  
		msg->content = root["content"].asString();  // 访问节点，upload_id = "UP000000"  
		string timestr = root["time"].asString();  // 访问节点，upload_id = "UP000000"  
		int    a, b, c, d, e, f;
		sscanf_s(timestr.c_str(), "%d-%d-%d %d:%d:%d", &a, &b, &c, &d, &e, &f);
		CTime    time(a, b, c, d, e, f);
		msg->time = time;
		string from_id = root["FromID"].asString();
		sscanf_s(from_id.c_str(), "%ul", &(msg->FromID));
		string to_id = root["ToID"].asString();

		sscanf_s(to_id.c_str(), "%ul", &(msg->ToID));
		msg->myWPragam = root["myWPragam"].asInt();
	}

}
void ServiceDiscover::StartAskLiveService(){
	HANDLE handle = CreateThread(NULL, 0, AskLive, (void*)this, 0, NULL);
}

void ServiceDiscover::StartResponseService(){
	HANDLE handle = CreateThread(NULL, 0, Response, (void*)this, 0, NULL);
}