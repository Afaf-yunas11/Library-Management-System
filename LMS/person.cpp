
#include "person.h"
#include <string> 
#include <cstring>
#include <cassert>
//written by m.ibraheem
//need to include cassert statements where needed

person::person(){
	m_strName = "";
	m_strPhoneNum = "";
	m_strIssuedISBN = "none";
}

person::person(person& obj){
	m_strName = obj.m_strName;
	m_strPhoneNum = obj.m_strPhoneNum;
	m_strIssuedISBN = obj.m_strIssuedISBN;
}

person::person(string name, string num, string isbn){
	m_strName = name;
	m_strPhoneNum = num;
	m_strIssuedISBN = isbn;
}

person::~person()
{
	
}

void person::SetPerson(string number, string name, string ISBN){
	m_strName = name;
	m_strPhoneNum = number;
	m_strIssuedISBN = ISBN;
}


void person::EditName(string name){
	m_strName = name;
}

void person::EditNumber(string num){
	m_strPhoneNum = num;
}

void person::EditIssuedISBN(string isbn)
{
	m_strIssuedISBN = isbn;
}

string person::GetName(){
	assert(m_strName.length() > 0);
	return m_strName;
}

string person::GetNumber()
{
	assert(m_strPhoneNum.length() > 0);
	return m_strPhoneNum;
}

string person::GetIssuedISBN()
{
	assert(m_strIssuedISBN.length() > 0);
	return m_strIssuedISBN;
}

void person::operator =(person& obj){
	(*this).m_strName = obj.m_strName;
	(*this).m_strPhoneNum = obj.m_strPhoneNum;
	(*this).m_strIssuedISBN = obj.m_strIssuedISBN;
}


bool person::operator ==(person& other) {
    return (m_strName == other.m_strName) &&
           (m_strPhoneNum == other.m_strPhoneNum) &&
           (m_strIssuedISBN == other.m_strIssuedISBN);
  }


bool person::operator!=(person& other) {
  return !(*this == other); // Leverage existing == operator
}
