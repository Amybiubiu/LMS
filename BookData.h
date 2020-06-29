const int LIST_MAX_NUM = 5;


class BookData : public Object
{
private:
	long bookID;
	char name[40];
	State state;
	// vector<long> PINList{vector<long>(1,0)};
	long PINList[LIST_MAX_NUM];
	int num;	//入库数量

public:
	BookData(long bookID, char * name, int num = 1,State state = SHELF)
	{
		SetID(bookID);
		SetName(name);
		SetState(state);
		this->num = num;
		for(int i = 0; i < LIST_MAX_NUM; ++i){
			PINList[i] = 0;
		}
	}

	BookData()
	{
		bookID = 0;
	}

	long GetID() const
	{
		return bookID;
	}

	const char * GetName() const
	{
		return name;
	}

	State GetState() const
	{
		return state;
	}

	long GetNum() const
	{
		return num;
	}

	int GetBorrowNum()
	{
		int n = 0;
		for(int i = 0; i < LIST_MAX_NUM; ++i){
			if(PINList[i] != 0)
				n++;
		}
		return n;
	}

	void SetID(long bookID)
	{
		this->bookID = bookID;
	}

	void SetName(const char * name)
	{
		strcpy(this->name, name);
	}

	void SetState(State state)
	{
		this->state = state;
	}

	long* GetPINList(){
		return PINList;
	}

	void addPIN(long PIN)
	{
		for(int i = 0; i < LIST_MAX_NUM; ++i){
			if(PINList[i] == 0){
				PINList[i] = PIN;
				return;
			}
		}
	}

	void deletePIN(long PIN)
	{
		for(int i = 0; i < LIST_MAX_NUM; ++i){
			if(PINList[i] = PIN){
				PINList[i] = 0;
				return;
			}
		}
	}

	void ShowData()
	{
		cout << "bookID" << "\t" << "name" << "\t" << "state" << "\t" <<"total num"<< endl;
		cout << bookID << "\t" << name << "\t" << state << "\t" << num << endl;
		cout << "PINList"<<endl;
		//这里显示都是0000
		for (auto &i : PINList) {
        	cout << i << " ";
    	}
		cout<<endl;
	}

};