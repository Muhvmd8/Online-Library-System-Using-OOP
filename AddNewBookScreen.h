#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBook.h"
#include "clsInputValidate.h"
#include "clsAuthor.h"

using namespace std;


class AddNewBookScreen : protected clsScreen
{
private:

	static void  _PrintBook(clsBook Book)
	{
		cout << "Book Details: " << endl;
		cout << "_______________________\n\n";
		cout << "ID: " << Book.GetId() << endl;
		cout << "Title: " << Book.Title << endl;
		cout << "Category: " << Book.Category << endl;
		cout << "Author Id: " << Book.AutherID << endl;
		cout << "_______________________\n\n";

	}
	
	static void _PrintAuthor(clsAuthor Author)
	{
		cout << "\Author Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Author.FirstName;
		cout << "\nLastName    : " << Author.LastName;
		cout << "\nFull Name   : " << Author.FullName();
		cout << "\nEmail       : " << Author.Email;
		cout << "\nPhone       : " << Author.Phone;
		cout << "\Author ID   : " << Author.GetAuthorID();
		cout << "\n___________________\n";

	}

	static clsAuthor _ReadAuthor()
	{

		int AuthorId;
		cout << "Please enter author id? ";
		AuthorId = clsInputValidate::ReadIntNumber();

		while (clsAuthor::IsAuthorExist(AuthorId))
		{
			cout << "This id is already exist, choose another id? ";
			AuthorId = clsInputValidate::ReadIntNumber();
		}

		clsAuthor Auhtor = clsAuthor::GetAddNewAuthorObject(AuthorId);

		cout << "\nEnter FirstName: ";
		Auhtor.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Auhtor.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Auhtor.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Auhtor.Phone = clsInputValidate::ReadString();

		return Auhtor;

	}

	static void _ReadBook(clsBook& Book)
	{

		cout << "\n\nPlease enter book title? ";
		Book.Title = clsInputValidate::ReadString();

		cout << "\n\nPlease enter book category? ";
		Book.Category = clsInputValidate::ReadString();

		char Answer = 'n';
		cout << "\n\nDo you want to assign author? [Y / N]? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Book.Author = _ReadAuthor();
			Book.AutherID = Book.Author.GetAuthorID();
		}

	}

public:

	static void ShowAddNewBookScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pAddNewBook))
		{
			return;
		}

		_DrawScreenHeader("\t Add New Book Screen");

		int Id;
		cout << "Please enter book id? ";
		Id = clsInputValidate::ReadIntNumber();

		while (clsBook::IsBookExist(Id))
		{
			cout << "This id is already exist, choose another id? ";
			Id = clsInputValidate::ReadIntNumber();
		}
		
		clsBook Book = clsBook::GetAddNewObject(Id);
		_ReadBook(Book);

		clsBook::enSaveResults SaveResult;

		SaveResult = Book.Save();

		switch (SaveResult)
		{
		case clsBook::svFailEmptyObject:
			cout << "Book is empty.\n\n";
			break;

		case clsBook::svFailExistBook:
			cout << "Book is already exist\n\n";
			break;

		case clsBook::svSucceeded:
			cout << "\n\nBook Added Sccessfully.\n\n";
			_PrintBook(Book);
			_PrintAuthor(Book.Author);
			break;
		
		}

	}

};

