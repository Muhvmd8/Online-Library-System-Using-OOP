#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsAuthor : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    int _Id;

    bool _MarkedForDelete = false;

    static clsAuthor _ConvertLinetoAuthorObject(string Line, string Seperator = "#//#")
    {
        vector<string> vAuthorData;
        vAuthorData = clsString::Split(Line, Seperator);

        return clsAuthor(enMode::UpdateMode, vAuthorData[0], vAuthorData[1], vAuthorData[2],
            vAuthorData[3], stoi(vAuthorData[4]));

    }

    static string _ConverAuthorObjectToLine(clsAuthor Author, string Seperator = "#//#")
    {

        string AuthorRecord = "";
        AuthorRecord += Author.FirstName + Seperator;
        AuthorRecord += Author.LastName + Seperator;
        AuthorRecord += Author.Email + Seperator;
        AuthorRecord += Author.Phone + Seperator;
        AuthorRecord += to_string(Author.GetAuthorID());

        return AuthorRecord;

    }

    static  vector <clsAuthor> _LoadAuthorsDataFromFile()
    {

        vector <clsAuthor> vAuthors;

        fstream MyFile;
        MyFile.open("Authors.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsAuthor Author = _ConvertLinetoAuthorObject(Line);

                vAuthors.push_back(Author);
            }

            MyFile.close();

        }

        return vAuthors;

    }

    static void _SaveAuthorsDataToFile(vector <clsAuthor> vAuthors)
    {

        fstream MyFile;
        MyFile.open("Authors.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsAuthor U : vAuthors)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverAuthorObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsAuthor> _vAuthors;
        _vAuthors = _LoadAuthorsDataFromFile();

        for (clsAuthor& U : _vAuthors)
        {
            if (U.GetAuthorID() == _Id)
            {
                U = *this;
                break;
            }

        }

        _SaveAuthorsDataToFile(_vAuthors);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverAuthorObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Authors.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsAuthor _GetEmptyAuthorObject()
    {
        return clsAuthor(enMode::EmptyMode, "", "", "", "", 0);
    }

public:

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageAuthors = 64
    };

    clsAuthor(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, int Id) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _Id = Id;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    int GetAuthorID()
    {
        return _Id;
    }


    static clsAuthor Find(int Id)
    {

        fstream MyFile;
        MyFile.open("Authors.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsAuthor Author = _ConvertLinetoAuthorObject(Line);
                if (Author.GetAuthorID() == Id)
                {
                    MyFile.close();
                    return Author;
                }

            }

            MyFile.close();

        }
        return _GetEmptyAuthorObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAuthorExists = 2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsAuthor::IsAuthorExist(_Id))
            {
                return enSaveResults::svFaildAuthorExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }

    }

    static bool IsAuthorExist(int _Id)
    {

        clsAuthor Author = clsAuthor::Find(_Id);
        return (!Author.IsEmpty());
    }

    bool Delete()
    {
        vector <clsAuthor> _vAuthors;
        _vAuthors = _LoadAuthorsDataFromFile();

        for (clsAuthor& U : _vAuthors)
        {
            if (U.GetAuthorID() == _Id)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveAuthorsDataToFile(_vAuthors);

        *this = _GetEmptyAuthorObject();

        return true;

    }

    static clsAuthor GetAddNewAuthorObject(int Id)
    {
        return clsAuthor(enMode::AddNewMode, "", "", "", "", Id);
    }

    static vector <clsAuthor> GetAuthorsList()
    {
        return _LoadAuthorsDataFromFile();
    }



};

