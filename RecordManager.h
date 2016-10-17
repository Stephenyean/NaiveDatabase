#pragma once
#include "bufmanager/BufPageManager.h"
#include "fileio/FileManager.h"
#include "utils/pagedef.h"
#include <iostream>

using namespace std;
enum RC {
	OK,
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

class RID{
private:
	int myPageNum;
	int mySlotNum;

public:
	RID();		//default constructor
	~RID();      //destructor
	RID(int pageNum, int slotNum);		//construct a new record from a given page number and slot number.
	RC GetPageNum(int &pageNum)const;  // Return page number
	RC GetSlotNum(int &slotNum)const;  // Return slot number
	void SetPageNum(int pageNum);		//reset pagenum when it is necessary
	void SetSlotNum(int slotNum);		//reset slotnum when it is necessary
	bool checkValid()const;				//checkout if a record has not already been read into the 
										//RM_Record object for which the method is called.
};

class RM_Record{
private:
	char *myPData;
	RID myRid;
public:
	RM_Record();		//constructor
	RM_Record(const char *pData, int record_size, const RID &rid);
	~RM_Record();		//destructor
	RC GetData(char *&pData)const;   //set pData to point to the record's contents
	RC GetRid(RID &rid)const;		//get the record id
	bool checkValid()const;			//just call the RID's checkValid()
};

class RM_FileHandle;
class RM_Manager {
public:
	RM_Manager(FileManager* fm, BufPageManager* bpm);
	~RM_Manager();
	RC CreateFile(const char* filename, int recordSize);

	RC DestroyFile(const char* filename);
	RC OpenFile(const char* filename, RM_FileHandle & fileHandle);
	RC CloseFile(RM_FileHandle &fileHandle);
	FileManager* fm;
	BufPageManager* bpm;
};

class RM_FileHandle{
public:
	RM_FileHandle();
	~RM_FileHandle();

    RC GetRec         (const RID &rid, RM_Record &rec) const;
                                                           // Get a record
    RC InsertRec      (const char *pData, RID &rid);       // Insert a new record,
                                                           //   return record id
    RC DeleteRec      (const RID &rid);                    // Delete a record
    RC UpdateRec      (const RM_Record &rec);              // Update a record
    RC ForcePages     (PageNum pageNum) const; // Write dirty page(s)
    int fileID;
    int slotSize;
    FileManager* fm;
	BufPageManager* bpm;
};


