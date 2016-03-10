#include "stdafx.h"


#pragma comment(lib,"lib_json.lib")




ServiceDiscover::ServiceDiscover(DataManager* delegate) :_udp_socket(-1), _udp_port(8082)
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
		return ;
	}
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = htons(INADDR_ANY);
	add.sin_port = htons(0);
	_serveradd.sin_family = AF_INET;
	_serveradd.sin_addr.s_addr = htons(INADDR_ANY);
	_serveradd.sin_port = htons(this->_udp_port);
	this->_udp_serversocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (this->_udp_serversocket == INVALID_SOCKET){
		printf("udp server socket 初始化错误\n");
	//	WSACleanup();
	}
	this->_udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (this->_udp_socket == INVALID_SOCKET){
		printf("udp socket 初始化错误\n");
		WSACleanup();
	}
	int opt =1000;
	setsockopt(this->_udp_socket, SOL_SOCKET, SO_BROADCAST|SO_RCVTIMEO, (char*)&opt, sizeof(opt));
	setsockopt(this->_udp_serversocket, SOL_SOCKET, SO_BROADCAST , (char*)&opt, sizeof(opt));
}
bool ServiceDiscover::close(){

	return false;
}

UINT AskLive(LPVOID pM){
	Message errmsg;
	errmsg.msg_type = msg_type_error;
	TRACE("%d",pM);
	ServiceDiscover*  that = (ServiceDiscover*)pM;
	DataManager* d = that->delegate;
	sockaddr_in  addto;
	char buf[100] = { 0 };
	Message Message;
	Message.time = CTime::GetCurrentTime();
	Message.msg_type = msg_type_event;
	Message.content = "0";
	Json::Value arrayObj;   // 构建对象  
	Json::Value new_item, new_item1, new_item2;
	new_item["msg_type"] = Message.msg_type;
	new_item1["content"] = Message.content;
	new_item2["time"] = Message.time.Format("%Y-%m-%d %H:%M:%S").GetBuffer(0);
	arrayObj.append(new_item);
	arrayObj.append(new_item1);
	arrayObj.append(new_item2);
	string json = arrayObj.toStyledString();

	const char* msg = json.c_str();
	ZeroMemory(&(addto), sizeof(addto));
	(addto).sin_family = AF_INET;
	(addto).sin_addr.s_addr = INADDR_BROADCAST;
	(addto).sin_port = htons(that->_udp_port);
	int nlen = sizeof(addto);
	
	while (1){
		int ret = sendto(that->_udp_socket, msg, (int)strlen(msg), 0, (sockaddr *)&(addto), nlen);
		
		if (ret == SOCKET_ERROR)
		{
		
			errmsg.content = "发送失败！";
			
//			d->handleServiceDiscoverMsg(errmsg);
		}
	long time    =	::GetCurrentTime();
	long endtime = time + 20;
		while (time < endtime){
			int ret = recvfrom(that->_udp_socket, buf, 256,0 , (struct sockaddr FAR *)&(addto), (int FAR *)&nlen);
			time = ::GetCurrentTime();
		}
		Sleep(2000);
	}
}

UINT Response(LPVOID pM){
	//收到别人的请求之后回复
	Message errmsg;
	errmsg.msg_type = msg_type_error;
	ServiceDiscover* that = (ServiceDiscover*)pM;
	DataManager* d = that->delegate;
	sockaddr_in from;
	// 把该套接字绑定在一个具体的地址上  
	if (bind(that->_udp_serversocket, (sockaddr *)&(that->_serveradd), sizeof(sockaddr_in)) != 0){
		
		errmsg.content = "绑定失败";
		
	//	d->handleServiceDiscoverMsg(errmsg);
		printf("bind failed\n");
		return NULL;
	}



	char buf[256];

	int nAddrLen = sizeof(from);
	while (1)
	{
		Sleep(10);
		ZeroMemory(&from, nAddrLen);
		int ret = recvfrom(that->_udp_serversocket, buf, 256, 0, (struct sockaddr FAR *)&from, (int FAR *)&nAddrLen);
		if (ret != SOCKET_ERROR){

			string getMsg = buf;
			Json::Reader reader;
			Json::Value root;
			if (reader.parse(getMsg, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
			{
				Message getmessage;
				getmessage.msg_type = root["msg_type"].asInt();  // 访问节点，upload_id = "UP000000"  
				getmessage.content = root["content"].asString();  // 访问节点，upload_id = "UP000000"  
				string timestr = root["time"].asString();  // 访问节点，upload_id = "UP000000"  

				//		CString timestr =CString( time.c_str());

				int    a, b, c, d, e, f;
				sscanf_s(timestr.c_str(), "%d-%d-%d %d:%d:%d", &a, &b, &c, &d, &e, &f);
				CTime    time(a, b, c, d, e, f);
				getmessage.time = time;
				that->delegate->handleServiceDiscoverMsg(getmessage);

			}

			Message Message;
			Message.time = CTime::GetCurrentTime();
			Message.msg_type = msg_type_event;
			Message.content = "0";
			Json::Value arrayObj;   // 构建对象  
			Json::Value new_item, new_item1, new_item2;
			new_item["msg_type"] = Message.msg_type;
			new_item1["content"] = Message.content;
			new_item2["time"] = Message.time.Format("%Y-%m-%d %H:%M:%S").GetBuffer(0);
			arrayObj.append(new_item);
			arrayObj.append(new_item1);
			arrayObj.append(new_item2);
			string json = arrayObj.toStyledString();
			const char* msg = json.c_str();
			sendto(that->_udp_serversocket, msg, strlen(msg), 0, (struct sockaddr FAR *)&from, nAddrLen);
			ZeroMemory(buf, 256);
		}
	
	}
	return 0;
}

void ServiceDiscover::StartAskLiveService(){
	LPVOID PM = (LPVOID)this;
	TRACE("%d", PM);
	CWinThread* handle = AfxBeginThread(AskLive, PM, 0, 0, 0, NULL);
	

}

void ServiceDiscover::StartResponseService(){
	LPVOID PM = (LPVOID)this;
	TRACE("%d", PM);
	CWinThread* handle = AfxBeginThread(Response, PM, 0,0, 0, NULL);
	printf("this %d\n", this);
}