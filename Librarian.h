/**
 * ͼ�����Ա
 */
#include "md5.h"
#include "md5.cpp"
#include <string>

class Librarian: public Object
{
private:
	long ID;
	char name[20];
	char passwd[9];

public:
	Librarian(long ID, const char * name) : ID(ID)
	{
		strcpy(this->name, name);
		strcpy(passwd, "900150983cd24fb0d6963f7d28e17f72");
	}

	char login()
	{
		char pw[9];
		for (int i = 0; i < 3; i ++)
		{
			cout << "Enter Password:";
			cin >> pw;
			MD5 md5(pw);
			string str = md5.md5();
			char *p=(char*)str.c_str();
			if (strcmp(p, passwd) == 0)
				return 'X';
		}
		cout << "Login Failed!" << endl;
		return 'E';
	}
};