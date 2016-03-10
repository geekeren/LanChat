#pragma once
#include <iostream>
#include <afx.h>
#define WM_MY_MESSAGE  WM_USER+1001
using namespace std;
enum  msg_Type
{
	msg_type_event = 0,//事件消息
	msg_type_text = 1,//文本
	msg_type_image = 2,//图片
	msg_type_file = 3,//文件
	msg_type_cmd = 4,//命令
	msg_type_game = 5,//游戏消息，每走一步棋的消息
	msg_type_error = 6,//系统错误信息
	msg_type_others = 7//其它，用于功能扩展
};

enum  msg_type_events
{
	msg_event_online = 1,//上线
	msg_event_offline = 0,//下线
	
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



