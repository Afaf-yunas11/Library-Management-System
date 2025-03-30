#pragma once
#include<iostream>
#include <string>
using namespace std;

//this header file contains declaration for the book class

class book {
	
	string m_strISBN;
	int m_intCopies;
	string m_strGenre;
	string m_strAuthor;
	string m_strTitle;

public:
	book();

	//parameterised constructor
	book(string isbn, int copies, string genre, string author, string title);

	void SetBook(string isbn, int copies, string genre, string author, string title);

	//pata nahi ye dono kyun banaye hain dimagh nhi chal rha
	string GetISBN();

	string GetGenre();

	string GetAuthor();
	
	string GetTitle();

	int GetCopies();

	void EditISBN(string isbn);

	void EditGenre(string genre);

	void EditAuthor(string author);

	void EditTitle(string title);

	void EditCopies(int copies);
	
	void SetAttributesAIO();
	
	//need to implement this in book.cpp yet
	//IMPLEMENT THIS
	void operator = (book& obj);
	
	//FIX THESE 2
	bool operator ==(book& obj);
	bool operator !=(book& obj);
	
	
};



