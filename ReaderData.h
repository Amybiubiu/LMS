

class ReaderData : public Object
{
protected:
	long PIN;
	char name[20];
	long bookList[LIMIT];
	Date borrowDate[LIMIT];
	int num;

public:
	ReaderData(int PIN,  char * name)
	{
		SetID(PIN);
		SetName(name);
		num = 0;
		for (int i = 0; i < LIMIT; i ++)
			bookList[i] = 0;
	}

	ReaderData()
	{
		PIN = 0; num = 0;
		for (int i = 0; i < LIMIT; i ++)
			bookList[i] = 0;
	}

	void SetID(long PIN)
	{
		this->PIN = PIN;
	}

	void SetName(const char * name)
	{
		strcpy(this->name, name);
	}

	long GetID() const
	{
		return PIN;
	}

	const char * GetName() const	//类里面的概念 const出现在函数名后面
	{
		return name;
	}

	int GetNum() const
	{
		return num;
	}

	long ReturnBook(long bookID)
	{
		for (int i = 0; i < LIMIT; i ++)
		{
			if (bookList[i] == bookID)
			{
				bookList[i] = 0; 
				-- num;
				return bookID;
			}
		}

		return 0;
	}

	long BorrowBook(long bookID)
	{
		for (int i = 0; i < LIMIT; i ++)
		{
			if (bookList[i] == 0)
			{
				bookList[i] = bookID;
				borrowDate[i] = Date();
				num ++;
				return bookID;
			}
		}

		cout << "Book reach the limit!" << endl;
		return 0;
	}

	void ShowData()
	{
		cout << PIN << '\t' << name << endl;
		for (int i = 0; i < LIMIT; i ++)
		{
			if (bookList[i])
			{
				cout << i + 1 << ":" << bookList[i] << '\t';
				borrowDate[i].Display();
			}
		}
	}
};