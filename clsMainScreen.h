#pragma once

#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "AddNewBookScreen.h"
#include "clsDeleteBookScreen.h"
#include "clsUpdateBookScreen.h"
#include "clsManageUsersScreen.h"
#include "clsShowBookListScreen.h"
#include "clsFindBookScreen.h"
#include "clsAllBooksFromSameCategory.h"

using namespace std;


class clsMainMenuScreen : protected clsScreen
{

private:

	enum enMainMenueOptions { eBooksList = 1, eAddNewBook = 2, eDeleteBook = 3,
     	eUpdateBook = 4, eFindBook = 5, eSameCategory = 6, eManageUsers = 7, eManageAuthors = 8, eExit = 9 };

	static short _ReadMainMenueOption()
	{

		cout << setw(37) << left << "\t\t\t\t     Choose what do you want to do? [1 to 9]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 10);

		return Choice;
		
	}

	static  void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowMainMenue();
	}

	static void _ShowBookListScreen()
	{
		clsListBooksScreen::ShowBooksList();
	}

	static void _ShowAddNewBookScreen()
	{
		AddNewBookScreen::ShowAddNewBookScreen();
	}

	static void _ShowDeleteBookScreen()
	{
		clsDeleteBookScreen::ShowDeleteBookScreen();
	}

	static void _ShowUpdateBookScreen()
	{
		clsUpdateBookScreen::ShowUpdateBookScreen();
	}

	static void _ShowFindBookScreen()
	{
		clsFindBookScreen::ShowFindBookScreen();
	}

	static void _ShowSameCategoryScreen()
	{
		clsAllBooksFromSameCategory::ShowBooksListFromSameCategoty();
	}

	static void _ShowManageUsersMenue()
	{
		clsManageUsersScreen::ShowManageUsersMenue();
	}

	static void _ShowManageAuthorsMenue()
	{
		cout << "Manage Author Screen will be here.";
	}

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _PerformMainMenueOption(enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{

		case enMainMenueOptions::eBooksList:
			system("cls");
			_ShowBookListScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eAddNewBook:
			system("cls");
			_ShowAddNewBookScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eDeleteBook:
			system("cls");
			_ShowDeleteBookScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eUpdateBook:
			system("cls");
			_ShowUpdateBookScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eFindBook:
			system("cls");
			_ShowFindBookScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eSameCategory:
			system("cls");
			_ShowSameCategoryScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eManageUsers:
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eManageAuthors:
			system("cls");
			_ShowManageAuthorsMenue();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eExit:
			system("cls");
			_Logout();
			break;
		}

	}

public:

	static void ShowMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Book List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Book.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Book.\n";
		cout << setw(37) << left << "" << "\t[4] Update Book Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Book.\n";
		cout << setw(37) << left << "" << "\t[6] Same Category.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Manage Authors.\n";
		cout << setw(37) << left << "" << "\t[9] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
	}

};

