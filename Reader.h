/**
 * 读者  选书与借书
 */

class Reader : public Object
{
private:
	long PIN;
	long bookID[LIMIT];
	int num;

public:
	Reader(long PIN = 0, const int num = 0): PIN(PIN), num(num)
	{
	}

	int AddBook(const long bookID)
	{
		if (num < LIMIT)
		{
			this->bookID[num] = bookID;
			cout << "Book " << bookID << " added!" << endl;
			num ++;
			return 1;
		} else
		{
			cout << "Cart is Full" << endl;
			return 0;
		}
	}

	long CheckOut()
	{
		return bookID[--num];
	}

	void ShowCart()
	{
		for (int i = 0; i < num; ++i)
		{
			cout << bookID[i] << endl;
		}
	}

	int GetNum() const
	{
		return num;
	}
};