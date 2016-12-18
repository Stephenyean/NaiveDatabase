#pragma once
#include "pf_defines.h"
#include "IX_Manager.h"
#include "RecordManager.h"
// Used by SM_Manager::CreateTable
class AttrInfo {
public:
	~AttrInfo()
	{
		if (attrName)
		{
			delete[] attrName;
		}
	}
	char     *attrName;           // Attribute name
	AttrType attrType;            // Type of attribute
	int      attrLength;          // Length of attribute
	bool notnull;
};

// Used by Printer class
struct DataAttrInfo {
	char     relName[MAXNAME + 1];  // Relation name
	char     attrName[MAXNAME + 1]; // Attribute name
	int      offset;              // Offset of attribute 
	AttrType attrType;            // Type of attribute 
	int      attrLength;          // Length of attribute
	int      indexNo;             // Attribute index number
};


class SM_Manager {
public:
	SM_Manager(IX_Manager *ixm, RM_Manager *rmm);  // Constructor
	~SM_Manager();                                  // Destructor
	RC_Return OpenDb(const char *dbName);                // Open database
	RC_Return CloseDb();                                  // Close database
	RC_Return CreateDb(const char* dbName);
	RC_Return DropDb(const char* dbName);
	RC_Return CreateTable(const char *relName,                // Create relation
		int        attrCount,
		AttrInfo   *attributes);
	RC_Return DropTable(const char *relName);               // Destroy relation
	bool IsTableExists(const char *relName);
	RC_Return GetTableAttrInfo(const char*dbName, const char *relName, int &attrCount, AttrInfo *&attributes);
	RC_Return SaveTableAttrInfo(const char*dbName, const char *relName, int attrCount, AttrInfo *attributes);
	RC_Return DropTableAttrInfo(const char*dbName, const char *relName);
	std::vector<std::string> GetTables(const char *dbName);
private:
	IX_Manager *ixm;
	RM_Manager *rmm;
	std::vector<RM_FileHandle> rmHandles;
	std::string work_database;
};