#include<iostream>
#include "room.h"
#include <string.h>
#include <cassert>
using namespace std;

	room::room(){
	 m_strTimeSlot=" ";
	m_strBookerNumber=" ";
	BookingStatus=false;
  m_intRoomNumber=0;

	}


	room::room(string ts, string bn, bool bs, int rn){
	 m_strTimeSlot=ts;
	m_strBookerNumber=bn;
	BookingStatus=bs;
  m_intRoomNumber=rn;
	
	}

	room (room&obj){
		 m_strTimeSlot=obj.strTimeSlot;
	m_strBookerNumber=obj.m_strBookerNumber;
	BookingStatus=obj.BookingStatus;
  m_intRoomNumber=obj.m_intRoomNumber;
		
		
		
		
	}
	void SetTimeSlot(string ts){
		m_strTimeslot=ts;
	}
	void SetBookerNumber(string bn){
		m_strBookerNumber=bn;
	}
	void SetBookingStatus(bool bs){
		BookingStatus=bs;
	}
	void SetRoomNumber(){
		m_intRoomNumber=rn;
	}
	
	string GetTimeSlot(){
		return m_strTimeSlot;
	}
	string GetBookerNumber(){
		return m_strBookerNumber;
	}
	string GetBookingStatus(){
		return BookingStatus;
	}
	int GetRoomNumber(){
		return RoomNumber;
	}