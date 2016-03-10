#include "stdafx.h"


SessionManager*  SessionManager::m_pSingleInstance(NULL);
SessionManager::SessionManager(){

}
SessionManager* SessionManager::GetInstance(){
	if (m_pSingleInstance == NULL)
		m_pSingleInstance = new SessionManager();

	return m_pSingleInstance;
}


SessionManager::~SessionManager()
{
	delete m_pSingleInstance;
}
void SessionManager::addSession(Session* session){
	sessions.push_back(session);
}
vector<Session*>  SessionManager::getSessions(){
	return this->sessions;
}
Session* SessionManager::getSessionByUserID(long id){
	//sessions = &SessionManager::Sessions;
	vector<Session*>::iterator iter;
	for (iter = sessions.begin(); iter != sessions.end(); iter++){
		Session* session = *iter;
		User	user = session->m_user;
		if (user.ID == id)
			return session;
	}
	return NULL;

}