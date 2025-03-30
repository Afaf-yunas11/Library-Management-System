#pragma once
#include <string>
#include "book.h"
#include "person.h"
#include <iostream>
#include "sqlite3.h"
#include "customList.h"
#include "librarian.h"
#include "room.h"
using namespace std;

class sqlitemanager
{
	//attributes
private:
	sqlite3* db;
	string Tablename;
	
	//int bookCallBack(void* data, int argc, char** argv, char**azColName);
public:
	//methods

	// Constructor and Destructor
	 sqlitemanager();
	~sqlitemanager();
	
	//open database
	int opendatabase(string DatabaseName);
	
	//Create Table with fields
    int createTableattributes(string tablename,string field);
     
    //Stores objects in database, takes as input all the attributes
    int storeBook(const string isbn, int copies, const string genre, const string author, const string title);
    int storePerson(const string number, const string name, const string issuedISBN );
    int storeLibrarian(const string number, const string name, const string password, const string workingHours );
    int storeMember(const string number, const string name ,const string password );
	int storeRoom( int roomNum, bool bookingStatus1 ,bool bookingStatus2,bool bookingStatus3 ,const string bookerNum1 , const string bookerNum2, const string bookerNum3 );
    
    //removes an object, only takes a variable to identify it all
    int removeBook(string remIsbn);
    int removePerson(string number);
    int removeLibrarian(string number);
    int removeMember(string number);
    int removeRoom(int roomnum);
    
    //updates an object, takes the new attributes as input
    int updateBook(string isbn, int copies, string genre, string author, string title);
	int updatePerson(string number, string  name , string issuedisbn);
	int updateLibrarian(string number, string  name , string password, string workingHours);
	int updateMember(string number, string  name,string password);
	int updateRoom(int roomNum, bool bookingStatus1 ,bool bookingStatus2,bool bookingStatus3 ,const string bookerNum1 , const string bookerNum2, const string bookerNum3);

	
	void storelibrarian();
	void storeroom();

	
	//see database   (using select query)
	
	//need to read objects from database
	//and store in a customList
	customList<book>* readBooks(const string tableName);
	customList<person>* readPerson(const string tableName);
	customList<librarian>* readLibrarian(const string tableName);
	customList<member>* readMember(const string tableName);
	customList<room>* readRooms(const string tableName);
	
	//need to make similar read functions for librarian, member , and so on
	
	int deleteTable(const string tableName);
};


