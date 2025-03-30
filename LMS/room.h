#pragma once
#include<iostream>
#include <string>
using namespace std;


class room {
	//the arrays below was added by bilal on 9th May Thursday
	string m_strBookerNumber[3];
	bool m_boolBookingStatus[3];
	int m_intRoomNumber;

public:
	room();


	room( string bn1,string bn2, string bn3, bool b1,bool b2,bool b3, int rn);

	room (room&obj);
	void setRoom (string bn1, string bn2,string bn3, bool b1,bool b2,bool b3, int rn);
	
	string GetBookerNumber(int index);
	bool GetBookingStatus(int index);
	int GetRoomNumber();
	
	void EditBookerNumber(string bn, int index);
	void EditBookingStatus(bool bs, int index);
	void EditRoomNumber(int rn);
	void operator = (room&obj);
	bool operator ==(room&obj);
	bool operator != (room&obj);
	
	
	
	
};
