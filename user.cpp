#include "user.h"

User::User(uLong id, string name,uLong ip) :ID(id), name(name),IP(ip){

}


void User::setName(string name){
	this->name = name;
}
User::~User()
{
}
