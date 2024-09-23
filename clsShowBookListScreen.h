#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBook.h"
#include <iomanip>

class clsListBooksScreen :protected clsScreen
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

    static void ShowBooksList()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pListBooks))
        {
            return;
        }

        vector <clsBook> vBooks = clsBook::GetBooksList();

        string Title = "\t  Book List Screen";
        string SubTitle = "\t    (" + to_string(vBooks.size()) + ") Book(s).";

        _DrawScreenHeader(Title, SubTitle);

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


