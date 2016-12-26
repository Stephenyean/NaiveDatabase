#include "QL_Manager.h"
#include <regex>
#include <algorithm>

QL_Manager::QL_Manager(SM_Manager* smm, IX_Manager* ixm, RM_Manager* rmm)
{
	this->smm = smm;
	this->ixm = ixm;
	this->rmm = rmm;
}
QL_Manager::~QL_Manager()
{
	smm = nullptr;
	ixm = nullptr;
	rmm = nullptr;
}


RC QL_Manager::Insert(const char  *relName, int nValues, vector<Value> values)
{
	if (relName == NULL)
	{
		auto e = new vector<int>;
		return QL_NULL_ERROR;
	}

	if (!smm->IsTableExists(relName))
	{
		return QL_TABLE_NOT_EXIST_ERROR;
	}

	if (verbose == 2) {
		cout << "verbose : " << verbose << endl;
		int i;
		cout << "Insert\n";
		cout << "   relName = " << relName << "\n";
		cout << "   nValues = " << nValues << "\n";
		for (i = 0; i < nValues; i++)
			cout << "   values[" << i << "]:" << values[i].data << "\n";
	}

	RC rc;
	int attrCount = -1;
	AttrInfo* attrInfo;
	if ((rc = smm->GetTableAttrInfo(smm->getWork_Database().c_str(), relName, attrCount, attrInfo)))
	{
		cout << "Error to get Table Attr Info\n";
		return rc;
	}
	
	if (!(attrCount == nValues))
	{
		return QL_INCORRECT_ATTR_COUNT;
	}
	/*
	for (int i = 0; i < attrCount; i++)
	{
		if (values[i].type != attrInfo[i].attrType)
		{
			return QL_INCORRECT_ATTR_TYPE;
		}
	}
	*/
	RM_FileHandle rmFileHandle;
	string fileName = smm->getWork_Database() + "\\" + relName;
	if ((rc = rmm->openFile(fileName.c_str(), rmFileHandle)))
	{
		cout << "Error to open table " << relName << endl;
		return rc;
	}

	IX_IndexHandle* ixIndexHandle = new IX_IndexHandle[attrCount];
	
	int recordSize = 0;

	for (int i = 0; i < attrCount; i++)
	{
		string indexFileName = smm->getWork_Database() + "\\" + relName;
		recordSize += attrInfo[i].attrLength;
		if ((rc = ixm->OpenIndex(indexFileName.c_str(), i, ixIndexHandle[i])))
		{
			cout << "Error to open index " << i << endl;
			return rc;
		}
	}

	
	char* pData = new char[recordSize + nValues];
	
	memset(pData, 0, recordSize + nValues);
	int offset = 0;
	bool* nullValues = new bool[nValues];
	for (int i = 0; i < nValues; i++)
	{
		if (values[i].type == AttrType::NUL)
			nullValues[i] = true;
		else
			nullValues[i] = false;
	}
	for (int i = 0; i < attrCount; i++)
	{
		
		memcpy(pData + offset, values[i].data, std::max(4, (int)strlen((char*)values[i].data) + 1));
		offset += attrInfo[i].attrLength;
	}
	
	RID rid;
	if (rc = rmFileHandle.insertRec(pData, rid, nullValues))
	{
		cout << "Insert record Error \n";
		return rc;
	}

	delete[]nullValues;
	nullValues = nullptr;

	for (int i = 0; i < attrCount; i++)
	{
		if (rc = ixIndexHandle[i].InsertEntry(values[i].data, rid))
		{
			cout << "Insert index Error " << i << endl;
			return rc;
		}
	}
	
	rmm->closeFile(rmFileHandle);
	for (int i = 0; i < attrCount; i++)
	{
		ixm->CloseIndex(ixIndexHandle[i]);
	}
	delete[]ixIndexHandle;
	ixIndexHandle = nullptr;
	delete[]attrInfo;
	attrInfo = nullptr;
	delete pData;
	pData = nullptr;
	return OK;
}


// 0. first judge if the database is open
// 1. judge if the tables exist
// 2. judge if the table has those columns
// 3. 
RC QL_Manager::Select(	int           nSelAttrs,        // # attrs in Select clause
						vector<RelAttr> selAttrs,       // attrs in Select clause
						int           nRelations,       // # relations in From clause
						vector<string> relations, // relations in From clause
						int           nConditions,      // # conditions in Where clause
						vector<Condition> conditions)  // conditions in Where clause
{
	// judge if database is open
	if (smm->getWork_Database().size() <= 0)
	{
		cout << "Database is not open\n";
		return QL_DATABASE_NOT_OPEN;
	}

	// judge if tables exist
	for (int i = 0; i < nRelations; i++)
	{
		if (relations[i].size() <=0)
		{
			cout << "table is NULL\n";
			return QL_NULL_ERROR;
		}
		if (!smm->IsTableExists(relations[i]))
		{
			cout << "table not exist" << endl;
			return QL_TABLE_NOT_EXIST_ERROR;
		}
	}
	RC rc;
	int *attrCount = new int[nRelations];
	AttrInfo** attrInfo = new AttrInfo*[nRelations];

	// get attr info for relations
	for (int i = 0; i < nRelations; i++)
	{
		if ((rc = smm->GetTableAttrInfo(smm->getWork_Database().c_str(), relations[i].c_str(), attrCount[i], attrInfo[i])))
		{
			cout << "Error to get Table Attr Info\n";
			return rc;
		}
	}

	// judge if nSleAttrs = -1

	if (nSelAttrs == -1)
	{
		for (int i = 0; i < nRelations; i++)
		{
			for (int j = 0; j < attrCount[i]; j++)
			{
				RelAttr relAttr;
				relAttr.relName = relations[i];
				relAttr.attrName = attrInfo[i][j].attrName;
				selAttrs.push_back(relAttr);
			}
			nSelAttrs += attrCount[i] + 1;
		}
	}


	// judge if attrName exists
	for (int i = 0; i < nSelAttrs; i++)
	{
		bool found = false;
		for (int j = 0; j < nRelations; j++)
		{
			if (string(selAttrs[i].relName) == string(relations[j]))
			{
				for (int k = 0; k < attrCount[j]; k++)
				{
					if (string(selAttrs[i].attrName) == string(attrInfo[j][k].attrName))
					{
						found = true;
					}
				}

			}
		}
		if (!found)
		{
			cout << "AtrrName Error\n";
			return QL_INCORRECT_ATTR_NAME;
		}
	}

	RM_FileHandle* rmFileHandle = new RM_FileHandle[nRelations];

	for (int i = 0; i < nRelations; i++)
	{
		string fileName = smm->getWork_Database() + "\\" + relations[i];
		rmm->openFile(fileName.c_str(), rmFileHandle[i]);
	}

	IX_IndexHandle ixIndexHandle;

	bool foundCondition = false;
	int iCondition = -1;

	//no condition
	if (nConditions == 0)
	{
		nConditions = 1;
		Condition condition;
		condition.bRhsIsAttr = 0;
		condition.op = NO_OP;
		condition.lhsAttr = selAttrs[0];
		condition.rhsValue = Value();
		condition.rhsValue.type = DINT;
		condition.rhsValue.data = (void*)(new int[1]);
		conditions.push_back(condition);
	}

	//find best condition to scan
	if (!foundCondition)
	{
		for (int i = 0; i < nConditions; i++)
		{
			if (conditions[i].op == EQ_OP)
			{
				iCondition = i;
				foundCondition = true;
				break;
			}
		}
	}
	
	if (!foundCondition)
	{
		for (int i = 0; i < nConditions; i++)
		{
			switch (conditions[i].op)
			{
				case GE_OP:
				case LE_OP:
				case GT_OP:
				case LT_OP:
					iCondition = i;
					foundCondition = true;
					break;
			}
		}
	}

	if (!foundCondition)
	{
		for (int i = 0; i < nConditions; i++)
		{
			if (conditions[i].op == NOTNULL_OP || conditions[i].op == NE_OP)
			{
				iCondition = i;
				foundCondition = true;
				break;
			}
		}
	}
	
	if (!foundCondition)
	{
		iCondition = 0;
		foundCondition = true;
	}

	//single table
	if (nRelations == 1)
	{
		if (conditions[iCondition].bRhsIsAttr != 0)
		{
			// TODO : need to modify
			return ERROR;
		}

		bool found = false;
		int conditionAttrLength;
		for (int i = 0; i < nRelations; i++)
		{
			if (string(relations[i]) == string(conditions[iCondition].lhsAttr.relName))
			{
				for (int k = 0; k < attrCount[i]; k++)
				{
					if (string(conditions[iCondition].lhsAttr.attrName) == string(attrInfo[i][k].attrName))
					{
						string indexFileName = smm->getWork_Database() + "\\" + relations[i];
						if (rc = ixm->OpenIndex(indexFileName.c_str(), k, ixIndexHandle))
						{
							cout << "Error to open Index " << k << endl;
							return ERROR;
						}
						conditionAttrLength = attrInfo[i][k].attrLength;
						found = true;
						break;
					}
				}
			}
			if (found)
				break;
		}
		if (!found)
		{
			cout << "Not found the Attribute\n";
			return QL_INCORRECT_ATTR_TYPE;
		}
		
		// open scan
		IX_IndexScan scan;
		char* data = new char[conditionAttrLength];
		int copyLength = 4;
		if (conditions[iCondition].rhsValue.type == STRING || conditions[iCondition].rhsValue.type == VARCHAR)
			copyLength = strlen((char*)conditions[iCondition].rhsValue.data) + 1;
		memcpy((void*)data, (void*)conditions[iCondition].rhsValue.data, copyLength);
		if (rc = scan.OpenScan(ixIndexHandle, conditions[iCondition].op, data))
		{
			cout << "Error to Open scan\n" << endl;
			return rc;
		}

		// judge other condition satisified
		RID rid;
		RM_Record record;
		while (!(rc = scan.GetNextEntry(rid)))
		{
			if (rc = rmFileHandle[0].getRec(rid, record))
			{
				cout << "Error to get Record\n";
				return rc;
			}
			bool satisfied = true;
			int nRelate = -1, nAttr = -1;
			for (int j = 0; j < nConditions; j++)
			{
				bool found = false;
				for (int i = 0; i < nRelations; i++)
				{
					if (string(conditions[j].lhsAttr.relName) == string(relations[i]))
					{
						for (int k = 0; k < attrCount[i]; k++)
						{
							if (string(conditions[j].lhsAttr.attrName) == string(attrInfo[i][k].attrName))
							{
								nRelate = i;
								nAttr = k;
								found = true;
								break;
							}
						}
					}
					if (found)
						break;
				}
				if (conditions[j].op == ISNULL_OP)
				{
					bool* nullValues = (bool*)record.pData;
					if (!nullValues[nAttr])
					{
						satisfied = false;
						break;
					}
					nullValues = nullptr;
				}
				else if (conditions[j].op == NOTNULL_OP)
				{
					bool* nullValues = (bool*)record.pData;
					if (nullValues[nAttr])
					{
						satisfied = false;
						break;
					}
					nullValues = nullptr;
				}
				else
				{
					if (attrInfo[nRelate][nAttr].attrType == AttrType::DINT)
					{
						int attrOffset = 0;
						for (int i = 0; i < nAttr; i++)
						{
							attrOffset += attrInfo[nRelate][i].attrLength;
						}
						int recordValue = *(int*)(record.pData + attrCount[nRelate] + attrOffset);
						int givenValue = *((int*)(conditions[j].rhsValue.data));
						if (!satisfiesCondition(recordValue, givenValue, conditions[j].op))
						{
							satisfied = false;
							break;
						}
					}
					else if (attrInfo[nRelate][nAttr].attrType == AttrType::STRING)
					{
						int attrOffset = 0;
						for (int i = 0; i < nAttr; i++)
						{
							attrOffset += attrInfo[nRelate][i].attrLength;
						}
						string recordValue = string(record.pData + attrCount[nRelate] + attrOffset);
						string givenValue = string((char*)(conditions[j].rhsValue.data));
						if (!satisfiesCondition(recordValue, givenValue, conditions[j].op))
						{
							satisfied = false;
							break;
						}
					}
				}

			}

			// satisfied then print
			if (satisfied)
			{
				// TODO : need to be modified
				bool * nullValue = (bool*)record.pData;
				int attrOffset = 0;
				for (int i = 0; i < attrCount[nRelate]; i++)
				{
					bool print = false;
					for (auto e : selAttrs)
					{
						if (relations[nRelate] == string(e.relName) && string(attrInfo[nRelate][i].attrName) == string(e.attrName))
						{
							print = true;
							break;
						}
					}
					
					if (print && !nullValue[i])
					{
						cout << i << " : ";
						if (attrInfo[nRelate][i].attrType == AttrType::DINT)
						{
							cout << *(int*)(record.pData + attrCount[nRelate] + attrOffset);
						}
						else if (attrInfo[nRelate][i].attrType == AttrType::STRING)
						{
							cout << (record.pData + attrCount[nRelate] + attrOffset);
						}
						else if (attrInfo[nRelate][i].attrType == AttrType::VARCHAR)
						{
							cout << (record.pData + attrCount[nRelate] + attrOffset);
						}
						else
						{
							return ERROR;
						}
						cout << "		";
					}
					attrOffset += attrInfo[nRelate][i].attrLength;
					
				}
				nullValue = nullptr;
				cout << endl;
			}
		}
	}
	// multiple table
	else if (nRelations == 2)
	{

		if (conditions[iCondition].bRhsIsAttr != 0)
		{
			// need to modify
			return ERROR;
		}

		bool found = false;
		int conditionAttrLength;
		for (int i = 0; i < nRelations; i++)
		{
			if (string(relations[i]) == string(conditions[iCondition].lhsAttr.relName))
			{
				for (int k = 0; k < attrCount[i]; k++)
				{
					if (string(conditions[iCondition].lhsAttr.attrName) == string(attrInfo[i][k].attrName))
					{
						string indexFileName =smm->getWork_Database() + "\\" + relations[i];
						if (rc = ixm->OpenIndex(indexFileName.c_str(), k, ixIndexHandle))
						{
							cout << "Error to open Index " << k << endl;
							return ERROR;
						}
						conditionAttrLength = attrInfo[i][k].attrLength;
						found = true;
						break;
					}
				}
			}
			if (found)
				break;
		}
		if (!found)
		{
			cout << "Not found the Attribute\n";
			return QL_INCORRECT_ATTR_TYPE;
		}

		IX_IndexScan scan;
		char* data = new char[conditionAttrLength];
		int copyLength = 4;
		if (conditions[iCondition].rhsValue.type == STRING || conditions[iCondition].rhsValue.type == VARCHAR)
			copyLength = strlen((char*)conditions[iCondition].rhsValue.data) + 1;
		memcpy((void*)data, (void*)conditions[iCondition].rhsValue.data, copyLength);
		if (rc = scan.OpenScan(ixIndexHandle, conditions[iCondition].op, data))
		{
			cout << "Error to Open scan\n" << endl;
			return rc;
		}

		RID rid;
		RM_Record record;
		while (!(rc = scan.GetNextEntry(rid)))
		{
			if (rc = rmFileHandle[0].getRec(rid, record))
			{
				cout << "Error to get Record\n";
				return rc;
			}
			bool satisfied = true;
			int nRelate = -1, nAttr = -1;
			for (int j = 0; j < nConditions; j++)
			{
				bool found = false;
				for (int i = 0; i < nRelations; i++)
				{
					if (string(conditions[j].lhsAttr.relName) == string(relations[i]))
					{
						for (int k = 0; k < attrCount[i]; k++)
						{
							if (string(conditions[j].lhsAttr.attrName) == string(attrInfo[i][k].attrName))
							{
								nRelate = i;
								nAttr = k;
								found = true;
								break;
							}
						}
					}
					if (found)
						break;
				}
				if (conditions[j].op == ISNULL_OP)
				{
					bool* nullValues = (bool*)record.pData;
					if (!nullValues[nAttr])
					{
						satisfied = false;
						break;
					}
					nullValues = nullptr;
				}
				else if (conditions[j].op == NOTNULL_OP)
				{
					bool* nullValues = (bool*)record.pData;
					if (nullValues[nAttr])
					{
						satisfied = false;
						break;
					}
					nullValues = nullptr;
				}
				else
				{
					if (attrInfo[nRelate][nAttr].attrType == AttrType::DINT)
					{
						int attrOffset = 0;
						for (int i = 0; i < nAttr; i++)
						{
							attrOffset += attrInfo[nRelate][i].attrLength;
						}
						int recordValue = *(int*)(record.pData + attrCount[nRelate] + attrOffset);
						int givenValue = *((int*)(conditions[j].rhsValue.data));
						if (!satisfiesCondition(recordValue, givenValue, conditions[j].op))
						{
							satisfied = false;
							break;
						}
					}
					else if (attrInfo[nRelate][nAttr].attrType == AttrType::STRING)
					{
						int attrOffset = 0;
						for (int i = 0; i < nAttr; i++)
						{
							attrOffset += attrInfo[nRelate][i].attrLength;
						}
						string recordValue = string(record.pData + attrCount[nRelate] + attrOffset);
						string givenValue = string((char*)(conditions[j].rhsValue.data));
						if (!satisfiesCondition(recordValue, givenValue, conditions[j].op))
						{
							satisfied = false;
							break;
						}
					}
				}

			}

			if (satisfied)
			{
				// need to be modified
				bool * nullValue = (bool*)record.pData;
				int attrOffset = 0;
				for (int i = 0; i < attrCount[nRelate]; i++)
				{
					bool print = false;
					for (auto e : selAttrs)
					{
						if (relations[nRelate] == string(e.relName) && string(attrInfo[nRelate][i].attrName) == string(e.attrName))
						{
							print = true;
							break;
						}
					}

					if (print && !nullValue[i])
					{
						cout << i << " : ";
						if (attrInfo[nRelate][i].attrType == AttrType::DINT)
						{
							cout << *(int*)(record.pData + attrCount[nRelate] + attrOffset);
						}
						else if (attrInfo[nRelate][i].attrType == AttrType::STRING)
						{
							cout << (record.pData + attrCount[nRelate] + attrOffset);
						}
						else if (attrInfo[nRelate][i].attrType == AttrType::VARCHAR)
						{
							cout << (record.pData + attrCount[nRelate] + attrOffset);
						}
						else
						{
							return ERROR;
						}
						cout << "		";
					}
					attrOffset += attrInfo[nRelate][i].attrLength;

				}
				nullValue = nullptr;
				cout << endl;
			}
		}
	}

	if (conditions[iCondition].bRhsIsAttr == 1)
	{

	}

	for (int i = 0; i < nRelations; i++)
	{
		rmm->closeFile(rmFileHandle[i]);
	}

	// clear workspace
	delete[]rmFileHandle;
	rmFileHandle = nullptr;
	ixm->CloseIndex(ixIndexHandle);

	return OK;
}


template<typename T>
bool QL_Manager::satisfiesCondition(T key, T value, CompOp compOp) {
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

//1.search index find next rid
//2.delete lastone in ixm
//3.
RC QL_Manager::Delete(const char *relName,            // relation to delete from
	 std::vector<Condition> & conditions)  // conditions in Where clause
{
	// get all attrInfos, judge attrExists
	int attrCount;
	AttrInfo * attributes = NULL;
	if (!CheckAndPreprocess(relName, conditions, attrCount, attributes))
		return ERROR;

	// choose correct condition
	RC rc;
	IX_IndexHandle ixIndexHandle;
	int iCondition = findBestCondition(conditions);
	int iIndex = findCorAttr(attrCount, attributes, conditions[iCondition]);
	string indexFileName = smm->getWork_Database() + "\\" + relName;
	if (rc = ixm->OpenIndex(indexFileName.c_str(), iIndex, ixIndexHandle))
	{
		cout << "Error to open Index " << iIndex << endl;
		return ERROR;
	}
	int conditionAttrLength = attributes[iIndex].attrLength;

	// open rmfileHandle
	RM_FileHandle rmFileHandle;
	string fileName = smm->getWork_Database() + "\\" + relName;
	rmm->openFile(fileName.c_str(), rmFileHandle);

	// open idx scan
	IX_IndexScan ixScan;
	char* data = new char[conditionAttrLength];
	int copyLength = 4;
	if (conditions[iCondition].rhsValue.type == STRING || conditions[iCondition].rhsValue.type == VARCHAR)
		copyLength = strlen((char*)conditions[iCondition].rhsValue.data)+1;
	memcpy((void*)data, (void*)conditions[iCondition].rhsValue.data, copyLength);
	if (rc = ixScan.OpenScan(ixIndexHandle, conditions[iCondition].op, data))
	{
		cout << "Error to Open scan\n" << endl;
		return rc;
	}

	// open deletemode
	RID rid;
	RM_Record record;
	while (!(rc = ixScan.GetNextEntry(rid)))
	{
		isSatisifyConditions(attrCount, attributes, rmFileHandle, ixScan, rid, record, conditions, 1);
	}

	// then delete in rm

	return OK;
}


RC QL_Manager::Update(const char *relName,            // relation to update
	const RelAttr &updAttr,         // attribute to update
	const int bIsValue,             // 0/1 if RHS of = is attribute/value
	const RelAttr &rhsRelAttr,      // attr on RHS of =
	const Value &rhsValue,          // value on RHS of =
	 std::vector<Condition> & conditions)  // conditions in Where clause
{
	return OK;
}

bool QL_Manager::CheckAndPreprocess(const char * relName, std::vector<Condition>& conditions, int & attrCount, AttrInfo *& attributes)
{
	// judge if database is open
	if (smm->getWork_Database().size() <= 0)
	{
		cout << "Database is not open\n";
		return false;
	}

	// judge if tables exist
	if (!smm->IsTableExists(relName))
	{
		cout << "table not exist" << endl;
		return false;
	}

	RC rc;

	// get attr info for relations
	if ((rc = smm->GetTableAttrInfo(smm->getWork_Database().c_str(), relName, attrCount, attributes)))
	{
		cout << "Error to get Table Attr Info\n";
		return false;
	}

	return true;
}

int QL_Manager::findBestCondition(std::vector<Condition> & conditions)
{
	int nConditions = conditions.size();
	bool foundCondition = false;
	int iCondition = -1;

	//no condition
	if (nConditions == 0)
	{
		nConditions = 1;
		Condition condition;
		condition.bRhsIsAttr = 0;
		condition.op = NO_OP;
		/*WARNING : not contain condition.lhsAttr*/
		condition.rhsValue = Value();
		condition.rhsValue.type = DINT;
		condition.rhsValue.data = (void*)(new int[1]);
		conditions.push_back(condition);
	}

	//find best condition to scan
	if (!foundCondition)
	{
		for (int i = 0; i < nConditions; i++)
		{
			if (conditions[i].op == EQ_OP)
			{
				iCondition = i;
				foundCondition = true;
				break;
			}
		}
	}

	if (!foundCondition)
	{
		for (int i = 0; i < nConditions; i++)
		{
			switch (conditions[i].op)
			{
			case GE_OP:
			case LE_OP:
			case GT_OP:
			case LT_OP:
				iCondition = i;
				foundCondition = true;
				break;
			}
		}
	}

	if (!foundCondition)
	{
		for (int i = 0; i < nConditions; i++)
		{
			if (conditions[i].op == NOTNULL_OP || conditions[i].op == NE_OP)
			{
				iCondition = i;
				foundCondition = true;
				break;
			}
		}
	}

	if (!foundCondition)
	{
		iCondition = 0;
		foundCondition = true;
	}
	return iCondition;
}

bool QL_Manager::isSatisifyConditions(int attrCount, AttrInfo * attributes, RM_FileHandle & rmFileHandle, IX_IndexScan & scan, const RID & rid, RM_Record &record, std::vector<Condition> & conditions, int deletemode)
{
	int nConditions = conditions.size();
	// find rid in rmm, put it in the record
	RC rc;
	if (rc = rmFileHandle.getRec(rid, record))
	{
		cout << "Error to get Record\n";
		return false;
	}
	
	// check all conditions
	bool satisfied = true;
	for (int j = 0; j < nConditions; j++)
	{
		// find attr position
		int nAttr = 0;
		for (int k = 0; k < attrCount; k++)
		{
			if (string(conditions[j].lhsAttr.attrName) == string(attributes[k].attrName))
			{
				nAttr = k;
				break;
			}
		}
		if (conditions[j].op == ISNULL_OP)
		{
			bool* nullValues = (bool*)record.pData;
			if (!nullValues[nAttr])
			{
				satisfied = false;
				break;
			}
			nullValues = nullptr;
		}
		else if (conditions[j].op == NOTNULL_OP)
		{
			bool* nullValues = (bool*)record.pData;
			if (nullValues[nAttr])
			{
				satisfied = false;
				break;
			}
			nullValues = nullptr;
		}
		else
		{
			if (attributes[nAttr].attrType == AttrType::DINT)
			{
				int attrOffset = 0;
				for (int i = 0; i < nAttr; i++)
				{
					attrOffset += attributes[i].attrLength;
				}
				int recordValue = *(int*)(record.pData + attrCount + attrOffset);
				int givenValue = *((int*)(conditions[j].rhsValue.data));
				if (!satisfiesCondition(recordValue, givenValue, conditions[j].op))
				{
					satisfied = false;
					break;
				}
			}
			else if (attributes[nAttr].attrType == AttrType::STRING)
			{
				int attrOffset = 0;
				for (int i = 0; i < nAttr; i++)
				{
					attrOffset += attributes[i].attrLength;
				}
				string recordValue = string(record.pData + attrCount + attrOffset);
				string givenValue = string((char*)(conditions[j].rhsValue.data));
				if (conditions[j].op == CompOp::LIKE_OP)
				{
					// replace other regex identifier
					vector<string> regexIds = { "\\", "(", ")", "?", ":", "[", "]", "*", "+","^", "$", "|" };
					for (string regexId : regexIds)
					{
						ReplaceAll(givenValue, regexId, "\\" + regexId);
					}
					// translate sql to regex
					ReplaceAll(givenValue, "_", "(.)");
					ReplaceAll(givenValue, "%", "(.)*");
					// find match
					satisfied = regex_match(recordValue, regex(givenValue));
				}
				else if (!satisfiesCondition(recordValue, givenValue, conditions[j].op))
				{
					satisfied = false;
					break;
				}
			}
		}
	}

	// if deletemode delete it in the rmm and ixm, WARNING NOT IN rmm ?
	if (deletemode && satisfied)
	{
		scan.DeleteCurrentEntry();
		rmFileHandle.deleteRec(rid);
	}
	return satisfied;
}

int QL_Manager::findCorAttr(int attrCount, const AttrInfo * attributes, const Condition & condition)
{
	bool found = false;
	int corAddr = 0;
	for (; corAddr < attrCount; corAddr++)
	{
		if (string(condition.lhsAttr.attrName) == string(attributes[corAddr].attrName))
		{
			found = true;
			break;
		}
	}
	if (found)
		return corAddr;
	else
		return -1;
}

std::string QL_Manager::ReplaceAll(std::string str, const std::string & from, const std::string & to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}
