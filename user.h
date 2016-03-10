#pragma once
#include <iostream>
#include "defines.h"

using namespace std;
class User
{
public:
	uLong ID;
	string name;
	uLong IP;

	User(uLong, string, uLong);

	void setName(string);
	~User();

};

