
template <class T>
class Database : public Object
{
private:
	fstream file;
	char filename[40];
	long fileLen, recSize;
	typedef map< long, T, less<long> > mtype;
	mtype recMap;

public:
	Database( char * filename)
	{
		strcpy(this->filename, filename);
		file.open(filename, ios::in | ios::binary);
		recSize = sizeof(T);
		if (file.is_open())
		{
			file.seekg(0, ios::end);
			if ((fileLen = file.tellg()) > 0)
			{
				T obj;
				file.seekg(0, ios::beg);
				do
				{
					file.read((char *)&obj, recSize);
					recMap.insert( pair<long, T>(obj.GetID(), obj) );
				} while (file.tellg() < fileLen);
				//所谓文件的作用就是按照字节读出然后插入到map中哦哦。
			}

			file.close();
		}
	}

	void SaveMap()
	{
		
		file.open(filename, ios::out | ios::binary | ios:: trunc);
		for (auto iter = recMap.begin(); iter != recMap.end(); ++iter)
		{
			file.write((char *)&iter->second, recSize);
		}

		file.close();
	}

	void Insert(T  obj)
	{
		//how does map key-value build? value_type??
		recMap.insert( pair<long, T>(obj.GetID(), obj) );
		// recMap[obj.GetID()] = obj;
	}

	T * Query(long objID)
	{
		auto iter= recMap.find(objID);
		if (iter == recMap.end())
		{
			cout << objID << " not found!" << endl;
			return NULL;
		} else
		{
			return &(iter->second);
		}
	}

	T * QueryName(const char * objName)
	{
		for (auto iter = recMap.begin(); iter != recMap.end(); iter ++)
		{
			if (strstr((iter->second).GetName(), objName) != NULL)
			{
				return &(iter->second);
			}
		}

		cout << objName << " in " << typeid(T).name() << " not found " << endl;
		return NULL;
	}

	void Delete(long objID)
	{
		Query(objID);
		recMap.erase(objID);
	}

	void ShowAllData()
	{
		T obj;

		cout << "Data in " << typeid(T).name() << ":" << endl;
		for (auto iter = recMap.begin(); iter != recMap.end(); iter ++)
		{
			(iter->second).ShowData();
		}
	}
};