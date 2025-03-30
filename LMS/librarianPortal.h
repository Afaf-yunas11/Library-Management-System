#pragma once
#include "sqlite3.h"
#include "db.h"
#include "book.h"
#include "person.h"
#include "member.h"
#include "librarian.h"
#include "room.h"

//this file and its associated cpp contains all the functions for the admin portal
//common functions for portals will be kept in another file called, commonFuncs.h and commonFuncs.cpp

void librarianMenu();

//takes as input all the lists as input, by reference so changes are reflected
void librarianPortal(customList<book>*& pBookList,customList<librarian>*& pLibrarianList, customList<person>*& pPersonList,
 					customList<room>*& pRoomList, customList<member>*& pMemberList, sqlitemanager& DBobj);