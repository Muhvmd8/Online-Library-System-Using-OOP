#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBook.h"
#include "clsInputValidate.h"

using namespace std;


class clsDeleteBookScreen : protected clsScreen
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

public:

    static void ShowDeleteBookScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteBook))
        {
            return;
        }

        _DrawScreenHeader("\tDelete Book Screen");

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

        cout << "\nAre you sure you want to delete this Book y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {


            if (Book1.Delete())
            {
                cout << "\nBook Deleted Successfully :-)\n";
                _PrintBook(Book1);
            }
            else
            {
                cout << "\nError Book Was not Deleted\n";
            }
        }
    }

};





