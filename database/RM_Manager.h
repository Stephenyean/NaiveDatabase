#pragma once
#include "bufmanager/BufPageManager.h"
#include "fileio/FileManager.h"
#include "utils/pagedef.h"
#include "pf_defines.h"
#include <iostream>
#include <limits.h>
using namespace std;
class IdMap {
public:
	static std::map<std::string, int> fileIDMap;
};


typedef int RC;
/*
enum RC_Return {
OK,
ERROR,
INVALID_RID,
INVALID_RECORD,
PF_EOF,         // end of file
PF_PAGEPINNED,       // page pinned in buffer
PF_PAGENOTINBUF,     // page to be unpinned is not in buffer
PF_PAGEUNPINNED,     // page already unpinned
PF_PAGEFREE,         // page already free
PF_INVALIDPAGE,      // invalid page number
PF_FILEOPEN,         // file handle already open
PF_FILECREATED,
PF_CLOSEDFILE,       // file is closed
PF_NOMEM,            // out of memory
PF_NOBUF,            // out of buffer space
PF_INCOMPLETEREAD,   // incomplete read of page from file
PF_INCOMPLETEWRITE,  // incomplete write of page to file
PF_HDRREAD,          // incomplete read of header from file
PF_HDRWRITE,         // incomplete write of header to file
// Internal PF errors:
PF_PAGEINBUF,        // new allocated page already in buffer
PF_HASHNOTFOUND,     // hash table entry not found
PF_HASHPAGEEXIST,    // page already exists in hash table
PF_INVALIDNAME,      // invalid file name
PF_UNIX             // Unix error
};
*/
struct File_Head {
public:
	int numPages;
	int recordSize;
	int nextFreePage;
	int bitMapSize;
	int maxRecordNumPerPage;
	int attrCount;
};

struct Page_Head {
public:
	int numRecords;
	int nextFreePage;
};

class RID {
private:
	int pageNum;
	int slotNum;

public:
	RID();		//default constructor
	~RID();      //destructor
	RID(int pageNum, int slotNum);		//construct a new record from a given page number and slot number.
	RC getPageNum(int &pageNum)const;  // Return page number
	RC getSlotNum(int &slotNum)const;  // Return slot number
	int getPageNum() { return pageNum; }
	int getSlotNum() { return slotNum; }
	void setPageNum(int pageNum);		//reset pagenum when it is necessary
	void setSlotNum(int slotNum);		//reset slotnum when it is necessary
	bool compare(const RID& rid);				// compare two rids if equal
	bool checkValid()const;				//checkout if a record has not already been read into the 
										//RM_Record object for which the method is called.
};

class RM_Record {
public:
	char *pData;
	RID	rid;
public:
	RM_Record();		//constructor
	RM_Record(const RM_Record & record);
	RM_Record(const char *pData, int record_size, const RID &rid);
	~RM_Record();		//destructor
	RC getData(char *&pData)const;   //set pData to point to the record's contents
	RC getRid(RID &rid)const;		//get the record id
	RC setData(char *pData);
	RC setRid(const RID &rid);
	int recordSize;
	bool checkValid()const;			//just call the RID's checkValid()
};

class RM_FileHandle;
class RM_Manager {
public:
	RM_Manager(FileManager* fm, BufPageManager* bpm);
	~RM_Manager();
	RC createFile(const char* filename, int recordSize, int attrCount);

	RC destroyFile(const char* filename);
	RC openFile(const char* filename, RM_FileHandle & fileHandle);
	RC closeFile(RM_FileHandle &fileHandle);

	FileManager* fm;
	BufPageManager* bpm;
	int verbose = 1;
};

class RM_FileHandle {
public:
	RM_FileHandle();
	~RM_FileHandle();

	RC getRec(const RID &rid, RM_Record &rec);
	// Get a record
	RC insertRec(const char *pData, RID &rid, bool* boolValue);		// Insert a new record,
													//   return record id
	RC deleteRec(const RID &rid);						// Delete a record
	RC updateRec(const RM_Record &rec, bool* boolValue);				// Update a record
	RC forcePages(PageNum pageNum);				// Write dirty page(s)
	int getBit(int index, char* b);
	RC setBit(int index, char* b, int);
	RC initPage(BufType b);
	int getNextFreeSlot(char* b, int recordNum);
	int getOffset(int slotNum) { return sizeof(Page_Head) + fileHead->bitMapSize + (fileHead->attrCount + fileHead->recordSize) * slotNum; }
	RC reloadFile();
	int fileID;
	File_Head * fileHead;
	FileManager* fm;
	BufPageManager* bpm;
	
	bool isOpen;
	int headIndex;
	int verbose = 1;
};

/*
struct IX_Head {
public:
	int numPages;      // # of pages in the file
	int pageSize;      // size per index node - usually PF_PAGE_SIZE
	PageNum rootPage;  // addr of root page
	int pairSize;      // size of each (key, RID) pair in index
	int order;         // order of btree
	int height;        // height of btree
	AttrType attrType;
	int attrLength;
};

*/


class RM_FileScan {
public:
	RM_FileScan();
	~RM_FileScan();
	RC OpenScan(const RM_FileHandle& fileHandle,
		AttrType attrtype,
		int attrLength,
		int attrOffset,
		CompOp compOp,
		void *value);
	RM_FileHandle fileHandle;
	AttrType attrtype;
	int attrLength;
	int attrOffset;
	CompOp compOp;
	void* value;
	int currentPage = 1;
	int currentSlot = 0;
	BufType b;
	char* bitMap;
	RC GetNextRec(RM_Record &rec);
	RC CloseScan();
	template<typename T>
	bool matchRecord(T recordValue, T givenValue);
};