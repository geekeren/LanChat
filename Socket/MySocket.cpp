#include "MySocket.h"
#define SOCKET_NUFFER_SIZE 2048

DWORD WINAPI recv_ThreadFun(void * d){
	MySocket* that = (MySocket*)d;
	char buf[2048];
	while (1){
		ZeroMemory(buf,2048);
		if (that->status == socket_ready){
			int ret = ::recv(that->_socket, buf, 2048, 0);
			if (ret < 0){				
				int err = WSAGetLastError();
				if (err == WSAEWOULDBLOCK || err == WSAENOBUFS){
					Sleep(1000);
				}
				else{
					that->status = socket_err;
					break;
				}
			}			
		   else{		
				char * buffer = (char*)malloc(ret+1);
				memcpy(buffer, buf, ret);
				buffer[ret] = '\0';
			//	printf("%s", buffer);
				that->onRecevice(ret, buffer);
			}
		}
		else{
			break;
		}
		
	}
	that->Close(socket_err);
	return NULL;
}

MySocket::MySocket( string ipAddr, int port) :
 _ip(ipAddr), _port(port), _socket(-1), status(socket_unknown)
{
}

bool MySocket::Connect(){
	if (this->status == socket_ready){
		return true;
	}
	else{
		this->status = socket_unknown;
		sockaddr_in addr, serveraddr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htons(INADDR_ANY);
		addr.sin_port = htons(0);
		_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (_socket == INVALID_SOCKET){
			this->status = socket_err;
			this->Close(socket_err);
			return false;
		}
		else{
			int opt = 1;
			if (setsockopt(_socket, SOL_SOCKET, SO_DONTLINGER, (char*)&opt, sizeof(opt)) != 0){
				this->status = socket_err;
				this->Close(socket_err);
				return false;
			}
			u_long optt = 1;
			int iResult = ioctlsocket(this->_socket, FIONBIO, &optt);//ÉèÖÃ·Ç×èÈû
			if (iResult != NO_ERROR){
				this->status = socket_err;
				this->Close(socket_err);
				return false;
			}
			serveraddr.sin_family = AF_INET;
			serveraddr.sin_addr.s_addr = inet_addr(this->_ip.c_str());
			serveraddr.sin_port = htons(_port);
			if (::connect(_socket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) != 0){
				this->status = socket_err;
				this->Close(socket_err);
				return false;
			}
			this->status = socket_ready;
			return true;
		}		
	}
}

void MySocket::Close(SocketStatus status){
	if (this->status == socket_disconnect)
		return;
	else{
		if (_socket !=INVALID_SOCKET)
		   ::closesocket(_socket);
		this->status = socket_disconnect;
	}
}

void MySocket::OnAccept(int handlesocket){
	this->_socket = handlesocket;
}

bool MySocket::sendMessage(string text){
	int len = text.length();
	return sendMessage(len ,text.c_str());
}

bool MySocket::sendMessage(int size,const char* buf){
	int send = 0;
	while (send < size){
		if (this->status == socket_ready){
		int sendsize = ::send(this->_socket, buf+send, size - send, 0);
		if (sendsize < 0){
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK || err == WSAENOBUFS){
				Sleep(1000);
			}
			else{
				this->status = socket_err;
				return false;
			}
			
		}
		else{
			send += sendsize;
		   }
		}
		else{
			this->status = socket_err;
			return false;
		}
	}
	return true;
}
void MySocket::Recevice(){	
	this->status = socket_ready;
	this->_recThread = CreateThread(NULL, 0, recv_ThreadFun, (void*)this, NULL, NULL); 	
}

MySocket::~MySocket()
{
	Close(this->status);
}
