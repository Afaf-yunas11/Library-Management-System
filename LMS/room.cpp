#include<iostream>
#include "room.h"
#include <string.h>
#include <cassert>
using namespace std;

room::room(){
	for(int i=0;i<3;i++)
	{
		m_strBookerNumber[i]=" ";
		m_boolBookingStatus[i]={false};
	
	}

	m_intRoomNumber=0;

}


room::room(string bn1, string bn2,string bn3, bool b1,bool b2,bool b3, int rn){
 
	m_strBookerNumber[0]=bn1;
	m_strBookerNumber[1]=bn2;
	m_strBookerNumber[2]=bn3;
	
	m_boolBookingStatus[0]=b1;
	m_boolBookingStatus[1]=b2;
	m_boolBookingStatus[2]=b3;	
	m_intRoomNumber=rn;
	
	//for error checking
//	cout<<endl<<"in parameterized constructor"<<endl;
//	for(int i=0;i<3;i++){
//		cout<<"bn "<<i<<" :"<<m_strBookerNumber[i]<<endl;
//		cout<<"bn "<<i<<" :"<<m_boolBookingStatus[i]<<endl;
//	}

}

room::room (room &obj)
{	
	for(int i=0;i<3;i++){
		
		m_boolBookingStatus[i]=obj.m_boolBookingStatus[i];
		m_strBookerNumber[i]=obj.m_strBookerNumber[i];
	}
	m_intRoomNumber=obj.m_intRoomNumber;
}
			
			
void room::setRoom(string bn1, string bn2,string bn3 ,bool b1, bool b2, bool b3, int rn){

	m_strBookerNumber[0]=bn1;
	m_strBookerNumber[1]=bn2;
	m_strBookerNumber[2]=bn3;
	
	m_boolBookingStatus[0]=b1;
	m_boolBookingStatus[1]=b2;
	m_boolBookingStatus[0]=b3;
	m_intRoomNumber=rn;
	
	}
	

string room:: GetBookerNumber(int index)
{

	assert(index >= 0 && index<3);
	assert(m_strBookerNumber[index].length() > 0);
	return m_strBookerNumber[index];

}

bool room:: GetBookingStatus(int index){
	assert(index >= 0 && index<3);
	assert(m_boolBookingStatus[index] == true || m_boolBookingStatus[index] == false);
	return m_boolBookingStatus[index];
}

int room:: GetRoomNumber(){
	
	assert(m_intRoomNumber >= 0);
	return m_intRoomNumber;

}
	
				

	void room::EditBookerNumber(string bn, int index){
		assert(index >= 0 && index<3);
		m_strBookerNumber[index]=bn;
	}
	void room:: EditBookingStatus(bool bs, int index){
		assert(index >= 0 && index<3);
		m_boolBookingStatus[index]=bs;
	}
	void room:: EditRoomNumber(int rn){
		m_intRoomNumber=rn;
	}
	
	
void room:: operator = (room&obj){
	//cout<<endl<<"assignment operator"<<endl;
		for(int i=0;i<3;i++){
			m_boolBookingStatus[i]=obj.m_boolBookingStatus[i];
			m_strBookerNumber[i]=obj.m_strBookerNumber[i];
				
	//		cout<<"bn "<<i<<" :"<<m_strBookerNumber[i]<<endl;
	//		cout<<"bn "<<i<<" :"<<m_boolBookingStatus[i]<<endl;
		}
		  m_intRoomNumber=obj.m_intRoomNumber;
	
}
		
	bool room:: operator ==(room&obj){
		bool flag=0;
		 if (  m_intRoomNumber == obj.m_intRoomNumber){
    		flag=true;
		}
		for(int i=0;i<3;i++){
			if(m_boolBookingStatus[i]!=obj.m_boolBookingStatus[i] ||
					m_strBookerNumber[i]!=obj.m_strBookerNumber[i]){
					flag=false;
			}
		}
	return flag;
	}
	bool room:: operator != (room&obj){
		 return !(*this == obj); 
		 
		 
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	