#include "pf_defines.h"
#include "RID_RM_record.h"
class RM_FileScan {
  public:
	RM_FileScan  ();                                // Constructor
	~RM_FileScan ();                                // Destructor
	RC OpenScan     (RM_FileHandle &fileHandle,  // Initialize file scan
					 AttrType      attrType,
					 int           attrLength,
					 int           attrOffset,
					 CompOp        compOp,
					 void          *value,
					 ClientHint    pinHint = NO_HINT);
	RC GetNextRec   (RM_Record &rec);                  // Get next matching record
	RC CloseScan    ();                                // Terminate file scan
private:
	bool isValidSlot(const int & pageNum, const int & slotNum);

	RM_FileHandle &fileHandle;  // Initialize file scan
	AttrType      attrType;
	int           attrLength;
	int           attrOffset;
	CompOp        compOp;
	void          *value;

	int pPageNum;
	int pSlotNum;
	int SlotSize;
	int maxPageNum;
	int maxSlotNum;
	unsigned char * lastRecordMem;

};