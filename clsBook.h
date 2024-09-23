#pragma once

#include <iostream>
#include "clsAuthor.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class clsBook
{

private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

    enMode _Mode;
    int _Id;
    string _Title;
    string _Category;
    int _AuthorId;
    clsAuthor _Author = clsAuthor::Find(-1); // composition

    bool _MarkedForDelete = false;

    static vector <clsBook> _LoadBooksDataFromFile()
    {
        vector <clsBook> vBooks;

        fstream MyFile;

        MyFile.open("Books.txt", ios::in); //Read Only

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsBook Book = _ConvertBookLineToObject(Line);
                vBooks.push_back(Book);
            }

            MyFile.close();

        }

        return vBooks;
    }

    static void  _SaveBookDataToFile(vector <clsBook> vBooks)
    {

        fstream MyFile;

        MyFile.open("Books.txt", ios::out);

        string Line;

        if (MyFile.is_open())
        {

            for (clsBook B : vBooks)
            {
                if (B.MarkedForDeleted() == false)
                {
                    Line = _ConvertBookObjectToLine(B);
                    MyFile << Line << endl;
                }
                
            }

            MyFile.close();

        }

    }

    static clsBook _ConvertBookLineToObject(string Line, string Separator = "#//#")
    {
        vector<string> vBookRecord;
        vBookRecord = clsString::Split(Line, Separator);

        return clsBook(enMode::UpdateMode, stoi(vBookRecord[0]), vBookRecord[1], 
            vBookRecord[2], stoi(vBookRecord[3]));

    }

    static string _ConvertBookObjectToLine(clsBook Book, string Separator = "#//#")
    {
        string BookRecord = "";

        BookRecord += to_string(Book.GetId()) + Separator;
        BookRecord += Book.Title + Separator;
        BookRecord += Book.Category + Separator;
        BookRecord += to_string(Book.AutherID);

        return BookRecord;
    }

    static void _AddDataLineToFile(string Line)
    {
        fstream MyFile;
        MyFile.open("Books.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << Line << endl;
            MyFile.close();
        }

    }

    static clsBook _GetEmptyBookObject()
    {
        return clsBook(enMode::EmptyMode, -1, "", "", -1);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertBookObjectToLine(*this));

        //clsAuthor::enSaveResults SaveResults;
        //SaveResults = this->Author.Save();

    }

    void _Update()
    {
        vector <clsBook > vBooks;
        vBooks = _LoadBooksDataFromFile();

        for (clsBook& B : vBooks )
        {

            if (B.GetId() == _Id)
            {
                B = *this;
                break;
            }

        }

        _SaveBookDataToFile(vBooks);
    }

public:

    bool MarkedForDeleted() const
    {
        return _MarkedForDelete;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    clsBook(enMode Mode, int id, string title, string category, int AuthorId)
    {
        _Category = category;
        _Title = title;
        _Id = id;
        _AuthorId = AuthorId;
        _Mode = Mode;
    }

    int GetId() const //Read only properity
    {
        return _Id;
    }

    void SetTitle(string Title)
    {
        _Title = Title;
    }

    string GetTitle() const
    {
        return _Title;
    }

    _declspec(property (get = GetTitle, put = SetTitle)) string Title;

    void SetCategory(string Category)
    {
        _Category = Category;
    }

    string GetCategory() const
    {
        return _Category;
    }

    _declspec(property (get = GetCategory, put = SetCategory)) string Category;

    void SetAuthorId(int Id)
    {
        _AuthorId = Id;
    }

    int GetAuthorId() const
    {
        return _AuthorId;
    }

    _declspec(property (get = GetAuthorId, put = SetAuthorId)) int AutherID;

    void SetAuthor(clsAuthor Author)
    {
        _Author = Author;
    }

    clsAuthor GetAuthor() const
    {
        return _Author;
    }

    _declspec(property (get = GetAuthor, put = SetAuthor)) clsAuthor Author;

    bool Delete()
    {
        
        vector<clsBook> vBooks;
        vBooks = _LoadBooksDataFromFile();

        for (clsBook& B : vBooks)
        {
            if (B.GetId() == _Id)
            {
                B._MarkedForDelete = true;
                break;
            }
        }

        _SaveBookDataToFile(vBooks);

        *this = _GetEmptyBookObject();

        return true;
    }

    static clsBook Find(int Id)
    {

        fstream MyFile;
        MyFile.open("Books.txt", ios::in);

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                clsBook Book = _ConvertBookLineToObject(Line);

                if (Book.GetId() == Id)
                {
                    MyFile.close();
                    return Book;
                }
            }

            MyFile.close();
        }

        return _GetEmptyBookObject();

    }

    //get all books has same category

    static vector <clsBook> GetAllBooksOfSameCategory(string Category)
    {

        vector <clsBook> vBooks;

        fstream MyFile;
        MyFile.open("Books.txt", ios::in);

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                clsBook Book = _ConvertBookLineToObject(Line);

                if (Book.Category == Category)
                {
                    vBooks.push_back(Book);
                }
            }

            MyFile.close();
        }

        return vBooks;
    }

    enum enSaveResults {  svFailEmptyObject = 0, svFailExistBook = 1, svSucceeded = 3 };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case clsBook::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFailEmptyObject;
            }
        }

        case clsBook::UpdateMode:

            _Update();
            return enSaveResults::svSucceeded;

        case clsBook::AddNewMode:
        {
            if (IsBookExist(_Id))
            {
                return enSaveResults::svFailExistBook;
            }

            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        }
            
        }

    }

    static clsBook GetAddNewObject(int Id)
    {
        return clsBook(enMode::AddNewMode, Id, "", "", -1);
    }

    static bool IsBookExist(int Id)
    {
        clsBook Book = clsBook::Find(Id);
        return (!Book.IsEmpty());
    }

    static vector <clsBook> GetBooksList()
    {
        return _LoadBooksDataFromFile();
    }

};



