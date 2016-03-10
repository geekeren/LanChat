#pragma once
#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#pragma comment (lib , "ws2_32.lib")
using namespace std;
typedef enum _socketStatus{
	socket_err,
	socket_disconnect,
	socket_ready,
	socket_unknown
} SocketStatus;

class MySocket
{
private :
	int _socket;
	string _ip;
	int _port;
	HANDLE _recThread;

public:
	SocketStatus  status;
	MySocket(string,int );
	bool Connect();
	void Close(SocketStatus);
	void OnAccept(int);
	virtual void onRecevice(int, const char*) = 0;
	bool sendMessage(string);
	bool sendMessage(int ,const char *);
	void Recevice();
	~MySocket();

	friend class MyServerSocket;
	friend DWORD WINAPI recv_ThreadFun(void *);
	
};

