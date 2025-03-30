
#include <windows.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "db.h"
#include "book.h"
#include "person.h"
#include "member.h"
#include "librarian.h"
#include "room.h"
#include "commonFuncs.h"
#include "adminPortal.h"
#include "Memberportal.h"
#include "librarianPortal.h"

using namespace std;

//23L-0771
//23L-0523
//23L-0745
//23L-0757

// using these for colored outputs
#define ANSI_RED "\033[1;31m"
#define ANSI_GREEN "\033[1;32m"
#define ANSI_RESET "\033[0m"
#define ANSI_BLUE "\033[1;34m"
#define ANSI_YELLOW "\033[1;36m"

//IMPORTANT TO REMEMBER, DO NOT DELETE

//Books table definition ISBN, Copies, Genre, Author, Title
//Persons table definition Number, Name, IssuedISBNS
//Librarian table definition Number, Name, Password, WorkingHours
//delete the Librarians table
//Member table definition number, name, password
//NOT VALID ANYMORE-Rooms table definition roomNumber, bookerNumber, bookingStatus , timeSlot 

//ROOMS table:
// RoomNumber(int), BookinStatus1(int),BookingStatus2(int),BookingStatus3(int),BookerNumber1(text),BookerNumber2(text),BookerNumber3(text)



//this function searches the customList and returns the object's index
//else returns -1



//THIS FUNCTION CAN BE REPLACED BY THE CUSTOMLIST GET INDEX FUNCTION, NO NEED TO REDO?
//DOES BASICALLY THE SAME THING
template <class T>
int searchList(customList<T>* ptrList, T& obj)
{
	int size = ptrList -> size();
	for (int i = 0; i < size; i++){
		if ((*ptrList)[i] == obj){
			return i;
		}
	}
	
	return -1;
}

//IS THIS USED ANYWHERE???
//returns true if sucessfully removed, else false
//modify this so it takes in an isbn
//bool removeBookfromList(customList<book>* ptrList, string ISBN)
//{
//	int index = searchISBN(ptrList, ISBN);
//	if (index == -1 )
//	{
//		return false;
//	}
//	else
//	{
//		cout<<"book has been found at index = "<<index<<endl;
//		(*ptrList).remove(index);
//	}
//	return true;
//}

//Rapper functions for member


//Reading in masterlist


//prints the main menu, only couts
void mainMenu()
{
	printSTMT("1) login as admin.");
	printSTMT("2) login as librarian.");
	printSTMT("3) login as member.");
	printSTMT("-1 to quit");
}



int main()
{
	
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//represents the console screen
//
//// Set console color attributes
//CONSOLE_SCREEN_BUFFER_INFOEX info;//contains information about the console screen buffer, including color attributes.
//info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
//GetConsoleScreenBufferInfoEx(hConsole, &info);
//info.ColorTable[0] = RGB(128,0,0);   // maroon color
//info.ColorTable[1] = RGB(165, 42, 42);   
//info.wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
//SetConsoleScreenBufferInfoEx(hConsole, &info);
//
//// Resize the console to apply the color changes
//COORD coord;
//coord.X = 80;  // Width of the console window
//coord.Y = 25;  // Height of the console window
//SetConsoleScreenBufferSize(hConsole, coord);
	
	int password;
	sqlitemanager library;
	int result = library.opendatabase("LMSdatabase");
	
	if (result == 0)
	{
	
		int main_choice;
		bool run = true;
		mainMenu();
		printSTMT("enter your choice: ");
		cin >> main_choice;
		
		while (cin.fail()) 
		{
			cin.clear();
			cin.ignore();
			printERR ("ENTER A VALID INTEGER: ");
        	
			cin >> main_choice;
		}
	
			

		while ( main_choice <-1 || main_choice > 3)
		{
			//cout <<"INVALID CHOICE, ENTER AGAIN: ";
			printERR("INVALID CHOICE, ENTER AGAIN: ");
			cin >> main_choice;
		}

		
		if (main_choice == -1)
		{
			run = false;
		}
		
		//if program runs, everything happens here
		while (run)
		{	
			system("cls");
			//initialising all lists, these are pointers to customLists, customLists created on the heap
			customList<book>* pBookList;
			customList<librarian>* pLibrarianList;
			customList<person>* pPersonList;
			customList<room>* pRoomList;
			customList<member>* pMemberList=NULL;
			
			
			//all lists have been initialised
			pBookList = library.readBooks("BOOKS");
			pLibrarianList = library.readLibrarian("LIBRARIAN");
			pPersonList = library.readPerson("PERSONS");
			pRoomList = library.readRooms("ROOMS");
			pMemberList=library.readMember("MEMBERS");
			
		
			//displayListFORMATTED(pRoomList);
			//logins as admin
			//ADMIN PASSWORD WILL BE 2354
			//3 tries allowed to get password right
			
			if (main_choice == 1)
			{
				int tries = 0;
				//need to check for password etc over here
				printSTMT("enter password: ");
				
				while (tries != 3)
				{
					cin >> password;	
					
					while (cin.fail()) 
					{
						cin.clear();
						cin.ignore();
				        printERR ("INPUT VALID INTEGER: ");
	        	
				
						cin >> password;
					}
	
				
					if (password == 2354)
					{
						//sucessfully logged in
						//enter admin code here
						int admin_choice = 0;
						printSTMT("SUCESSFULLY AUTHENTICATED, ENTERED ADMIN MODE");
						//line();
						
						adminPortal(pBookList, pLibrarianList, pPersonList, pRoomList, pMemberList, library);
						break;
					}
					else 
					{
						tries ++;
						printERR("WRONG PASSWORD ENTER AGAIN: ");
					}
				}
				
				if (tries == 3)
				{
					printERR("you have tried 3 times, try again later. ");
				}
			}
			//CHECKING ISSUE BOOK BE SURE TO DELETE LATER
	
			//member part here
			else if(main_choice ==3)
			{
				//member code here
	    		string number;
				string password;
				
				bool authenticated = false;
				int tries=0;
				
				while (tries <= 3 && !authenticated)
				{
				
					printSTMT("LOG IN TO ACCESS MEMBER PORTAL");
					printSTMT("enter number: ");
					cin >> number;
					printSTMT("enter password: ");
					cin >> password;
				
					//need to validate info
					
					if(ValidateMember(pMemberList,number,password))
					{
						printSTMT("ACCESS APPROVED");
						//cout<<"Welcome LIBRARIAN";
						authenticated= true;
					}
					else
					{
						printERR("ACCESS DENIED");
						authenticated=false;
						tries=tries+1;	
					}
				
			
				}
				
				
				if(authenticated)
				{
					
					int memIndex = searchMember(pMemberList, number);
					
					if (memIndex == -1)
					{
						//cout <<"something went wrong. Restart program."<<endl; 
						printERR("SOMETHING WENT WRONG. RESTART PROGRAM");
					}
					
					//cout <<"SUCESSFULLY AUTHENTICATED, ENTERED MEMBER MODE"<<endl;
					
					printSTMT("SUCESSFULLY AUTHENTICATED, ENTERED MEMBER MODE");
					
					line();
					member_portal(pBookList, pRoomList, pMemberList, pPersonList, number,
							 (*pMemberList)[memIndex].GetName(), library);
				}

	    	}
	    	//librarian part here
			else if(main_choice ==2)
			{
	    		//Librarian code here
	    		string number;
				string password;
				
				bool authenticated = false;
				int tries=0;
				//cout<<"LIBRARIAN! Login to access Database"<<endl;
				printSTMT("LOG IN TO ACCESS LIBRARIAN PORTAL");
				do{
					//cout<<"Enter Number :";//INPUT NUMBER INSTEAD OF NAME
					printSTMT("enter number: ");
					cin>>number;
					//cout<<"Enter Password :";
					printSTMT("enter password: ");
					cin>>password;
					tries++;
					
					if(ValidateMember(pLibrarianList,number,password))
					{
						//cout<<"ACCESS APPROVED "<<endl;
						printSTMT("ACCESS APPROVED");
						//cout<<"Welcome LIBRARIAN";
						authenticated= true;
					}
					else
					{
						//cout<<"ACCESS DENIED "<<endl;
						printERR("ACCESS DENIED");
					}
				
				}while(tries<=3 && !authenticated);
				
					
				
				
				if(authenticated)
				{
					system("cls");
					//cout <<"SUCESSFULLY AUTHENTICATED, ENTERED LIBRARIAN MODE"<<endl;
					printSTMT("SUCESSFULLY AUTHENTICATED, ENTERED LIBRARIAN MODE");
					line();
					librarianPortal(pBookList,pLibrarianList,pPersonList,pRoomList,pMemberList,library);
				}

			}
			
			system("cls");
			mainMenu();
			//cout<<"enter your choice: ";
			printSTMT("enter your choice: ");
			cin >> main_choice;
			


			while (cin.fail()) 
			{
			cin.clear();
			cin.ignore();
			printERR ("ENTER A VALID INTEGER: ");
        
			cin >> main_choice;

			}
			
			while ( main_choice <-1 || main_choice > 3)
			{
				//cout <<"INVALID CHOICE, ENTER AGAIN: ";
				printERR("INVALID CHOICE, ENTER AGAIN: ");
				cin >> main_choice;
			}
			
			if (main_choice == -1)
			{
				run = false;
			}
			
			system("cls");

		}
	}
	
	else 
	{
		//cout<<"something has gone wrong, cannot start program."<<endl;
		printERR("SOMETHING HAS GONE WRONG, RESTART PROGRAM, CONTACT AN ADMIN IF ISSUE PERSISTS.");
	}
	
	return 0;
}









