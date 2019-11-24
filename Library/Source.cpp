#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<iomanip>
#include <ctype.h>
#include <windows.h>
#include <cstring>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

//1. В структуре Date нужен динамический массив для месяца

enum BookEditOneCharFunc
{
	Start,
	Booktitle,
	BookDateofpublication,
	BookAuthor,
	BookGenre,
	BookCost,
	BookRating,
	Exit
};
struct Date
{
	int day;
	char month[20];
	int year;
};
struct FIO
{
	char* Name[100];
	char* Surname[100];
	char* Middlename[100];
};
struct book
{
	int idbook;
	Date Dateofpublication;
	char* Title;
	char* Author;
	char* Genre;
	double Cost;
	double Rating;
};
struct reader
{
	int idreader;
	Date DateofBirth;
	FIO Fio;
	int PassportID;
	int numberofbooksread;
	book* Booklist;
};
void Create_Book(book& obj)
{
	char buf[500];
	cout << "Book Title ->";
	cin.getline(buf, 500);
	obj.Title = new char[strlen(buf) + 1];
	strcpy(obj.Title, buf);
	cout << "Enter Book Date of publication->" << endl;
	cout << "Day->";
	cin >> obj.Dateofpublication.day;
	cin.ignore();
	cout << "Month->";
	cin.getline(obj.Dateofpublication.month, 20);
	cout << "Year->";
	cin >> obj.Dateofpublication.year;
	cin.ignore();
	cout << "Enter Book Author->";
	cin.getline(buf, 500);
	obj.Author = new char[strlen(buf) + 1];
	strcpy(obj.Author, buf);
	cout << "Enter Book Genre ->";
	cin.getline(buf, 500);
	obj.Genre = new char[strlen(buf) + 1];
	strcpy(obj.Genre, buf);
	cout << "Enter Book Rating->";
	cin >> obj.Rating;
	cout << "Enter Book Price->";
	cin >> obj.Cost;
	cin.ignore();
}
void AddBook(book*& arr, int& size, int& id)
{
	if (size == 0)
		arr = new book[1];
	else
	{
		book* tmp = new book[size + 1];
		for (int i = 0; i < size; ++i)
		{
			tmp[i] = arr[i];
		}
		delete[]arr;
		arr = tmp;
	}
	arr[size].idbook = id++;
	Create_Book(arr[size++]);
}
int FindById(book* arr, int size, int id)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i].idbook == id)
			return i;
	}
	return -1;
}
void Del_Book_By_ID(book*& arr, int& size, int id)
{
	int pos = FindById(arr, size, id);
	if (pos == -1)
		return;
	delete[]arr[pos].Title;
	delete[]arr[pos].Author;
	delete[]arr[pos].Genre;
	if (size == 1)
	{
		delete[]arr;
		size = 0;
		return;
	}
	book* tmp = new book[--size];
	for (int i = 0, j = 0; i < size; ++i, ++j)
	{
		if (i == pos)
			j++;
		tmp[i] = arr[j];
	}
	delete[]arr;
	arr = tmp;
}
///сделать вывод книг списком в цикле текст верху не меняется внизу данные без текста
void Print_books(book obj)
{
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
	cout << "***********" << "id=" << obj.idbook << "*************" << endl;
	cout << "Book Title ->" << obj.Title << endl;
	cout << "Date of publication->" << obj.Dateofpublication.day<<" "<<obj.Dateofpublication.month<< " " << obj.Dateofpublication.year;
	cout << "Book Author->" << obj.Author << endl;
	cout << "Book Genre->" << obj.Genre << endl;
	cout << "Book Rating->" << obj.Rating << endl;
	cout << "Book Price->" << obj.Cost << endl;
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
} 
void Edit_Book_AllChar_byID(book*& arr, int& size, int id)
{
	int pos = FindById(arr, size, id);
	char buf[500];
	if (pos == -1)
	{
		return;
	}
	else
	{
		book* tmp = new book[size];
		for (int i = 0; i < size; ++i)
		{
			tmp[i] = arr[i];
		}
		cout << "Your book title->" << arr[pos].Title << endl;
		cout << "Enter new book title ->";
		cin.getline(buf, 500);
		tmp[pos].Title = new char[strlen(buf) + 1];
		strcpy(tmp[pos].Title, buf);
		cout << "Your Book Date of publication-> " << arr[pos].Dateofpublication.day << " " << arr[pos].Dateofpublication.month << "  " << arr[pos].Dateofpublication.year<< endl;
		cout << "Day->";
		cin >> tmp[pos].Dateofpublication.day;
		cin.ignore();
		cout << "Month->";
		cin.getline(tmp[pos].Dateofpublication.month, 20);
		cout << "Year->";
		cin >> tmp[pos].Dateofpublication.year;
		cin.ignore();
		cout << "Book Author ->" << arr[pos].Author << endl;
		cout << "Enter new Book Author ->";
		cin.getline(buf, 500);
		tmp[pos].Author = new char[strlen(buf) + 1];
		strcpy(tmp[pos].Author, buf);
		cout << "Your Book genre ->" << tmp[pos].Genre << endl;
		cout << "Enter new Book genre ->";
		cin.getline(buf, 500);
		tmp[pos].Genre = new char[strlen(buf) + 1];
		strcpy(tmp[pos].Genre, buf);
		cout << "Your Book rating->" << arr[pos].Rating << endl;
		cout << "Enter new rating->";
		cin >> tmp[pos].Rating;
		cout << "Your Book price->" << arr[pos].Cost << endl;
		cout << "Enter new price->";
		cin >> tmp[pos].Cost;
		cin.ignore();

		delete[]arr[pos].Title;
		delete[]arr[pos].Author;
		delete[]arr[pos].Genre;
		delete[]arr;
		arr = tmp;
	}

}
void Edit_Book_One_Char_byID_menucore(book*& arr, int& size, int& id, char* chuserchoice, bool& x)
{
	int pos = FindById(arr, size, id);
	char buf[500];
	book* tmp = new book[size];
	for (int i = 0; i < size; ++i)
	{
		tmp[i] = arr[i];
	}
	BookEditOneCharFunc userchoice = Start;
	int filmid = 0;
	if (strcmp(chuserchoice, "Booktitle") == 0)
		userchoice = BookEditOneCharFunc::Booktitle;
	else if (strcmp(chuserchoice, "BookDateofpublication") == 0)
		userchoice = BookEditOneCharFunc::BookDateofpublication;
	else if (strcmp(chuserchoice, "BookAuthor") == 0)
		userchoice = BookEditOneCharFunc::BookAuthor;
	else if (strcmp(chuserchoice, "BookGenre") == 0)
		userchoice = BookEditOneCharFunc::BookGenre;
	else if (strcmp(chuserchoice, "BookCost") == 0)
		userchoice = BookEditOneCharFunc::BookCost;
	else if (strcmp(chuserchoice, "Exit") == 0)
		userchoice = BookEditOneCharFunc::BookRating;
	else
		userchoice = BookEditOneCharFunc::Exit;
	switch (userchoice)
	{
	case Booktitle:
		cout << "Your book title->" << arr[pos].Title << endl;
		cout << "Enter new book title ->";
		cin.getline(buf, 500);
		tmp[pos].Title = new char[strlen(buf) + 1];
		strcpy(tmp[pos].Title, buf);
		delete[]arr[pos].Title;
		break;
	case BookDateofpublication:
		cout << "Your Book Date of publication-> " << arr[pos].Dateofpublication.day << " " << arr[pos].Dateofpublication.month << "  " << arr[pos].Dateofpublication.year << endl;
		cout << "Day->";
		cin >> tmp[pos].Dateofpublication.day;
		cin.ignore();
		cout << "Month->";
		cin.getline(tmp[pos].Dateofpublication.month, 20);
		cout << "Year->";
		cin >> tmp[pos].Dateofpublication.year;
		cin.ignore();
		break;
	case BookAuthor:
		cout << "Book Author ->" << arr[pos].Author << endl;
		cout << "Enter new Book Author ->";
		cin.getline(buf, 500);
		tmp[pos].Author = new char[strlen(buf) + 1];
		strcpy(tmp[pos].Author, buf);
		delete[]arr[pos].Author;
		break;
	case BookGenre:
		cout << "Your Book genre ->" << tmp[pos].Genre << endl;
		cout << "Enter new Book genre ->";
		cin.getline(buf, 500);
		tmp[pos].Genre = new char[strlen(buf) + 1];
		strcpy(tmp[pos].Genre, buf);
		delete[]arr[pos].Genre;
		break;
	case BookRating:
		cout << "Your Book rating->" << arr[pos].Rating << endl;
		cout << "Enter new rating->";
		cin >> tmp[pos].Rating;
		cin.ignore();
		break;
	case BookCost:
		cout << "Your Book price->" << arr[pos].Cost << endl;
		cout << "Enter new price->";
		cin >> tmp[pos].Cost;
		cin.ignore();
		break;
	case Exit:
		x = false;
		break;
	}
	delete[]arr;
	arr = tmp;
}
void Edit_Book_One_Char_byID(book*& arr, int& size, int id)
{
	int pos = FindById(arr, size, id);
	if (pos == -1)
	{
		return;
	}
	else
	{
		char buf[500];
		bool x = true;
		while (x)
		{
			BookEditOneCharFunc userchoice = Start;
			cout << "*******************************************************" << endl;
			cout << "Enter how field you want change (for example 'Booktitle') " << endl;
			cout << "1.Booktitle\n2.BookDateofpublication\n3.BookAuthor\n4.BookGenre\n5.BookCost\n6.BookRating\n7.Exit\n" << endl;
			cin.getline(buf, 500);
			Edit_Book_One_Char_byID_menucore(arr, size, id, buf, x);
		}
	}
}



int main()
{
	char buf[500];
	int idbook = 1;
	int idreader = 1;
	int size = 0;
	book* Book = nullptr;


	//cout << "Memory Leaks - " << _CrtDumpMemoryLeaks() << endl;
	system("pause");
}