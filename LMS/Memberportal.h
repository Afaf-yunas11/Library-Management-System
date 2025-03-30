#pragma once
#include "sqlite3.h"
#include "db.h"
#include "book.h"
#include "person.h"
#include "member.h"
#include "librarian.h"
#include "room.h"
#include"commonFuncs.h"

void memberMenu();

void member_portal(customList<book>*& pBookList,customList<room>*& pRoomList,customList<member>*&pMemberList,
					customList<person>*& pPersonList, string personNum, string personName, sqlitemanager& DBobj);