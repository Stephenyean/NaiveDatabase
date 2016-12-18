#include "SM_Manager.h"
#include <direct.h>  
#include <fstream>
#include <windows.h>

SM_Manager::SM_Manager(IX_Manager * ixm, RM_Manager * rmm) :
ixm(ixm), rmm(rmm), work_database("")
{
}

SM_Manager::~SM_Manager()
{
}

RC_Return SM_Manager::OpenDb(const char * dbName)
{
	// set working database
	if (_access(dbName, 0) == 0) // argv[2] means test for existence
	{
		work_database = std::string(dbName);
		return OK;
	}
	else
	{
		cout << "Database " << dbName << " is not exists.\n";
		return OPEN_ERROR;
	}
	
}

RC_Return SM_Manager::CloseDb()
{
	//1.close all files -> flush the buffer
	if (work_database.length() <= 0)
	{
		cout << "No opening database. Please \"USE DATABASE <dbname>;\"\n";
		return NO_OPENING_DATABASE_ERROR;
	}
	for (auto rmHandle : rmHandles)
	{
		rmm->closeFile(rmHandle);
	}
	work_database.clear();
	rmHandles.clear();
	return OK;
}

RC_Return SM_Manager::CreateDb(const char * dbName)
{
	// mkdir database
	if (mkdir(dbName) == 0)
	{
		return OK;
	}
	else
	{
		cout << "Database " << dbName << " is exists.\n";
		return CREATE_ERROR;
	}
}

RC_Return SM_Manager::DropDb(const char * dbName)
{
	// rm -r database
	// set work database as null
	if (_access(dbName, 0) != 0)
	{
		cout << "Database " << dbName << " is not exists.\n";
		return OPEN_ERROR;
	}
	if (rmdir(dbName) == 0)
	{
		if (strcmp(dbName, work_database.c_str()) == 0)
		{
			work_database.clear();
		}
		return OK;
	}
	else
	{
		return CREATE_ERROR;
	}
	return RC_Return();
}

RC_Return SM_Manager::CreateTable(const char * relName, int attrCount, AttrInfo * attributes)
{
	// touch table attrInfo
	// create index for all
	if (work_database.length() <= 0)
	{
		cout << "No opening database. Please \"USE DATABASE <dbname>;\"\n";
		return NO_OPENING_DATABASE_ERROR;
	}
	if (IsTableExists(relName))
	{
		cout << "Table " << relName << " is exists.\n";
		return CREATE_ERROR;
	}
	for (size_t i = 0; i < attrCount; i++)
	{
		for (size_t j = i+1; j < attrCount; j++)
		{
			if (strcmp(attributes[i].attrName, attributes[j].attrName) == 0)
			{
				cout << "Too much column " << attributes[i].attrName << ".\n";
			}
		}
	}
	size_t record_size = 0;
	for (size_t i = 0; i < attrCount; i++)
	{
		record_size += attributes[i].attrLength;
	}
	rmm->createFile((work_database + "\\" + relName).c_str(), record_size);
	for (size_t i = 0; i < attrCount; i++)
	{
		ixm->CreateIndex((work_database + "\\" + relName).c_str(), i, attributes[i].attrType, attributes[i].attrLength);
	}
	SaveTableAttrInfo(NULL, relName, attrCount, attributes);
	return OK;
}

RC_Return SM_Manager::DropTable(const char * relName)
{
	// rm table attrinfo
	if (work_database.length() <= 0)
	{
		cout << "No opening database. Please \"USE DATABASE <dbname>;\"\n";
		return NO_OPENING_DATABASE_ERROR;
	}
	if (!IsTableExists(relName))
	{
		cout << "Table " << relName << " is not exists.\n";
		return DROP_ERROR;
	}
	int attrCount = 0;
	AttrInfo *attributes = NULL;
	GetTableAttrInfo(NULL, relName, attrCount, attributes);
	for (size_t i = 0; i < attrCount; i++)
	{
		ixm->DestroyIndex((work_database + "\\" + relName).c_str(), i);
	}
	rmm->destroyFile((work_database + "\\" + relName).c_str());
	remove((work_database + "\\" + relName + ".attr").c_str());
	delete[] attributes;
	return OK;
}

bool SM_Manager::IsTableExists(const char * relName)
{
	return !_access((work_database + "\\" + relName + ".attr").c_str(), 0);
}

RC_Return SM_Manager::GetTableAttrInfo(const char*dbName, const char * relName, int & attrCount, AttrInfo *& attributes)
{
	if (!dbName)
	{
		if (work_database.length() <= 0)
		{
			cout << "No opening database. Please \"USE DATABASE <dbname>;\"\n";
			return NO_OPENING_DATABASE_ERROR;
		}
		dbName = work_database.c_str();
	}
	ifstream fin;
	fin.open((std::string(dbName) + "\\" + relName + ".attr").c_str());
	if (fin) {
		fin >> attrCount;
		attributes = new AttrInfo[attrCount];
		for (size_t i = 0; i < attrCount; i++)
		{
			attributes[i].attrName = new char[MAXNAME];
			fin >> attributes[i].attrName;
			fin >> attributes[i].attrLength;
			int temp;  fin >> temp; attributes[i].attrType = AttrType(temp);
			fin >> attributes[i].notnull;
		}
		fin.close();
		return OK;
	}
	else {

		return OPEN_ERROR;
	}
}

RC_Return SM_Manager::SaveTableAttrInfo(const char * dbName, const char * relName, int attrCount, AttrInfo * attributes)
{
	if (!dbName)
	{
		dbName = work_database.c_str();
	}
	ofstream fout((std::string(dbName) + "\\" + relName + ".attr").c_str());
	fout << attrCount << endl;
	for (size_t i = 0; i < attrCount; i++)
	{
		fout << attributes[i].attrName << endl;
		fout << attributes[i].attrLength << endl;
		fout << attributes[i].attrType << endl;
		fout << attributes[i].notnull << endl;
	}
	fout.close();
	return RC_Return();
}

RC_Return SM_Manager::DropTableAttrInfo(const char * dbName, const char * relName)
{
	remove((string(dbName)+"\\"+relName).c_str());
	return OK;
}

std::vector<std::string> SM_Manager::GetTables(const char *dbName)
{
	std::vector<std::string> tableNames;
	HANDLE hFind;
	WIN32_FIND_DATA data;

	hFind = FindFirstFile((string(dbName)+"\\*.*").c_str(), &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			string fileName = string(data.cFileName);
			if (fileName.find(".attr") == string::npos)
				continue;
			tableNames.push_back(fileName.substr(0, fileName.size() - 5));
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
	return tableNames;
}
