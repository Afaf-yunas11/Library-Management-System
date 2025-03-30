#pragma once
#include<iostream>
#include <string>
#include"member.h"
using namespace std;


class librarian:public member {

	
	string m_strWorkingHours;
public:
		
	librarian();
	librarian ( string name, string phone, string pass, string isbn, string working_hours);
	//modified by bilal kashif
	librarian( librarian& obj);
		
	void setWorkingHours(string working_hours);
	
	string GetWorkingHours();

	void EditWorkingHours(string wh);

	void operator=(librarian& obj);
	bool operator ==(librarian&obj);
	bool operator != (librarian&obj);
	
	virtual ~librarian();
};

