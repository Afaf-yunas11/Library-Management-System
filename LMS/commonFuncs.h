#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <type_traits>
#include "sqlite3.h"
#include "db.h"
#include "book.h"
#include "person.h"
#include "member.h"
#include "librarian.h"
#include "room.h"


//this file and its associated .cpp file contains all the commmon code such as add books etc
//Mohammad Ibraheem 23L-0771

// using these for colored outputs
#define ANSI_RED "\033[1;31m"
#define ANSI_GREEN "\033[1;32m"
#define ANSI_RESET "\033[0m"
#define ANSI_BLUE "\033[1;34m"
//apparently this yellow is not yellow its more like cyan
#define ANSI_YELLOW "\033[1;36m"

//prints a statement in green
void printSTMT(string statement);

//prints an error message in red
void printERR(string error);

//prints a line on the console
void line();

//calls the clear member func of customList.h
void clearAllLists(customList<book>*& pAddBookList, customList<librarian>*& pAddLibrarianList,
                   customList<person>*& pAddPersonList, customList<room>*& pAddRoomList,
                   customList<member>*& pAddMemberList,
                   customList<book>*& pUpdateBookList, customList<librarian>*& pUpdateLibrarianList,
                   customList<person>*& pUpdatePersonList, customList<room>*& pUpdateRoomList,
                   customList<member>*& pUpdateMemberList,
                   customList<string>*& pDeleteBookList, customList<string>*& pDeleteLibrarianList,
                   customList<string>*& pDeletePersonList, customList<string>*& pDeleteRoomList,
                   customList<string>*& pDeleteMemberList);


//this function is supposed to display ALL lists, formatted
template <typename T>
void displayListFORMATTED(customList<T>*& pList)
{
	//size of the list
	int ListSize = pList->size();
	//checking the type of object list
	
	if (typeid(T) == typeid(book))
	{
		//if T is a book
		
		int isbnCharSize = 4;
		int titleCharSize = 5;
		int authorCharSize = 6;
		int copiesCharSize = 10;
		int genreCharSize = 5;
		
		//finding the largest number of characters for each attribute
		customList<book>* ptrBookList = (customList<book>*)pList;
		
		for (int i = 0; i < ListSize; i++)
		{
			book tempBook = (*ptrBookList)[i];
			if (tempBook.GetISBN().length() > isbnCharSize)
			{
				isbnCharSize = tempBook.GetISBN().length();
			}
			
			if (tempBook.GetTitle().length() > titleCharSize)
			{
				titleCharSize = tempBook.GetTitle().length();
			}
			
			if (tempBook.GetAuthor().length() > authorCharSize)
			{
				authorCharSize = tempBook.GetAuthor().length();
			}
			
			if (tempBook.GetGenre().length() > genreCharSize)
			{
				genreCharSize = tempBook.GetGenre().length();
			}
			
			if (to_string(tempBook.GetCopies()).length() > copiesCharSize)
			{
				copiesCharSize = to_string(tempBook.GetCopies()).length();
			}
		}
		
		
		
		
		cout <<ANSI_BLUE<<setw(isbnCharSize+ 3)<<left<<"ISBN"<<
				setw(titleCharSize+ 3)<<left<<"TITLE"<<
				setw(authorCharSize+ 3)<<left<<"AUTHOR"<<
				setw(copiesCharSize + 10)<<left<<"NUM_COPIES"<<
				setw(genreCharSize + 3)<<left<<"GENRE"<<ANSI_RESET<<endl;
				
		//printing books
		//cout <<"list size = "<<ListSize<<endl;
		for (int i = 0; i <ListSize; i++)
		{
			book tempBook = (*ptrBookList)[i];

			
			cout <<ANSI_YELLOW<<setw(isbnCharSize+ 3)<<left<< tempBook.GetISBN()<<
				setw(titleCharSize+ 3)<<left<<tempBook.GetTitle()<<
				setw(authorCharSize+ 3)<<left<<tempBook.GetAuthor()<<
				setw(copiesCharSize + 10)<<left<<tempBook.GetCopies()<<
				setw(genreCharSize + 3)<<left<<tempBook.GetGenre()<<ANSI_RESET<<endl;
		}
	}
	else if (typeid(T) == typeid(person))
	{
		//if it is a person
		
		int phoneCharSize = 9;
		int nameCharSize = 4;
		int issuedCharSize = 11;
		//finding the largest number of characters for each attribute
 
		
		//customList<person>* ptrPersonList = static_cast<customList<person>*>(pList);
		
		customList<person>* pPersonList = (customList<person>*)pList;
		
		for (int i = 0; i < ListSize; i++)
		{
			person tempPerson = (*pPersonList)[i];
			if (tempPerson.GetNumber().length() > phoneCharSize)
			{
				phoneCharSize = tempPerson.GetNumber().length();
			}
			
			if (tempPerson.GetName().length() > nameCharSize)
			{
				nameCharSize = tempPerson.GetName().length();
			}
			
			if (tempPerson.GetIssuedISBN().length() > issuedCharSize)
			{
				issuedCharSize = tempPerson.GetIssuedISBN().length();
			}
			
		}
		cout <<ANSI_BLUE<<setw(phoneCharSize + 3)<<left<<"PHONE NUM"<<
				setw(nameCharSize + 3)<<left<<"NAME"<<
				setw(issuedCharSize+ 3)<<left<<"ISSUED ISBN"<<ANSI_RESET<< endl;
				
				
		//printing persons
		//cout <<"list size = "<<ListSize<<endl;
		for (int i = 0; i <ListSize; i++)
		{
			person tempPerson = (*pPersonList)[i];
			
			cout <<ANSI_YELLOW<<setw(phoneCharSize + 3)<<left<<tempPerson.GetNumber()<<
				setw(nameCharSize + 3)<<left<<tempPerson.GetName()<<
				setw(issuedCharSize+ 3)<<left<<tempPerson.GetIssuedISBN()<<ANSI_RESET<< endl;
		}
	}
	
	if (typeid(T) == typeid(librarian))
	{
		//if it is a librarian
		int phoneCharSize = 9;
		int nameCharSize = 4;
	
		int passwordSize = 8;
		
		int workHrCharSize = 13;
		
		customList<librarian>* pLibrarianList = (customList<librarian>*)pList;
		
		//finding the largest number of characters for each attribute
		for (int i = 0; i < ListSize; i++)
		{
			librarian tempLibrarian = (*pLibrarianList)[i];
			if (tempLibrarian.GetNumber().length() > phoneCharSize)
			{
				phoneCharSize = tempLibrarian.GetNumber().length();
			}
			
			if (tempLibrarian.GetName().length() > nameCharSize)
			{
				nameCharSize = tempLibrarian.GetName().length();
			}
			
			if (tempLibrarian.GetPassword().length() > passwordSize)
			{
				passwordSize = tempLibrarian.GetPassword().length();
			}
			
			if (tempLibrarian.GetWorkingHours().length() > workHrCharSize)
			{
				workHrCharSize = tempLibrarian.GetWorkingHours().length();
			}
		}
		cout <<ANSI_BLUE<<setw(phoneCharSize + 3)<<left<<"PHONE NUM"<<
				setw(nameCharSize + 3)<<left<<"NAME"<<
				setw(passwordSize+ 3)<<left<<"PASSWORD"<<
				setw(workHrCharSize + 3)<<left<<"WORKING HOURS"<<ANSI_RESET<<endl;
				
				
		//printing librarians
		//cout <<"list size = "<<ListSize<<endl;
		for (int i = 0; i <ListSize; i++)
		{
			librarian tempLibrarian = (*pLibrarianList)[i];
			
			cout <<ANSI_YELLOW<<setw(phoneCharSize + 3)<<left<<tempLibrarian.GetNumber()<<
				setw(nameCharSize + 3)<<left<<tempLibrarian.GetName()<<
				setw(passwordSize+ 3)<<left<<tempLibrarian.GetPassword()<<
				setw(workHrCharSize + 3)<<left<<tempLibrarian.GetWorkingHours()<<ANSI_RESET<<endl;
		}
		
	}
	
	if (typeid(T) == typeid(member))
	{
		//if it is a member
		int phoneCharSize = 9;
		int nameCharSize = 4;
	
		int passwordSize = 8;
		
		
		customList<member>* pMemberList = (customList<member>*)pList;
		//finding the largest number of characters for each attribute
		for (int i = 0; i < ListSize; i++)
		{
			member tempMember = (*pMemberList)[i];
			if (tempMember.GetNumber().length() > phoneCharSize)
			{
				phoneCharSize = tempMember.GetNumber().length();
			}
			
			if (tempMember.GetName().length() > nameCharSize)
			{
				nameCharSize = tempMember.GetName().length();
			}
			
			if (tempMember.GetPassword().length() > passwordSize)
			{
				passwordSize = tempMember.GetPassword().length();
			}
			
			
		}
		cout <<ANSI_BLUE<<setw(phoneCharSize + 3)<<left<<"PHONE NUM"<<
				setw(nameCharSize + 3)<<left<<"NAME"<<
				setw(passwordSize+ 3)<<left<<"PASSWORD"<<ANSI_RESET<<endl;
				
				
		//printing librarians
		//cout <<"list size = "<<ListSize<<endl;
		for (int i = 0; i <ListSize; i++)
		{
			member tempMember = (*pMemberList)[i];
			cout <<ANSI_YELLOW<<setw(phoneCharSize + 3)<<left<<tempMember.GetNumber()<<
				setw(nameCharSize + 3)<<left<<tempMember.GetName()<<
				setw(passwordSize+ 3)<<left<<tempMember.GetPassword()<<ANSI_RESET<<endl;

		}
	}
	
	if (typeid(T) == typeid(room))
	{
		
		int bookerOneCharLen = 0;
		int bookerTwoCharLen = 0;
		int bookerThreeCharLen = 0;
		
		int roomNumCharLen = 0;
		int availibilityCharLen = 1;
		
		customList<room>* pRoomList = (customList<room>*)pList;
		
		for (int i = 0; i < pRoomList->size(); i++)
		{
			room tempRoom = (*pRoomList)[i];
			
			if (tempRoom.GetBookerNumber(0).length() >bookerOneCharLen)
			{
				bookerOneCharLen = tempRoom.GetBookerNumber(0).length();
			}
			
			if (tempRoom.GetBookerNumber(1).length() > bookerTwoCharLen)
			{
				bookerTwoCharLen = tempRoom.GetBookerNumber(1).length();
			}
			if (tempRoom.GetBookerNumber(2).length() > bookerThreeCharLen)
			{
				bookerThreeCharLen = tempRoom.GetBookerNumber(2).length();
			}
			
			if (to_string(tempRoom.GetRoomNumber()).length() > roomNumCharLen)
			{
				roomNumCharLen = to_string(tempRoom.GetRoomNumber()).length();
			}
			
			//no need to check for avalibility char len as it is always going to be 1
		}
		
		string firstBooker = "FIRST BOOKER";
		string secondBooker = "SECOND BOOKER";
		string thirdBooker = "THIRD BOOKER";
		string roomNumber = "ROOM NUMBER";
		string avaliability = "SLOT 1 STATUS";
		if (firstBooker.length() >bookerOneCharLen)
		{
			bookerOneCharLen = firstBooker.length();
		}
		
		if (secondBooker.length() > bookerTwoCharLen)
		{
			bookerTwoCharLen = secondBooker.length();
		}
		if (thirdBooker.length() > bookerThreeCharLen)
		{
			bookerThreeCharLen = thirdBooker.length();
		}
		
		if (roomNumber.length() > roomNumCharLen)
		{
			roomNumCharLen = roomNumber.length();
		}
		
		if (avaliability.length() > availibilityCharLen)
		{
			availibilityCharLen = avaliability.length();
		}
		
		cout <<ANSI_BLUE<<setw(roomNumCharLen + 3)<<left<<"ROOM NUMBER"
				<<setw(bookerOneCharLen + 3)<<left<<"FIRST BOOKER"
				<<setw(availibilityCharLen + 3)<<left<<"SLOT 1 STATUS"
				<<setw(bookerTwoCharLen + 3)<<left<<"SECOND BOOKER"
				<<setw(availibilityCharLen + 3)<<left<<"SLOT 2 STATUS"
				<<setw(bookerThreeCharLen + 3)<<left<<"THIRD BOOKER"
				<<setw(availibilityCharLen + 3)<<left<<"SLOT 3 STATUS"<<ANSI_RESET<<endl;
		for (int i = 0; i < pRoomList->size(); i++)
		{
			room tempRoom = (*pRoomList)[i];
			
			cout <<ANSI_YELLOW<<setw(roomNumCharLen + 3)<<left<<tempRoom.GetRoomNumber()
				<<setw(bookerOneCharLen + 3)<<left<<tempRoom.GetBookerNumber(0)
				<<setw(availibilityCharLen + 3)<<left<<tempRoom.GetBookingStatus(0)
				<<setw(bookerTwoCharLen + 3)<<left<<tempRoom.GetBookerNumber(1)
				<<setw(availibilityCharLen + 3)<<left<<tempRoom.GetBookingStatus(1)
				<<setw(bookerThreeCharLen + 3)<<left<<tempRoom.GetBookerNumber(2)
				<<setw(availibilityCharLen + 3)<<left<<tempRoom.GetBookingStatus(2)<<ANSI_RESET<<endl;
		}
	}
	
	if (typeid(T) == typeid(string))
	{
		cout <<"PRINTING STRINGS"<<endl;
		
		customList<string>* pStringList = (customList<string>*)pList;
		for (int i = 0; i < ListSize; i++)
		{
			cout <<(*pStringList)[i]<<endl;
		}
	}
}


//returns the index of the person who's phoneNumber is entered
int searchMember(customList<member>*& pMemberList, string phoneNum);

//takes as input the number of books they want to enter
//takes as user input the attributes, and adds it to the list
void addBooks(customList<book>*& pBookList,customList<book>*& pAddList, int bookNumber);


//searches for an ISBN in a bookList, returns index if found
//else returns -1
int searchISBN(customList<book>*& pBookList, string isbn);

//takes user input for the isbns of the books they want to remove
void removeBooks(customList<string>*& removeISBNList, customList<book>* pBookList, int number);

//bookNumber = number of books you want to update
//takes as input the attributes of the new book
//returns 1 if book sucessfully updated
//returns -1 if cannot update book
//adds this book to pUpdateList
int updateBooks(customList<book>*& pBookList, customList<book>*& pUpdateList,  string ISBN, string title, string genre, string author,
				int copies );

//uses int updateBooks to take user input and update books
void updateBooksWRAP(customList<book>*& pBookList, customList<book>*& pUpdateList, int updateNum);

//stores all the stuff in arrays , called when issuing a book
//adds a person updates books does all that stuff;
//personNum and personName, will be passed as parameters in member portal
//will not be passed in librarian portal
void issueBook(customList<book>*& pBookList, customList<book>*& pUpdateList, customList<person>*& addPersonList,
				string personNum = "", string personName = "");


void returnBook(customList<book>*& pBookList, customList<book>*& pBookUpdateList, customList<person>*& pPersonList,
				 customList<string>*& pPersonRemoveList, int returnNum, string personNum = "");

//takes as input the number of books they want to enter
//takes as user input the attributes, and adds it to the list
//since booker's number can not be known at this stage, it's not taken from the user.
void addRooms(customList<room>*& pRoomList,customList<room>*& pAddList, int rooms);

//searches for a Room number in a roomList, returns index if found
//else returns -1
int searchRoomNumber(customList<room>*& pRoomList, int roomnum);

//gets booking status of a room in a roomList, returns index if found
//else returns -1
int getBookingStatus(customList<room>*& pRoomList, int roomnum);



//rooms = number of rooms you want to update
//takes as input the attributes of the new room
//returns 1 if the room is sucessfully updated
//returns -1 if cannot update a room
//adds this room to pUpdateList
int updateRooms(customList<room>*& pRoomList,customList<room>*& pUpdateList, int RoomNumber, bool BookingStatus1, bool BookingStatus2, bool BookingStatus3, string BookerNumber1, string BookerNumber2, string BookerNumber3 );

//uses int updateRooms to take user input and update rooms
void updateRoomsWRAP(customList<room>*& pRoomList, customList<room>*& pUpdateList, int updateNum);


//updates books
void updateBooksWRAP(customList<book>*& pBookList, customList<book>*& pUpdateList, int updateNum);

//stores all the stuff in arrays , called when booking a room
//updates the room 
void bookRoom (customList<room>*& pRoomList, customList<room>*& pUpdateList, string bookerNum="");

void unBookRoom(customList<room>*& pRoomList, customList<room>*& pUpdateRoomList, string bookerNumber="");


//finds a specific phone number from the list of persons
//only works for PERSON OR ONE OF ITS CHILD CLASSES, DO NOT CALL FOR OTHER CLASSES
// returns -1 if not found
template <typename T>
int searchNumber(customList<T>* pPersonList, string number);




//takes as parameter the number of librarians they want to enter
//takes as user input the attributes, and adds it to the list
void addLibrarian(customList<librarian>*& pLibrarianList,customList<librarian>*& plibrarianAddList, int librarianNumber);
void addMember(customList<member>*& pLibrarianList,customList<member>*& plibrarianAddList, int librarianNumber);



//takes as input the attributes of the new librarian
//returns 1 if the librarian added to update list
//returns -1 if librarian not present in main list
int updateLibrarians(customList<librarian>*& pLibrarianList,customList<librarian>*& pUpdateList, string number, string name, string password, string working_hours);



//takes as parameter the number of books to be added
//prompts user to enter attributes for each librarian
//calls updateLibrarians for each book
void updateLibrariansWRAP(customList<librarian>*& pLibrarianList, customList<librarian>*& pUpdateList, int updateNum);

//takes as parameter the number of books to be removed
//prompts user to enter number for the librarian
// adds librarian number if not present in removeLibrarianNumberList
// else it shows error that librarian already listed for removal 
void removeLibrarians(customList<librarian>*& pLibrarianList, customList<string>*& removeLibrarianNumberList, int number);
void removeMember(customList<member>*& pMemberList, customList<string>*& removeMemberNumberList, int number);
void removeRooms(customList<room>* pRoomList,customList<string>* & removeRoomNumberList, int number);
//AFAF YUNAS
//MEMBERS



void updateMemberWRAP(customList<member>*& pMemberList, customList<member>*& pUpdateList, int updateNum);

void removePersonWRAP(customList<person>*& pPersonList, customList<string>*& pRemovePersonList, int remNum);


template<class T>
bool ValidateMember(customList<T>*& pMemberList,string number,string password){
	bool check=false;
	for(int i=0;i<pMemberList->size();i++)
	{
		T tempobj = (*pMemberList)[i];
		if(tempobj.GetNumber()==number && tempobj.GetPassword()==password)
		{
			check=true;
		}
		
	}
	return check;
	
}




//PLEASE KEEP THIS PART AT THE END OF THIS FILE.
//THE FOLLOWING FUNCTIONS HAVE BEEN MOVED FROM MAIN.CPP TO HERE, TO REMOVE CLUTTER AND MAKE STUFF EASIER
//ALL OF THESE FUNCTIONS WORK WITH OBJECTS NOT POINTERS, KEEP IN MIND PLEASE 
void removeMembersfromSql(customList<string>& removeNumbers, sqlitemanager& DBobj);

void updateMembertoSql(customList<member>& memberList, sqlitemanager& DBobj);

void addMemberstoSql(customList<member>& memberList, sqlitemanager& DBobj);

void addBookstoSql(customList<book>& bookList, sqlitemanager& DBobj);

void addPersonstoSql(customList<person>& personList, sqlitemanager& DBobj);

void addLibrarianstoSql(customList<librarian>& librarianList, sqlitemanager& DBobj);

void addRoomstoSql(customList<room>& roomList, sqlitemanager& DBobj);

void removeBooksfromSql(customList<string>& removeISBNS, sqlitemanager& DBobj);

void removePersonsfromSql(customList<string>& removeNumbers, sqlitemanager& DBobj);

void removeLibrariansfromSql(customList<string>& removeNumbers, sqlitemanager& DBobj);

void removeRoomsfromSql(customList<string>& removeNumbers, sqlitemanager& DBobj);

void updateBookstoSql(customList<book>& bookList, sqlitemanager& DBobj);

void updatePersontoSql(customList<person>& personList, sqlitemanager& DBobj);

void updateLibrariantoSql(customList<librarian>& librarianList, sqlitemanager& DBobj);

void updateRoomtoSql(customList<room>& roomList, sqlitemanager& DBobj);

//THE FOLLOWING FUNCTIONS CALL THE ABOVE FUNCTIONS, UPDATE, ADD AND REMOVE, AIO 
//THESE ONES WORK WITH POINTERS

//called when updating stuff in database
void updateToDatabase(customList<book>* bookUpdateList, customList<person>* personUpdateList, customList<member>* memberUpdateList, customList<librarian>* librarianUpdateList, 
					customList<room>* roomUpdateList, sqlitemanager& DBobj);

//called when adding stuff to database;
void addToDatabase(customList<book>* &bookAddList, customList<person>* &personAddList, customList<member>* &memberAddList, customList<librarian>* &librarianAddList, 
					customList<room>* &roomAddList, sqlitemanager& DBobj);
					
//called when removing stuff from database

void removeFromDatabase(customList<string>* bookRemoveList, customList<string>* personRemoveList, customList<string>* memberRemoveList, customList<string>* librarianRemoveList, 
					customList<string>* roomRemoveList, sqlitemanager& DBobj);