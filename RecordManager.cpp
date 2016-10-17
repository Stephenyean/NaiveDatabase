#include "RecordManager.h"
#include <cstring>
RM_Manager::RM_Manager(FileManager* fm, BufPageManager* bpm)
{
	this->fm=fm;
	this->bpm=bpm;
}

RM_Manager::~RM_Manager()
{
}

RC RM_Manager::CreateFile(const char * filename, int recordSize)
{
	fm->createFile(filename);
	int fileID;
	fm->openFile(filename,fileID);
	int pageID=0,index;
	BufType b = bpm->allocPage(fileID, pageID, index, false);
	int recordSize_temp=1;
	// assert  recordSize shouldn't be too big
	while(recordSize_temp<recordSize) recordSize_temp = recordSize_temp<<1;

	b[0]=recordSize_temp;
	b[1]=PAGE_SIZE/recordSize_temp-1;
	b[2]=0;
	b=bpm->getPage(fileID,pageID,index);
	cout<<b[0]<<" "<<b[1]<<" "<<b[2]<<" "<<(int)b<<endl;
	bpm->markDirty(index);
	bpm->writeBack(index);
	return PF_FILECREATED;
}

RC RM_Manager::DestroyFile(const char * filename)
{
	return RC();
}

RC RM_Manager::OpenFile(const char * filename, RM_FileHandle & fileHandle)
{
	int fileID;
	fm->openFile(filename,fileID);
	cout<<"fileID: "<<fileID<<endl;
	fileHandle.fileID=fileID;
	fileHandle.fm=this->fm;
	fileHandle.bpm=this->bpm;
	return PF_FILEOPEN;
}

RC RM_Manager::CloseFile(RM_FileHandle & fileHandle)
{
	return RC();
}


RM_FileHandle::RM_FileHandle()
{

}

RM_FileHandle::~RM_FileHandle(){}

RC RM_FileHandle::GetRec         (const RID &rid, RM_Record &rec) const
{
	/*
	int pageID,slotID,index,slotSize;
	rid.GetPageNum(pageID);
	rid.GetSlotNum(slotID);
	BufType b = bpm->getPage(fileID, 0, index);
	slotSize=b[1];
	rec.GetRid()=rid;
	b = bpm->getPage(fileID, pageID, index);
	memcpy(rec.GetData(),(void*)(b+slotSize/4*slotID),slotSize);
	*/
	return OK;
}

RC RM_FileHandle::InsertRec      (const char *pData, RID &rid)
{
	int pageID=0;
	int index;
	cout<<"fileID:: "<<fileID<<endl;
	BufType b = bpm->getPage(fileID, pageID, index);
	int slotSize=b[0];
	int slotNum=b[1];
	int pageSize=b[2];
	int currentPage=0;
	int leftSlot=0;
	bool success=false;
	cout<<slotSize<<" "<<slotNum<<" "<<pageSize<<" "<<(int)b<<endl;
	
	while(currentPage!=pageSize)
	{
		currentPage++;
		pageID=currentPage;
		b = bpm->getPage(fileID, pageID, index);
		leftSlot = b[PAGE_INT_NUM-1];
		if(leftSlot!=0)
		{
			for(int i=0;i<slotNum;i++)
			{
				if((b[2046 - i/32] & 1<<(i%32)) == 0 )
				{
					b[2046 - i/32] = (b[2046 -i/32] | (1<<(i%32)));
					memcpy((void*)(b+slotSize/4*i),pData,strlen(pData));
					bpm->markDirty(index);
					b[PAGE_INT_NUM-1]++;
					cout<<b[PAGE_INT_NUM-1]<<endl;
					rid.SetPageNum(currentPage);
					rid.SetSlotNum(i);
					bpm->writeBack(index);
					break;
				}
			}
			success=true;
			break;
		}
	}

	if(!success)
	{
		pageID=0;
		b = bpm->getPage(fileID, pageID, index);
		b[2]++;
		pageID=b[2];
		bpm->markDirty(index);
		bpm->writeBack(index);
		b = bpm->allocPage(fileID, pageID, index, false);
		//b = bpm->getPage(fileID, pageID, index);
		bpm->markDirty(index);
		cout<<(int)b<<" "<<(int)(b+slotSize/4*slotNum)<<endl;

		memset((void*)(b+slotSize/4*(slotNum)),0,slotSize);
		
		b[PAGE_INT_NUM-1]=1;
		b[2046] =b[2046] | (1<<0);
		cout<<b[2046]<<endl;
		memcpy((void*)(b),pData,strlen(pData));
		rid.SetPageNum(pageID);
		rid.SetSlotNum(0);
		bpm->writeBack(index);
		
	}
	
	return OK;
}

RC RM_FileHandle::DeleteRec      (const RID &rid)
{
	int pageID,slotID,index;
	rid.GetPageNum(pageID);
	rid.GetSlotNum(slotID);
	BufType b = bpm->getPage(fileID, pageID, index);
	b[PAGE_INT_NUM-1]--;
	bpm->markDirty(index);
	b[2046 - slotID/32] = (b[2046 -slotID/32] | (1<<(slotID%32)));
	bpm->writeBack(index);
	return OK;
}

RC RM_FileHandle::UpdateRec      (const RM_Record &rec)
{
	int pageID,slotID,index;
	RID rid;
	rec.GetRid(rid);
	rid.GetPageNum(pageID);
	rid.GetSlotNum(slotID);
	BufType b = bpm->getPage(fileID, 0, index);
	int slotSize = b[1];
	b = bpm->getPage(fileID, pageID, index);
	char* data;rec.GetData(data);
	memcpy((void*)(b+slotSize/4*slotID),data,strlen(data));
	bpm->markDirty(index);
	bpm->writeBack(index);
	return OK;
}

RC RM_FileHandle::ForcePages     (PageNum pageNum) const
{
	int index;
	BufType b = bpm->getPage(fileID, pageNum, index);
	bpm->markDirty(index);
	return OK;
}

//.....................RID
RID::RID(){
	/*
		For this method, init the numbers to -1 to make it a unviable record identifier before given numbers 
	*/
	this->myPageNum = -1;
	this->mySlotNum = -1;
}

RID::RID(int pageNum, int slotNum){
	this->myPageNum = pageNum;
	this->mySlotNum = slotNum;
}

RID::~RID(){
	
}

RC RID::GetPageNum(int &pageNum)const{
	/*
		For this method, it should be a (positive) error 
		if the RID object for which the method is called is not a viable record identifier. 
		(For example, a RID object will not be a viable record identifier if it was created using the default constructor 
		and has not been passed to the RM_Record::GetRid method.) 
		If this method succeeds, it should set pageNum to the record identifier's page number.
	*/
	pageNum = this->myPageNum;
	if(myPageNum < 0){
		return INVALID_RID;
	}
	return OK;
}

RC RID::GetSlotNum(int &slotNum)const{
	/*
		For this method, it should be a (positive) error 
		if the RID object for which the method is called is not a viable record identifier. 
		If this method succeeds, it should set slotNum to the record identifier's slot number.
	*/
	slotNum = this->mySlotNum;
	if(mySlotNum < 0){
		return INVALID_RID;
	}
	return OK;
}

void RID::SetPageNum(int pageNum){
	this->myPageNum = pageNum;
}

void RID::SetSlotNum(int slotNum){
	this->mySlotNum = slotNum;
}

bool RID::checkValid()const{
	/*
		For this method, it just check out if it is a valid record identifier.
	*/
	return ((myPageNum >= 0) && (mySlotNum >= 0));
}

//..................RM_Record
RM_Record::RM_Record(){

}

RM_Record::RM_Record(const char *pData, int record_size, const RID &rid){
	this->myPData=new char[record_size];
	memcpy(this->myPData, pData, record_size * sizeof(char));
	this->myRid=rid;
}

RM_Record::~RM_Record(){

}

RC RM_Record::GetData(char *&pData)const{
	/*
		For this method, it should be a (positive) error 
		if a record has not already been read into the RM_Record object for which the method is called. 
		This method provides access to the contents (data) of the record. 
		If the method succeeds, pData should point to the contents of the copy of the record 
		created by RM_FileHandle::GetRec() or RM_FileScan::GetNextRec().
	*/
	pData = this->myPData;
	if(!checkValid()){
		return INVALID_RECORD;
	}
	return OK;
}

RC RM_Record::GetRid(RID &rid)const{
	/*
		For this method, it should be a (positive) error 
		if a record has not already been read into the RM_Record object for which the method is called. 
		If this method succeeds, rid should contain the identifier for the record.
	*/
	rid = this->myRid;
	if(!checkValid()){
		return INVALID_RECORD;
	}
	return OK;
}

bool RM_Record::checkValid()const{
	return myRid.checkValid();
}