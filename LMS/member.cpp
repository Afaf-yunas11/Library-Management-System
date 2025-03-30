
#include "member.h"
#include "person.h"
#include <string>
#include <cassert>
using namespace std;

member::member(){

	m_strPassword = "";
}

member::member(member& obj):person(obj.GetName(),obj.GetNumber(),obj.GetIssuedISBN()){

	m_strPassword = obj.m_strPassword;
}

member::member(string name, string phone, string pass, string isbn):person(name,phone,isbn){

	m_strPassword = pass;
}

member::~member()
{
	
}
void member:: SetPassword(string pass){
	m_strPassword = pass;
}
	
void member::EditPassword(string pass){
		m_strPassword = pass;
}
	
string member::GetPassword(){
		assert(m_strPassword.length() > 0);
	return m_strPassword;
}

void member::operator  =(member& obj){

	m_strPassword = obj.m_strPassword;
	person::operator  =(obj);
}

bool member::operator  ==(member& obj){
	if ( !strcmp(m_strPassword.c_str(),obj.m_strPassword.c_str())){
		return true;
	}
	
	return false;
} 

bool member::operator  !=(member& obj){
	return !(*this == obj); 
	}
	
	


