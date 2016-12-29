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
	string str1 = string("_") + dbName;
	const char * _dbName = str1.c_str();
	if (_access(_dbName, 0) == 0) // argv[2] means test for existence
	{
		work_database = std::string(_dbName);
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
		cout << "No opening database. Please \"USE <dbname>;\"\n";
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
	string str1 = string("_") + dbName;
	const char * _dbName = str1.c_str();
	if (mkdir(_dbName) == 0)
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
	dbrelNameBuffer.clear();
	// rm -r database
	// set work database as null
	string str1 = string("_") + dbName;
	const char * _dbName = str1.c_str();
	if (_access(_dbName, 0) != 0)
	{
		cout << "Database " << dbName << " is not exists.\n";
		return OPEN_ERROR;
	}
	if (remove_dir(_dbName) == 0)
	{
		if (strcmp(_dbName, work_database.c_str()) == 0)
		{
			work_database.clear();
		}
		return OK;
	}
	else
	{
		cout << "Database " << dbName << " is using.\n";
		return DROP_ERROR;
	}
	
}

RC_Return SM_Manager::CreateTable(const char * relName, int attrCount, AttrInfo * attributes, int primaryKeyIx)
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
	rmm->createFile((work_database + "\\" + relName).c_str(), record_size, attrCount);
	for (size_t i = 0; i < attrCount; i++)
	{
		ixm->CreateIndex((work_database + "\\" + relName).c_str(), i, attributes[i].attrType, attributes[i].attrLength);
	}
	SaveTableAttrInfo(NULL, relName, attrCount, attributes, primaryKeyIx);
	return OK;
}

RC_Return SM_Manager::DropTable(const char * relName)
{
	dbrelNameBuffer.clear();
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
	int attrCount = 0, primaryKeyIx = 0;
	AttrInfo *attributes = NULL;
	GetTableAttrInfo(NULL, relName, attrCount, attributes, primaryKeyIx);
	for (size_t i = 0; i < attrCount; i++)
	{
		ixm->DestroyIndex((work_database + "\\" + relName).c_str(), i);
	}
	rmm->destroyFile((work_database + "\\" + relName).c_str());
	remove((work_database + "\\" + relName + ".attr").c_str());
	delete[] attributes;
	return OK;
}

bool SM_Manager::IsTableExists(string relName)
{
	return !_access((work_database + "\\" + relName + ".attr").c_str(), 0);
}

RC_Return SM_Manager::GetTableAttrInfo(const char * dbName, const char * relName, int & attrCount, AttrInfo *& attributes)
{
	int primaryKeyIx;
	return GetTableAttrInfo(dbName, relName, attrCount, attributes, primaryKeyIx);
}

RC_Return SM_Manager::GetTableAttrInfo(const char*dbName, const char * relName, int & attrCount, AttrInfo *& attributes, int & primaryKeyIx)
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
	// cacheHit
	if (std::string(dbName) + "\\" + relName == dbrelNameBuffer)
	{
		attrCount = attrCountBuffer;
		attributes = attributesBuffer;
		primaryKeyIx = primaryKeyIxBuffer;
	}
	ifstream fin;
	fin.open((std::string(dbName) + "\\" + relName + ".attr").c_str());
	if (fin) {
		fin >> attrCount;
		fin >> primaryKeyIx;
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
		// cacheStore
		dbrelNameBuffer = std::string(dbName) + "\\" + relName;
		attrCountBuffer = attrCount;
		attributesBuffer = attributes;
		primaryKeyIxBuffer = primaryKeyIx;
		return OK;
	}
	else {
		return OPEN_ERROR;
	}
}

RC_Return SM_Manager::SaveTableAttrInfo(const char * dbName, const char * relName, int attrCount, AttrInfo * attributes, int primaryKeyIx)
{
	if (!dbName)
	{
		dbName = work_database.c_str();
	}
	ofstream fout((std::string(dbName) + "\\" + relName + ".attr").c_str());
	fout << attrCount << endl;
	fout << primaryKeyIx << endl;
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
	string str1 = string("_") + dbName;
	const char * _dbName = str1.c_str();
	remove((string(_dbName)+"\\"+relName).c_str());
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

bool SM_Manager::remove_dir(const std::string &refcstrRootDirectory, bool bDeleteSubdirectories)
{
	bool            bSubdirectory = false;       // Flag, indicating whether
												 // subdirectories have been found
	HANDLE          hFile;                       // Handle to directory
	std::string     strFilePath;                 // Filepath
	std::string     strPattern;                  // Pattern
	WIN32_FIND_DATA FileInformation;             // File information


	strPattern = refcstrRootDirectory + "\\*.*";
	hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FileInformation.cFileName[0] != '.')
			{
				strFilePath.erase();
				strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

				if (FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (bDeleteSubdirectories)
					{
						// Delete subdirectory
						int iRC = remove_dir(strFilePath, bDeleteSubdirectories);
						if (iRC)
							return iRC;
					}
					else
						bSubdirectory = true;
				}
				else
				{
					// Set file attributes
					if (::SetFileAttributes(strFilePath.c_str(),
						FILE_ATTRIBUTE_NORMAL) == FALSE)
						return ::GetLastError();

					// Delete file
					if (::DeleteFile(strFilePath.c_str()) == FALSE)
						return ::GetLastError();
				}
			}
		} while (::FindNextFile(hFile, &FileInformation) == TRUE);

		// Close handle
		::FindClose(hFile);

		DWORD dwError = ::GetLastError();
		if (dwError != ERROR_NO_MORE_FILES)
			return dwError;
		else
		{
			if (!bSubdirectory)
			{
				// Set directory attributes
				if (::SetFileAttributes(refcstrRootDirectory.c_str(),
					FILE_ATTRIBUTE_NORMAL) == FALSE)
					return ::GetLastError();

				// Delete directory
				if (::RemoveDirectory(refcstrRootDirectory.c_str()) == FALSE)
					return ::GetLastError();
			}
		}
	}

	return 0;
}


