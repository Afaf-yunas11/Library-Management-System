
#include<iostream>
#include <string>
#include "customList.h"
#include"librarian.h"

#include "book.h"
#include "db.h"

using namespace std;

//function for book callback
//this callback function used no where else so i guess its ok to put it here?

int bookCallBack(void *data, int argc, char **argv, char **azColName) 
{
	
	//argc stores the number of attributes
	//argv is the actual value in the field
	//azColName is the field name
	
	customList<book> *bookList = static_cast<customList<book> *>(data);
	
    book temp;
    
    for (int i = 0; i < argc; i++) {
        if (strcmp(azColName[i], "ISBN") == 0) {
            temp.EditISBN(argv[i]);
        } else if (strcmp(azColName[i], "Title") == 0) {
        	//cout<<"title = "<<argv[i]<<endl;
            temp.EditTitle(argv[i]);
        } else if (strcmp(azColName[i], "Author") == 0) {
            temp.EditAuthor(argv[i]);
        } else if (strcmp(azColName[i], "Copies") == 0) {
            temp.EditCopies(stoi(argv[i]));
        } else if (strcmp(azColName[i], "Genre") == 0){
        	temp.EditGenre(argv[i]);
		}
		
    }
    (*bookList).push(temp);
    return 0;
}


int personCallBack (void *data, int argc, char **argv, char **azColName) 
{
	
	//argc stores the number of attributes
	//argv is the actual value in the field
	//azColName is the field name
	
	customList<person> *personList = static_cast<customList<person> *>(data);
	
    person temp;
    
    for (int i = 0; i < argc; i++) 
	{
        if (strcmp(azColName[i], "name") == 0)
		{
			
            temp.EditName(argv[i]);
        } else if (strcmp(azColName[i], "number") == 0)
		 {
        	//cout<<"title = "<<argv[i]<<endl;
            temp.EditNumber(argv[i]);
        } 
		else (strcmp(azColName[i], "issuedISBN") == 0); 
		{
            temp.EditIssuedISBN(argv[i]);
        }
        
        
    }
    
    (*personList).push(temp);
    
    
    return 0;
    
    
}


int memberCallBack(void* data, int argc, char** argv, char** azColName) {
	
    customList<member>* memberList = static_cast<customList<member>*>(data);
    member temp;
    
    for (int i = 0; i < argc; i++) {
        if (strcmp(azColName[i], "name") == 0) {
        	
            temp.EditName(argv[i]);
        } else if (strcmp(azColName[i], "number") == 0) {
            temp.EditNumber(argv[i]);
        }  else if (strcmp(azColName[i], "password") == 0) {
            temp.EditPassword(argv[i]);
        } 
        
        
    }
    
    (*memberList).push(temp);
    
    return 0;
}


int librarianCallBack(void *data, int argc, char **argv, char **azColName){
	customList<librarian> *librarianList = static_cast<customList<librarian> *>(data);
	
    librarian temp;
    
    for (int i = 0; i < argc; i++) 
	{
        if (strcmp(azColName[i], "Name") == 0)
		{
            temp.EditName(argv[i]);
        } else if (strcmp(azColName[i], "Number") == 0)
		 {
        	//cout<<"title = "<<argv[i]<<endl;
            temp.EditNumber(argv[i]);
        } 
		else if(strcmp(azColName[i], "Password") == 0)
		{
            temp.EditPassword(argv[i]);
        }
        else if(strcmp(azColName[i], "WorkingHours") == 0){
        	temp.EditWorkingHours(argv[i]);
		}
    }
    
    (*librarianList).push(temp);
    
    
    return 0;
    
    
}

int roomCallBack(void *data, int argc, char **argv, char **azColName)
{
    customList<room> *roomList = static_cast<customList<room> *>(data);

    room temp;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(azColName[i], "BookingStatus1") == 0)
        {
             bool bookingStatus = (!strcmp(argv[i],"1"))?1:0;
            temp.EditBookingStatus(bookingStatus,0);
           // cout<<endl<<"booking status 1:"<<bookingStatus<<endl;
        }
        else if (strcmp(azColName[i], "BookingStatus2") == 0)
        {
            bool bookingStatus = (!strcmp(argv[i],"1"))?1:0;
            temp.EditBookingStatus(bookingStatus,1);
        }
        else if (strcmp(azColName[i], "BookingStatus3") == 0)
        {
            bool bookingStatus = (!strcmp(argv[i],"1"))?1:0;
            temp.EditBookingStatus(bookingStatus,2);
        }
        else if (strcmp(azColName[i], "BookerNumber1") == 0)
        {
            temp.EditBookerNumber(argv[i],0);
        }
        else  if (strcmp(azColName[i], "BookerNumber2") == 0)
        {
            temp.EditBookerNumber(argv[i],1);
        }
        else  if (strcmp(azColName[i], "BookerNumber3") == 0)
        {
            temp.EditBookerNumber(argv[i],2);
        }
        else if (strcmp(azColName[i], "RoomNumber") == 0)
        {
            int roomNumber = atoi(argv[i]);
            temp.EditRoomNumber(roomNumber);
        }
    }

    (*roomList).push(temp);

    return 0;
}

//constructor and destructor
sqlitemanager::sqlitemanager() : db(NULL) {}

sqlitemanager::~sqlitemanager(){
	if (db)
		sqlite3_close(db);
		cout<<"Database Closed Successfuly";
}

//opening database
int sqlitemanager::opendatabase(string Databasename){
	string dbFileName = Databasename + ".db";

	int rc = sqlite3_open(dbFileName.c_str(), &db);        //.c_str converts string tablename to c_style (const char* )string as sqlite3_open needs it 

	if (rc != SQLITE_OK)                                    //SQLITE_OK=0 (a constant retured by sqlite3 functions in case of success)
	{

		cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;

		return 1;
	}
	else
	{
		cout << Databasename<< "  opened successfully! " << endl;
	}

	return 0;
}

//Function to create table with fields
int sqlitemanager :: createTableattributes(string  tablename , string field){
    Tablename=tablename;
    // Create the table if it doesn't exist
    std::string query = "CREATE TABLE IF NOT EXISTS " + Tablename + " (" +field +")";
    char* errorMsg = NULL;
    
    int result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errorMsg);
    
    if (result != SQLITE_OK)
	 {
        std::cerr <<  "Error creating table: " << errorMsg << std::endl;
        sqlite3_free(errorMsg);
        return 1;
    }
   
	return 0;
}

//adds a single book at a time
int sqlitemanager::storeBook( const string isbn, int copies, const string genre, const string author, const string title) 
{
    string query = "INSERT INTO BOOKS (ISBN, Copies, Genre, Author, Title) VALUES ('" + isbn + "', " + to_string(copies) + ", '" + genre + "', '" + author + "', '" + title + "');";
    char* errorMsg = nullptr;
    //cout<<"db = "<<db<<endl;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
    
	//cout << "Result is " << result << endl;//21
    
    if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    }
    
    return result;
}



 int sqlitemanager::storePerson(const string number, const string name, const string issuedISBN ){
 	string query = "INSERT INTO PERSONS (Number, Name, IssuedISBN) VALUES ('" + number + "','" + name + "', '" +issuedISBN + "');";
    //cout<<query;
    char* errorMsg = nullptr;
    //cout<<"db = "<<db<<endl;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
    
	//cout << "Result is " << result << endl;//21
    
    if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    }
    
    return result;
 	
 	
 }

int sqlitemanager::storeLibrarian(const string number, const string name, const string password, const string workingHours ){
 	string query = "INSERT INTO LIBRARIAN (Number, Name, Password, WorkingHours) VALUES ('" + number + "','" + name +"','"+password+"','"+workingHours+ "');";
    //cout<<query;
    char* errorMsg = nullptr;
    //cout<<"db = "<<db<<endl;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
    
//	cout << "Result is " << result << endl;//21
    
    if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    }
    
    return result;
 	
 	
 }


int sqlitemanager::storeRoom( int roomNum, bool bookingStatus1 ,bool bookingStatus2,bool bookingStatus3 ,const string bookerNum1 , const string bookerNum2, const string bookerNum3 ){
	string bs1=(bookingStatus1)?"1":"0";
	string bs2=(bookingStatus2)?"1":"0";	
	string bs3=(bookingStatus3)?"1":"0";
 	string query = "INSERT INTO ROOMS (RoomNumber,BookingStatus1,BookingStatus2,BookingStatus3,BookerNumber1,BookerNumber2,BookerNumber3) VALUES ('"+to_string(roomNum)+"',"+ bs1 +","+ bs2 +","+ bs3 +",'" +bookerNum1+"','"+bookerNum2+"','"+bookerNum3+"');";
   	
    char* errorMsg = nullptr;
    //cout<<"db = "<<db<<endl;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
    
	//cout << "Result is " << result << endl;//21
    
    if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    }
    
    return result;
 	
 	
 }



int sqlitemanager::removeBook(string remIsbn)
{
	string query = "DELETE FROM BOOKS WHERE ISBN = '"+ remIsbn+"';";
	char* errorMsg = nullptr;
	int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
	
	if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
        //might include assert statements later
        sqlite3_free(errorMsg);
    }
    
    return result;
}

int sqlitemanager::removePerson(string number)
{
	
	string query = "DELETE FROM PERSONS WHERE Number = '"+ number +"';";
	char* errorMsg = nullptr;
	int result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errorMsg);
	
	if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
        //might include assert statements later
        sqlite3_free(errorMsg);
    }
    
    
    
    
    return result;
}

int sqlitemanager::removeLibrarian(string number)
{
	
	string query = "DELETE FROM Librarian WHERE Number = '"+ number +"';";
	char* errorMsg = nullptr;
	int result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errorMsg);
	
	if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
        //might include assert statements later
        sqlite3_free(errorMsg);
    }
    
    
    
    
    return result;
}

int sqlitemanager::removeRoom(int roomNum)
{
	
	string query = "DELETE FROM ROOMS WHERE RoomNumber ='" + to_string(roomNum) + "';";
	char* errorMsg = nullptr;
	int result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errorMsg);
	
	if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
       
        sqlite3_free(errorMsg);
    }
    
    return result;
}


//updates a single book at a time
int sqlitemanager::updateBook(string isbn, int copies, string genre, string author, string title)
{
	string query = "UPDATE BOOKS SET Copies = '"+ to_string(copies)+"', Genre = '"+genre+"', Author = '"+author+"', Title = '" + title+"' WHERE ISBN = '"+isbn+"';";
	char* errorMsg = nullptr;
	int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
	
	if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
        //might include assert statements later
        sqlite3_free(errorMsg);
    }
    
    return result;
}

int sqlitemanager::updatePerson(string number, string  name , string issuedisbn)
{
	string query = "UPDATE person SET  name = '"+name+"', number = '"+number+"', IssuedISBN = '" + issuedisbn+"' WHERE Number = '"+number+"';";
	char* errorMsg = nullptr;
	int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
	
	if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
      
        sqlite3_free(errorMsg);
    }
    
    return result;
}

int sqlitemanager:: updateLibrarian(string number, string  name ,string password, string workingHours){
	string query = "UPDATE LIBRARIAN SET  Name = '"+name+"', Number = '"+number+"',  Password='"+password+"', WorkingHours ='"+workingHours+"' WHERE Number = '"+number+"';";
	char* errorMsg = nullptr;
	int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
	
	if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
      
        sqlite3_free(errorMsg);
    }
    
    return result;
}

int sqlitemanager::updateRoom(int roomNum, bool bookingStatus1 ,bool bookingStatus2,bool bookingStatus3 ,const string bookerNum1 , const string bookerNum2, const string bookerNum3)
{	
	//cout<<endl<<"in update room, "<<"bs1 "<<bookingStatus1<<" bs2 "<<bookingStatus2<<" bs3 "<<bookingStatus3<<endl;
	string bs1=(bookingStatus1)?"1":"0";
	string bs2=(bookingStatus2)?"1":"0";	
	string bs3=(bookingStatus3)?"1":"0";
	string query = "UPDATE ROOMS SET  RoomNumber = "+to_string(roomNum)+",BookingStatus1="+ bs1 +",BookingStatus2="+ bs2 +",BookingStatus3="+ bs3 +", BookerNumber1='"+ bookerNum1+"',BookerNumber2='"+bookerNum2+"',BookerNumber3='"+bookerNum3+"'   WHERE  RoomNumber= "+ to_string(roomNum)+";";
	char* errorMsg = nullptr;
//	cout<<query<<endl;
	int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
	
	if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
      
        sqlite3_free(errorMsg);
    }
    
    return result;
}





customList<book>* sqlitemanager::readBooks(const string tableName){
	//this function is supposed to read books from a "books" table
	customList<book>* bookList = new customList<book>;
	
	string query = "SELECT * FROM " + tableName + ";";
	char* errorMsg = nullptr;
	
	int result = sqlite3_exec(db, query.c_str(), bookCallBack, bookList, &errorMsg);
	if (result != SQLITE_OK){
		cout<<"error: "<<result<<" error is: "<<errorMsg<<endl;
	}
	
	return bookList;
}

customList<person>* sqlitemanager::readPerson(const string tableName){
	//this function is supposed to read books from a "books" table
	customList<person>* bookList = new customList<person>;
	
	string query = "SELECT * FROM " + tableName + ";";
	char* errorMsg = nullptr;
	
	int result = sqlite3_exec(db, query.c_str(), personCallBack, bookList, &errorMsg);
	if (result != SQLITE_OK){
		cout<<"error: "<<result<<" error is: "<<errorMsg<<endl;
	}
	
	return bookList;
}

customList<librarian>* sqlitemanager::readLibrarian(const string tableName){
	//this function is supposed to read books from a "books" table
	customList<librarian>* librarianList = new customList<librarian>;
	
	string query = "SELECT * FROM " + tableName + ";";
	char* errorMsg = nullptr;
	
	int result = sqlite3_exec(db, query.c_str(), librarianCallBack, librarianList, &errorMsg);
	if (result != SQLITE_OK){
		cout<<"error: "<<result<<" error is: "<<errorMsg<<endl;
	}
	
	return librarianList;
}

customList<room>* sqlitemanager::readRooms(const string tableName)
{//tableName should be ROOMS
	customList<room>* roomList = new customList<room>;
	
	string query = "SELECT * FROM " + tableName +";";
	char* errorMsg = nullptr;
	
	int result = sqlite3_exec(db, query.c_str(), roomCallBack, roomList, &errorMsg);
	if (result != SQLITE_OK)
	{
		cout <<"error: "<<result<<" error is: "<<errorMsg<<endl;
	}
	
	return roomList;
}

//deletes a table, only use it to delete a table, nothing else
int sqlitemanager::deleteTable(const string tableName){
	string query = "DROP TABLE "+tableName+";";
	
	char* errorMsg = nullptr;
	
	int result = sqlite3_exec(db, query.c_str(),nullptr,nullptr, &errorMsg);
	if (result != SQLITE_OK){
		cout<<"error: "<<result<<" error is: "<<errorMsg<<endl;
	}
	
	return result;
}

//display
//"Number TEXT PRIMARY KEY, Name TEXT,IssuedISBNs TEXT, Password TEXT")


//FUNCTIONS FOR MEMBER 

//this function is supposed to read members from a "MEMBERS" table
customList<member>* sqlitemanager::readMember(const string tableName)
{

	customList<member>* memberList = new customList<member>;
	
	string query = "SELECT * FROM " + tableName + ";";
	char* errorMsg = nullptr;
	
	int result = sqlite3_exec(db, query.c_str(), memberCallBack, memberList, &errorMsg);
	if (result != SQLITE_OK){
		cout<<"error: "<<result<<" error is: "<<errorMsg<<endl;
	}
	
	return memberList;
}

//REMOVES A MEMBER FROM "MEMBER" TABLE

int sqlitemanager::removeMember(string number)
{
	
	string query = "DELETE FROM MEMBERS WHERE Number = '"+ number +"';";
	char* errorMsg = nullptr;
	int result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errorMsg);
	
	if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
        //might include assert statements later
        sqlite3_free(errorMsg);
    }
    
    return result;
}

//Update a member from "MEMBER" table

int sqlitemanager::updateMember(string number, string  name ,string password)
{
	string query = "UPDATE MEMBERS SET  Name = '"+name+"', Number = '"+number+"',Password='"+password+"' WHERE Number = '"+number+"';";
	char* errorMsg = nullptr;
	int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
	
	if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
      
        sqlite3_free(errorMsg);
    }
    
    return result;
}


//Stores a member in "MEMBER" table

 int sqlitemanager::storeMember(const string number, const string name,const string password ){
 	string query = "INSERT INTO MEMBERS (number, name, password) VALUES ('" + number + "','" + name + "', '"+password+"');";
    //cout<<query;
    char* errorMsg = nullptr;
    //cout<<"db = "<<db<<endl;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
    
//	cout << "Result is " << result << endl;//21
    
    if (result != SQLITE_OK) {
        cerr << "Error storing data: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    }
    
    return result;
 	
 	
 }





