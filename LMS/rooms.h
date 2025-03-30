#pragma once
#include<iostream>
#include <string>
using namespace std;


class room {
	string m_strTimeSlot;
	string m_strBookerNumber;
	bool BookingStatus;
		int m_intRoomNumber;

public:
	room();


	room(string ts, string bn, bool bs, int rn);

	room (room&obj);
	void SetTimeSlot(string ts);
	void SetBookerNumber(string bn);
	void SetBookingStatus(bool bs);
	void SetRoomNumber();
	
	string GetTimeSlot();
	string GetBookerNumber();
	string GetBookingStatus();
	int GetRoomNumber();
	
};
