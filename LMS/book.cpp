
#include<iostream>
#include "book.h"
#include <string.h>
#include <cassert>
using namespace std;

book::book() {
	m_strISBN = "";
	m_intCopies = 0;
	m_strGenre = "";
	m_strAuthor = "";
	m_strTitle = "";
}

book::book(string isbn, int copies, string genre, string author, string title) {
	m_strISBN = isbn;
	//might remove these assert statements later and only check when i am trying to output
	assert(m_strISBN.length() > 0);
	m_intCopies = copies;
	assert(m_intCopies >= 0);
	m_strGenre = genre;
	assert(m_strGenre.length() > 0);
	m_strAuthor = author;
	assert(m_strAuthor.length() > 0);
	m_strTitle = title;
	assert(m_strTitle.length() > 0);
}

void book::SetBook(string isbn, int copies, string genre, string author, string title) {
	m_strISBN = isbn;
	//might remove these assert statements later and only check when i am trying to output
	assert(m_strISBN.length() > 0);
	m_intCopies = copies;
	assert(m_intCopies >= 0);
	m_strGenre = genre;
	assert(m_strGenre.length() > 0);
	m_strAuthor = author;
	assert(m_strAuthor.length() > 0);
	m_strTitle = title;
	assert(m_strTitle.length() > 0);
}

string book::GetISBN(){
	return m_strISBN;
}

string book::GetGenre() {
	return m_strGenre;
}

string book::GetAuthor() {
	return m_strAuthor;
}

string book::GetTitle() {
	return m_strTitle;
}

int book::GetCopies() {
	return m_intCopies;
}

void book::EditISBN(string isbn) {
	m_strISBN = isbn;
	assert(m_strISBN.length() > 0);
}

void book::EditGenre(string genre) {
	m_strGenre = genre;
	assert(m_strGenre.length() > 0);
}

void book::EditAuthor(string author) {
	m_strAuthor = author;
	assert(m_strAuthor.length() > 0);
}

void book::EditTitle(string title) {
	m_strTitle = title;
	assert(m_strTitle.length() > 0);
}

void book::EditCopies(int copies) {
	m_intCopies = copies;
	assert(m_intCopies >= 0);
}

void book::operator =(book& obj){
	m_strTitle = obj.m_strTitle;
	m_intCopies = obj.m_intCopies;
	m_strAuthor = obj.m_strAuthor;
	m_strGenre = obj.m_strGenre;
	m_strISBN = obj.m_strISBN;
	
}
//fix these 2
//add  = operator
bool book::operator==( book& other) {
    return (m_strTitle == other.m_strTitle &&
            m_strAuthor == other.m_strAuthor &&
            m_strGenre == other.m_strGenre &&
            m_strISBN == other.m_strISBN &&
            m_intCopies == other.m_intCopies);
}


bool book::operator!=( book& other) {
    return !(*this == other); // Leverage existing == operator
  }

void book::SetAttributesAIO() {
    cout << "Enter ISBN: ";
    cin >> m_strISBN;

    cout << "Enter number of copies: ";
    cin >> m_intCopies;
    //cin.ignore(); // Ignore the remaining newline character in the input buffer

    cout << "Enter genre: " ;
    cin >> m_strGenre;

    cout << "Enter author: ";
    cin >> m_strAuthor;

    cout << "Enter title: ";
    cin >> m_strTitle;
}

