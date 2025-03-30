#pragma once
#include<iostream>
#include <string>
#include"person.h"
using namespace std;


class member: public person{
protected:
	string m_strPassword;

public:
	//done
	member();
	
	//done
	member(member& obj);
	
	//done
	member(string name, string phone, string pass,string isbn);
	
	virtual ~member();
	
	//done
	string GetPassword();
	void SetPassword(string pass);
	void EditPassword(string pass);
	
	//done
	void operator =(member& obj);
	
	//done
	bool operator == (member& obj);
	
	//done
	bool operator != (member& obj);
	
};


