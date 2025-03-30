#include "adminPortal.h"
#include <string>
#include "sqlite3.h"
#include "db.h"
#include "book.h"
#include "person.h"
#include "member.h"
#include "librarian.h"
#include "room.h"
#include "commonFuncs.h"

void mainAdminMenu()
{
	line();
	printSTMT("1) view current lists");
	printSTMT("2) add new objects");
	printSTMT("3) update objects");
	printSTMT("4) remove objects");
	printSTMT("0 to push changes to database");
	printSTMT("-1 to go back");
//	cout <<"1. view current lists"<<endl;
//	cout <<"2. add new objects"<<endl;
//	cout <<"3. update objects"<<endl;
//	cout <<"4. remove objects"<<endl;
//	cout <<"0 to push changes to database"<<endl;
//	cout <<"-1 to go back."<<endl;
}

void viewMenu()
{
    printSTMT("1) view book list");
    printSTMT("2) view librarian list");
    printSTMT("3) view member list");
    printSTMT("4) view person list");
    printSTMT("5) view room list");
    printSTMT("-1 to go back.");
}

void addMenu()
{
    line();
    printSTMT("1) add books");
    printSTMT("2) add librarians");
    printSTMT("3) add members");
    printSTMT("4) add rooms");
    printSTMT("-1 to go back");
    printSTMT("0 to push changes to database");
}

void removeMenu()
{
    line();
    printSTMT("1) remove books");
    printSTMT("2) remove librarians");
    printSTMT("3) remove members");
    printSTMT("4) remove rooms");
    printSTMT("5) remove persons");
    printSTMT("-1 to go back");
    printSTMT("0 to push changes to database");
}

void updateMenu()
{
    line();
    printSTMT("1) update books");
    printSTMT("2) update librarians");
    printSTMT("3) update members");
    printSTMT("4) update rooms");
    printSTMT("-1 to go back");
    printSTMT("0 to push changes to database");
}



//takes as input all the lists as input, by reference so changes are reflected
void adminPortal(customList<book>*& pBookList,customList<librarian>*& pLibrarianList, customList<person>*& pPersonList,
 					customList<room>*& pRoomList, customList<member>*& pMemberList, sqlitemanager& DBobj)
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
	
	int main_choice = 0;
	int view_choice = 0;
	int add_choice = 0;
	int remove_choice = 0;
	int update_choice = 0;
	mainAdminMenu();
	//cout <<"enter choice: ";
	printSTMT("enter choice: ");
	cin >> main_choice;
	
	while (cin.fail()) 
	{
			cin.clear();
			cin.ignore();
			printERR ("ENTER A VALID INTEGER: ");
        
			cin >> main_choice;

	}
	
	bool run = true;
	
	
	while ( main_choice <-1 || main_choice > 5)
	{
		//cout <<"INVALID CHOICE, ENTER AGAIN: ";
		printERR("INVALID CHOICE, ENTER AGAIN: ");
		cin >> main_choice;
		while (cin.fail()) 
		{
			cin.clear();
			cin.ignore();
			printERR ("ENTER A VALID INTEGER: ");
	    
			cin >> main_choice;

		}
	}
	
	if (main_choice == -1)
	{
		run = false;
	}
	
	while (run)
	{
		system("cls");
		//view list portal
		if (main_choice == 1)
		{
			bool runView = true;
			line();
			viewMenu();
			printSTMT("enter choice: ");
			cin >> view_choice;
			
			while (cin.fail()) 
			{
				cin.clear();
				cin.ignore();
				printERR ("ENTER A VALID INTEGER: ");
	        
				cin >> view_choice;

			}
			while (view_choice <-1 || view_choice > 5)
			{

				cout <<"INVALID CHOICE, ENTER AGAIN: ";
				cin >> view_choice;
				while (cin.fail()) 
				{
					cin.clear();
					cin.ignore();
					printERR ("ENTER A VALID INTEGER: ");
		        
					cin >> view_choice;
	
				}

			}
			
			if (view_choice == -1)
			{
			    runView = false;
			}
			
			while(runView)
			{
				system("cls");
				//viewing books
				if (view_choice == 1)
				{
					displayListFORMATTED(pBookList);
				}
				
				//viewing librarians
				else if (view_choice == 2)
				{
					displayListFORMATTED(pLibrarianList);
				}
				
				//viewing members
				else if (view_choice == 3)
				{
					displayListFORMATTED(pMemberList);
				}
				
				//viewing persons
				else if (view_choice == 4)
				{
					displayListFORMATTED(pPersonList);
				}
				//view rooms
				else if (view_choice == 5)
				{
					displayListFORMATTED(pRoomList);
				}
				
				line();
				viewMenu();
				printSTMT("enter choice: ");
				cin >> view_choice;
				
				while (cin.fail()) 
				{
					cin.clear();
					cin.ignore();
					printERR ("ENTER A VALID INTEGER: ");
		        
					cin >> view_choice;
	
				}
				while (view_choice <-1 || view_choice > 5)
				{
	
					cout <<"INVALID CHOICE, ENTER AGAIN: ";
					cin >> view_choice;
					while (cin.fail()) 
					{
						cin.clear();
						cin.ignore();
						printERR ("ENTER A VALID INTEGER: ");
			        
						cin >> view_choice;
		
					}
	
				}
				
				if (view_choice == -1)
				{
				    runView = false;
				}
			}
		}
		//add portal
		else if (main_choice == 2)
		{
			system("cls");
			bool runAdd = true;
			//line();
			addMenu();
			//cout <<"enter choice: ";
			printSTMT("enter choice: ");
			cin >> add_choice;
			while (cin.fail()) 
			{
				cin.clear();
				cin.ignore();
				printERR ("ENTER A VALID INTEGER: ");
	        
				cin >> view_choice;

			}
			
			while (add_choice <-1 || add_choice > 4)
			{
				//cout <<"INVALID CHOICE, ENTER AGAIN: ";
				printERR("INVALID CHOICE, ENTER AGAIN: ");
				cin >> add_choice;
				while (cin.fail()) 
				{
					cin.clear();
					cin.ignore();
					printERR ("ENTER A VALID INTEGER: ");
		        
					cin >> view_choice;
	
				}
			}
			
			if (add_choice == -1)
			{
				runAdd = false;
			}
		
			
			while(runAdd)
			{
				system("cls");
				//adding books
				if (add_choice == 1)
				{
					int bookNum;
					//cout <<"how many books to add: ";
					printSTMT("how many books to add: ");
					cin >> bookNum;
					
					while (cin.fail()) 
					{
						cin.clear();
						cin.ignore();
						printERR ("ENTER A VALID INTEGER: ");
			        
						cin >> bookNum;
		
					}
					
					while (bookNum < 0)
					{
						//cout <<"enter a positive number: ";
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> bookNum;
						while (cin.fail()) 
						{
							cin.clear();
							cin.ignore();
							printERR ("ENTER A VALID INTEGER: ");
				        
							cin >> bookNum;
			
						}
					}
					
					addBooks(pBookList,pAddBookList,  bookNum);
					
				}
				//adding librarians
				else if (add_choice == 2)
				{
					int librarianNum;
					//cout <<"how many librarians to add: ";
					printSTMT("how many librarians to add: ");
					cin >> librarianNum;
					
					while (cin.fail()) 
					{
						cin.clear();
						cin.ignore();
						printERR ("ENTER A VALID INTEGER: ");
			        
						cin >> librarianNum;
		
					}
					
					while (librarianNum < 0)
					{
						//cout <<"enter a positive number: ";
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> librarianNum;
						
						while (cin.fail()) 
						{
							cin.clear();
							cin.ignore();
							printERR ("ENTER A VALID INTEGER: ");
				        
							cin >> librarianNum;
			
						}
					}
					
					addLibrarian(pLibrarianList, pAddLibrarianList, librarianNum);
//					cout <<"ADD LIBRARIAN LIST"<<endl;
//					
//					displayListFORMATTED(pAddLibrarianList);
				}
				
				//adding members
				else if (add_choice == 3)
				{
					int memberNum = 0;

					printSTMT("how many members to add?: ");
					cin >>memberNum;
					while (cin.fail()) 
					{
						cin.clear();
						cin.ignore();
						printERR ("ENTER A VALID INTEGER: ");
			        
						cin >> memberNum;
		
					}
					
					
					while (memberNum < 0)
					{
					    printERR("ENTER A POSITIVE NUMBER: ");
					    cin >> memberNum;
					    
					    while (cin.fail()) 
						{
							cin.clear();
							cin.ignore();
							printERR ("ENTER A VALID INTEGER: ");
				        
							cin >> memberNum;
			
						}
					}
					
					addMember(pMemberList, pAddMemberList, memberNum);
					
//					cout <<"ADD MEMBER LIST"<<endl;
//					cout <<"add member List size = "<<pAddMemberList->size()<<endl;
//					displayListFORMATTED(pAddMemberList);
				}
				
				//adding rooms
				else if (add_choice == 4)
				{
					int roomNum;
					printSTMT("how many rooms to add: ");
					cin >> roomNum;
					while (cin.fail()) 
					{
						cin.clear();
						cin.ignore();
						printERR ("ENTER A VALID INTEGER: ");
			        
						cin >> roomNum;
		
					}
					
					while (roomNum < 0)
					{
						printERR("ENTER A POSITIVE NUMBER: ");
					    cin >> roomNum;
					    
						while (cin.fail()) 
						{
							cin.clear();
							cin.ignore();
							printERR ("ENTER A VALID INTEGER: ");
				        
							cin >> roomNum;
			
						}
					}
					
					addRooms(pRoomList, pAddRoomList, roomNum);
					
//					cout <<"ADD ROOM LIST"<<endl;
//					
//					displayListFORMATTED(pAddRoomList);
				}
				
				else if (add_choice == 0)
				{
					printSTMT("UPDATING DATABASE");
					addToDatabase(pAddBookList, pAddPersonList, pAddMemberList, pAddLibrarianList, pAddRoomList,  DBobj);
					updateToDatabase(pUpdateBookList, pUpdatePersonList, pUpdateMemberList, pUpdateLibrarianList, pUpdateRoomList, DBobj);
					removeFromDatabase(pDeleteBookList, pDeletePersonList, pDeleteMemberList, pDeleteLibrarianList, pDeleteRoomList, DBobj);
					
					
					clearAllLists(pAddBookList, pAddLibrarianList, pAddPersonList, pAddRoomList, pAddMemberList, 
									pUpdateBookList, pUpdateLibrarianList, pUpdatePersonList, pUpdateRoomList, pUpdateMemberList,
									pDeleteBookList, pDeleteLibrarianList, pDeletePersonList, pDeleteRoomList, pDeleteMemberList);
					
					delete pBookList;
					delete pLibrarianList;
					delete pPersonList;
					delete pRoomList;
					delete pMemberList;
					
					
					
					pBookList = DBobj.readBooks("BOOKS");
					pLibrarianList = DBobj.readLibrarian("LIBRARIAN");
					pPersonList = DBobj.readPerson("PERSONS");
					pRoomList = DBobj.readRooms("ROOMS");
					pMemberList = DBobj.readMember("MEMBERS");
				}
				
				line();
				addMenu();
				//cout <<"enter choice: ";
				printSTMT("enter choice: ");
				cin >> add_choice;
				while (cin.fail()) 
				{
					cin.clear();
					cin.ignore();
					printERR ("ENTER A VALID INTEGER: ");
		        
					cin >> add_choice;
	
				}
				
				while (add_choice <-1 || add_choice > 4)
				{
					//cout <<"INVALID CHOICE, ENTER AGAIN: ";
					printERR("INVALID CHOICE, ENTER AGAIN: ");
					cin >> add_choice;
					
					while (cin.fail()) 
					{
						cin.clear();
						cin.ignore();
						printERR ("ENTER A VALID INTEGER: ");
			        
						cin >> add_choice;
		
					}
				}
				
				if (add_choice == -1)
				{
					runAdd = false;
				}
			}
		}
		
		//remove portal
		else if (main_choice == 4)
		{
			system("cls");
			bool runRem = true;
			//line();
			removeMenu();
			printSTMT("enter choice: ");
			cin >> remove_choice;
			
			while (cin.fail()) 
			{
				cin.clear();
				cin.ignore();
				printERR ("ENTER A VALID INTEGER: ");
	        
				cin >> remove_choice;

			}
			
			while (remove_choice <-1 || remove_choice > 5)
			{
				printERR("INVALID CHOICE, ENTER AGAIN: ");
				cin >> remove_choice;
				while (cin.fail()) 
				{
					cin.clear();
					cin.ignore();
					printERR ("ENTER A VALID INTEGER: ");
		        
					cin >> remove_choice;
	
				}
			}
			
			if (remove_choice == -1)
			{
				runRem = false;
			}
			
			while (runRem)
			{
				
				system("cls");
				
				//removing books
				if (remove_choice == 1)
				{
					int removeBookNum = 0;
					
					//cout <<"enter number of books you want to remove: ";
					printSTMT("enter number of books you want to remove: ");
					cin >> removeBookNum;
					while (cin.fail()) 
					{
						cin.clear();
						cin.ignore();
						printERR ("ENTER A VALID INTEGER: ");
			        
						cin >> removeBookNum;
		
					}
					while (removeBookNum< 0)
					{
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> removeBookNum;
						while (cin.fail()) 
						{
							cin.clear();
							cin.ignore();
							printERR ("ENTER A VALID INTEGER: ");
				        
							cin >> removeBookNum;
			
						}
					}
					
					removeBooks(pDeleteBookList, pBookList, removeBookNum);
					
//					cout <<"REMOVE BOOK LIST"<<endl;
//					
//					displayListFORMATTED(pDeleteBookList);
				}
				
				//removing librarians
				else if (remove_choice == 2)
				{
					int removeLibrarianNum = 0;
					
					printSTMT("enter number of Librarians you want to remove: ");
					cin >> removeLibrarianNum;
					while (cin.fail()) 
					{
						cin.clear();
						cin.ignore();
						printERR ("ENTER A VALID INTEGER: ");
			        
						cin >> removeLibrarianNum;
		
					}
					while (removeLibrarianNum< 0)
					{
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> removeLibrarianNum;
						while (cin.fail()) 
						{
							cin.clear();
							cin.ignore();
							printERR ("ENTER A VALID INTEGER: ");
				        
							cin >> removeLibrarianNum;
			
						}
					}
					
					removeLibrarians(pLibrarianList, pDeleteLibrarianList, removeLibrarianNum);
					
//					cout <<"REMOVE LIBRARIAN LIST"<<endl;
//					displayListFORMATTED(pDeleteLibrarianList);
				}
				
				//removing members
				else if (remove_choice == 3)
				{
					int removeMemberNum = 0;
					
					printSTMT("enter number of Members you want to remove: ");
					cin >> removeMemberNum;
					while (cin.fail()) 
					{
						cin.clear();
						cin.ignore();
						printERR ("ENTER A VALID INTEGER: ");
			        
						cin >> removeMemberNum;
		
					}
					
					while (removeMemberNum< 0)
					{
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> removeMemberNum;
						while (cin.fail()) 
						{
							cin.clear();
							cin.ignore();
							printERR ("ENTER A VALID INTEGER: ");
				        
							cin >> removeMemberNum;
			
						}
					}
					
					removeMember(pMemberList, pDeleteMemberList, removeMemberNum);
					
//					cout <<"REMOVE MEMBER LIST"<<endl;
//					displayListFORMATTED(pDeleteMemberList);
				}
				
				//removing rooms
				else if (remove_choice == 4)
				{
					int removeRoomNum = 0;
					
					printSTMT("enter number of rooms you want to remove: ");
					cin >> removeRoomNum;
					
					while (cin.fail() || removeRoomNum < 0)
					{
					    cin.clear();  // Clear the error flag on cin
					    cin.ignore();  // Ignore invalid input
					    printERR("ENTER A POSITIVE NUMBER: ");
					    cin >> removeRoomNum;
					}
					
					removeRooms(pRoomList, pDeleteRoomList, removeRoomNum);
					
//					cout <<"REMOVE ROOM LIST"<<endl;
//					displayListFORMATTED(pDeleteRoomList);
				}
				
				else if (remove_choice == 5)
				{
					int remNumber;
					printSTMT("how many people to remove: ");
					cin >> remNumber;
					
					while (remNumber < 0 || cin.fail())
					{
						cin.clear();
						cin.ignore();
						printERR("ENTER A POSITIVE INTEGER: ");
						cin >> remNumber;
					}
					
					removePersonWRAP(pPersonList, pDeletePersonList, remNumber);
				}
				
				//updating database
				else if (remove_choice == 0)
				{
					printSTMT("UPDATING DATABASE");
					addToDatabase(pAddBookList, pAddPersonList, pAddMemberList, pAddLibrarianList, pAddRoomList,  DBobj);
					updateToDatabase(pUpdateBookList, pUpdatePersonList, pUpdateMemberList, pUpdateLibrarianList, pUpdateRoomList, DBobj);
					removeFromDatabase(pDeleteBookList, pDeletePersonList, pDeleteMemberList, pDeleteLibrarianList, pDeleteRoomList, DBobj);
					
					
					clearAllLists(pAddBookList, pAddLibrarianList, pAddPersonList, pAddRoomList, pAddMemberList, 
									pUpdateBookList, pUpdateLibrarianList, pUpdatePersonList, pUpdateRoomList, pUpdateMemberList,
									pDeleteBookList, pDeleteLibrarianList, pDeletePersonList, pDeleteRoomList, pDeleteMemberList);
					
					delete pBookList;
					delete pLibrarianList;
					delete pPersonList;
					delete pRoomList;
					delete pMemberList;
					
					
					
					pBookList = DBobj.readBooks("BOOKS");
					pLibrarianList = DBobj.readLibrarian("LIBRARIAN");
					pPersonList = DBobj.readPerson("PERSONS");
					pRoomList = DBobj.readRooms("ROOMS");
					pMemberList = DBobj.readMember("MEMBERS");
				}
				
				line();
				removeMenu();
				printSTMT("enter choice: ");
				cin >> remove_choice;

				while (remove_choice <-1 || remove_choice > 4 || cin.fail())
				{
					printERR("INVALID CHOICE, ENTER AGAIN: ");
					cin.clear();
					cin.ignore();
					cin >> remove_choice;
				}
				
				if (remove_choice == -1)
				{
					runRem = false;
				}
			}
		}
		
		//update portal
		
		else if (main_choice == 3)
		{
			bool runUpdate = true;
			//line();
			updateMenu();
			printSTMT("enter choice: ");
			cin >> update_choice;
			
			while (update_choice <-1 || update_choice > 4|| cin.fail())
			{
				cin.clear();
				cin.ignore();
				printERR("INVALID CHOICE, ENTER AGAIN: ");
				cin >> update_choice;
			}
			
			if (update_choice == -1)
			{
				runUpdate = false;
			}
			
			while (runUpdate)
			{
				system("cls");
				//updating books
				if (update_choice == 1)
				{
					int updateBookNum = 0;
					
					printSTMT("enter the number of books you want to update: ");
					cin >> updateBookNum;
					while (updateBookNum< 0 || cin.fail())
					{
						cin.clear();
						cin.ignore();
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> updateBookNum;
					}
					updateBooksWRAP(pBookList, pUpdateBookList,updateBookNum );
					
//					cout <<"PRINTING UPDATE BOOK LIST"<<endl;
//					displayListFORMATTED(pUpdateBookList);
				}
				
				//updating librarians
				else if (update_choice == 2)
				{
					int updateLibrarianNum = 0;
					
					printSTMT("enter the number of librarians you want to update: ");
					cin >> updateLibrarianNum;
					
					while (updateLibrarianNum< 0 || cin.fail())
					{
						cin.clear();
						cin.ignore();
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> updateLibrarianNum;
					}
					
					updateLibrariansWRAP(pLibrarianList, pUpdateLibrarianList, updateLibrarianNum);
					
				}
				
				//updating member
				else if (update_choice == 3)
				{
					int updateMemberNum = 0;
					
					printSTMT("enter the number of members you want to update: ");
					cin >> updateMemberNum;
					
					while (updateMemberNum< 0 || cin.fail())
					{
						cin.clear();
						cin.ignore();
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> updateMemberNum;
					}
					updateMemberWRAP(pMemberList, pUpdateMemberList, updateMemberNum);
					
//					cout <<"PRINTING UPDATE MEMBER LIST"<<endl;
//					displayListFORMATTED(pUpdateMemberList);
				}
				
				//updating rooms
				else if (update_choice == 4)
				{
					int updateRoomNum = 0;
					
					printSTMT("enter the number of rooms you want to update: ");
					cin >> updateRoomNum;
					
					while (updateRoomNum< 0 || cin.fail())
					{
						cin.clear();
						cin.ignore();
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> updateRoomNum;
					}
					updateRoomsWRAP(pRoomList, pUpdateRoomList, updateRoomNum);
					
//					cout <<"PRINTING UPDATE ROOM LIST"<<endl;
//					displayListFORMATTED(pUpdateRoomList);
				}
				
				else if (update_choice == 0)
				{
					printSTMT("UPDATING DATABASE");
					addToDatabase(pAddBookList, pAddPersonList, pAddMemberList, pAddLibrarianList, pAddRoomList,  DBobj);
					updateToDatabase(pUpdateBookList, pUpdatePersonList, pUpdateMemberList, pUpdateLibrarianList, pUpdateRoomList, DBobj);
					removeFromDatabase(pDeleteBookList, pDeletePersonList, pDeleteMemberList, pDeleteLibrarianList, pDeleteRoomList, DBobj);
					
					
					clearAllLists(pAddBookList, pAddLibrarianList, pAddPersonList, pAddRoomList, pAddMemberList, 
									pUpdateBookList, pUpdateLibrarianList, pUpdatePersonList, pUpdateRoomList, pUpdateMemberList,
									pDeleteBookList, pDeleteLibrarianList, pDeletePersonList, pDeleteRoomList, pDeleteMemberList);
					
					delete pBookList;
					delete pLibrarianList;
					delete pPersonList;
					delete pRoomList;
					delete pMemberList;
					
					
					
					pBookList = DBobj.readBooks("BOOKS");
					pLibrarianList = DBobj.readLibrarian("LIBRARIAN");
					pPersonList = DBobj.readPerson("PERSONS");
					pRoomList = DBobj.readRooms("ROOMS");
					pMemberList = DBobj.readMember("MEMBERS");
				}
				
				line();
				updateMenu();
				printSTMT("enter choice: ");
				cin >> update_choice;
				while (update_choice <-1 || update_choice > 4|| cin.fail())
				{
					cin.clear();
					cin.ignore();
					printERR("INVALID CHOICE, ENTER AGAIN: ");
					cin >> update_choice;
				}
				
				if (update_choice == -1)
				{
					runUpdate = false;
				}
				
			}
		}
		
		//writing changes to sql
		else if (main_choice == 0)
		{
			printSTMT("UPDATING DATABASE");
			addToDatabase(pAddBookList, pAddPersonList, pAddMemberList, pAddLibrarianList, pAddRoomList,  DBobj);
			updateToDatabase(pUpdateBookList, pUpdatePersonList, pUpdateMemberList, pUpdateLibrarianList, pUpdateRoomList, DBobj);
			removeFromDatabase(pDeleteBookList, pDeletePersonList, pDeleteMemberList, pDeleteLibrarianList, pDeleteRoomList, DBobj);
					
			delete pBookList;
			delete pLibrarianList;
			delete pPersonList;
			delete pRoomList;
			delete pMemberList;
			
			pBookList = DBobj.readBooks("BOOKS");
			pLibrarianList = DBobj.readLibrarian("LIBRARIAN");
			pPersonList = DBobj.readPerson("PERSONS");
			pRoomList = DBobj.readRooms("ROOMS");
			pMemberList = DBobj.readMember("MEMBERS");
			
			//clearing the temporary lists
			
			clearAllLists(pAddBookList, pAddLibrarianList, pAddPersonList, pAddRoomList, pAddMemberList, 
							pUpdateBookList, pUpdateLibrarianList, pUpdatePersonList, pUpdateRoomList, pUpdateMemberList,
							pDeleteBookList, pDeleteLibrarianList, pDeletePersonList, pDeleteRoomList, pDeleteMemberList);
		}
		
		system("cls");
		mainAdminMenu();
		//cout <<"enter choice: ";
		printSTMT("enter choice: ");
		cin >> main_choice;
		
		
		while ( main_choice <-1 || main_choice > 5 || cin.fail())
		{
			//cout <<"INVALID CHOICE, ENTER AGAIN: ";
			cin.clear();
			cin.ignore();
			printERR("INVALID CHOICE, ENTER AGAIN: ");
			cin >> main_choice;
		}
		
		if (main_choice == -1)
		{
			run = false;
		}
	}
}