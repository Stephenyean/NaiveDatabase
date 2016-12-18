#include "RecordManager.h"
#include "IX_Manager.h"
#include "sql-parser\src\SQLParser.h"
#include "sql-parser\src\sqlhelper.h"
#include "Parser.h"
#include <tchar.h>
#include <fstream>
#include <string>
using namespace std;
void testIX();
void testScan();
void generateData(AttrType attrtype, char* file);
int main()
{
	// std::string query = "CREATE DATABASE ddd;";
	// return testParser(query);
	//generateData(STRING, "string.txt");
	// testIX();
	Parser parser;
	parser.parse();
	return 0;
}

int testParser(std::string query) {
	// parse a given query
	hsql::SQLParserResult* result = hsql::SQLParser::parseSQLString(query);

	// check whether the parsing was successful
	if (result->isValid) {
		printf("Parsed successfully!\n");
		printf("Number of statements: %lu\n", result->size());

		for (hsql::SQLStatement* stmt : result->statements) {
			// process the statements...
			hsql::printStatementInfo(stmt);
		}

		return 0;
	}
	else {
		printf("Invalid SQL!\n");
		return -1;
	}
}

void testIX()
{
	MyBitMap::initConst();
	FileManager* fm = new FileManager();
	BufPageManager* bpm = new BufPageManager(fm);
	RM_Manager* rm = new RM_Manager(fm, bpm);
	IX_Manager* im = new IX_Manager(fm, bpm);
	rm->createFile("a.txt", 4);

	im->CreateIndex("a", 0, (AttrType)DINT, 400);
	RM_FileHandle rmHandle;
	rm->openFile("a.txt", rmHandle);
	IX_IndexHandle ixHandle;
	im->OpenIndex("a", 0, ixHandle);
	RID rid1;
	ifstream fin("data.txt");
	
	for (int i = 0; i < 2000; i++)
	{
		int data;
		fin >> data;
		rmHandle.insertRec((char*)(&data), rid1);
		ixHandle.InsertEntry((void*)(&data), rid1);
	}
	RC rc;
	IX_IndexScan scan;
	int value = 5705;
	if (scan.OpenScan(ixHandle, LE_OP, (void*)&value) == 0)
	{
		RID rid;
		RM_Record record;
		while (scan.GetNextEntry(rid) == 0)
		{
			rmHandle.getRec(rid, record);
			cout << *(int*)(record.pData) << endl;
		}
		cout << "finish\n";
	}
	else
	{
		cout << "couldn't open scan\n";
	}
	scan.CloseScan();
	rm->closeFile(rmHandle);
	im->CloseIndex(ixHandle);

}

void testScan()
{
	MyBitMap::initConst();
	FileManager* fm = new FileManager();
	BufPageManager* bpm = new BufPageManager(fm);
	RM_Manager* rm = new RM_Manager(fm, bpm);
	rm->createFile("a.txt", 10);
	RM_FileHandle rmHandle;
	rm->openFile("a.txt", rmHandle);
	RID rid1;
	ifstream fin("string.txt");
	for (int i = 0; i < 20; i++)
	{
		char data[10];
		fin >> data;
		rmHandle.insertRec(data, rid1);
	}
	RC rc;
	RM_FileScan scan;
	char value[10]="lmn";
	if (scan.OpenScan(rmHandle, STRING, 10, 0, GT_OP, (void*)value) == 0)
	{
		RM_Record record;
		while (scan.GetNextRec(record) == 0)
		{
			cout << record.pData << endl;
		}
		cout << "finish\n";
	}
	else
	{
		cout << "couldn't open scan\n";
	}
	scan.CloseScan();
	rm->closeFile(rmHandle);
}
void generateData(AttrType attrtype, char* file)
{
	ofstream fout(file);
	if (attrtype == DINT)
	{
		for (int i = 0; i < 10000; i++)
		{
			fout << rand() << endl;
		}
	}
	else if (attrtype == DFLOAT)
	{
		for (int i = 0; i < 10000; i++)
		{
			fout << float(rand()) / RAND_MAX << endl;
		}
	}
	else if (attrtype == STRING)
	{
		for (int i = 0; i < 10000; i++)
		{
			char str[10];
			for (int j = 0; j < 9; j++)
				str[j] = 'a' + rand() % 26;
			str[9] = '\0';
			fout << str << endl;
		}
	}
	fout.close();
}