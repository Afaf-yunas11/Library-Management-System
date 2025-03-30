#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include "sqlite3.h"
#include "db.h"
#include "book.h"
#include "person.h"
#include "member.h"
#include "librarian.h"
#include "room.h"
#include "commonFuncs.h"
//the associated cpp with commonFuncs.h

// using these for colored outputs
#define ANSI_RED "\033[1;31m"
#define ANSI_GREEN "\033[1;32m"
#define ANSI_RESET "\033[0m"
#define ANSI_BLUE "\033[1;34m"
#define ANSI_YELLOW "\033[1;36m"

using namespace std;

void printSTMT(string statement)
{
	cout <<ANSI_GREEN<<statement<<ANSI_RESET<<endl;
}

//PRINTS A LINE, TRANSFERRED FROM MAIN TO HERE
void line()
{
	printSTMT("==============================================");
}

void printERR(string statement)
{
	cout <<ANSI_RED<<statement<<ANSI_RESET<<endl;
}

//clears all temporary lists
void clearAllLists(customList<book>*& pAddBookList, customList<librarian>*& pAddLibrarianList,
                   customList<person>*& pAddPersonList, customList<room>*& pAddRoomList,
                   customList<member>*& pAddMemberList,
                   customList<book>*& pUpdateBookList, customList<librarian>*& pUpdateLibrarianList,
                   customList<person>*& pUpdatePersonList, customList<room>*& pUpdateRoomList,
                   customList<member>*& pUpdateMemberList,
                   customList<string>*& pDeleteBookList, customList<string>*& pDeleteLibrarianList,
                   customList<string>*& pDeletePersonList, customList<string>*& pDeleteRoomList,
                   customList<string>*& pDeleteMemberList) {
    // clear all lists
    pAddBookList->clear();
    pAddLibrarianList->clear();
    pAddPersonList->clear();
    pAddRoomList->clear();
    pAddMemberList->clear();

    pUpdateBookList->clear();
    pUpdateLibrarianList->clear();
    pUpdatePersonList->clear();
    pUpdateRoomList->clear();
    pUpdateMemberList->clear();

    pDeleteBookList->clear();
    pDeleteLibrarianList->clear();
    pDeletePersonList->clear();
    pDeleteRoomList->clear();
    pDeleteMemberList->clear();
}

int searchMember(customList<member>*& pMemberList, string phoneNum)
{
	int tempIndex = -1;
	for (int i = 0; i < pMemberList->size(); i++)
	{
		if ((*pMemberList)[i].GetNumber() == phoneNum)
		{
			return i;
		}
	}
	
	return tempIndex;
}

int searchISBN(customList<book>*& pBookList, string isbn)
{
	int tempIndex = -1;
	for (int i = 0; i < pBookList->size(); i++)
	{
		if((*pBookList)[i].GetISBN() == isbn)
		{
			tempIndex = i;
			break;
		}
	}
	
	return tempIndex;
}

template <typename T>
int searchNumber(customList<T>* pPersonList, string number){
		int tempIndex = -1;
	for (int i = 0; i < pPersonList->size(); i++)
	{
		if((*pPersonList)[i].GetNumber() == number)
		{
			tempIndex = i;
			break;
		}
	}
	
	return tempIndex;
}



void addBooks(customList<book>*& pBookList,customList<book>*& pAddList, int bookNumber)
{
	for (int i = 0; i < bookNumber; i++)
	{
		string isbn;
		int copies;
		string genre;
		string author;
		string title;
		
		printSTMT(to_string(i+1) + " book.");
		//cout <<"isbn: ";
		printSTMT("isbn: ");
		cin >>isbn;
		
		//cout <<"title: ";
		printSTMT("title: ");
		cin >> title;
		
		//cout <<"author: ";
		printSTMT("author: ");
		cin >>author;
		
		//cout <<"genre: ";
		printSTMT("genre: ");
		cin >> genre;
		
		//cout <<"copies: ";
		printSTMT("copies: ");
		cin >> copies;
		while(copies<1){
			printERR("THE NUMBER OF COPIES NEED TO BE A POSITIVE NUMBER");
			cin>>copies;
			while (cin.fail()) {
	        	printERR ("Input failed. Please enter a valid integer.");
				cin.clear();
				cin.ignore();
				cin>>copies;
			}
		}
		book tempBook(isbn, copies, genre, author, title);
		
		//need to check for existing ISBN
		int tempIndex = searchISBN(pBookList, isbn);
		
		if (tempIndex == -1)
		{
			pAddList->push(tempBook);
		}
		else {
			//cout <<"BOOK ALREADY EXISTS, CANNOT ADD."<<endl;
			printERR("BOOK ALREADY EXISTS, CANNOT ADD");
		}
	}
}

void addLibrarian(customList<librarian>*& pLibrarianList,customList<librarian>*& pLibrarianAddList, int librarianNumber)
{
	for (int i = 0; i < librarianNumber; i++)
	{
		string number;
		string name;
		string password;
		string working_hours;
		
		//cout<<i+1<<" librarian"<<endl;
		//cout <<"number: ";
		printSTMT(to_string(i+1) + "librarian. ");
		printSTMT("number: ");
		cin >>number;
		
		//cout <<"name: ";
		printSTMT("name: ");
		cin >> name;
		
		//cout <<"password: ";
		printSTMT("password: ");
		cin >>password;
		
		//cout <<"working hours ";
		printSTMT("working hours: ");
		cin >> working_hours;
	
		librarian tempLibrarian(name,number,password,"-1", working_hours);
		
		//need to check for existing ISBN
		int tempIndex = searchNumber(pLibrarianList, number);
		
		if (tempIndex == -1)
		{
			pLibrarianAddList->push(tempLibrarian);
		}
		else {
			//cout <<"LIBRARIAN ALREADY EXISTS, CANNOT ADD."<<endl;
			printERR("LIBRARIAN ALREADY EXISTS, CANNOT ADD.");
		}
	}
}

void addRooms(customList<room>*& pRoomList,customList<room>*& pAddList, int rooms)
{
	for (int i = 0; i < rooms; i++)
	{
	
		int roomNum;
		string BookerNumber[3];
		bool bookingStatus[3];
		
		//cout<<i+1<<" Room"<<endl;
		
		printSTMT(to_string(i+1) + "Room. ");
		//cout <<"Room Number: ";
		printSTMT("room number: ");
		cin >>roomNum;
			if (cin.fail()) {
        printERR ("Input failed. Please enter a valid integer.");}
		int index=searchRoomNumber(pRoomList,roomNum);
		int index2=searchRoomNumber(pAddList,roomNum);
		if(index==-1&& index2==-1){

			for(int i=0;i<3;i++){
				//cout<<"Booker Number"<<i+1<<":";
				printSTMT("booker number "+ to_string(i + 1) + ": ");
				cin>>BookerNumber[i];
				//cout <<"Booking Status"<<i+1<<":";
			
				printSTMT("booking status "+ to_string(i + 1) + ": ");
				cin >>bookingStatus[i];
				while (cin.fail()) 
						{
							cin.clear();
							cin.ignore();
							printERR ("ENTER EITHER 1 OR 0: ");
				        
							cin >> bookingStatus[i];
			
						}
			}
			
			// code changed temporarily will be fixed soon
			room tempRoom(BookerNumber[0],BookerNumber[1],BookerNumber[2],bookingStatus[0],bookingStatus[1],bookingStatus[2], roomNum);
			
			//need to check for existing room number
			
				pAddList->pushByRef(tempRoom);
		}
		else
		{
			//cout <<"ROOM ALREADY EXISTS, CANNOT ADD."<<endl;
			printERR("ROOM ALREADY EXISTS, CANNOT ADD. ");
		}
	}
}


int updateBooks(customList<book>*& pBookList,customList<book>*& pUpdateList, string ISBN, string title, string genre, string author,
				int copies )
{

	book tempBook(ISBN, copies, genre, author, title);
	
	//checking if isbn already exists in bookList
	int index = searchISBN(pBookList, ISBN);
	if (index == -1)
	{
		//book not existing in original book list
		return -1;
	}
	else 
	{
		//book exists in original book list
		//add it to the books to be updated list
		pUpdateList->push(tempBook);
		return 1;
	}
	
}



void updateBooksWRAP(customList<book>*& pBookList, customList<book>*& pUpdateList, int updateNum)
{
	//cout <<"UPDATING BOOKS"<<endl;
	printSTMT("UPDATING BOOKS");
	for (int i = 0; i < updateNum; i++)
	{
		string isbn;
		int copies;
		string genre;
		string author;
		string title;
		
		//cout<<i+1<<". enter attributes"<<endl;
		printSTMT(to_string(i+ 1) + " book, enter attributes");
		//cout <<"isbn: ";
		printSTMT("isbn: ");
		cin >>isbn;
		
		//cout <<"title: ";
		printSTMT("title: ");
		cin >> title;
		
		//cout <<"author: ";
		printSTMT("author: ");
		cin >>author;
		
		//cout <<"genre: ";
		printSTMT("genre: ");
		cin >> genre;
		
		//cout <<"copies: ";
		printSTMT("copies: ");
		cin >> copies;
		
		while(copies<1 || cin.fail()){
			
			cin.clear();
			cin.ignore();
			printERR("THE NUMBER OF COPIES NEED TO BE A POSITIVE NUMBER");
			cin>>copies;
			
		}
		
		int returned = updateBooks(pBookList, pUpdateList, isbn, title, genre, author, copies);
		if (returned == -1)
		{
			//cout <<"BOOK DOES NOT EXIST, CANNOT UPDATE"<<endl;
			printERR("BOOK DOES NOT EXIST, CANNOT UPDATE");
		}
		else 
		{
			//cout <<"BOOK ADDED TO UPDATE LIST"<<endl;
			printSTMT("BOOK ADDED TO UPDATE LIST");
		}
	}
}


void issueBook(customList<book>*& pBookList, customList<book>*& pUpdateList, customList<person>*& addPersonList,
				string personNum, string personName)
{
	//cout <<"ISSUING A BOOK"<<endl;
	printSTMT("ISSUING A BOOK");
	//book info
	string isbn;
	int copies;
	string genre;
	string author;
	string title;
	
	//cout <<"isbn: ";
	printSTMT("ISBN: ");
	cin >>isbn;
	
	//checking if isbn exists and copies of the book exist
	int index = searchISBN(pBookList, isbn);
	if (index == -1)
	{
		//cout <<"ISBN NOT FOUND, CANNOT ISSUE BOOK." <<endl;
		printERR("ISBN NOT FOUND, CANNOT ISSUE BOOK. ");
	}
	else 
	{
		int existingCopies = (*pBookList)[index].GetCopies();
		
		
		
		if (existingCopies == 0)
		{
			//cout <<"NO COPIES EXIST, CANNOT ISSUE"<<endl;
			printERR("NO COPIES EXIST, CANNOT ISSUE. ");
		}
		else 
		{
			//isbn found and copies exist
			copies = existingCopies - 1;
			
			//checking if personNum and personName has been passed into the function
			if (personNum == "")
			{
				//cout <<"phone num(person): ";
				printSTMT("phone num (person): ");
				cin >> personNum;
			}
			
			if (personName == "")
			{
				//cout <<"name(person): ";
				printSTMT("name (person): ");
				cin >> personName;
			}
			
			genre = (*pBookList)[index].GetGenre();
			author = (*pBookList)[index].GetAuthor();
			title = (*pBookList)[index].GetTitle();
			
			//UPDATE THIS BOOK
			updateBooks(pBookList, pUpdateList, isbn, title, genre, author, copies);
			
			//ADD THIS PERSON
			person tempPerson(personName, personNum, isbn);
			addPersonList->push(tempPerson);
			
			//cout <<"BOOK ISSUED."<<endl;
			printSTMT("BOOK ISSUED. ");
		}
	}
	
}


void returnBook(customList<book>*& pBookList, customList<book>*& pBookUpdateList, customList<person>*& pPersonList,
				 customList<string>*& pPersonRemoveList, int returnNum, string personNum)
{
	
	for (int i = 0; i < returnNum; i++)
	{
		string returnISBN;
		//string personNum;
		//cout <<"enter ISBN of book: ";
		printSTMT("enter ISBN of book: ");
		cin >> returnISBN;
		
		if (personNum == "")
		{
			//cout <<"enter number of the person who issued book: ";
			printSTMT("enter number (person): ");
			cin >> personNum;
		}
		
		bool actuallyIssued = false;
		
		//checking if person actually issued book
		for (int j = 0; j < pPersonList->size(); j++)
		{
			if ((*pPersonList)[j].GetNumber() == personNum && (*pPersonList)[j].GetIssuedISBN() == returnISBN)
			{
				
				actuallyIssued = true;
				break;
			}
//			cout<<(*pPersonList)[i].GetNumber()<<"   "<<(*pPersonList)[i].GetIssuedISBN()<<endl;
		}
		
		if (actuallyIssued)
		{
			//the person actually issued the book
			
			
			int bookIndex = searchISBN(pBookList, returnISBN);
			if (bookIndex == -1)
			{
				//cout <<"BOOK NOT FOUND IN DATABASE, PLEASE CONTACT AN ADMIN"<<endl;
				printERR("BOOK NOT FOUND IN DATABASE, PLEASE CONTACT AN ADMIN");
			}
			else
			{
				pPersonRemoveList->push(personNum);
				
				//updating Book Attributes
				book tempBook = (*pBookList)[bookIndex];
				
				int copies = tempBook.GetCopies() + 1;
				tempBook.EditCopies(copies);
				
				pBookUpdateList->push(tempBook);
			}
		}
		else 
		{
			//cout <<personNum<<" DID NOT ISSUE THIS BOOK, CANNOT RETURN"<<endl;
			printERR(personNum + " DID NOT ISSUE THIS BOOK, CANNOT RETURN");
		}
	}
}

int searchRoomNumber(customList<room>*& pRoomList, int roomnum)
{
	int tempIndex = -1;
	for (int i = 0; i < pRoomList->size(); i++)
	{
		if((*pRoomList)[i].GetRoomNumber() == roomnum)
		{
			tempIndex = i;
			break;
		}
	}
	
	return tempIndex;
}


int getBookingStatus(customList<room>*& pRoomList, int roomnum)
{
	int tempIndex = -1;
	for (int i = 0; i < pRoomList->size(); i++)
	{	//index zero added for the time being, code shall be fixed soon
		if((*pRoomList)[i].GetBookingStatus(0) == 1)
		{
			tempIndex = i;
			break;
		}
	}
	
	return tempIndex;
}




void removeBooks(customList<string>*& removeISBNList, customList<book>* pBookList,  int number)
{
	//cout <<"DELETING BOOKS"<<endl;
	printSTMT("DELETING BOOKS");
	for (int i = 0; i < number; i++)
	{
		string removeISBN;
		//cout <<i + 1<<" .enter the isbn: ";
		printSTMT(to_string(i + 1) + ". enter the ISBN: ");
		cin >> removeISBN;
		
		//checking if ISBN actually exists
		if (searchISBN(pBookList, removeISBN) == -1)
		{
			//cout <<"BOOK NOT FOUND, CANNOT DELETE"<<endl;
			printERR("BOOK NOT FOUND, CANNOT DELETE");
		}
		else 
		{
		
			//checking if the isbn is already in the remove list
			if (removeISBNList->getIndex(removeISBN) == -1)
			{
				//not found in list
				removeISBNList->push(removeISBN);
			}
			else 
			{
				//found in list
				//cout <<"ISBN ALREADY LISTED FOR REMOVAL"<<endl;
				printERR("ISBN ALREADY LISTED FOR REMOVAL");
			}
		}
		
	}
}

void removeRooms(customList<room>* pRoomList,customList<string>* & removeRoomNumberList, int number)
{
	//cout <<"DELETING ROOMS"<<endl;
	printSTMT("DELETING ROOMS");
	
	for (int i = 0; i < number; i++)
	{
		int removeRoomNumber;
		//cout <<i<<"Enter the room number: ";
		printSTMT(to_string(i+ 1) + "enter the room number: ");
		cin >> removeRoomNumber;
		
		//checking if the room number is already in the remove list
		if(searchRoomNumber(pRoomList,removeRoomNumber)==-1){
			//cout<<"ROOM DOES NOT EXIST, CANNOT REMOVE"<<endl;
			printERR("ROOM DOES NOT EXIST, CANNOT REMOVE");
			
		}
		else
		{
			if (removeRoomNumberList->getIndex(to_string(removeRoomNumber)) == -1)
			{
				//not found in list
				removeRoomNumberList->push(to_string(removeRoomNumber));
			} 
			else 
			{
				//found in list
				//cout <<"ROOM NUMBER ALREADY LISTED FOR REMOVAL"<<endl;
				printERR("ROOM NUMBER ALREADY LISTED FOR REMOVAL");
			}
		
		}
	}
}


void removeLibrarians(customList<librarian>*& pLibrarianList, customList<string>* & removeLibrarianNumberList, int number)
{
	//cout <<"DELETING LIBRARIANS"<<endl;
	printSTMT("DELETING LIBRARIANS");
	
	for (int i = 0; i < number; i++)
	{
		string removeLibrarianNumber;
		//cout <<i<<"Enter the librarian number: ";
		printSTMT(to_string(i + 1) + "enter librarian num: ");
		cin >> removeLibrarianNumber;
		
		//checking if the librarian acc exists
		bool exists = false;
		for (int i = 0; i < pLibrarianList->size();i++ )
		{
			if ((*pLibrarianList)[i].GetNumber() == removeLibrarianNumber)
			{
				exists = true;
				break;
			}
		}
		if (exists)
		{
			
		
			//checking if the room number is already in the remove list
			if (removeLibrarianNumberList->getIndex(removeLibrarianNumber) == -1)
			{
				//not found in list
				removeLibrarianNumberList->push(removeLibrarianNumber);
			}
			else 
			{
				//found in list
				//cout <<"LIBRARIAN NUMBER ALREADY LISTED FOR REMOVAL"<<endl;
				printERR("LIBRARIAN NUMBER ALREADY LISTED FOR REMOVAL");
			}
			
		}
		//number not found
		else 
		{
			//cout <<"LIBRARIAN DOES NOT EXIST, CANNOT REMOVE"<<endl;
			printERR("LIBRARIAN DOES NOT EXIST, CANNOT REMOVE");
		}
	}
}

void removeMember(customList<member>*& pMemberList ,customList<string>* & removeMemberNumberList, int number)
{
	//cout <<"DELETING MEMBERS"<<endl;
	printSTMT("DELETING MEMBERS");
	for (int i = 0; i < number; i++)
	{
		string removeMemberNumber;
		//cout <<i<<"Enter the member number: ";
		printSTMT(to_string(i+ 1) + " enter the member num: ");
		cin >> removeMemberNumber;
		
		//checking if the number acc exists
		bool exists = false;
		for (int i = 0; i < pMemberList->size(); i++)
		{
			if ((*pMemberList)[i].GetNumber() == removeMemberNumber)
			{
				exists = true;
				break;
			}
		}
		if (exists)
		{
		
			//checking if the room number is already in the remove list
			if (removeMemberNumberList->getIndex(removeMemberNumber) == -1)
			{
				//not found in list
				removeMemberNumberList->push(removeMemberNumber);
			}
			else 
			{
				//found in list
				//cout <<"MEMBER NUMBER ALREADY LISTED FOR REMOVAL"<<endl;
				printERR("MEMBER NUMBER ALREADY LISTED FOR REMOVAL");
			}
		}
		else 
		{
			//cout <<"MEMBER DOES NOT EXIST, CANNOT REMOVE"<<endl;
			printERR("MEMBER DOES NOT EXIST, CANNOT REMOVE");
		}
	}
}

//returns -1 if room does not exist in original list
int updateRooms(customList<room>*& pRoomList,customList<room>*& pUpdateList, int RoomNumber, bool BookingStatus1, bool BookingStatus2, bool BookingStatus3, string BookerNumber1, string BookerNumber2, string BookerNumber3 )
{
	//checking if room exists in roomList
	
	room tempRoom(BookerNumber1, BookerNumber2, BookerNumber3, BookingStatus1,BookingStatus2,BookingStatus3, RoomNumber);
	//cout<<endl<<"bs1"<<BookingStatus1<<" bn1"<<BookerNumber1<<endl<<"bs2"<<BookingStatus2<<" bn2"<<BookerNumber2<<endl<<"bs3"<<BookingStatus3<<" bn3"<<BookerNumber3<<endl;
	//search with in room 
	int index = searchRoomNumber(pRoomList,RoomNumber);
	if (index == -1)
	{
		//room not existing in original room list
		return -1;
	}
	else 
	{
		//room exists in original room list
		//add it to the rooms to be updated list
//		for(int i=0;i<3;i++){
//			tempRoom.GetBookingStatus(i);
//			tempRoom.GetBookerNumber(i);
//			cout<<endl;
//		}
		pUpdateList->push(tempRoom);
		return 1;
	}
	
}


void updateRoomsWRAP(customList<room>*& pRoomList, customList<room>*& pUpdateList, int updateNum)
{
	//cout <<"UPDATING ROOMS"<<endl;
	
	printSTMT("UPDATING ROOMS");
	
	for (int i = 0; i < updateNum; i++)
	{
		int roomNum;
		bool bookingStatus[3];
		string bookerNum[3];
		
		printSTMT(to_string(i + 1) + " room. ");

		//cout <<"enter room number of the room: ";
		printSTMT("enter room number: ");
		cin >>roomNum;
		
		while (cin.fail())
		{
			cin.clear();
			cin.ignore();
			printERR("enter a valid room number: ");
			cin >> roomNum;
		}
		
		int index = searchRoomNumber(pRoomList, roomNum);
		if (index != -1)
		{
		
			for(int j=0;j<3;j++){
			
				//cout <<"Booking Status(bool): "<<i+1<<": ";
				
				printSTMT("booking status(bool) " + to_string(j + 1) + ": ");
				cin >>bookingStatus[i];
				
				while (cin.fail()) 
				{
					cin.clear();
					cin.ignore();
					printERR ("ENTER EITHER 1 OR 0: ");
		        
					cin >> bookingStatus[j + 1];
	
				}
				
		       	//cout <<"Booker Number(string): "<<i+1<<": ";
		       	printSTMT("booker number(string) " + to_string(j + 1) + ": ");
				cin >> bookerNum[j];
			}
			
			
			int returned = updateRooms(pRoomList, pUpdateList,roomNum,bookingStatus[0],bookingStatus[1],bookingStatus[2],bookerNum[0],bookerNum[1],bookerNum[2]);
			
//			for(int i=0;i<3;i++)
//			{
//				cout <<"Booking Status(bool): "<<i+1<<bookingStatus[i];
//				
//		       	cout <<"Booker Number(string): "<<i+1<<bookerNum[i];
//			}

			if (returned == -1)
			{
				//cout <<"ROOM NOT FOUND, CANNOT UPDATE"<<endl;
				printERR("ROOM NOT FOUND, CANNOT UPDATE");
			}
			else 
			{
				//cout <<"ROOM ADDED TO UPDATE LIST"<<endl;
				printSTMT("ROOM ADDED TO UPDATE LIST");
			}
		}
		else 
		{
			//cout <<"ROOM NOT FOUND, CANNOT UPDATE"<<endl;
			printERR("ROOM NOT FOUND, CANNOT UPDATE");
		}
	}
}


void bookRoom (customList<room>*& pRoomList, customList<room>*& pUpdateList, string bookerNum)
{

	//cout <<"BOOKING A ROOM"<<endl;
	printSTMT("BOOKING A ROOM");
	
	//cout<<"We have three time slots:"<<endl<<"1. 9 am to 10 am"<<endl<<"2. 10 am to 11 am"<<endl<<"3. 11 am to 12pm"<<endl;
	printSTMT("we have three time slots: ");
	printSTMT("1. 9 am to 10 am");
	printSTMT("2. 10 am to 11 am");
	printSTMT("3. 11 am to 12 am");
	//room info
	int roomNum;
	bool bookingStatus;
	room tempRoom;
	//cout <<"Room Number: ";
	printSTMT("room number: ");
	cin >>roomNum;
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
    	printERR ("Input failed. Please enter a valid integer.");
    	cin>>roomNum;
	}
	//checking if room num exists 
	int index = searchRoomNumber(pRoomList, roomNum);
	if(index!=-1)
	{
		
		//cout<<endl<<"THE ROOM HAS THE FOLLOWING SLOTS AVAILABLE: "<<endl;
		cout <<endl;
		printSTMT("THE ROOM HAS THE FOLLOWING SLOTS AVAILABLE: ");
		
		bool available=0;
		for(int i=0;i<3;i++)
		{
			if(!(*pRoomList)[index].GetBookingStatus(i))
			{	available=1;
				//cout<<9+i<<" to "<<10+i<<endl;
				printSTMT(to_string( i + 9) + " to " + to_string( i + 10));
			}
		}
		
		if(available){
		
			//cout<<endl<<"Which slot do you want to book(from 1 to 3)?"<<endl;
			cout <<endl;
			printSTMT("which slot do you want to book ( enter 1 to 3): ");
			int slot;
			cin>>slot;
				if (cin.fail()) {
        printERR ("Input failed. Please enter a valid integer.");}
			if(slot>3 || slot<1)
			{
				//cout<<"INVALID SLOT NUMBER"<<endl;
				printERR("INVALID SLOT NUMBER");
			}
			else if((*pRoomList)[index].GetBookingStatus(slot-1))
			{
				//cout<<"SLOT UNAVAILABLE"<<endl;	 
				printERR("SLOT UNAVAILABLE");
			}
			else
			{	
				if(bookerNum==""){
					//cout<<"Enter your contact number:"<<endl;
					printSTMT("enter contact number: ");
					cin >>bookerNum;
				}
				tempRoom=(*pRoomList)[index];
				tempRoom.EditBookingStatus(1,slot-1);
				tempRoom.EditBookerNumber(bookerNum,slot-1);
				updateRooms(pRoomList, pUpdateList,tempRoom.GetRoomNumber(),tempRoom.GetBookingStatus(0),tempRoom.GetBookingStatus(1),tempRoom.GetBookingStatus(2),tempRoom.GetBookerNumber(0),tempRoom.GetBookerNumber(1),tempRoom.GetBookerNumber(2));
				//cout<<"ROOM BOOKED"<<endl;
				printSTMT("ROOM BOOKED");
			}
		}
		else
		{
			//cout<<"NO SLOT AVAILABLE"<<endl;
			printERR("NO SLOT AVAILABLE");
		}
	}else
	{
		//cout<<"ROOM DOES NOT EXIST"<<endl;
		printERR("ROOM DOES NOT EXIST");
	}
	
        

	
	
}

void unBookRoom(customList<room>*& pRoomList, customList<room>*& pUpdateRoomList, string bookerNumber){
	
	int num,slot,index;
	
	//cout<<"UNBOOKING ROOM"<<endl;
	printSTMT("UN-BOOKING ROOM");
	
	//cout<<"Enter the number of the room:"<<endl;
	printSTMT("enter the number of the room: ");
	cin>>num;
	
	while (cin.fail() || num < 0)
	{
		cin.clear();
		cin.ignore();
		printERR("ENTER A VALID SLOT NUMBER: ");
		cin >> num;
	}
	
	index=searchRoomNumber(pRoomList,num);
	
	if(index!=-1)
	{
		//cout<<"Which booking do you want to cancel(from 1 to 3)"<<endl;
		printSTMT("which booking do you want to cancel (enter 1 to 3): ");
		cin>>slot;
		
		
		while (cin.fail() || slot < 0 || slot > 3)
		{
			cin.clear();
			cin.ignore();
			printSTMT("ENTER A VALID SLOT NUMBER: ");
			cin >> slot;
		}
		
		slot--;
		if(bookerNumber==""){
			//cout<<"Enter your booker number"<<endl;
			printSTMT("enter booker number: ");
			cin>>bookerNumber;
		}
		
		if((*pRoomList)[index].GetBookingStatus(slot)){
			if((*pRoomList)[index].GetBookerNumber(slot)==bookerNumber){
				//cout<<"The room has been unbooked";
				printSTMT("the room has been unbooked");
				room temp=(*pRoomList)[index];
				temp.EditBookingStatus(0,slot);
				string none="none";
				temp.EditBookerNumber(none,slot);
				pUpdateRoomList->push(temp);
				
			}else
			{
				//cout<<"CAN NOT CANCEL BOOKING, THE ROOM WAS BOOKED BY SOMEONE ELSE"<<endl;
				printERR("CANNOT CANCEL BOOKING, THE ROOM WAS BOOKED BY SOMEONE ELSE");
			}
		}
		else
		{
			//cerr<<"THE SLOT WAS FREE"<<endl;
			printERR("SLOT ALREADY FREE, CANNOT CANCEL BOOKING");
		}
		
	}
	else
	{
		//cerr<<"ROOM NOT FOUND"<<endl;
		printERR("ROOM NOT FOUND, CANNOT CANCEL BOOKING");
	}
	
}
//Functions for Member


void addMember(customList<member>*& pMemberList,customList<member>*& pMemberAddList, int MemberNumber)
{
	for (int i = 0; i < MemberNumber; i++)
	{
		string number;
		string name;
		string password;
		
		
		//cout<<endl<<i+1<<" member"<<endl;
		printSTMT(to_string(i + 1) + "member");
		
		//cout <<"number: ";
		printSTMT("number: ");
		cin>>number;
		
		//cout << "name: ";
		printSTMT("name: ");
		
		cin >>name;
		//cout << "password: ";
		printSTMT("password: ");
		
		cin >>password;
		
		
		
		member tempMember(name,number,password,"-1");
		//cout <<"NAME IS: "<<tempMember.GetName()<<endl;
		//need to check for existing PhoneNum
		int tempIndex = searchNumber(pMemberList, number);
		
		if (tempIndex == -1)
		{
			pMemberAddList->push(tempMember);
		}
		else 
		{
			//cout <<"MEMBER ALREADY EXISTS, CANNOT ADD."<<endl;
			printERR("MEMBER ALREADY EXISTS, CANNOT ADD");
		}
	}
}





void updateMemberWRAP(customList<member>*& pMemberList, customList<member>*& pUpdateList, int updateNum)
{
	bool check = false;
	//cout <<"UPDATING MEMBERS"<<endl;
	printSTMT("UPDATING MEMBERS");
	for (int i = 0; i < updateNum; i++)
	{
		string number;
		string name;
		string password;
	
		//cout<<i+1<<"enter number of the member: ";
		printSTMT(to_string(i+ 1) + "member");
		
		printSTMT("number: ");
		cin >> number;
		
		//checking if member acc exists
		for(int i=0;i<pMemberList->size();i++)
		{
			if((*pMemberList)[i].GetNumber() == number)
			{
				check=true;
				break;
			}
			
		}
		
	    if(check)  //MEMBER EXIST THEN ASK FOR UPDATED ATTRIBUTES
		{
			//cout<<". enter attributes "<<endl;
			
			//cout <<"Updated name: ";
			printSTMT("new name: ");
			cin >> name;
			
			//cout <<"Updated password: ";
			printSTMT("new password: ");
			cin >>password;
			
			member tempobjj(name,number,password,"-1");
	
			pUpdateList->push(tempobjj);
			//cout<<endl<<"MEMBER ADDED TO UPDATED LIST"<<endl;
			
			printSTMT("MEMBER LISTED FOR UPDATE");
	
		}
		else
		{
		
			//cout<<"No Such Member Exists";
			printERR("NO MEMBER EXISTS, CANNOT UPDATE");
		}	
			
	}
}


//LIBRARIAN UPDATE FUNCTIONS

void removePersonWRAP(customList<person>*& pPersonList, customList<string>*& pRemovePersonList, int remNum)
{
	for (int i = 0; i < remNum; i++)
	{
		string number;
		printSTMT(to_string(i + 1) + " person. ");
		printSTMT("enter number: ");
		cin >> number;
		
		while(cin.fail())
		{
			cin.ignore();
			cin.clear();
			printERR("ENTER A VALID NUMBER: ");
			cin >> number;
		}
		
		bool inList = false;
		
		for (int j = 0; j < pPersonList->size(); j++)
		{
			if ((*pPersonList)[i].GetNumber() == number)
			{
				inList = true;
				break;
			}
		}
		
		if (inList)
		{
			//checking if number already listed for removal
			bool alreadyListed = false;
			for (int j = 0; j <pRemovePersonList->size(); j++)
			{
				if ((*pRemovePersonList)[j] == number)
				{
					alreadyListed = true;
					break;
				}
				
			}
			
			if (alreadyListed)
			{
				printERR("PERSON ALREADY LISTED FOR REMOVAL");
			}
			else 
			{
				printSTMT("person listed for removal");
				pRemovePersonList->push(number);
			}
		}
		else
		{
			printERR("PERSON NOT FOUND, CANNOT REMOVE");
		}
	}
}

void updateLibrariansWRAP(customList<librarian>*& pLibrarianList, customList<librarian>*& pUpdateList, int updateNum)
{
	bool check=false;
	
	//cout <<"UPDATING LIBRARIANS"<<endl;
	printSTMT("UPDATING LIBRARIANS");
	
	for (int i = 0; i < updateNum; i++)
	{
		string input;
	
		//cout<<i+1<<". enter Librarian Number:";
		printSTMT(to_string(i + 1) + " librarian");
		
		printSTMT("enter number: ");
		cin>>input;
		
		librarian temp;
		for(int i=0;i<pLibrarianList->size();i++)
		{
			
			if((*pLibrarianList)[i].GetNumber() == input)
			{
				check=true;
				temp=(*pLibrarianList)[i];
			}
			
		}
	    
		if(check)  //	LIBRARIAN EXIST THEN ASK FOR UPDATED ATTRIBUTES
		{
			
			//cout <<"enter new name: ";
			printSTMT("enter new name: ");
			cin >>input;
			temp.EditName(input);
			input="";
			
			//cout <<"enter new password: ";
			printSTMT("enter new password: ");
			cin >>input;
			temp.SetPassword(input);
			input="";
			
			
			//cout <<"enter new working hours: ";
			printSTMT("enter new working hours: ");
			cin >>input;
			temp.setWorkingHours(input);
			input="";
				
			pUpdateList->push(temp);
			//cout<<endl<<"LIBRARIAN ADDED TO UPDATED LIST";
			printSTMT("LIBRARIAN LISTED FOR UPDATE");
		}
		else
		{
		
			//cout<<"NO SUCH LIBRARIAN EXISTS, CANNOT UPDATE"<<endl;
			printERR("NO SUCH LIBRARIAN EXISTS, CANNOT UPDATE");
		}	
				
	}
}




//this takes person and member list as parameters
// then matches phone numbers, if match is found it copies it into issuedisbn field
void fill_Members(customList<member>* & pMemberList, customList<person>* &pPersonList){
	
	int j=0;// for traversing member list
	
	for(int i=0;i<pPersonList->size() && j<pMemberList->size();i++){
		if((*pMemberList)[i].GetNumber()==(*pPersonList)[i].GetNumber()){
			(*pMemberList)[i].EditIssuedISBN((*pPersonList)[i].GetIssuedISBN());
			
			j++;
		}
	}
}


//PLEASE KEEP THIS PART AT THE END OF THIS FILE.
//THE FOLLOWING FUNCTIONS HAVE BEEN MOVED FROM THE MAIN.CPP TO THIS FILE, TO REMOVE CLUTTER AND MAKE  EASIER
void removeMembersfromSql(customList<string>& removeNumbers, sqlitemanager& DBobj)
{
	int size = removeNumbers.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.removeMember(removeNumbers[i]);
		assert(result == 0);
	}
	
}

void updateMembertoSql(customList<member>& memberList, sqlitemanager& DBobj){
	int size = memberList.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.updateMember(memberList[i].GetNumber(), memberList[i].GetName(),memberList[i].GetPassword());
		assert(result == 0);
	}
}

void addMemberstoSql(customList<member>& memberList, sqlitemanager& DBobj)
{
	int size = memberList.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.storeMember(memberList[i].GetNumber(), memberList[i].GetName(),memberList[i].GetPassword());
		assert(result == 0);
	}
}
//adds books to sql, takes customList of books as input
void addBookstoSql(customList<book>& bookList, sqlitemanager& DBobj)
{
	int size = bookList.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.storeBook(bookList[i].GetISBN(), bookList[i].GetCopies(), bookList[i].GetGenre(), bookList[i].GetAuthor(), bookList[i].GetTitle());
		assert(result == 0);
	}
}

//adds persons to sql, takes customList of persons as input
void addPersonstoSql(customList<person>& personList, sqlitemanager& DBobj)
{
	int size = personList.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.storePerson(personList[i].GetNumber(), personList[i].GetName(), personList[i].GetIssuedISBN());
		assert(result == 0);
	}
}

//adds librarians to sql, takes customList of librarians as input
void addLibrarianstoSql(customList<librarian>& librarianList, sqlitemanager& DBobj)
{
	int size = librarianList.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.storeLibrarian(librarianList[i].GetNumber(), librarianList[i].GetName(),librarianList[i].GetPassword(),librarianList[i].GetWorkingHours()) ;
		assert(result == 0);
	}
}

void addRoomstoSql(customList<room>& roomList, sqlitemanager& DBobj)
{
	int size = roomList.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.storeRoom(roomList[i].GetRoomNumber(), roomList[i].GetBookingStatus(0), roomList[i].GetBookingStatus(1), roomList[i].GetBookingStatus(2), roomList[i].GetBookerNumber(0), roomList[i].GetBookerNumber(1), roomList[i].GetBookerNumber(2)) ;
		assert(result == 0);
	}
}
//removes books from sql, takes a customList of isbns of the books to be removed
void removeBooksfromSql(customList<string>& removeISBNS, sqlitemanager& DBobj)
{
	int size = removeISBNS.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.removeBook(removeISBNS[i]);
		assert(result == 0);
	}
}

//removes person from sql, takes a customList of numbers to be removed
void removePersonsfromSql(customList<string>& removeNumbers, sqlitemanager& DBobj)
{
	int size = removeNumbers.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.removePerson(removeNumbers[i]);
		assert(result == 0);
	}
	
}

//removes librarians from sql
void removeLibrariansfromSql(customList<string>& removeNumbers, sqlitemanager& DBobj)
{
	int size = removeNumbers.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.removeLibrarian(removeNumbers[i]);
		assert(result == 0);
	}
	
}
void removeRoomsfromSql(customList<string>& removeNumbers, sqlitemanager& DBobj)
{
	int size = removeNumbers.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.removeRoom(stoi(removeNumbers[i]));
		assert(result == 0);
	}
	
}
//updates books, takes a list of the new books to be updated
void updateBookstoSql(customList<book>& bookList, sqlitemanager& DBobj)
{
	int size = bookList.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.updateBook(bookList[i].GetISBN(), bookList[i].GetCopies(), bookList[i].GetGenre(), bookList[i].GetAuthor(), bookList[i].GetTitle());
		assert(result == 0);
	}
}

//updates persons
void updatePersontoSql(customList<person>& personList, sqlitemanager& DBobj){
	int size = personList.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.updatePerson(personList[i].GetNumber(), personList[i].GetName(), personList[i].GetIssuedISBN());
		assert(result == 0);
	}
}

//updates Librarian
void updateLibrariantoSql(customList<librarian>& librarianList, sqlitemanager& DBobj)
{
	int size = librarianList.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.updateLibrarian(librarianList[i].GetNumber(), librarianList[i].GetName(), librarianList[i].GetPassword(), librarianList[i].GetWorkingHours());
		assert(result == 0);
	}
}

void updateRoomtoSql(customList<room>& roomList, sqlitemanager& DBobj)
{
	int size = roomList.size();
	for (int i = 0; i < size; i++)
	{
		int result = DBobj.updateRoom(roomList[i].GetRoomNumber(), roomList[i].GetBookingStatus(0), roomList[i].GetBookingStatus(1), roomList[i].GetBookingStatus(2), roomList[i].GetBookerNumber(0), roomList[i].GetBookerNumber(1), roomList[i].GetBookerNumber(2) );
		assert(result == 0);
	}
}

//THE FOLLOWING FUNCTIONS CALL THE ABOVE FUNCTIONS, UPDATE, ADD AND REMOVE, AIO 
//THESE ONES WORK WITH POINTERS

//called when updating stuff in database
void updateToDatabase(customList<book>* bookUpdateList, customList<person>* personUpdateList, customList<member>* memberUpdateList, customList<librarian>* librarianUpdateList, 
					customList<room>* roomUpdateList, sqlitemanager& DBobj)
{
	updateBookstoSql((*bookUpdateList), DBobj);
	updatePersontoSql((*personUpdateList), DBobj);
	updateMembertoSql((*memberUpdateList), DBobj);
	updateLibrariantoSql((*librarianUpdateList), DBobj);
	updateRoomtoSql((*roomUpdateList), DBobj);
}

//called when adding stuff to database;
void addToDatabase(customList<book>* &bookAddList, customList<person>* &personAddList, customList<member>* &memberAddList, customList<librarian>* &librarianAddList, 
					customList<room>* &roomAddList, sqlitemanager& DBobj)
{	
	//cout<<"in addToDatabase"<<endl;
	addBookstoSql((*bookAddList), DBobj);
	addPersonstoSql((*personAddList), DBobj);
	addMemberstoSql((*memberAddList), DBobj);
	addLibrarianstoSql((*librarianAddList), DBobj);
	addRoomstoSql((*roomAddList), DBobj);
	//cout<<"Exiting Add";
}
//called when removing stuff from database

void removeFromDatabase(customList<string>* bookRemoveList, customList<string>* personRemoveList, customList<string>* memberRemoveList, customList<string>* librarianRemoveList, 
					customList<string>* roomRemoveList, sqlitemanager& DBobj)
{
	removeBooksfromSql((*bookRemoveList), DBobj);
	removePersonsfromSql((*personRemoveList), DBobj);
	removeMembersfromSql((*memberRemoveList), DBobj);
	removeLibrariansfromSql((*librarianRemoveList), DBobj);
	removeRoomsfromSql((*roomRemoveList), DBobj);
}
