#include "IX_Manager.h"
using namespace std;


IX_Manager::IX_Manager(FileManager* fm, BufPageManager* bpm)
{
	this->fm=fm;
	this->bpm=bpm;
}

IX_Manager::~IX_Manager()
{

}

RC IX_Manager::CreateIndex(const char* fileName, int indexNo, AttrType attrType, int attrLength)
{
	char* indexFileName = new char[strlen(fileName) + 10];
	sprintf_s(indexFileName, strlen(fileName) + 10, "%s.%d", fileName, indexNo);
	int fileID;
	fm->createFile(indexFileName);
	fm->openFile(indexFileName, fileID);
	int index;
	BufType b = bpm->allocPage(fileID, 0, index, false);
	IX_File_Head* fileHead = (IX_File_Head*)b;
	fileHead->attrLength = attrLength;
	fileHead->attrType = attrType;
	fileHead->height = 1;
	fileHead->numPages = 1;
	fileHead->order = 1;
	fileHead->rootPage = -1;
	fileHead->pairSize = attrLength + 8;
	fileHead->pageSize = PAGE_SIZE;
	fileHead->degree = computeDegree(attrLength);
	bpm->markDirty(index);
	bpm->writeBack(index);
	fm->closeFile(fileID);
	return OK;
}

inline int IX_Manager::computeDegree(int attrLength)
{
	return (PAGE_SIZE - sizeof(IX_Page_head) - sizeof(IX_Node)) / (attrLength + sizeof(IX_Node));
}

// function: open index
RC IX_Manager::OpenIndex(const char* fileName, int indexNo, IX_IndexHandle &indexHandle)
{
	char* indexFileName = new char[strlen(fileName) + 10];
	sprintf_s(indexFileName, strlen(fileName) + 10, "%s.%d", fileName, indexNo);
	int fileID;
	fm->openFile(indexFileName, fileID);
	int index;
	BufType b = bpm->getPage(fileID, 0, index);
	IX_File_Head * ixHead = (IX_File_Head*)b;
	indexHandle.bpm = this->bpm;
	indexHandle.fm = this->fm;
	indexHandle.fileID = fileID;
	return OK;
}

RC IX_Manager::DestroyIndex(const char* fileName, int indexNo)
{
	// waite to be modified;
	return OK;
}

RC IX_Manager::CloseIndex(IX_IndexHandle &indexHandle)
{
	//waited to be modified
	indexHandle.forcePages(-1);
	if (verbose == 2)
		cout << "[info] close index" << endl;
	return OK;
}

IX_IndexHandle::IX_IndexHandle() {

}

IX_IndexHandle::~IX_IndexHandle() {

}
// @function insert entry
// 0. reloadHead, do some judgement
// 1. judge if rootPage exists
//		no. create a rootPage, add pageHead, modify fileHead
// 2. judge if it's leafPage
//		no. recursive
// 3. if rootLeaf is full
//		yes. allocate a new Page, move half of the nodes to the new page, modify the parent
// 4. if parent is full
//		recursive
RC IX_IndexHandle::InsertEntry(void *pData, const RID &rid)  // Insert new index entry
{
	// do some judgement
	// waited to be modified
	
	reloadFile();
	int index;
	if (ixHead->rootPage == -1) // root page doesn't exist
	{
		BufType b = bpm->allocPage(fileID, ixHead->numPages, index, false);
		initIxPage((char*)b);
		bpm->markDirty(index);
		ixHead->rootPage = ixHead->numPages;
		ixHead->numPages++;
		bpm->markDirty(ixIndex);
	}

	//BufType b = bpm->getPage(fileID, ixHead->rootPage, index);
	return RecursiveInsertEntry(ixHead->rootPage, pData, rid);
}

RC IX_IndexHandle::RecursiveInsertEntry(int pageNum, void *pData, const RID &rid)
{
	int index;
	BufType b = bpm->getPage(fileID, pageNum, index);
	IX_Page_head* pageHead = (IX_Page_head*)b;
	int position = -1;
	getPosition(pData, position, b);
	// not leaf page, recursive insert
	if (!pageHead->isLeafPage)
	{

		IX_Node* nodeArray = (IX_Node*)((char*)b + sizeof(IX_Page_head) + ixHead->attrLength * ixHead->degree);
		return RecursiveInsertEntry(nodeArray[position].nextPage, pData, rid);

	}
	else // page is leafPage
	{
		// judge if entry is also in the tree
		// waited to add

		if (pageHead->numEntries < ixHead->degree) // is not full
		{
			if (ixHead->attrType == DINT)
			{
				int keyData = *((int*)pData);
				int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
				IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);

				nodeArray[pageHead->numEntries + 1] = nodeArray[pageHead->numEntries];
				for (int i = pageHead->numEntries; i > position; i--)
				{
					keyArray[i] = keyArray[i - 1];
					nodeArray[i] = nodeArray[i - 1];
				}
				keyArray[position] = keyData;
				nodeArray[position].nextPage = -1;
				nodeArray[position].rid = rid;
				if (verbose == 2)
				{
					cout << "[info] insert index " << keyData << endl;
				}
			}
			// waited to add other kind of data(float char)
			pageHead->numEntries++;
			bpm->markDirty(pageNum);
			return OK;
		}
		else // full, split
		{
			// allocate a new page
			BufType newb = bpm->allocPage(fileID, ixHead->numPages, index, false);
			initIxPage((char*)newb);
			bpm->markDirty(index);
			ixHead->numPages++;
			bpm->markDirty(ixIndex);
			pageHead->numEntries = (ixHead->degree + 1) / 2;
			IX_Page_head * newPageHead = (IX_Page_head*)newb;
			newPageHead->numEntries = (ixHead->degree + 1) - pageHead->numEntries;
			newPageHead->nextpage = pageHead->nextpage;
			pageHead->nextpage = ixHead->numPages - 1;
			if (ixHead->attrType == DINT)
			{
				int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
				IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);
				int* newKeyArray = (int*)((char*)newb + sizeof(IX_Page_head));
				IX_Node* newNodeArray = (IX_Node*)((char*)newKeyArray + ixHead->attrLength * ixHead->degree);
				// copy half of the data to the new page
				int N = ixHead->degree;
				// modify the data
				int M = sizeof(IX_Page_head);
				if (position < (N + 1) / 2)
				{
					//memcpy((char*)newb + M, (char*)b + M + ixHead->attrLength * ((N + 1) / 2 - 1), ixHead->attrLength * (N - ((N + 1) / 2 - 1)));
					//memcpy((char*)newb + M + N * ixHead->attrLength, (char*)b + M + N * ixHead->attrLength + sizeof(IX_Node) * ((N + 1) / 2 - 1), M * (N - ((N + 1) / 2 - 1)));
					for (int j = (N + 1) / 2; j < N + 1; j++)
					{
						newKeyArray[j - (N + 1) / 2] = keyArray[j - 1];
						newNodeArray[j - (N + 1) / 2] = nodeArray[j - 1];
					}
					for (int j = (N + 1) / 2 - 1; j > position; j--)
					{
						keyArray[j] = keyArray[j - 1];
						nodeArray[j] = nodeArray[j - 1];
					}

					keyArray[position] = *(int*)pData;
					nodeArray[position].nextPage = -1;
					nodeArray[position].rid = rid;
					// add other types
				}
				else
				{
					for (int j = 0; j < N + 1 - (N + 1) / 2; j++)
					{
						if (j < position - (N + 1) / 2)
						{
							newKeyArray[j] = keyArray[j + (N + 1) / 2];
							newNodeArray[j] = nodeArray[j + (N + 1) / 2];
						}
						else if (j > position - (N + 1) / 2)
						{
							newKeyArray[j] = keyArray[j + (N + 1) / 2 - 1];
							newNodeArray[j] = nodeArray[j + (N + 1) / 2 - 1];
						}
						else
						{
							newKeyArray[j] = *(int*)pData;
							newNodeArray[j].nextPage = -1;
							newNodeArray[j].rid = rid;
						}
					}
				}
				int parent = pageHead->parentPage;
				bool pageNumIsRoot = false;
				if (pageNum == ixHead->rootPage)
					pageNumIsRoot = true;
				RC rc = RecursiveSplitNode(pageNum, ixHead->numPages - 1, (void*)newKeyArray, parent);
				newPageHead->parentPage = parent;
				if (pageNumIsRoot)
					pageHead->parentPage = parent;
			}
			
		}
	}
	return OK;
}
	
int trans(int start, int position)
{
	if (start == position)
		return -1;
	else if (start < position)
		return start;
	else
		return start - 1;
}

int trans2(int start, int position)
{
	if (start == (position + 1))
		return -1;
	else if (start < (position + 1))
		return start;
	else
		return start - 1;
}

RC IX_IndexHandle::RecursiveSplitNode(int pageNum, int newPageNum, void* pData, int& parent)
{
	// judge if pageNum is rootPage
	if (ixHead->rootPage == pageNum)
	{
		cout << "split root\n";
		int index;
		BufType b = bpm->allocPage(this->fileID, ixHead->numPages, index, false);
		ixHead->rootPage = ixHead->numPages;
		ixHead->numPages++;
		bpm->markDirty(index);
		bpm->markDirty(ixIndex);
		IX_Page_head * pageHead = (IX_Page_head*)b;
		pageHead->isLeafPage = false;
		pageHead->numEntries = 1;
		pageHead->parentPage = -1;
		
		if (ixHead->attrType == DINT)
		{
			int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
			keyArray[0] = *(int*)pData;
			IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->degree * ixHead->attrLength);
			nodeArray[0].nextPage = pageNum;
			nodeArray[1].nextPage = newPageNum;
		}
		// add other type
		parent = ixHead->numPages - 1;
		return OK;
	}
	else {
		int index;
		BufType b = bpm->getPage(this->fileID, parent, index);
		IX_Page_head * pageHead = (IX_Page_head*)b;
		bpm->markDirty(index);

		// non-leaf page is full
		int position = -1;
		getPosition(pData, position, b);
		if (ixHead->degree == pageHead->numEntries)
		{
			BufType newb = bpm->allocPage(fileID, ixHead->numPages, index, false);
			initIxPage((char*)newb);
			bpm->markDirty(index);
			ixHead->numPages++;
			bpm->markDirty(ixIndex);
			pageHead->numEntries = (ixHead->degree + 1) / 2;
			IX_Page_head * newPageHead = (IX_Page_head*)newb;
			newPageHead->numEntries = ixHead->degree - pageHead->numEntries;
			newPageHead->isLeafPage = false;
			if (ixHead->attrType == DINT)
			{
				int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
				int keyData = *(int*)pData;
				IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);
				int* newKeyArray = (int*)((char*)newb + sizeof(IX_Page_head));
				IX_Node* newNodeArray = (IX_Node*)((char*)newKeyArray + ixHead->attrLength * ixHead->degree);
				// copy half of the data to the new page
				int N = ixHead->degree;
				cout << keyData << " " << newPageNum << endl;
				for (int j = 0; j < N; j++)
				{
					cout << nodeArray[j].nextPage << " " << keyArray[j] << " ";
				}
				cout << nodeArray[N].nextPage << endl;
				int newData = -1;
				if (trans((N + 1) / 2, position) >= 0)
					newData = keyArray[trans((N + 1) / 2, position)];
				else
					newData = keyData;
				// modify the data
				for (int j = (N + 1) / 2 + 1; j < N + 1; j++)
				{
					if (trans(j, position) >= 0)
						newKeyArray[j - (N + 1) / 2 - 1] = keyArray[trans(j, position)];
					else
						newKeyArray[j - (N + 1) / 2 - 1] = keyData;
				}
				for (int j = (N + 1) / 2 - 1; j >= 0; j--)
				{
					if (trans(j, position) >= 0)
						keyArray[j] = keyArray[trans(j, position)];
					else
						keyArray[j] = keyData;
				}
				for (int j = (N + 1) / 2 + 1; j < N + 2; j++)
				{
					if (trans2(j, position) >= 0)
						newNodeArray[j - (N + 1) / 2 - 1] = nodeArray[trans2(j, position)];
					else
						newNodeArray[j - (N + 1) / 2 - 1].nextPage = newPageNum;
				}
				for (int j = (N + 1) / 2; j >= 0; j--)
				{
					if (trans2(j, position) >= 0)
						nodeArray[j] = nodeArray[trans2(j, position)];
					else
						nodeArray[j].nextPage = newPageNum;
				}
				for (int j = 0; j < (N + 1)/2; j++)
				{
					cout << nodeArray[j].nextPage << " " << keyArray[j] << " ";
				}
				cout << nodeArray[(N + 1) / 2].nextPage << endl;
				for (int j = 0; j < (N - (N + 1)/2); j++)
				{
					cout << newNodeArray[j].nextPage << " " << newKeyArray[j] << " ";
				}
				cout << newNodeArray[N - (N + 1) / 2].nextPage << endl;
				int parent3 = parent;
				if (position >= (N + 1) / 2)
					parent = ixHead->numPages - 1;
				bool pageNumIsRoot = false;
				if (parent3 == ixHead->rootPage)
					pageNumIsRoot = true;
				int parent2 = pageHead->parentPage;
				RC rc = RecursiveSplitNode(parent3, ixHead->numPages - 1, (void*)(&newData), parent2);
				newPageHead->parentPage = parent2;
				if (pageNumIsRoot)
					pageHead->parentPage = parent2;
			}
			// add other type
			return OK;
		}
		else //non-leaf page is not full
		{
			if (ixHead->attrType == DINT)
			{
				int keyData = *((int*)pData);
				int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
				IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);

				//nodeArray[pageHead->numEntries + 1] = nodeArray[pageHead->numEntries];
				for (int i = pageHead->numEntries; i > position; i--)
				{
					keyArray[i] = keyArray[i - 1];
					nodeArray[i + 1] = nodeArray[i];
				}
				keyArray[position] = keyData;
				nodeArray[position + 1].nextPage = newPageNum;
			}
			pageHead->numEntries++;
		}
		return OK;
	}
	return OK;
}

RC IX_IndexHandle::forcePages(PageNum pageNum)
{
	if (pageNum == -1) // writeBack All pages
	{
		for (int i = 0; i < ixHead->numPages; i++)
		{
			int index;
			BufType b = bpm->getPage(fileID, i, index);
			bpm->markDirty(index);
			bpm->writeBack(index);
		}
	}
	else
	{
		int index;
		BufType b = bpm->getPage(fileID, pageNum, index);
		bpm->markDirty(index);
		bpm->writeBack(index);
	}
	if (verbose == 2)
		cout << "[info] forces Page at " << pageNum << endl;
	return OK;
}

RC IX_IndexHandle::getPosition(void* pData, int& position, BufType b)
{
	IX_Page_head* pageHead = (IX_Page_head*)b;
	if (ixHead->attrType == DINT)
	{
		int keyData = *((int*)pData);
		int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
		IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);
		for (int i = 0; i < pageHead->numEntries; i++)
		{
			if (keyData < keyArray[i])
			{
				position = i;
				break;
			}
		}
		if (position == -1)
			position = pageHead->numEntries;
	}
	// add two other kind of data
	return OK;
}

RC IX_IndexHandle::getMiddleData(void* pData, BufType b, int position, void* p)
{
	IX_Page_head* pageHead = (IX_Page_head*)b;
	if (ixHead->attrType == DINT)
	{
		int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
		IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);
		if (position > (pageHead->numEntries + 1) / 2)
			p = (void*)keyArray[(pageHead->numEntries + 1) / 2];
		else if (position < (pageHead->numEntries + 1) / 2)
			p = (void*)keyArray[(pageHead->numEntries + 1) / 2 - 1];
		else
			p = pData;
	}
	// add two other kind of data
	return OK;
}
RC IX_IndexHandle::initIxPage(char* b)
{
	IX_Page_head * pageHead = (IX_Page_head*)b;
	pageHead->numEntries = 0;
	pageHead->parentPage = -1;
	pageHead->isLeafPage = true;
	pageHead->nextpage = -1;
	return OK;
}
RC IX_IndexHandle::reloadFile()
{
	BufType b = bpm->getPage(fileID, 0, ixIndex);
	ixHead = (IX_File_Head*)b;
	return OK;
}

// @function lazy delete the entry in the tree
// 1. get the root page
// 2. recursive get the leaf page
// 3. judge if the entry is in the tree
// 4. when find the entry with the same pData, compare their rid
// 5. delete the one with the same rid
// 6. after deletion, judge if the page is null

RC IX_IndexHandle::DeleteEntry  (void *pData, const RID &rid)  // Delete index entry
{
	reloadFile();
	int index;
	int pageNum = ixHead->rootPage;
	IX_Page_head * pageHead;
	int position = -1;
	IX_Node* nodeArray ;
	BufType b;
	do{
		b = bpm->getPage(fileID, pageNum, index);
		pageHead = (IX_Page_head*)b;
		getPosition(pData, position, b);
		nodeArray = (IX_Node*)((char*)b + sizeof(IX_Page_head) + ixHead->attrLength * ixHead->degree);
		pageNum = nodeArray[position].nextPage;
	}while(!pageHead->isLeafPage);
	int result = -1;
	if (ixHead->attrType == DINT)
	{
		int* keyArray = (int*)(b + sizeof(IX_Page_head));
		int keyData = *(int*)pData;
		while (true)
		{
			if (position >= pageHead->numEntries)
			{
				// get to next page
				if (pageHead->nextpage == -1)
				{
					// no next page;
					break;
				}
				else
				{
					pageNum = pageHead->nextpage;
					b = bpm->getPage(fileID, pageNum, index);
					nodeArray = (IX_Node*)((char*)b + sizeof(IX_Page_head) + ixHead->attrLength * ixHead->degree);
					keyArray = (int*)(b + sizeof(IX_Page_head));
					position = 0;
					if (verbose = 2)
						cout << "[info] get to next page to delete " << keyData << endl;
				}
			}
			if (keyArray[position] > keyData)
			{
				break;
			}
			else if (keyArray[position] < keyData)
			{
				position++;
			}
			else if(nodeArray[position].rid.compare(rid))
			{
				// delete this record;
				for (int j = position; j < pageHead->numEntries - 1; j++)
				{
					keyArray[j] = keyArray[j + 1];
					nodeArray[j] = nodeArray[j + 1];
				}
				pageHead->numEntries--;
				result = 0;
				bpm->markDirty(index);
				if (verbose == 2)
					cout << "[info] delete entry with data " << keyData << endl;
			}

		}
	}
	if (result == -1)
	{
		if (verbose == 2)
		{
			cout << "[info] cann't find " << *(int*)pData << " and delete it\n";
		}
	}
	else if (result == 0)
	{
		if (pageHead->numEntries <= 0)
		{
			// delete this page
			// implement it later
		}
	}
	return OK;
}

IX_IndexScan::IX_IndexScan()                                 // Constructor
{

}
IX_IndexScan::~IX_IndexScan()                                 // Destructor
{

}

RC IX_IndexScan::OpenScan (const IX_IndexHandle &indexHandle, CompOp compOp, void *value)
{
	this->indexHandle = indexHandle;
	this->compOp = compOp;
	this->value = value;
	if (indexHandle.ixHead->numPages < 2)
		return ERROR;
	int index;
	//b = indexHandle.bpm->getPage(indexHandle.fileID, indexHandle.ixHead->rootPage, index);
	currentPage = indexHandle.ixHead->rootPage;
	attrLength = indexHandle.ixHead->attrLength;
	attrtype = indexHandle.ixHead->attrType;
	RC rc = SearchEntry(currentPage, currentPosition);
	if (rc != 0)
	{
		cout << "[info] error to open index sacn\n";
		currentPage = -1;
		currentPosition = -1;
		return ERROR;
	}
	b = indexHandle.bpm->getPage(indexHandle.fileID, currentPage, index);
	pageHead = (IX_Page_head*)b;
	return OK;
}

// @function search the first entry that satisfied the condition
// 1. get the root page
// 2. judge if the current page is leaf page
//		a. if not leaf page, recursive search the child node page turn to 3.
//		b. if leaf page turn to 5.
// 3. judge the CompOp, if it's LT or LE , go to the leftmost child, for other op, find the first position that has a GE value compared to the keyvalue;
// 4. if the page is leaf page, turn to 5
// 5. 
RC IX_IndexScan::SearchEntry(int& pageNum, int& position)
{
	int index;
	b = indexHandle.bpm->getPage(indexHandle.fileID, pageNum, index);
	IX_Page_head* pageHead=(IX_Page_head*)b;
	if (!pageHead->isLeafPage)
	{
		IX_Node* nodeArray = (IX_Node*)((char*)b + sizeof(IX_Page_head) + attrLength*indexHandle.ixHead->degree);
		if (compOp == LE_OP || compOp == LT_OP)
		{
			pageNum = nodeArray[0].nextPage;
		}
		else
		{
			if (attrtype == DINT)
			{
				int keyValue = *(int*)value;
				int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
				if (keyValue <= keyArray[0])
					pageNum = nodeArray[0].nextPage;
				if (keyArray[pageHead->numEntries - 1] > keyValue)
					pageNum = nodeArray[pageHead->numEntries].nextPage;
				else
				{
					for (int j = 1; j < pageHead->numEntries; j++)
					{
						if (keyArray[j] >= keyValue)
							pageNum = nodeArray[j].nextPage;
					}
				}
			}
			// add other types
		}
		return SearchEntry(pageNum, position);
	}
	else if(pageHead->isLeafPage)
	{
		bool found = false;
		if (attrtype == DINT)
		{
			int keyValue = *(int*)value;
			int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
			for (int j = 0; j < pageHead->numEntries; j++)
			{
				if (satisfiesCondition(keyArray[j], keyValue))
				{
					found = true;
					position = j;
					break;
				}
			}
		}
		else if (attrtype == FLOAT)
		{

		}
		// add other types

		if (found)
			return OK;
		else
			return ERROR;
	}
	return OK;
}

template<typename T>
bool IX_IndexScan::satisfiesCondition(T key, T value) {
	bool match = false;
	switch (compOp) {
	case EQ_OP:
		if (key == value) match = true;
		break;
	case LT_OP:
		if (key < value) match = true;
		break;
	case GT_OP:
		if (key > value) match = true;
		break;
	case LE_OP:
		if (key <= value) match = true;
		break;
	case GE_OP:
		if (key >= value) match = true;
		break;
	default:
		break;
	}
	return match;
}

// @function get the next entry that satisfied the condition
//	1. judge if currentPosition bigger then numEntries
//		a if yes, go to the next page
//		    (1) judge if next page exist, if not return else go to next page ,reset position
//		b. if no judge if current value satisfy condition
//			(1) yes, return current rid, and positin++
//			(2) no,  return ERROR
RC IX_IndexScan::GetNextEntry(RID &rid)                         // Get next matching entry
{
	if (currentPage == -1)
	{
		cout << "[info] error to open index scan\n";
		return ERROR;
	}

	while (true)
	{
		if (currentPosition == pageHead->numEntries)
		{
			currentPage = pageHead->nextpage;
			if (currentPage < 0)
				return ERROR;
			else
			{
				int index;
				b = indexHandle.bpm->getPage(indexHandle.fileID, currentPage, index);
				pageHead = (IX_Page_head*)b;
				currentPosition = 0;
			}
		}
		IX_Node* nodeArray = (IX_Node*)((char*)b + sizeof(IX_Page_head) + attrLength* indexHandle.ixHead->degree);
		if (attrtype == DINT)
		{
			int keyValue = *(int*)value;
			int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
			if (satisfiesCondition(keyArray[currentPosition], keyValue))
			{
				rid.setPageNum(nodeArray[currentPosition].rid.getPageNum());
				rid.setSlotNum(nodeArray[currentPosition].rid.getSlotNum());
				currentPosition++;
				return OK;
			}
			else
				return ERROR;

		}
	}
	return OK;
}

RC IX_IndexScan::CloseScan()                                 // Terminate index scan
{
	return OK;
}