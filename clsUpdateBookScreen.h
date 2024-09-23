#pragma once
#include <iostream>
#include "clsBook.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;


class clsUpdateBookScreen : protected clsScreen
{
private:

    static void _PrintBook(clsBook Book)
    {
        cout << "\nBook Card:";
        cout << "\n___________________";
        cout << "\nBook ID   : " << Book.GetId();
        cout << "\nTitle     : " << Book.Title;
        cout << "\nCategory  : " << Book.Category;
        cout << "\nAuthor ID : " << Book.AutherID;
        cout << "\n___________________\n";

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
            cout << "\n\nPlease enter author id? ";
            Book.AutherID = clsInputValidate::ReadIntNumber();
        }
        else
            Book.AutherID = -1;

    }

public:

    static void ShowUpdateBookScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateBook))
        {
            return;
        }

        _DrawScreenHeader("\t Update Book Screen");

        int Id = 0;

        cout << "\nPlease Enter ID: ";
        Id = clsInputValidate::ReadIntNumber();
        while (!clsBook::IsBookExist(Id))
        {
            cout << "\nID is not found, choose another one: ";
            Id = clsInputValidate::ReadIntNumber();
        }

        clsBook Book1 = clsBook::Find(Id);
        _PrintBook(Book1);

        cout << "\nAre you sure you want to update this Book y/n? ";

        char Answer = 'n';
        cin >> Answer;


        if (Answer == 'y' || Answer == 'Y')
        {
            _ReadBook(Book1);

            clsBook::enSaveResults SaveResults;

            SaveResults = Book1.Save();

            switch (SaveResults)
            {
            case clsBook::svFailEmptyObject:
            {
                cout << "There are a ploblem\n";

               break;
            }
            case clsBook::svFailExistBook:
            {
                cout << "There are a ploblem\n";
                break;
            }
                
            case clsBook::svSucceeded:
            {
                cout << "\nBook Deleted Successfully :-)\n";
                _PrintBook(Book1);
                break;
            }

            }


        }


    }

};

