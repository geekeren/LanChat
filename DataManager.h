#pragma once
#include <vector>
#include "User.h"
#include "Message.h"
#include "Session.h"
#include "SessionManager.h"
#include <WinSock2.h>
#define WM_LISTCHANGE_MESSAGE WM_MY_MESSAGE +1
//���ݹ����࣬�������������ݲ�����ݽ��д������Ϊҵ��ģ��
class DataManager 
{
private :
	//���˸��㷢��Ϣ�ķ���
	SOCKET MsgServer;

	//������ ,���ڷ��־������ڰ�װ��ͬһ���������
	SOCKET SeiviceDiscoverServer;

	//�洢�ھ������ڰ�װ��ͬһ����������û�
	vector<User*>* Users;
	//vector<User*>* Users;

	static DataManager* m_pSingleInstance;
	DataManager();
	~DataManager();

public:
	static  DataManager* getInstance();
	void startMsgServer();
	//������ĳ���ˡ�����
	SOCKET connectToUser(User);

	//���������ַ���
	void startDiscoverServer();
	//����ͬ������ַ���
	virtual void handleServiceDiscoverMsg(Message);
	//����ͨ��ʱ����Ϣ
	virtual void handleMessage(Message);
	//������Ϣ
	bool sendMsg(User, Message,SOCKET);

	//������Ϣ
	void handleMsg(); 


	
	vector<User>& getOnLanUsers();
	 void scanOnLanUsers();

};

