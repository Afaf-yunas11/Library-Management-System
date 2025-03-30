//person header file
//written by m.ibraheem
#pragma once
#include<iostream>
#include <string>
using namespace std;

class person{
private:
	string m_strIssuedISBN;
protected:
	string m_strName;
	string m_strPhoneNum;
	//this string will contain "none" if no books have been issued
	//else will contain the ISBN of the issued book.
	
	
public:
	//done
	//default constructor
	person();
	
	//done
	//parameterised constructor
	person(string name, string num, string ISBN);
	
	//done
	person(person& obj);
	
	//done
	void SetPerson(string number, string name,string ISBN);
	
	//done
	void EditName(string name);
	
	//done
	void EditNumber(string num);
	
	//done
	void EditIssuedISBN(string isbn);
	
	//done
	string GetIssuedISBN();
	
	//done
	string GetName();
	
	//done
	string GetNumber();
	
	//done
	//assignment operator
	void operator  = (person& obj);
	
	//done
	bool operator ==(person& obj);
	//done
	bool operator !=(person& obj);
	
	virtual ~person();
};
