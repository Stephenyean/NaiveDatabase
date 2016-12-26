#include "RM_Manager.h"
#include <cstring>


map<string, int> IdMap::fileIDMap;
RM_Manager::RM_Manager(FileManager* fm, BufPageManager* bpm)
{
	this->fm = fm;
	this->bpm = bpm;
	
}

RM_Manager::~RM_Manager()
{
}

RC RM_Manager::createFile(const char * filename, int recordSize, int attrCount)
{
	//judge if file is created successfully
	fm->createFile(filename);

	int fileID;
	fm->openFile(filename, fileID);
	IdMap::fileIDMap[filename] = fileID;
	int pageID = 0, index;
	BufType b = bpm->allocPage(fileID, pageID, index, false);
	//int recordSize_temp=1;
	// assert  recordSize shouldn't be too big
	// recordSize waited to be modified

	// set the header of file
	File_Head *fileHead = (File_Head*)b;
	fileHead->numPages = 1;
	fileHead->recordSize = recordSize;
	fileHead->nextFreePage = -1;
	fileHead->maxRecordNumPerPage = int((PAGE_SIZE - sizeof(File_Head)) / (recordSize + attrCount + 0.125));
	fileHead->bitMapSize = fileHead->maxRecordNumPerPage / 8;
	fileHead->attrCount = attrCount;
	if ((fileHead->maxRecordNumPerPage % 8) != 0)
		fileHead->bitMapSize++;
	//b=bpm->getPage(fileID, pageID, index);
	//cout<<b[0]<<" "<<b[1]<<" "<<b[2]<<" "<<(int)b<<endl;
	bpm->markDirty(index);
	//bpm->writeBack(index);

	//close file
	if (verbose == 2)
		cout << "[info] create file " << filename << endl;
	//fm->closeFile(fileID);
	return OK;
}

RC RM_Manager::destroyFile(const char * filename)
{
	// waited to be modified
	if (IdMap::fileIDMap.count(filename))
		IdMap::fileIDMap.erase(filename);
	remove(filename);
	return OK;
}

RC RM_Manager::openFile(const char * filename, RM_FileHandle & fileHandle)
{
	int fileID;
	if (IdMap::fileIDMap.count(filename) == 0)
	{
		fm->openFile(filename, fileID);
		IdMap::fileIDMap[filename] = fileID;
	}
	else
		fileID = IdMap::fileIDMap[filename];
	//cout<<"fileID: "<<fileID<<endl;
	fileHandle.fileID = fileID;
	fileHandle.fm = this->fm;
	fileHandle.bpm = this->bpm;

	int pageID = 0, index;
	BufType b = bpm->getPage(fileID, pageID, index);
	fileHandle.fileHead = (File_Head*)b;
	fileHandle.isOpen = true;
	fileHandle.headIndex = index;
	//cout << "fileHead: " << fileHandle.fileHead->numRecords << endl;
	if (verbose == 2)
		cout << "[info] open file " << filename << endl;
	return OK;
}

RC RM_Manager::closeFile(RM_FileHandle & fileHandle)
{
	fileHandle.isOpen = false;
	//fileHandle.forcePages(-1);
	//fm->closeFile(fileHandle.fileID);
	fileHandle.fileHead = nullptr;
	if (verbose == 2)
		cout << "[info] close file " << endl;
	return OK;
}


RM_FileHandle::RM_FileHandle()
{

}

RM_FileHandle::~RM_FileHandle() {}

/*
For this and the following methods, it should be a (positive) error if the RM_FileHandle object
for which the method is called does not refer to an open file. This method should retrieve the
record with identifier rid from the file. It should be a (positive) error if rid does not identify
an existing record in the file. If the method succeeds, rec should contain a copy of the specified
record along with its record identifier (see the RM_Record class description below).
*/
RC RM_FileHandle::getRec(const RID &rid, RM_Record &rec)
{
	if (!isOpen)
		return PF_CLOSEDFILE;
	reloadFile();

	if (rec.checkValid())
	{
		delete[]rec.pData;
		rec.pData = nullptr;
	}
	int pageNum, slotNum;
	rec.recordSize = fileHead->recordSize + fileHead->attrCount + 1;
	if (rid.getPageNum(pageNum) != 0)
		return INVALID_RID;

	if (rid.getSlotNum(slotNum) != 0)
		return INVALID_RID;

	// assert the file is open
	int index;
	BufType b = bpm->getPage(fileID, pageNum, index);

	int offset = getOffset(slotNum);
	char* data = (char*)b + offset;
	char* newData = new char[fileHead->recordSize + fileHead->attrCount + 1];
	memcpy(newData, data, fileHead->recordSize + fileHead->attrCount + 1);
	rec.setData(newData);
	rec.setRid(rid);
	return OK;
}

// 1. judge if the file is open
// 2. judge if there is free page
//		no: allocate a new page
//			set the head of the page
// 3. insert the record to a free page
// 4. modify the bitmap and head
// 5. check if the page if full
//		no: getNextFreePage, if no, freePage = -1


RC RM_FileHandle::insertRec(const char *pData, RID &rid, bool* NullValue)
{
	if (!isOpen)
		return PF_CLOSEDFILE;
	reloadFile();
	int index;
	if (fileHead->nextFreePage == -1) // allocate a new page
	{
		BufType b = bpm->allocPage(fileID, fileHead->numPages, index, false);
		fileHead->nextFreePage = fileHead->numPages;
		fileHead->numPages++;
		initPage(b);
		bpm->markDirty(index);
		if (verbose == 2)
			cout << "[info] allocate a new page\n";
	}
	int pageNum = fileHead->nextFreePage;
	BufType b = bpm->getPage(fileID, fileHead->nextFreePage, index);
	Page_Head* pageHead = (Page_Head*)b;
	int position = getNextFreeSlot((char*)b + sizeof(Page_Head), fileHead->maxRecordNumPerPage);
	if (position < 0)
	{
		cout << "[debug] insertRec Error\n";
		return ERROR;
	}
	// modify bitmap
	setBit(position, (char*)b + sizeof(Page_Head), 1);
	char* data = (char*)b + getOffset(position);
	memcpy(data, (void*)NullValue, fileHead->attrCount);
	memcpy(data + fileHead->attrCount, pData, fileHead->recordSize);
	// modify pageHead
	pageHead->numRecords++;
	//cout << pageHead->numRecords << endl;
	// judge if page is full
	if (pageHead->numRecords >= fileHead->maxRecordNumPerPage)
		fileHead->nextFreePage = pageHead->nextFreePage;
	if (verbose == 2)
	{
		cout << "[info] insert Record\n" ;
	}
	// set markDirty
	bpm->markDirty(headIndex);

	// set rid
	rid.setPageNum(pageNum);
	rid.setSlotNum(position);
	pageHead = nullptr;
	data = nullptr;
	return OK;
}

RC RM_FileHandle::reloadFile()
{
	BufType b = bpm->getPage(fileID, 0, headIndex);
	fileHead = (File_Head*)b;
	return OK;
}
int RM_FileHandle::getNextFreeSlot(char* b, int recordNum)
{
	for (int i = 0; i < recordNum; i++)
		if (getBit(i, b) == 0)
			return i;
	return -1;
}
RC RM_FileHandle::initPage(BufType b)
{
	Page_Head* pageHead = (Page_Head*)b;
	pageHead->nextFreePage = -1;
	pageHead->numRecords = 0;
	char* bitMap = (char*)b + sizeof(Page_Head);
	memset(bitMap, 0, fileHead->bitMapSize);
	return OK;
}

// 1. judge if file is open
// 2. judge if fileHead is in buffer
// 3. delte the record
//		a. modify pageHead
//		b. modify bitMap
// 4. judge if the page is full before deletion
//		yes. modify the fileHead's nextFreePage
//		no. over
RC RM_FileHandle::deleteRec(const RID &rid)
{
	if (!isOpen)
		return PF_CLOSEDFILE;
	reloadFile();

	int pageID, slotID, index;
	rid.getPageNum(pageID);
	rid.getSlotNum(slotID);
	// modify 
	BufType b = bpm->getPage(fileID, pageID, index);
	Page_Head* pageHead = (Page_Head *)b;
	pageHead->numRecords--;
	char* bitMap = (char*)b + sizeof(Page_Head);
	setBit(slotID, bitMap, 0);

	// judge if the file is full before deletion
	if (pageHead->numRecords == fileHead->maxRecordNumPerPage - 1)
	{
		pageHead->nextFreePage = fileHead->nextFreePage;
		fileHead->nextFreePage = pageID;
		bpm->markDirty(headIndex);
	}
	if (verbose == 2)
		cout << "[info] delete record at " << "(" << pageID << "," << slotID << ")\n";

	// markDirty
	bpm->markDirty(index);
	return OK;
}

RC RM_FileHandle::updateRec(const RM_Record &rec, bool* nullValue)
{
	if (!isOpen)
		return PF_CLOSEDFILE;
	reloadFile();
	int pageID, slotID, index;
	RID rid;
	rec.getRid(rid);
	rid.getPageNum(pageID);
	rid.getSlotNum(slotID);
	if (!rid.checkValid())
	{
		cout << "[Debug]: record invalid\n";
		return INVALID_RECORD;
	}
	BufType b = bpm->getPage(fileID, pageID, index);
	char* data = (char*)b + getOffset(slotID);
	memcpy(data, (void*)nullValue, fileHead->attrCount);
	memcpy(data + fileHead->attrCount, rec.pData, fileHead->recordSize);
	bpm->markDirty(index);
	if (verbose == 2)
		cout << "[info] update record " << rec.pData << "(" << pageID << "," << slotID << ")\n";
	return OK;
}

RC RM_FileHandle::forcePages(PageNum pageNum)
{
	if (pageNum == -1) // writeBack All pages
	{
		for (int i = 0; i < fileHead->numPages; i++)
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

int RM_FileHandle::getBit(int index, char* b)
{
	return b[index / 8] & (1 << (7 - (index % 8)));
}

RC RM_FileHandle::setBit(int index, char* b, int bit)
{
	if (bit == 1)
		b[index / 8] |= (1 << (7 - (index % 8)));
	else
		b[index / 8] &= (255 - (1 << (7 - (index % 8))));
	return OK;
}

//.....................RID
RID::RID() {
	/*
	For this method, init the numbers to -1 to make it a unviable record identifier before given numbers
	*/
	this->pageNum = -1;
	this->slotNum = -1;
}

RID::RID(int pageNum, int slotNum) {
	this->pageNum = pageNum;
	this->slotNum = slotNum;
}

RID::~RID() {

}

RC RID::getPageNum(int &pageNum)const {
	/*
	For this method, it should be a (positive) error
	if the RID object for which the method is called is not a viable record identifier.
	(For example, a RID object will not be a viable record identifier if it was created using the default constructor
	and has not been passed to the RM_Record::GetRid method.)
	If this method succeeds, it should set pageNum to the record identifier's page number.
	*/
	pageNum = this->pageNum;
	if (pageNum < 0) {
		return INVALID_RID;
	}
	return OK;
}

RC RID::getSlotNum(int &slotNum)const {
	/*
	For this method, it should be a (positive) error
	if the RID object for which the method is called is not a viable record identifier.
	If this method succeeds, it should set slotNum to the record identifier's slot number.
	*/
	slotNum = this->slotNum;
	if (slotNum < 0) {
		return INVALID_RID;
	}
	return OK;
}

void RID::setPageNum(int pageNum) {
	this->pageNum = pageNum;
}

void RID::setSlotNum(int slotNum) {
	this->slotNum = slotNum;
}

/*
For this method, it just check out if it is a valid record identifier.
*/
bool RID::checkValid()const {
	return ((pageNum >= 0) && (slotNum >= 0));
}

bool RID::compare(const RID& rid) {
	return (rid.pageNum == this->pageNum && rid.slotNum == this->slotNum);
}
//..................RM_Record
RM_Record::RM_Record() {
	this->pData = nullptr;
}

RM_Record::RM_Record(const char *pData, int record_size, const RID &rid) {
	this->pData = new char[record_size];
	memcpy(this->pData, pData, record_size * sizeof(char));
	this->rid = rid;
}

RM_Record::~RM_Record() {
	delete[]pData;
	this->pData = nullptr;
}

/*
For this method, it should be a (positive) error
if a record has not already been read into the RM_Record object for which the method is called.
This method provides access to the contents (data) of the record.
If the method succeeds, pData should point to the contents of the copy of the record
created by RM_FileHandle::GetRec() or RM_FileScan::GetNextRec().
*/
RC RM_Record::getData(char *&pData)const {

	pData = this->pData;
	if (!checkValid()) {
		return INVALID_RECORD;
	}
	return OK;
}

/*
For this method, it should be a (positive) error
if a record has not already been read into the RM_Record object for which the method is called.
If this method succeeds, rid should contain the identifier for the record.
*/
RC RM_Record::getRid(RID &rid)const {

	rid = this->rid;
	if (!checkValid()) {
		return INVALID_RECORD;
	}
	return OK;
}

RC RM_Record::setData(char* pData) {
	if (!this->pData)
	{
		this->pData = new char[recordSize];
	}
	else {
		delete[]this->pData;
		this->pData = new char[recordSize];
	}
	memcpy(this->pData, pData, recordSize);
	return OK;
}

RC RM_Record::setRid(const RID& rid) {
	int slotNum, pageNum;
	rid.getSlotNum(slotNum);
	rid.getPageNum(pageNum);
	this->rid.setSlotNum(slotNum);
	this->rid.setPageNum(pageNum);
	return OK;
}
bool RM_Record::checkValid()const {
	return rid.checkValid() && (pData != NULL);
}

RM_FileScan::RM_FileScan()
{
}

RM_FileScan::~RM_FileScan()
{
}

RC RM_FileScan::OpenScan(const RM_FileHandle& fileHandle,
	AttrType attrtype,
	int attrLength,
	int attrOffset,
	CompOp compOp,
	void *value)
{
	this->fileHandle = fileHandle;
	this->attrLength = attrLength;
	this->attrtype = attrtype;
	this->attrOffset = attrOffset;
	this->compOp = compOp;
	this->value = value;
	if (fileHandle.fileHead->numPages < 2)
		return ERROR;
	int index;
	b = fileHandle.bpm->getPage(fileHandle.fileID, 1, index);
	bitMap = (char*)b + sizeof(Page_Head);
	return OK;
}

RC RM_FileScan::GetNextRec(RM_Record &rec)
{
	rec.recordSize = fileHandle.fileHead->recordSize + fileHandle.fileHead->attrCount;
	while (true)
	{
		if (currentSlot >= fileHandle.fileHead->maxRecordNumPerPage)
		{
			if (currentPage + 1 == fileHandle.fileHead->numPages)
				return ERROR;
			int index;
			b = fileHandle.bpm->getPage(fileHandle.fileID, currentPage + 1, index);
			bitMap = (char*)b + sizeof(Page_Head);
			currentPage++;
			currentSlot = 0;
		}
		if (fileHandle.getBit(currentSlot, bitMap))
		{
			char* data = (char*)b + fileHandle.getOffset(currentSlot) + fileHandle.fileHead->attrCount + attrOffset ;
			if (attrtype == DINT)
			{
				int recordValue = *(int*)data;
				int givenValue = *(int*)value;
				if (matchRecord(recordValue, givenValue))
				{
					rec.setData((char*)b + fileHandle.getOffset(currentSlot));
					rec.setRid(RID(currentPage, currentSlot));
					currentSlot++;
					return OK;
				}
				else
					currentSlot++;
			}
			else if (attrtype == DFLOAT)
			{
				float recordValue = *(float*)data;
				float givenValue = *(float*)value;
				if (matchRecord(recordValue, givenValue))
				{
					rec.setData((char*)b + fileHandle.getOffset(currentSlot));
					rec.setRid(RID(currentPage, currentSlot));
					currentSlot++;
					return OK;
				}
				else
					currentSlot++;
			}
			else if (attrtype == STRING)
			{
				string recordValue(data);
				string givenValue((char*)value);
				if (matchRecord(recordValue, givenValue))
				{
					rec.setData((char*)b + fileHandle.getOffset(currentSlot));
					rec.setRid(RID(currentPage, currentSlot));
					currentSlot++;
					return OK;
				}
				else
					currentSlot++;
			}
			else
			{
				return ERROR;
			}
		}
		else
		{
			currentSlot++;
		}
	}
}

template<typename T>
bool RM_FileScan::matchRecord(T recordValue, T givenValue) {
	bool recordMatch = false;
	switch (compOp) {
	case EQ_OP:
		if (recordValue == givenValue) recordMatch = true;
		break;
	case LT_OP:
		if (recordValue < givenValue) recordMatch = true;
		break;
	case GT_OP:
		if (recordValue > givenValue) recordMatch = true;
		break;
	case LE_OP:
		if (recordValue <= givenValue) recordMatch = true;
		break;
	case GE_OP:
		if (recordValue >= givenValue) recordMatch = true;
		break;
	case NE_OP:
		if (recordValue != givenValue) recordMatch = true;
		break;
	default:
		break;
	}
	return recordMatch;
}

RC RM_FileScan::CloseScan()
{
	b = nullptr;
	bitMap = nullptr;
	value = nullptr;
	return OK;
}