#pragma once
#include <iostream>
#include "clsBook.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAllBooksFromSameCategory : protected clsScreen
{
private:

    static void _PrintBookRecordLine(clsBook Book)
    {

        cout << setw(8) << left << "" << "| " << setw(12) << left << Book.GetId();
        cout << "| " << setw(25) << left << Book.Title;
        cout << "| " << setw(12) << left << Book.Category;
        cout << "| " << setw(20) << left << Book.AutherID;
    }

public:

    static void ShowBooksListFromSameCategoty()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pSameCategory))
        {
            return;
        }

        vector <clsBook> vBooks;
        
        string Title = "\tBooks From Same Category Screen";
        _DrawScreenHeader(Title);
        
        string Category;
        cout << "Please enter Category? ";
        Category = clsInputValidate::ReadString();

        vBooks = clsBook::GetAllBooksOfSameCategory(Category);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "Book ID";
        cout << "| " << left << setw(25) << "Title";
        cout << "| " << left << setw(12) << "Category";
        cout << "| " << left << setw(20) << "Author ID";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vBooks.size() == 0)
            cout << "\t\t\t\tNo Books Available In the System!";
        else

            for (clsBook Book : vBooks)
            {
                _PrintBookRecordLine(Book);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }
};

