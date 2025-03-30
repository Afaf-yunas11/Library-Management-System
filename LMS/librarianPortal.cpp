#include "librarianPortal.h"
#include <string>
#include "sqlite3.h"
#include "db.h"
#include "book.h"
#include "person.h"
#include "member.h"
#include "librarian.h"
#include "room.h"
#include "commonFuncs.h"

void mainLibrarianMenu()
{
	line();
    printSTMT("1) view current lists");
    printSTMT("2) add new objects");
    printSTMT("3) update objects");
    printSTMT("4) remove objects");
    printSTMT("5) issue book");
    printSTMT("6) return book");
    printSTMT("7) book room");
    printSTMT("8) cancel room booking");
    printSTMT("0 to push changes to database");
    printSTMT("-1 to go back");
}

void viewLibrarianMenu()
{
	line();
    printSTMT("1) view book list");
    printSTMT("2) view member list");
    printSTMT("3) view room list");
    printSTMT("4) view issued books");
    printSTMT("-1 to go back");
}

void addLibrarianMenu()
{
    line();
    printSTMT("1) add books");
    printSTMT("2) add members");
    printSTMT("3) add rooms");
    printSTMT("-1 to go back");
    printSTMT("0 to push changes to database");
}

void removeLibrarianMenu()
{
    line();
    printSTMT("1) remove books");
    printSTMT("2) remove members");
    printSTMT("3) remove rooms");
    printSTMT("-1 to go back");
    printSTMT("0 to push changes to database");
}

void updateLibrarianMenu()
{
    line();
    printSTMT("1) update books");
    printSTMT("2) update members");
    printSTMT("3) update rooms");
    printSTMT("-1 to go back");
    printSTMT("0 to push changes to database");
}


//takes as input all the lists as input, by reference so changes are reflected
void librarianPortal(customList<book>*& pBookList,customList<librarian>*& pLibrarianList, customList<person>*& pPersonList,
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
	
	mainLibrarianMenu();
	printSTMT("enter choice: ");
	cin >> main_choice;
	bool run = true;
	
	
	while ( main_choice <-1 || main_choice > 8)
	{
		printERR("INVALID CHOICE, ENTER AGAIN: ");
		cin >> main_choice;
				while (cin.fail()) {
			cin.clear();
			cin.ignore();
			        printERR ("Input failed. Please enter a valid integer.");
        
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
			viewLibrarianMenu();
			printSTMT("enter choice: ");
			cin >> view_choice;
			
			while (view_choice <-1 || view_choice > 4 || cin.fail())
			{
				cin.clear();
				cin.ignore();
				printERR("INVALID CHOICE, ENTER AGAIN: ");
				cin >> view_choice;
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
//				else if (view_choice == 2)
//				{
//					displayListFORMATTED(pLibrarianList);
//				}
				
				//viewing members
				else if (view_choice == 2)
				{
					displayListFORMATTED(pMemberList);
				}
				
				//view rooms
				else if (view_choice == 3)
				{
					displayListFORMATTED(pRoomList);
				}
				
				else if (view_choice == 4)
				{
					displayListFORMATTED(pPersonList);
				}
				viewLibrarianMenu();
				printSTMT("enter choice: ");
				cin >> view_choice;

				
				while (view_choice <-1 || view_choice > 4 || cin.fail())

				{
					cin.clear();
					cin.ignore()
;					printERR("INVALID CHOICE, ENTER AGAIN: ");
					cin >> view_choice;
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
			
			bool runAdd = true;
			line();
			addLibrarianMenu();
			printSTMT("enter choice: ");
			cin >> add_choice;
		
			while (add_choice <-1 || add_choice > 3 || cin.fail())
			{
				cin.clear();
				cin.ignore();
				printERR("INVALID CHOICE, ENTER AGAIN: ");
				cin >> add_choice;
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
					
					while (bookNum < 0 || cin.fail())
					{
						//cout <<"enter a positive number: ";
						cin.clear();
						cin.ignore();
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> bookNum;
					
					}
					
					addBooks(pBookList,pAddBookList,  bookNum);
					
				}

				
				//adding members
				else if (add_choice == 2)
				{
					int memberNum = 0;

					cout <<"how many members to add?: ";
					cin >>memberNum;
					
					while (memberNum < 0 || cin.fail())
					{
						cin.clear();
						cin.ignore();
				        printERR ("Input failed. Please enter a valid integer.");
	        	
						cin >> memberNum;
					}
					addMember(pMemberList, pAddMemberList, memberNum);
				}
				
				//adding rooms
				else if (add_choice == 3)
				{
					int roomNum;
					printSTMT("how many rooms to add: ");
					cin >> roomNum;
						
					while (roomNum < 0 || cin.fail())
					{
						cin.clear();
						cin.ignore();
						
					    printERR("ENTER A POSITIVE NUMBER: ");
					    cin >> roomNum;
					}
					
					addRooms(pRoomList, pAddRoomList, roomNum);
				}
				
				else if (add_choice == 0)
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
				
				line();
				addLibrarianMenu();
				//cout <<"enter choice: ";
				printSTMT("enter choice: ");
				cin >> add_choice;
	
				while (add_choice <-1 || add_choice > 4 || cin.fail())
				{
					
					cin.clear();
					cin.ignore();
			        printERR ("Input failed. Please enter a valid integer.");
        	
					cin >> add_choice;
				}
				
				
				if (add_choice == -1)
				{
					runAdd = false;
					system("cls");
				}
			}
		}
		
		//remove portal
		else if (main_choice == 4)
		{
			bool runRem = true;
			line();
			removeLibrarianMenu();
			printSTMT("enter choice: ");
			cin >> remove_choice;
			
			while (remove_choice <-1 || remove_choice > 3 || cin.fail())
			{
				cin.clear();
				cin.ignore();
				printERR("INVALID CHOICE, ENTER AGAIN: ");
				cin >> remove_choice;
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
				
					while (removeBookNum< 0 || cin.fail())
					{
						cin.clear();
						cin.ignore();
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> removeBookNum;
					}
					
					removeBooks(pDeleteBookList, pBookList, removeBookNum);
				}
				
				//removing librarians
//				else if (remove_choice == 2)
//				{
//					int removeLibrarianNum = 0;
//					
//					cout <<"enter number of Librarians you want to remove: ";
//					cin >> removeLibrarianNum;
//					
//					while (removeLibrarianNum< 0)
//					{
//						cout <<"enter a positive number: ";
//						cin >> removeLibrarianNum;
//					}
//					
//					removeLibrarians(pLibrarianList, pDeleteLibrarianList, removeLibrarianNum);
//					
//					cout <<"REMOVE LIBRARIAN LIST"<<endl;
//					displayListFORMATTED(pDeleteLibrarianList);
//				}
				
				//removing members
				else if (remove_choice == 2)
				{
					int removeMemberNum = 0;
					
					printSTMT("enter number of Members you want to remove: ");
					cin >> removeMemberNum;
					
					while (removeMemberNum< 0 || cin.fail())
					{
						cin.clear();
						cin.ignore();
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> removeMemberNum;
					}
					
					removeMember(pMemberList, pDeleteMemberList, removeMemberNum);
				}
				
				//removing rooms
				else if (remove_choice == 3)
				{
					int removeRoomNum = 0;
					
					printSTMT("enter number of rooms you want to remove: ");
					cin >> removeRoomNum;
					
					while (removeRoomNum< 0 || cin.fail())
					{
						cin.clear();
						cin.ignore();
						printERR("ENTER A POSITIVE NUMBER: ");
						cin >> removeRoomNum;
					}
					
					removeRooms(pRoomList, pDeleteRoomList, removeRoomNum);
				}
				
				//updating database
				else if (remove_choice == 0)
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
				
				line();
				removeLibrarianMenu();
				//cout <<"enter choice: ";
				printSTMT("enter choice: ");
				cin >> remove_choice;
				
				while (remove_choice <-1 || remove_choice > 3 || cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout <<"INVALID CHOICE, ENTER AGAIN: ";
					cin >> remove_choice;
				}
				
				if (remove_choice == -1)
				{
					runRem = false;
					system("cls");
				}
			}
		}
		
		//update portal
		
		else if (main_choice == 3)
		{
			bool runUpdate = true;
			line();
			updateLibrarianMenu();
			cout <<"enter choice: ";
			cin >> update_choice;
	
			while (update_choice <-1 || update_choice > 3 || cin.fail())
			{
				
				cin.clear();
				cin.ignore();
			    printERR ("Input failed. Please enter a valid integer.");
        
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
					
					//cout <<"enter number of books you want to update: ";
					printSTMT("enter number of books you want to update: ");
					cin >> updateBookNum;
					
					while (updateBookNum< 0|| cin.fail())
					{
						cin.clear();
						cin.ignore();
						printERR("enter a positive number: ");
						cin >> updateBookNum;

					}
					updateBooksWRAP(pBookList, pUpdateBookList,updateBookNum );
					
					
				}
				
				//updating librarians
//				else if (update_choice == 2)
//				{
//					int updateLibrarianNum = 0;
//					
//					cout <<"enter number of librarians you want to update: ";
//					cin >> updateLibrarianNum;
//					
//					while (updateLibrarianNum< 0)
//					{
//						cout <<"enter a positive number: ";
//						cin >> updateLibrarianNum;
//					}
//					
//					updateLibrariansWRAP(pLibrarianList, pUpdateLibrarianList, updateLibrarianNum);
//					
//					cout <<"PRINTING UPDATE LIBRARIAN LIST"<<endl;
//					displayListFORMATTED(pUpdateLibrarianList);
//				}
				
				//updating member
				else if (update_choice == 2)
				{
					int updateMemberNum = 0;
					
					//cout <<"enter number of Members you want to update: ";
					printSTMT("enter number of members you want to update: ");
					cin >> updateMemberNum;
					
					while (updateMemberNum< 0 || cin.fail())
					{
						cin.clear();
						cin.ignore();
						printERR("enter a positive number: ");
						cin >> updateMemberNum;
								
					}
					updateMemberWRAP(pMemberList, pUpdateMemberList, updateMemberNum);
					
				}
				
				//updating rooms
				else if (update_choice == 3)
				{
					int updateRoomNum = 0;
					
					//cout <<"enter number of Rooms you want to update: ";
					printSTMT("enter number of rooms you want to update: ");
					cin >> updateRoomNum;
					
					while (updateRoomNum< 0 || cin.fail())
					{
					
						cin.clear();
						cin.ignore();
				        printERR ("Input failed. Please enter a valid integer.");
	        
						cin >> updateRoomNum;
					}
					
					updateRoomsWRAP(pRoomList, pUpdateRoomList, updateRoomNum);
					
				}
				
				else if (update_choice == 0)
				{
					cout <<"UPDATING DATABASE"<<endl;
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
				}
				line();
				updateLibrarianMenu();
				//cout <<"enter choice: ";
				printSTMT("enter choice: ");
				cin >> update_choice;
					
				
				while (update_choice <-1 || update_choice > 3 || cin.fail())
				{
					cin.clear();
					cin.ignore();
			        printERR ("Input failed. Please enter a valid integer.");
        
					cin >> update_choice;
				}
				
				if (update_choice == -1)
				{
					runUpdate = false;
					system("cls");
				}
				
			}
		}
		
		//issue book
		else if(main_choice==5)
		{
			system("cls");
			issueBook( pBookList, pUpdateBookList, pAddPersonList);
		}
		
		//return book
		else if(main_choice==6)
		{
			system("cls");
			int returnNum=0;
			//cout<<"RETURNING BOOKS"<<endl;
			//cout<<"Enter the number of  books that you want to return "<<endl;
			printSTMT("RETURNING BOOKS");
			printSTMT("enter the number of books that you want to return: ");
			cin>>returnNum;
			
			while (returnNum < 0 || cin.fail())
			{
				cin.clear();
				cin.ignore();
				printERR("enter a positive number: ");
				cin >> returnNum;
			}
			returnBook(pBookList,pUpdateBookList,pPersonList,pDeletePersonList,returnNum);
		}
		
		//book room
		else if(main_choice==7)
		{
			system("cls");
			displayListFORMATTED(pRoomList);
			bookRoom(pRoomList,pUpdateRoomList);
		}
		//unbook room
		else if(main_choice==8)
		{
			system("cls");
			displayListFORMATTED(pRoomList);
			unBookRoom(pRoomList,pUpdateRoomList);
		}
		
		else if (main_choice == 0)
		{
		
			//writing changes to sql
			//cout <<"UPDATING DATABASE"<<endl;
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
		}
		
		//system("cls");
		line();
		mainLibrarianMenu();
		printSTMT("enter choice: ");
		cin >> main_choice;
		
		
		while ( main_choice <-1 || main_choice > 8 || cin.fail())
		{
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