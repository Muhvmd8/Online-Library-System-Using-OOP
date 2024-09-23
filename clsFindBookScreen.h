#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBook.h"
#include "clsInputValidate.h"

using namespace std;






class clsFindBookScreen : protected clsScreen
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

    static void ShowFindBookScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pFindBook))
        {
            return;
        }

        _DrawScreenHeader("\t  Find Book Screen");

        int Id = 0;

        cout << "Please enter Book ID? ";
        Id = clsInputValidate::ReadIntNumber();

        while (!clsBook::IsBookExist(Id))
        {
            cout << "\nID is not found, choose another one: ";
            Id = clsInputValidate::ReadIntNumber();
        }

        clsBook Book1 = clsBook::Find(Id);

        if (!Book1.IsEmpty())
        {
            cout << "\nBook Found -)\n";
            
        }

        else
        {
            cout << "\nBook Not Found -(\n";
        }  

        _PrintBook(Book1);
    }

};

