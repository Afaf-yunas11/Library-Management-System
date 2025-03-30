#include<iostream>
#include "librarian.h"
#include "member.h"
#include <string.h>
#include <cassert>
using namespace std;

librarian::librarian() {
    m_strWorkingHours = "";
}

librarian::librarian(string name, string phone, string pass, string isbn, string working_hours) : member(name, phone, pass, isbn) {
    m_strWorkingHours = working_hours;
}

// Copy constructor
librarian::librarian( librarian& obj) : member(obj) {
    m_strPassword = obj.m_strPassword;
    m_strName = obj.m_strName;
    m_strPhoneNum = obj.m_strPhoneNum;
    m_strWorkingHours = obj.m_strWorkingHours;
}

librarian::~librarian()
{
	
}
void librarian::setWorkingHours(string working_hours) {
    m_strWorkingHours = working_hours;
}

string librarian::GetWorkingHours() {
    assert(m_strWorkingHours.length() > 0);
    return m_strWorkingHours;
}

void librarian::EditWorkingHours(string wh) {
    m_strWorkingHours = wh;
}

void librarian::operator=(librarian& obj) {
	m_strName = obj.m_strName;
    m_strPassword = obj.m_strPassword;
    m_strWorkingHours = obj.m_strWorkingHours;
    //m_strPhoneNum=obj.m_strPhoneNum;
    member::operator=(obj);
}

bool librarian::operator==(librarian& obj) {
    return (m_strWorkingHours == obj.m_strWorkingHours);
}

bool librarian::operator!=(librarian& obj) {
    return !(*this == obj);
}
