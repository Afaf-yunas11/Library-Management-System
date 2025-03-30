#include "sqlite3.h"
#include "db.h"
#include "book.h"
#include "iomanip"
#include "person.h"
#include "member.h"
#include "librarian.h"
#include "room.h"
#include"commonFuncs.h"
#include"Memberportal.h"


void memberMenu()
{
    printSTMT("1) Issue Book");
    printSTMT("2) Return Book");
    printSTMT("3) Book Room");
    printSTMT("4) unBook Room");
    printSTMT("5) View Books");
    printSTMT("6) Search Specific Book");
    printSTMT("7) Search Genre");
    printSTMT("8) View your issued books");
    printSTMT("enter -1 to go back");
}


void member_portal(customList<book>*& pBookList,customList<room>*& pRoomList,customList<member>*& pMemberList, 
					customList<person>*& pPersonList, string personNum, string personName,  sqlitemanager& DBobj)
{
    //making add lists
	customList<book>* pAddBookList = new customList<book>;
	customList<librarian>* pAddLibrarianList = new customList<librarian>;
	customList<person>* pAddPersonList = new customList<person>;
	customList<room>* pAddRoomList = new customList<room>;
	customList<member>* pAddMemberList = new customList<member>;
	
	//making updateLists
	customList<book>* pUpdateBookList = new customList<book>;
	customList<librarian>* pUpdateLibrarianList = new customList<librarian>;
	customList<person>* pUpdatePersonList = new customList<person>;
	customList<room>* pUpdateRoomList = new customList<room>;
	customList<member>* pUpdateMemberList = new customList<member>;
	
	//making removeLists
	customList<string>* pDeleteBookList = new customList<string>;
	customList<string>* pDeleteLibrarianList = new customList<string>;
	customList<string>* pDeletePersonList = new customList<string>;
	customList<string>* pDeleteRoomList = new customList<string>;
	customList<string> *pDeleteMemberList = new customList<string>;
	
	
    int choice;
    
	
	line();
	memberMenu();
	//cout <<"enter choice: ";
	printSTMT("enter choice: ");
	cin >> choice;
	bool run  = true;
	
	while ( choice <-1 || choice > 8 || choice == 0 || cin.fail())
	{
		cin.clear();
		cin.ignore();
		printERR("INVALID CHOICE, ENTER AGAIN: ");
		cin >> choice;
	}
	
	if (choice == -1)
	{
		run = false;
	}
	
	while (run)
	{
		system("cls");
		switch (choice)
		{
			//issue book
			case 1:
			{
				system("cls");
				issueBook( pBookList, pUpdateBookList,  pAddPersonList, personNum, personName)	;
			
			}	
		
			break;
			//return book
			case 2:
			{
				system("cls");
				int returnNum = 0;
				//cout <<"enter the number of books you want to return: ";
				printSTMT("enter the number of books you want to return: ");
				cin >> returnNum;
				
				while (cin.fail()) 
				{
					cin.clear();
					cin.ignore();
					printERR ("ENTER A VALID INTEGER: ");
		        
					cin >> returnNum;
		
				}
				
				while(returnNum < 0)
				{
					printERR("ENTER A POSITIVE NUMBER: ");
					cin >> returnNum;
					
					while (cin.fail()) 
					{
						cin.clear();
						cin.ignore();
						printERR ("ENTER A VALID INTEGER: ");
			        
						cin >> returnNum;
		
					}
				}
				
				returnBook(pBookList, pUpdateBookList, pPersonList, pDeletePersonList, returnNum, personNum);
			}	
		
			break;	
			
			//book room
			case 3:
			{
				system("cls");
				displayListFORMATTED(pRoomList);
				line();
				bookRoom (pRoomList,  pUpdateRoomList, personNum);
			}	
			
			break;	
			
			//unbook room
			case 4:
			{
				
				system("cls");
				displayListFORMATTED(pRoomList);
				unBookRoom(pRoomList, pUpdateRoomList, personNum);
				
			}
			break;
			case 5:
			{
				system("cls");
				displayListFORMATTED(pBookList);
				
			}	
			break;	
			
			case 6:
			{
				system("cls");
				string title;
				printSTMT("enter title: ");
				cin.ignore();
				getline(cin,title);
				bool check=false;
				
				int copies = 0;
				
				for(int i=0;i<pBookList->size();i++)
				{
					if((*pBookList)[i].GetTitle()==title && (*pBookList)[i].GetCopies()!=0)
					{
						check=true;
						copies = (*pBookList)[i].GetCopies();
					}
				}
				if(check)
				{
					printSTMT(to_string(copies) + " copies available.");
				}
				else
				{
					//cout<<"Sorry! We do not have book with title"<<title;
					printERR("BOOK NOT AVAILABLE");
				}
				
			}	
			break;	
			case 7:
			{
				system("cls");
				customList<book>* pSpecificBooks = new customList<book>;
				
				string yondra="";
			
				int check=0;
				//cout<<"Which Genre you want to search?: ";
				printSTMT("enter genre: ");
				cin.ignore();
				getline(cin,yondra);
				
				for(int i=0;i<pBookList->size();i++)
			    {
					if ((*pBookList)[i].GetGenre() == yondra)
					{
						pSpecificBooks->push((*pBookList)[i]);
						
					}
				
				}
				
				if (pSpecificBooks->size() > 0)
				{
					displayListFORMATTED(pSpecificBooks);
				}
				else 
				{
					printERR("NO BOOKS IN THE GENRE FOUND, SORRY");
				}
			}
			
			break;
		
			case 8:
			{
				system("cls");
				customList<person>* pTempList = new customList<person>;
				
				for (int i = 0 ; i < pPersonList->size(); i++)
				{
					if ((*pPersonList)[i].GetNumber() == personNum)
					{
						pTempList->push((*pPersonList)[i]);
					}
				}
				
				if (pTempList->size() != 0)
				{
					displayListFORMATTED(pTempList);
				}
				else 
				{
					printERR("YOU HAVE NO ISSUED BOOKS");
				}
				
				delete pTempList;
				pTempList = nullptr;
			}
		default:
		
		break;
		
		}
		
		addToDatabase(pAddBookList, pAddPersonList, pAddMemberList, pAddLibrarianList, pAddRoomList,  DBobj);
		updateToDatabase(pUpdateBookList, pUpdatePersonList, pUpdateMemberList, pUpdateLibrarianList, pUpdateRoomList, DBobj);
		removeFromDatabase(pDeleteBookList, pDeletePersonList, pDeleteMemberList, pDeleteLibrarianList, pDeleteRoomList, DBobj);
				
		delete pBookList;
		//delete pLibrarianList;
		//delete pPersonList;
		delete pRoomList;
		delete pMemberList;
		
		pBookList = DBobj.readBooks("BOOKS");
		//pLibrarianList = DBobj.readLibrarian("LIBRARIAN");
		pPersonList = DBobj.readPerson("PERSONS");
		pRoomList = DBobj.readRooms("ROOMS");
		pMemberList = DBobj.readMember("MEMBERS");
		
		//clearing the temporary lists
		
		clearAllLists(pAddBookList, pAddLibrarianList, pAddPersonList, pAddRoomList, pAddMemberList, 
						pUpdateBookList, pUpdateLibrarianList, pUpdatePersonList, pUpdateRoomList, pUpdateMemberList,
						pDeleteBookList, pDeleteLibrarianList, pDeletePersonList, pDeleteRoomList, pDeleteMemberList);
		
		
		line();
		memberMenu();
		//cout <<"enter choice: ";
		printSTMT("enter choice: ");
		cin >> choice;

		while (cin.fail()) 
		{
			cin.clear();
			cin.ignore();
			printERR ("ENTER A VALID INTEGER: ");
	    
			cin >> choice;

		}
		

		

		while ( choice <-1 || choice > 8 || choice == 0)
		{
			printERR("INVALID CHOICE, ENTER AGAIN: ");
			cin >> choice;
			while (cin.fail()) 
			{
				cin.clear();
				cin.ignore();
				printERR ("ENTER A VALID INTEGER: ");
	        
				cin >> choice;

			}
		}
		
		if (choice == -1)
		{
			run = false;
		}
		
	}
} 
							
   