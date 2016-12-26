#include "IX_Manager.h"
using namespace std;


IX_Manager::IX_Manager(FileManager* fm, BufPageManager* bpm)
{
	this->fm=fm;
	this->bpm=bpm;
}

IX_Manager::~IX_Manager()
{
	fm = nullptr;
	bpm = nullptr;
}

RC IX_Manager::CreateIndex(const char* fileName, int indexNo, AttrType attrType, int attrLength)
{
	char* indexFileName = new char[strlen(fileName) + 10];
	sprintf_s(indexFileName, strlen(fileName) + 10, "%s.%d", fileName, indexNo);
	int fileID;
	fm->createFile(indexFileName);
	fm->openFile(indexFileName, fileID);
	IdMap::fileIDMap[indexFileName] = fileID;
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
	//bpm->writeBack(index);
	//fm->closeFile(fileID);
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
	if (IdMap::fileIDMap.count(indexFileName) == 0)
	{
		fm->openFile(indexFileName, fileID);
		IdMap::fileIDMap[indexFileName] = fileID;
	}
	else
		fileID = IdMap::fileIDMap[indexFileName];
	int index;
	BufType b = bpm->getPage(fileID, 0, index);
	IX_File_Head * ixHead = (IX_File_Head*)b;
	indexHandle.bpm = this->bpm;
	indexHandle.fm = this->fm;
	indexHandle.fileID = fileID;
	indexHandle.ixIndex = index;
	indexHandle.ixHead = ixHead;
	return OK;
}

RC IX_Manager::DestroyIndex(const char* fileName, int indexNo)
{
	// waite to be modified;
	if (IdMap::fileIDMap.count((string(fileName) + "." + to_string(indexNo)).c_str()) != 0)
		IdMap::fileIDMap.erase((string(fileName) + "." + to_string(indexNo)).c_str());
	remove((string(fileName) + "." + to_string(indexNo)).c_str());
	return OK;
}

RC IX_Manager::CloseIndex(IX_IndexHandle &indexHandle)
{
	//waited to be modified
	//indexHandle.forcePages(-1);
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
			else if (ixHead->attrType == STRING || ixHead->attrType == VARCHAR)
			{
				char* keyData = (char*)pData;
				char* keyArray = (char*)((char*)b + sizeof(IX_Page_head));
				IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);

				nodeArray[pageHead->numEntries + 1] = nodeArray[pageHead->numEntries];
				for (int i = pageHead->numEntries; i > position; i--)
				{
					memcpy((void*)(keyArray + ixHead->attrLength * i), (void*)(keyArray + ixHead->attrLength * (i - 1)), ixHead->attrLength);
					//keyArray[i] = keyArray[i - 1];
					nodeArray[i] = nodeArray[i - 1];
				}
				int copyLength = strlen((char*)keyData) + 1;
				memcpy((void*)(keyArray + ixHead->attrLength * position), (void*)keyData, copyLength);
				//keyArray[position] = keyData;
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
			if(verbose == 2)
				cout << "[Info]: Insert Index\n";
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
			else if (ixHead->attrType == STRING || ixHead->attrType == VARCHAR)
			{
				char* keyArray = (char*)((char*)b + sizeof(IX_Page_head));
				IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);
				char* newKeyArray = (char*)((char*)newb + sizeof(IX_Page_head));
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
						memcpy(newKeyArray + ixHead->attrLength*(j - (N + 1) / 2), keyArray + ixHead->attrLength*(j - 1), ixHead->attrLength);
						newNodeArray[j - (N + 1) / 2] = nodeArray[j - 1];
					}
					for (int j = (N + 1) / 2 - 1; j > position; j--)
					{
						memcpy(newKeyArray + ixHead->attrLength*j, keyArray + ixHead->attrLength*(j - 1), ixHead->attrLength);
						nodeArray[j] = nodeArray[j - 1];
					}
					int copyLength = strlen((char*)pData) + 1;
					memcpy(keyArray + ixHead->attrLength*position, pData, copyLength);
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
							memcpy(newKeyArray + ixHead->attrLength*j, keyArray + ixHead->attrLength*(j + (N + 1) / 2), ixHead->attrLength);
							newNodeArray[j] = nodeArray[j + (N + 1) / 2];
						}
						else if (j > position - (N + 1) / 2)
						{
							memcpy(newKeyArray + ixHead->attrLength*j, keyArray + ixHead->attrLength*(j + (N + 1) / 2 - 1), ixHead->attrLength);
							newNodeArray[j] = nodeArray[j + (N + 1) / 2 - 1];
						}
						else
						{
							int copyLength = strlen((char*)pData) + 1;
							memcpy(newKeyArray + ixHead->attrLength*j, pData, copyLength);
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
			keyArray = nullptr;
			nodeArray = nullptr;
		}
		else if (ixHead->attrType == STRING || ixHead->attrType == VARCHAR)
		{
			char* keyArray = (char*)((char*)b + sizeof(IX_Page_head));
			keyArray[0] = *(int*)pData;
			IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->degree * ixHead->attrLength);
			nodeArray[0].nextPage = pageNum;
			nodeArray[1].nextPage = newPageNum;
			keyArray = nullptr;
			nodeArray = nullptr;
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
				//cout << keyData << " " << newPageNum << endl;
				for (int j = 0; j < N; j++)
				{
					//cout << nodeArray[j].nextPage << " " << keyArray[j] << " ";
				}
				//cout << nodeArray[N].nextPage << endl;
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
			else if (ixHead->attrType == STRING || ixHead->attrType == VARCHAR)
			{
				char* keyArray = (char*)((char*)b + sizeof(IX_Page_head));
				char* keyData = (char*)pData;
				IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);
				char* newKeyArray = (char*)((char*)newb + sizeof(IX_Page_head));
				IX_Node* newNodeArray = (IX_Node*)((char*)newKeyArray + ixHead->attrLength * ixHead->degree);
				// copy half of the data to the new page
				int N = ixHead->degree;
				char* newData = new char[ixHead->attrLength];
				memset(newData, 0, ixHead->attrLength);
				if (trans((N + 1) / 2, position) >= 0)
					memcpy(newData, keyArray + ixHead->attrLength * trans((N + 1) / 2, position), ixHead->attrLength);
				else
					memcpy(newData, keyData, ixHead->attrLength);
				// modify the data
				for (int j = (N + 1) / 2 + 1; j < N + 1; j++)
				{
					if (trans(j, position) >= 0)
						memcpy(newKeyArray + ixHead->attrLength*(j - (N + 1) / 2 - 1), keyArray + ixHead->attrLength*trans(j, position), ixHead->attrLength);
					else
						memcpy(newKeyArray + ixHead->attrLength*(j - (N + 1) / 2 - 1), keyData, ixHead->attrLength);
				}
				for (int j = (N + 1) / 2 - 1; j >= 0; j--)
				{
					if (trans(j, position) >= 0)
						memcpy(keyArray + ixHead->attrLength*j, keyArray + ixHead->attrLength*trans(j, position), ixHead->attrLength);
					else
						memcpy(keyArray + ixHead->attrLength*j, keyData, ixHead->attrLength);
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
				//for (int j = 0; j < (N + 1)/2; j++)
				//{
				//	cout << nodeArray[j].nextPage << " " << keyArray[j] << " ";
				//}
				//cout << nodeArray[(N + 1) / 2].nextPage << endl;
				//for (int j = 0; j < (N - (N + 1)/2); j++)
				//{
				//	cout << newNodeArray[j].nextPage << " " << newKeyArray[j] << " ";
				//}
				//cout << newNodeArray[N - (N + 1) / 2].nextPage << endl;
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

				delete[]newData;
				newData = nullptr;
				newNodeArray = nullptr;
				newKeyArray = nullptr;
				nodeArray = nullptr;
				keyData = nullptr;
				keyArray = nullptr;
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
				keyArray = nullptr;
				nodeArray = nullptr;
			}
			else if (ixHead->attrType == STRING || ixHead->attrType == VARCHAR)
			{
				char* keyData = (char*)pData;
				char* keyArray = (char*)((char*)b + sizeof(IX_Page_head));
				IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);

				//nodeArray[pageHead->numEntries + 1] = nodeArray[pageHead->numEntries];
				for (int i = pageHead->numEntries; i > position; i--)
				{
					memcpy(keyArray + ixHead->attrLength*i, keyArray + ixHead->attrLength*(i - 1), ixHead->attrLength);
					nodeArray[i + 1] = nodeArray[i];
				}
				memcpy(keyArray + ixHead->attrLength*position, keyData, ixHead->attrLength);
				nodeArray[position + 1].nextPage = newPageNum;
				keyArray = nullptr;
				nodeArray = nullptr;
				keyData = nullptr;
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
			if (keyData <= keyArray[i])
			{
				position = i;
				break;
			}
		}
		if (position == -1)
			position = pageHead->numEntries;
		keyArray = nullptr;
		nodeArray = nullptr;
	}
	else if (ixHead->attrType == STRING || ixHead->attrType == VARCHAR)
	{
		char* keyData = (char*)pData;
		char* keyArray = (char*)((char*)b + sizeof(IX_Page_head));
		IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);
		for (int i = 0; i < pageHead->numEntries; i++)
		{
			if (string(keyData) < string(keyArray + i*ixHead->attrLength))
			{
				position = i;
				break;
			}
		}
		if (position == -1)
			position = pageHead->numEntries;
		keyArray = nullptr;
		nodeArray = nullptr;
		keyData = nullptr;
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
		keyArray = nullptr;
		nodeArray = nullptr;
	}
	else if (ixHead->attrType == STRING || ixHead->attrType == VARCHAR)
	{
		char* keyArray = (char*)((char*)b + sizeof(IX_Page_head));
		IX_Node* nodeArray = (IX_Node*)((char*)keyArray + ixHead->attrLength * ixHead->degree);
		if (position >(pageHead->numEntries + 1) / 2)
			p = (void*)(keyArray + ixHead->attrLength*((pageHead->numEntries + 1) / 2));
		else if (position < (pageHead->numEntries + 1) / 2)
			p = (void*)(keyArray + ixHead->attrLength*((pageHead->numEntries + 1) / 2 - 1));
		else
			p = pData;
		keyArray = nullptr;
		nodeArray = nullptr;
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
	bool found = false;
	if (ixHead->attrType == DINT)
	{
		int* keyArray = (int*)(b + sizeof(IX_Page_head));
		int keyData = *(int*)pData;
		while (true)
		{
			if (position >= pageHead->numEntries)
			{
				if (pageHead->nextpage == -1)
					break;
				else
				{
					b = bpm->getPage(fileID, pageHead->nextpage, index);
					pageHead = (IX_Page_head*)b;
					getPosition(pData, position, b);
					nodeArray = (IX_Node*)((char*)b + sizeof(IX_Page_head) + ixHead->attrLength * ixHead->degree);
					pageNum = nodeArray[position].nextPage;
				}
			}
			else if (keyArray[position] != keyData)
				break;
			else if (nodeArray[position].rid.compare(rid))
			{
				// delete this record;
				for (int j = position; j < pageHead->numEntries - 1; j++)
				{
					keyArray[j] = keyArray[j + 1];
					nodeArray[j] = nodeArray[j + 1];
				}
				pageHead->numEntries--;
				found = true;
				bpm->markDirty(index);
				if (verbose == 2)
					cout << "[info] delete entry with data " << keyData << endl;
				break;
			}
			else
				position++;

		}
	}
	else if (ixHead->attrType == STRING || ixHead->attrType == VARCHAR)
	{
		char* keyArray = (char*)(b + sizeof(IX_Page_head));
		char* keyData = (char*)pData;
		while (true)
		{
			if (position >= pageHead->numEntries)
			{
				if (pageHead->nextpage == -1)
					break;
				else
				{
					b = bpm->getPage(fileID, pageHead->nextpage, index);
					pageHead = (IX_Page_head*)b;
					getPosition(pData, position, b);
					nodeArray = (IX_Node*)((char*)b + sizeof(IX_Page_head) + ixHead->attrLength * ixHead->degree);
					pageNum = nodeArray[position].nextPage;
				}
			}
			else if (string(keyArray + ixHead->attrLength * position) != string(keyData))
				break;
			else if (nodeArray[position].rid.compare(rid))
			{
				// delete this record;
				for (int j = position; j < pageHead->numEntries - 1; j++)
				{
					memcpy(keyArray + ixHead->attrLength * j, keyArray + ixHead->attrLength * (j + 1), ixHead->attrLength);
					nodeArray[j] = nodeArray[j + 1];
				}
				pageHead->numEntries--;
				found = true;
				bpm->markDirty(index);
				if (verbose == 2)
					cout << "[info] delete entry with data " << keyData << endl;
				break;
			}
			else
				position++;

		}
	}
	if (found == false)
	{
		if (verbose == 2)
		{
			cout << "[info] cann't find " << *(int*)pData << " and delete it\n";
		}
	}
	else if (found == true)
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
	value = nullptr;
	pageHead = nullptr;
}
IX_IndexScan::~IX_IndexScan()                                 // Destructor
{
	value = nullptr;
	pageHead = nullptr;
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
	scanIndex = index;
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
			bool found = false;
			if (attrtype == DINT)
			{
				int keyValue = *(int*)value;
				int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
				if (keyValue <= keyArray[0])
				{
					pageNum = nodeArray[0].nextPage;
					found = true;
				}
				else if (keyValue > keyArray[pageHead->numEntries - 1])
				{
					pageNum = nodeArray[pageHead->numEntries].nextPage;
					found = true;
				}
				else
				{
					for (int j = 1; j < pageHead->numEntries; j++)
					{
						if (keyArray[j] >= keyValue)
						{
							pageNum = nodeArray[j].nextPage;
							found = true;
							break;
						}
					}
				}
			}
			else if (attrtype == STRING || attrtype == VARCHAR)
			{
				char* keyValue = (char*)value;
				char* keyArray = (char*)((char*)b + sizeof(IX_Page_head));
				if (string(keyValue) <= string(keyArray))
				{
					pageNum = nodeArray[0].nextPage;
					found = true;
				}
				if (string(keyArray + (pageHead->numEntries - 1)*attrLength) <= string(keyValue))
				{
					pageNum = nodeArray[pageHead->numEntries].nextPage;
					found = true;
				}
				else
				{
					for (int j = 1; j < pageHead->numEntries; j++)
					{
						if (string(keyArray + j * attrLength) >= string(keyValue))
						{
							pageNum = nodeArray[j].nextPage;
							found = true;
							break;
						}
					}
				}
			}
			if (!found)
				cout << "Error Search Entry\n";
			// add other types
		}
		return SearchEntry(pageNum, position);
	}
	else if(pageHead->isLeafPage)
	{
		if (pageHead->numEntries == 0)
		{
			if (pageHead->nextpage < 0)
				return IX_NO_SUCH_INDEX;
			return SearchEntry(pageHead->nextpage, position);
		}
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
		else if (attrtype == STRING || attrtype ==  VARCHAR)
		{
			char* keyValue = (char*)value;
			char* keyArray = (char*)((char*)b + sizeof(IX_Page_head));
			for (int j = 0; j < pageHead->numEntries; j++)
			{
				if (satisfiesCondition(string(keyArray + j * attrLength), string(keyValue)))
				{
					found = true;
					position = j;
					break;
				}
			}
		}
		// add other types

		if (found)
			return OK;
		else
			return IX_NO_SUCH_INDEX;
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
	case NO_OP:
	case NOTNULL_OP:
		match = true;
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
RC IX_IndexScan::GetNextEntry(RID &rid, bool DeleteMode)                         // Get next matching entry
{
	RC rc;
	if (currentPage == -1)
	{
		cout << "[info] error to open index scan\n";
		return ERROR;
	}

	bool found = false;
	while (!found)
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
				scanIndex = index;
			}
			continue;
		}
		found = true;
		IX_Node* nodeArray = (IX_Node*)((char*)b + sizeof(IX_Page_head) + attrLength* indexHandle.ixHead->degree);
		if (attrtype == DINT)
		{
			int keyValue = *(int*)value;
			int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
			if (satisfiesCondition(keyArray[currentPosition], keyValue))
			{
				rid.setPageNum(nodeArray[currentPosition].rid.getPageNum());
				rid.setSlotNum(nodeArray[currentPosition].rid.getSlotNum());
				if (DeleteMode)
				{
					pageHead->numEntries--;
					for (int j = currentPosition; j < pageHead->numEntries; j++)
					{
						keyArray[j] = keyArray[j + 1];
						nodeArray[j] = nodeArray[j + 1];
					}
					indexHandle.bpm->markDirty(scanIndex);
				}
				else
					currentPosition++;

				rc = OK;
				found = true;
			}
			else
				rc = ERROR;
			keyArray = nullptr;
		}
		else if (attrtype == STRING || attrtype == VARCHAR)
		{
			char* keyValue = (char*)value;
			char* keyArray = (char*)((char*)b + sizeof(IX_Page_head));
			if (satisfiesCondition(string(keyArray + currentPosition * attrLength), string(keyValue)))
			{
				rid.setPageNum(nodeArray[currentPosition].rid.getPageNum());
				rid.setSlotNum(nodeArray[currentPosition].rid.getSlotNum());
				if (DeleteMode)
				{
					pageHead->numEntries--;
					for (int j = currentPosition; j < pageHead->numEntries; j++)
					{
						memcpy(keyArray + j * indexHandle.ixHead->attrLength, keyArray + (j + 1)*indexHandle.ixHead->attrLength, indexHandle.ixHead->attrLength);
						nodeArray[j] = nodeArray[j + 1];
					}
					indexHandle.bpm->markDirty(scanIndex);
				}
				else
					currentPosition++;
				rc = OK;
				found = true;
			}
			else
				rc = ERROR;
			keyValue = nullptr;
			keyArray = nullptr;
		}
		nodeArray = nullptr;
	}
	return rc;
}

RC IX_IndexScan::DeleteCurrentEntry()
{
	currentPosition -= 1;
	IX_Node* nodeArray = (IX_Node*)((char*)b + sizeof(IX_Page_head) + attrLength* indexHandle.ixHead->degree);
	if (attrtype == DINT)
	{
		int keyValue = *(int*)value;
		int* keyArray = (int*)((char*)b + sizeof(IX_Page_head));
		pageHead->numEntries--;
		for (int j = currentPosition; j < pageHead->numEntries; j++)
		{
			keyArray[j] = keyArray[j + 1];
			nodeArray[j] = nodeArray[j + 1];
		}
		indexHandle.bpm->markDirty(scanIndex);
	}
	else if (attrtype == STRING || attrtype == VARCHAR)
	{
		char* keyValue = (char*)value;
		char* keyArray = (char*)((char*)b + sizeof(IX_Page_head));
		pageHead->numEntries--;
		for (int j = currentPosition; j < pageHead->numEntries; j++)
		{
			memcpy(keyArray + j * indexHandle.ixHead->attrLength, keyArray + (j + 1)*indexHandle.ixHead->attrLength, indexHandle.ixHead->attrLength);
			nodeArray[j] = nodeArray[j + 1];
		}
		indexHandle.bpm->markDirty(scanIndex);
	}
	return RC();
}

RC IX_IndexScan::CloseScan()                                 // Terminate index scan
{
	return OK;
}