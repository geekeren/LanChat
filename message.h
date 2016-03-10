#pragma once
#include <iostream>
#include <afx.h>
#define WM_MY_MESSAGE  WM_USER+1001
using namespace std;
enum  msg_Type
{
	msg_type_event = 0,//�¼���Ϣ
	msg_type_text = 1,//�ı�
	msg_type_image = 2,//ͼƬ
	msg_type_file = 3,//�ļ�
	msg_type_cmd = 4,//����
	msg_type_game = 5,//��Ϸ��Ϣ��ÿ��һ�������Ϣ
	msg_type_error = 6,//ϵͳ������Ϣ
	msg_type_others = 7//���������ڹ�����չ
};

enum  msg_type_events
{
	msg_event_online = 1,//����
	msg_event_offline = 0,//����
	
};

typedef struct message
{
	unsigned long FromID, ToID;
	int msg_type;
	CTime time;
	string content;
	int  myWPragam;

	void  MsgTobuffer(char**buffer){
		int len = (this->content).length() + 150;
		(*buffer) = (char*)malloc(len);
		ZeroMemory(*buffer, len);
		CString str1 = time.Format("%Y-%m-%d %H:%M:%S");

		char buf[100];
		ZeroMemory(buf, 100);
		sprintf_s(buf, 100, "%u", this->FromID);
		string from_id = string(buf);

		ZeroMemory(buf, 100);
		sprintf_s(buf, 100, "%u", this->ToID);
		string to_id = string(buf);

		this->myWPragam;
		sprintf_s(*buffer, len, "{ \"FromID\": \"%s\" , \"ToID\": \"%s\" , \"msg_type\" : %d , \"content\": \"%s\" , \"time\" : \"%S\" , \"myWPragam\" : %d }",
			from_id.c_str(), to_id.c_str(), this->msg_type, (this->content).c_str(), str1, this->myWPragam);

	}

} Message;



