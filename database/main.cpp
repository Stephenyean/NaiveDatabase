#include "RM_Manager.h"
#include "QL_Manager.h"
#include "IX_Manager.h"
#include "parser\src\SQLParser.h"
#include "parser\src\sqlhelper.h"
#include "Parser.h"
#include <tchar.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
void testIX();
void testIX2();
void testScan();
void generateData(AttrType attrtype, char* file);
int testParser(std::string query);
int main()
{

	Parser parser;
	parser.parse();
	
	//FILE* fin = fopen("./_orderDB/orders", "rb");
	//int len = ftell(fin);
	//char b[16390];
	//fread(b, 16390, 1, fin);
	//cout << b[16382] << endl;
	//cout << b[16383] << endl;
	//cout << b[16384] << endl;
	//cout << b[16385] << endl;

	return 0;
}

//int testParser(std::string query) {
//	// parse a given query
//	hsql::SQLParserResult* result = hsql::SQLParser::parseSQLString(query);
//
//	// check whether the parsing was successful
//	if (result->isValid) {
//		printf("Parsed successfully!\n");
//		printf("Number of statements: %lu\n", result->size());
//
//		for (hsql::SQLStatement* stmt : result->statements) {
//			// process the statements...
//			hsql::printStatementInfo(stmt);
//		}
//
//		return 0;
//	}
//	else {
//		printf("Invalid SQL!\n");
//		return -1;
//	}
//}

void testIX()
{
	MyBitMap::initConst();
	FileManager* fm = new FileManager();
	BufPageManager* bpm = new BufPageManager(fm);
	RM_Manager* rm = new RM_Manager(fm, bpm);
	IX_Manager* im = new IX_Manager(fm, bpm);
	rm->createFile("a.txt", 4, 1);

	im->CreateIndex("a", 0, (AttrType)DINT, 400);
	RM_FileHandle rmHandle;
	rm->openFile("a.txt", rmHandle);
	IX_IndexHandle ixHandle;
	im->OpenIndex("a", 0, ixHandle);
	RID rid1;
	ifstream fin("data.txt");
	
	for (int i = 0; i < 200; i++)
	{
		//cout << i << " : \n";
		int data;
		fin >> data;
		bool* nullValue=new bool[1];
		nullValue[0] = false;
		rmHandle.insertRec((char*)(&data), rid1, nullValue);
		ixHandle.InsertEntry((void*)(&data), rid1);
		delete[]nullValue;
		nullValue = nullptr;
	}
	RC rc;
	IX_IndexScan scan;
	int deleted = 491;
	if (!(rc = scan.OpenScan(ixHandle, NO_OP, (void*)&deleted)))
	{
		RID rid;
		RM_Record record;
		while (scan.GetNextEntry(rid, true) == 0)
		{
			rmHandle.deleteRec(rid);
		}
	}
	scan.CloseScan();
	int value = 5705;
	if (scan.OpenScan(ixHandle, NO_OP, (void*)&value) == 0)
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


void testIX2()
{
	MyBitMap::initConst();
	FileManager* fm = new FileManager();
	BufPageManager* bpm = new BufPageManager(fm);
	RM_Manager* rm = new RM_Manager(fm, bpm);
	IX_Manager* im = new IX_Manager(fm, bpm);
	rm->createFile("a.txt", 12, 1);

	im->CreateIndex("a", 0, (AttrType)STRING, 400);
	RM_FileHandle rmHandle;
	rm->openFile("a.txt", rmHandle);
	IX_IndexHandle ixHandle;
	im->OpenIndex("a", 0, ixHandle);
	RID rid1;
	ifstream fin("string.txt");
	RC rc;
	IX_IndexScan scan;
	char value[10] = "llllll";

	for (int i = 0; i < 500; i++)
	{
		string data;
		fin >> data;
		bool* nullValue = new bool[1];
		nullValue[0] = false;
		rmHandle.insertRec(data.c_str(), rid1, nullValue);
		ixHandle.InsertEntry((void*)(data.c_str()), rid1);
		delete[]nullValue;
		nullValue = nullptr;
	}

	if (scan.OpenScan(ixHandle, LE_OP, (void*)value) == 0)
	{
		RID rid;
		RM_Record record;
		while (scan.GetNextEntry(rid) == 0)
		{
			rmHandle.getRec(rid, record);
			cout << (char*)(record.pData) << endl;
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
	rm->createFile("a.txt", 10, 1);
	RM_FileHandle rmHandle;
	rm->openFile("a.txt", rmHandle);
	RID rid1;
	ifstream fin("string.txt");
	for (int i = 0; i < 500; i++)
	{
		char data[10];
		fin >> data;
		rmHandle.insertRec(data, rid1, new bool[10]{ false });
	}
	RC rc;
	RM_FileScan scan;
	char value[10]="lmn";
	if (scan.OpenScan(rmHandle, STRING, 10, 0, GT_OP, (void*)value) == 0)
	{
		RM_Record record;
		while (scan.GetNextRec(record) == 0)
		{
			cout << record.pData + rmHandle.fileHead->attrCount << endl;
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