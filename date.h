#include <ctime>

using namespace std;

class Date : public Object
{
	int year, month, day;

	int DayOfMonth (int y, int m) const
	{
		int d = 0;
		switch (m)
		{
		case 1: 
		case 3:
		case 5:
		case 7: 
		case 8:
		case 10:
		case 12: d = 31;  break;
		case 4: 
		case 6:
		case 9:
		case 11: d = 30;  break;
		case 2: d = 28 + IsLeapYear(y);  break;
		}

		return d;
	}

public:
	Date()
	{
		time_t curTime = time(NULL);
		tm time = *localtime(&curTime);
		day = time.tm_mday;
		month = time.tm_mon + 1;
		year = time.tm_year + 1900;
	}

	Date(int y, int m, int d) : year(y), month(m), day(d)
	{
		if ((y <= 0 ) || (m <= 0) || m > 12 || d <= 0 || d > DayOfMonth(y, m))
		{
			year = 1900;
			month = day = 1;
		}
	}

	virtual ~Date()
	{
	}

	int GetYear() const
	{
		return year;
	}

	int GetMonth() const
	{
		return month;
	}

	int GetDay() const
	{
		return day;
	}

	bool IsLeapYear() const
	{
		return IsLeapYear(year);
	}

	bool IsLeapYear(const int y) const
	{
		return year % 400 ? (year % 100 ? (year % 4 ? false : true) : false): true;
	}

	void Display() const
	{
		cout << year << "-" << month << "-" << day << endl;
	}
};