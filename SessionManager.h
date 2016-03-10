#pragma once

using namespace std;
class Session;
class SessionManager
{
private:
	
	 static  SessionManager *m_pSingleInstance;
	
	 SessionManager();
	 ~SessionManager();
	 //find

public:
 	 bool hasUser(long UserID);
	  vector<Session*> sessions;
	  void addSession(Session*);
	  vector<Session*> getSessions();
//	void addSession(Session);
	static SessionManager * GetInstance();
	 Session* getSessionByUserID(long);
};

