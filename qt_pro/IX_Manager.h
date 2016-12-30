#ifndef IX_MANAGER_H
#define IX_MANAGER_H
#include "bufmanager/BufPageManager.h"
#include "fileio/FileManager.h"
#include "utils/pagedef.h"
#include "pf_defines.h"
#include "RM_Manager.h"
#include <iostream>
#include <limits.h>
using namespace std;

struct IX_File_Head {
public:
	int numPages;      // # of pages in the file
	int pageSize;      // size per index node - usually PF_PAGE_SIZE
	PageNum rootPage;  // addr of root page
	int pairSize;      // size of each (key, RID) pair in index
	int order;         // order of btree
	int height;        // height of btree
	AttrType attrType;
	int attrLength;
	int degree;
};

struct IX_Page_head {
	int numEntries;
	int parentPage;
	bool isLeafPage;
	int nextpage;
};

struct IX_Node {
	int nextPage;
	RID rid;
};
class IX_IndexHandle;
class IX_Manager{
public:
	IX_Manager  (FileManager* fm, BufPageManager* bpm);
	~IX_Manager ();

	RC CreateIndex  (const char* fileName, int indexNo, AttrType attrType, int attrLength);
	RC DestroyIndex (const char* fileName, int indexNo);
	RC OpenIndex    (const char* fileName, int indexNo, IX_IndexHandle &indexHandle);
	RC CloseIndex   (IX_IndexHandle &indexHandle);
	int computeDegree(int attrLength);
	FileManager* fm;
	BufPageManager* bpm;
	int verbose = 1;
};


class IX_IndexHandle {
public:
	IX_IndexHandle  ();                             // Constructor
	~IX_IndexHandle ();                             // Destructor
	RC InsertEntry  (void *pData, const RID &rid);  // Insert new index entry
	RC DeleteEntry  (void *pData, const RID &rid);  // Delete index entry
	RC forcePages(PageNum pageNum);				// Write dirty page(s)
	RC RecursiveSplitNode (int pageNum, int newPageNum, void* pData, int& parent);
	RC RecursiveInsertEntry (int pageNum, void *pData, const RID &rid);
	RC getPosition(void* pData, int& position, BufType b);
	RC getMiddleData(void* pData, BufType b, int position, void* p);
	RC initIxPage(char* b);
	RC reloadFile();
	FileManager* fm;
	BufPageManager* bpm;
	IX_File_Head* ixHead;
	int ixIndex;
	int fileID;
	int verbose = 1;
};


class IX_IndexScan {
public:
	IX_IndexScan  ();                                 // Constructor
	~IX_IndexScan ();                                 // Destructor
	RC OpenScan      (const IX_IndexHandle &indexHandle, // Initialize index scan
					  CompOp      compOp,
					  void        *value);           
	RC GetNextEntry  (RID &rid, bool DeleteMode = false);                         // Get next matching entry
	RC DeleteCurrentEntry();
	RC CloseScan     ();                                 // Terminate index scan
	RC SearchEntry	(int&, int&);
	template<typename T>
	bool satisfiesCondition(T key, T value);
	IX_IndexHandle indexHandle;
	CompOp compOp;
	void* value;
	AttrType attrtype;
	int attrLength;
	int currentPage;
	int currentPosition;
	BufType b;
	IX_Page_head* pageHead;
	int scanIndex;
};


#endif
