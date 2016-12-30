#include "RM_FileScan.h"
#include <bitset>
using namespace std;
RC RM_FileScan::OpenScan(RM_FileHandle & fileHandle, AttrType attrType, int attrLength, int attrOffset, CompOp compOp, void * value, ClientHint pinHint)
{
	this->fileHandle = fileHandle;
	this->attrType = attrType;
	this->attrLength = attrLength;
	this->attrOffset = attrOffset;
	this->compOp = compOp;
	this->value = value;
	this->pPageNum = 0;
	this->pSlotNum = -1;

	RM_Record rm_record;
	this->fileHandle.GET(RID(0, 0), rm_record);
	char * data;
	rm_record.GetData(data);
	this->SlotSize = ((int *)data)[0];
	this->maxSlotNum = ((int *)data)[1];
	this->maxPageNum = ((int *)data)[2];
	return OK;
}

RC RM_FileScan::GetNextRec(RM_Record & rec)
{
	do
	{
		char *data;
		
		if (this->pPageNum > this->maxPageNum)
		{
			return RM_EOF:
		}
		//������һҳ
		if (pSlotNum == this->maxSlotNum)
		{
			pPageNum++;
			pSlotNum = -1;
		}
		//ҳ��ʼ����ȡ
		if (pSlotNum == -1)
		{
			RM_Record rm_record;
			this->fileHandle.GetRec(RID(this->pPageNum, this->maxSlotNum), rm_record);
			rm_record.GetData((char *&)this->lastRecordMem);
			pSlotNum++;
		}
		for (; this->pSlotNum < this->maxSlotNum; this->pSlotNum++)
		{
			if (isValidSlot(this->pPageNum, this->pSlotNum))
			{
				char * mem;
				this->fileHandle.GetRec(RID(this->pPageNum, this->maxSlotNum), rec);
				rec.GetData((char *&)mem);
				switch (this->attrType)
				{
				case INT:
				{
					int data;
					memcpy(&data, mem + this->attrOffset, attrLength);
					if (validate(data, *(int *)value, this->compOp))
					{
						this->pSlotNum++;
						return OK;
					}
				}
				case FLOAT:
				{
					float data;
					memcpy(&data, mem + this->attrOffset, attrLength);
					if (validate(data, *(float *)value, this->compOp))
					{
						this->pSlotNum++;
						return OK;
					}
				}
				case STRING:
				{
					if (validate(mem + this->attrOffset, (char *)value, this->compOp))
					{
						this->pSlotNum++;
						return OK;
					}
				}
				case NUL:
				{
					if (validate(value))
					{
						return OK;
					}
					break;
				}

				default:
					break;
				}
			}
		}
		data = nullptr;
	} while (true);

}

RC RM_FileScan::CloseScan()
{
	return OK;
}

bool RM_FileScan::isValidSlot(const int & pageNum, const int & slotNum)
{

	lastRecordMem += (8 << 10);
	lastRecordMem -= (slotNum / 8) + 1;
	int x = slotNum % 8;
	return (((*lastRecordMem) >> x) & 1) == 1;
}

bool validate(const int & lhs, const int & rhs, const CompOp & op) {
	switch (op) {
	case EQ_OP:
		return lhs == rhs;
	case LT_OP:
		return lhs < rhs;
	case GT_OP:
		return lhs > rhs;
	case LE_OP:
		return lhs <= rhs;
	case GE_OP:
		return lhs >= rhs;
	case NE_OP:
		return lhs != rhs;
	default:
		return false;
	}
}

bool validate(const float & lhs, const float & rhs, const CompOp & op) {
	float delta = rhs - lhs;
	switch (op) {
	case EQ_OP:
		return delta < EPS && delta > -EPS;
	case LT_OP:
		return delta < -EPS;
	case GT_OP:
		return delta > EPS;
	case LE_OP:
		return delta < EPS;
	case GE_OP:
		return delta > -EPS;
	case NE_OP:
		return delta > EPS || delta < -EPS;
	default:
		return false;
	}
}

bool validate(const char * lhs, const char * rhs, const CompOp & op) {
	switch (op) {
	case EQ_OP:
		return string(lhs) == string(rhs);
	case NE_OP:
		return string(lhs) != string(rhs);
	default:
		return false;
	}
}

bool validate(const void * value) {
	return value != NULL;
}