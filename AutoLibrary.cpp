/**
 * �Զ�ͼ��� ������
 */

#pragma warning(disable:4786)
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <map>

#include "global.h"
#include "date.h"
#include "BookData.h"
#include "ReaderData.h"
#include "Database.h"
#include "Librarian.h"
#include "Reader.h"

using namespace std;

bool cmpIgnoreCase(char c1, char c2)
{
	c1 = (c1 >= 0x41 && c1 <= 0x60) ? c1 : c1 - 0x20;
	c2 = (c2 >= 0x41 && c2 <= 0x60) ? c2 : c2 - 0x20;
	return c1 == c2;
}

int main()
{
	Database<BookData>    bookBase("books.dat");///Users/mac/Desktop/rails/
	Database<ReaderData>  readerBase("readers.dat");

	char choice = 'X';
	//第一层选择
	while (!cmpIgnoreCase(choice, 'E'))
	{
		cout << "(L)ibrarian entry,  (R)eader entry,  (E)xit:";
		cin >> choice;
		Librarian * mgr = NULL;
		Reader * rdr = NULL;

		switch (choice)
		{
		case 'L': case 'l':
			mgr = new Librarian(101, "yjc");
			choice = mgr->login(); 
			//第二层选择
			while (!cmpIgnoreCase(choice, 'E'))
			{
				cout << "(A)dd reader, (D)elete user, Add (B)ook, (Q)uery Reader, （S)how all data, (E)xit:";	//(P)ut book to shelf, 
				cin >> choice;

				switch (choice)
				{
					long ID;
					char name[40];
					int num;
				case 'A': case 'a':
					cout << "Give a reader PIN and input a name:";
					cin >> ID;
					cin.ignore(256, ' ');
					cin.get(name, 20, '\n');
					readerBase.Insert(ReaderData(ID, name));
					// readerBase.SaveMap();
					break;

				case 'D': case 'd':
					long PIN;
					cout <<"Input a user id:";
					cin >> PIN;
					readerBase.Delete(PIN);
					break;

				case 'B': case 'b':
					cout << "Input a book ID and bookNum and name :";
					cin >> ID >> num;
					cin.ignore(256,'\n');
					cin.get(name, 40, '\n');
					bookBase.Insert(BookData(ID, name, num));
					// bookBase.SaveMap();
					break;

				case 'Q': case 'q':
					cout << "Input a reader's PIN:";
					cin >> ID;
					if (readerBase.Query(ID) == NULL)
					{
						cout << "No such a reader! " << endl;
					} else
					{
						readerBase.Query(ID)->ShowData();
					}
					break;

				// case 'P': case 'p':
				// 	cout << "Input a book ID:";
				// 	cin >> ID;
				// 	if (bookBase.Query(ID) == NULL)
				// 	{
				// 		cout << "No such a book!" << endl;
				// 	} else
				// 	{
				// 		bookBase.Query(ID)->SetState(SHELF);
				// 	}
				// 	break;

				case 'S': case 's':
					readerBase.ShowAllData();
					bookBase.ShowAllData();
					break;

				case 'E': case 'e':
					break;
					
				default:
					cout << "Unavailable Function!" << endl;
				}
			}

		    delete mgr;
		    choice = 'X';
		    break;

		case 'R': case 'r':
			long PIN, bookID;
			int i, t1, t2;
			char name[40];

			for (i = 0; i < 3; i ++)
			{
				cout << "Input PIN:";
				cin >> PIN;
				if (readerBase.Query(PIN) != NULL)
				{
					rdr = new Reader(PIN);
					break;
				}
			}

			if (i == 3)
			{
				cout << "Check In Failed!" << endl;
				choice = 'E';
			}

			while (!cmpIgnoreCase(choice, 'E'))
			{
				cout << "(A)dd book to Cart,  Check (O)out, (Q)uery Book By Name, (R)eturn book, (L)ist My Books, show (C)art, (E)xit:";
				cin >> choice;
				switch (choice)
				{
				case 'A': case 'a':
					cout << "Input a book ID:";
					cin >> bookID;
					if (bookBase.Query(bookID) != NULL && bookBase.Query(bookID)->GetState() == SHELF)
					{
						rdr->AddBook(bookID);
					}
					break;

				case 'O': case 'o':
					t1 = rdr->GetNum();
					t2 = readerBase.Query(PIN)->GetNum();
					//to do
					if (t1 > 0 && t2 <= LIMIT)
					{
						cout << PIN << " " << readerBase.Query(PIN)->GetName() << " Book List" << endl;
						for (i = 0; i < t1 && i < (LIMIT - t2); i ++)
						{
							//all function to object,so oop scheme?
							//to change...
							bookID = readerBase.Query(PIN)->BorrowBook(rdr->CheckOut());
							bookBase.Query(bookID)->addPIN(PIN);
							BookData* p = bookBase.Query(bookID);
							//如果全部被借光
							if(p->GetBorrowNum() == p->GetNum())
								bookBase.Query(bookID)->SetState(READER);
							cout << i + 1 << "\t" << bookBase.Query(bookID)->GetName() << endl;
						}
					}

					Date().Display();
    				break;

				case 'Q': case 'q':
					cout << "Input a book name (part):";
					cin.ignore(256,'\n');	//ignore?
					cin.get(name, 40, '\n');
					if (bookBase.QueryName(name) != NULL)
					{
						bookBase.QueryName(name)->ShowData();
					}
					break;

				case 'R': case 'r':
					cout << "Input book' s ID: ";
					cin.ignore();
					cin >> bookID;
					//to change...
					if(!readerBase.Query(PIN)->ReturnBook(bookID)){
						cout << "你尚未借此书，无法还书";
					}else{
						BookData* p = bookBase.Query(bookID);
						p->deletePIN(PIN);
						//可能全部被借光到还书一本
						bookBase.Query(bookID)->SetState(SHELF);
					};
					break;
				
				case 'L': case 'l':
					readerBase.Query(PIN)->ShowData();
					break;
						
				case 'C': case 'c':
					rdr->ShowCart();
					break;

				case 'E': case 'e':
					break;

				default:
					cout << "Unavailable Function!" << endl;
				}
			}

			delete mgr;
			choice = 'X';	//why should reset as 'x'?,and is not need in some where else;
			break;

		case 'E': case 'e':
			break;

		default:
			cout << "Unavailable Function!" << endl;
		}
	}
	//reinsert and savemap
	readerBase.SaveMap();
	bookBase.SaveMap();
	return 0;
}