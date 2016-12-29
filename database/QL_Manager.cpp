#include "QL_Manager.h"
#include <regex>
#include <algorithm>
#include <set>
#include <algorithm>
#include <iomanip>

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
		//auto e = new vector<int>;
		std::cout << "relation is null\n";
		return QL_NULL_ERROR;
	}

	if (!smm->IsTableExists(relName))
	{
		std::cout << "Table doesn't exist\n";
		return QL_TABLE_NOT_EXIST_ERROR;
	}

	if (verbose == 2) {
		std::cout << "verbose : " << verbose << endl;
		int i;
		std::cout << "Insert\n";
		std::cout << "   relName = " << relName << "\n";
		std::cout << "   nValues = " << nValues << "\n";
		for (i = 0; i < nValues; i++)
			std::cout << "   values[" << i << "]:" << values[i].data << "\n";
	}

	RC rc;
	int attrCount = -1;
	AttrInfo* attrInfo;
	int primaryIndex;
	if ((rc = smm->GetTableAttrInfo(smm->getWork_Database().c_str(), relName, attrCount, attrInfo, primaryIndex)))
	{
		std::cout << "Error to get Table Attr Info\n";
		return rc;
	}

	for (int i = 0; i < values.size(); i++)
	{
		if (values[i].type != AttrType::NUL && attrInfo[i].attrType != values[i].type)
		{
			if (attrInfo[i].attrType == STRING && values[i].type == VARCHAR)
				continue;
			if (attrInfo[i].attrType == VARCHAR && values[i].type == STRING)
				continue;
			std::cout << "Type Error\n";
			return ERROR;
		}
		if (attrInfo[i].notnull && (values[i].type == AttrType::NUL))
		{
			std::cout << attrInfo[i].attrName << " shouldn't be null" << endl;
			return ERROR;
		}
	}
	
	if (!(attrCount == nValues))
	{
		std::cout << "arguments not enough\n";
		return QL_INCORRECT_ATTR_COUNT;
	}

	RM_FileHandle rmFileHandle;
	string fileName = smm->getWork_Database() + "\\" + relName;
	if ((rc = rmm->openFile(fileName.c_str(), rmFileHandle)))
	{
		std::cout << "Error to open table " << relName << endl;
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
			std::cout << "Error to open index " << i << endl;
			return rc;
		}
	}
	assert(primaryIndex < (int)values.size());
	if (primaryIndex >= 0)
	{
		IX_IndexScan scan;
		if ((rc = scan.OpenScan(ixIndexHandle[primaryIndex], CompOp::EQ_OP, values[primaryIndex].data)) == OK)
		{
			std::cout << "Duplicate Primary Key\n";
			return ERROR;
		}
		scan.CloseScan();
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
		int copyLength = 4;
		if (attrInfo[i].attrType == STRING || attrInfo[i].attrType == VARCHAR)
			copyLength = strlen((char*)values[i].data) + 1;
		memcpy(pData + offset, values[i].data, copyLength);
		offset += attrInfo[i].attrLength;
	}
	
	RID rid;
	if (rc = rmFileHandle.insertRec(pData, rid, nullValues))
	{
		std::cout << "Insert record Error \n";
		return rc;
	}

	delete[]nullValues;
	nullValues = nullptr;
	for (int i = 0; i < attrCount; i++)
	{
		if (values[i].type == AttrType::NUL)
		{
			if (attrInfo[i].attrType == DINT)
			{
				values[i].data = (void*)(new int[1]);
				*((int*)values[i].data) = -99999999;
			}
			else
			{
				values[i].data = (void*)(new char[3]);
				((char*)values[i].data)[0] = '\n';
				((char*)values[i].data)[1] = '\n';
				((char*)values[i].data)[2] = '\0';
			}
		}
		if (rc = ixIndexHandle[i].InsertEntry(values[i].data, rid))
		{
			std::cout << "Insert index Error " << i << endl;
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
						vector<Condition> conditions,  // conditions in Where clause
						hsql::SelectStatement * stmt)
{
	// judge if database is open
	if (smm->getWork_Database().size() <= 0)
	{
		std::cout << "Database is not open\n";
		return QL_DATABASE_NOT_OPEN;
	}

	// judge if tables exist
	for (int i = 0; i < nRelations; i++)
	{
		if (relations[i].size() <=0)
		{
			std::cout << "table is NULL\n";
			return QL_NULL_ERROR;
		}
		if (!smm->IsTableExists(relations[i]))
		{
			std::cout << "table not exist" << endl;
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
			std::cout << "Error to get Table Attr Info\n";
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
			nSelAttrs += attrCount[i];
		}
		nSelAttrs++;
	}

	/*if (type != hsql::SelectStatement::SelectType::NO_OP)
	{
		assert(nSelAttrs == 1);
	}*/

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
			std::cout << "AtrrName Error\n";
			return QL_INCORRECT_ATTR_NAME;
		}
	}

	RM_FileHandle* rmFileHandle = new RM_FileHandle[nRelations];

	for (int i = 0; i < nRelations; i++)
	{
		string fileName = smm->getWork_Database() + "\\" + relations[i];
		rmm->openFile(fileName.c_str(), rmFileHandle[i]);
	}

	IX_IndexHandle ixIndexHandle, ixIndexHandle2;

	bool foundCondition = false;
	int iCondition = -1;
	vector<vector<string>> results;

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
			if (conditions[i].op == EQ_OP && conditions[i].bRhsIsAttr == 0)
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
			if (!(conditions[i].bRhsIsAttr == 0))
				continue;
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
		iCondition = 0;
		foundCondition = true;
	}

	int indexRelate, indexAttr;
	int indexRelate2, indexAttr2;
	IX_IndexScan scan1;
	IX_IndexScan scan2;

	if (nRelations == 1)
	{
		vector<string> printNames;
		for (int i = 0; i < attrCount[0]; i++)
		{
			bool print = false;
			for (auto e : selAttrs)
			{
				if (relations[0] == string(e.relName) && string(attrInfo[0][i].attrName) == string(e.attrName))
				{
					print = true;
					break;
				}
			}
			if (print)
				printNames.push_back(string(attrInfo[0][i].attrName));
		}
		results.push_back(printNames);
		if (conditions[iCondition].bRhsIsAttr == 1)
		{
			RM_FileScan rmScan;
			void * value = (void*)(new int[1]);
			if (rc = rmScan.OpenScan(rmFileHandle[0], attrInfo[0][0].attrType, attrInfo[0][0].attrLength, 0, CompOp::NO_OP, value))
			{
				std::cout << "Error to open rmscan \n";
				return ERROR;
			}

			RM_Record rec;
			
			while (! rmScan.GetNextRec(rec))
			{
				bool satisfied = true;
				vector<string> result;
				for (int i = 0; i < conditions.size(); i++)
				{

					if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[i], relations, false))
					{
						std::cout << "Error to find correct attribute" << endl;
						return ERROR;
					}
					if (rc = findCorAttr(indexRelate2, indexAttr2, attrCount, attrInfo, conditions[i], relations, true))
					{
						std::cout << "Error to find correct attribute" << endl;
						return ERROR;
					}

					int offset1 = getOffset(indexRelate, indexAttr, attrInfo);
					int offset2 = getOffset(indexRelate2, indexAttr2, attrInfo);
					if (!isRecordSatisfied((void*)(rec.pData + attrCount[0] + offset1), conditions[i].op, (void*)(rec.pData + attrCount[0] + offset2), attrInfo[0][indexAttr].attrType))
					{
						satisfied = false;
						break;
					}
				}

				if (satisfied)
				{
					print(rec, attrCount, 0, selAttrs, relations, attrInfo, result);
					results.push_back(result);
				}
			}
		}
		else
		{
			
			if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[iCondition], relations, false))
			{
				std::cout << "Error to find correct attribute" << endl;
				return ERROR;
			}

			string indexFileName = smm->getWork_Database() + "\\" + relations[0];
			if (rc = ixm->OpenIndex(indexFileName.c_str(), indexAttr, ixIndexHandle))
			{
				std::cout << "Error to open Index " << indexAttr << endl;
				return ERROR;
			}
			int conditionAttrLength = attrInfo[0][indexAttr].attrLength;
			char* data = new char[conditionAttrLength];
			memset(data, 0, conditionAttrLength);
			
			int copyLength = 4;
			if (conditions[iCondition].rhsValue.type == STRING || conditions[iCondition].rhsValue.type == VARCHAR)
				copyLength = strlen((char*)conditions[iCondition].rhsValue.data) + 1;
			memcpy((void*)data, (void*)conditions[iCondition].rhsValue.data, copyLength);
			if (rc = scan1.OpenScan(ixIndexHandle, conditions[iCondition].op, data))
			{
				std::cout << "Error to Open scan\n" << endl;
				return rc;
			}
			RID rid;
			RM_Record rec;
			while (!(rc = scan1.GetNextEntry(rid)))
			{
				vector<string> result;
				if (rc = rmFileHandle[0].getRec(rid, rec))
				{
					std::cout << "Error to get Record\n";
					return rc;
				}
				bool satisfied = true;
				for (int j = 0; j < nConditions; j++)
				{
					if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[j], relations, false))
					{
						std::cout << "Error to find correct attribute" << endl;
						return ERROR;
					}
					if (conditions[j].op == ISNULL_OP)
					{
						bool* nullValues = (bool*)rec.pData;
						if (!nullValues[indexAttr])
						{
							satisfied = false;
							break;
						}
						nullValues = nullptr;
					}
					else if (conditions[j].op == NOTNULL_OP)
					{
						bool* nullValues = (bool*)rec.pData;
						if (nullValues[indexAttr])
						{
							satisfied = false;
							break;
						}
						nullValues = nullptr;
					}
					else
					{
						int offset1 = getOffset(indexRelate, indexAttr, attrInfo);
						
						if (conditions[j].bRhsIsAttr)
						{
							int offset2 = getOffset(indexRelate2, indexAttr2, attrInfo);
							if (rc = findCorAttr(indexRelate2, indexAttr2, attrCount, attrInfo, conditions[j], relations, true))
							{
								std::cout << "Error to find correct attribute" << endl;
								return ERROR;
							}
							if (!isRecordSatisfied((void*)(rec.pData + attrCount[0] + offset1), conditions[j].op, (void*)(rec.pData + attrCount[0] + offset2), attrInfo[0][indexAttr].attrType))
							{
								satisfied = false;
							}
						}
						else
						{
							if (!isRecordSatisfied((void*)(rec.pData + attrCount[0] + offset1), conditions[j].op, conditions[j].rhsValue.data, attrInfo[0][indexAttr].attrType))
							{
								satisfied = false;
							}
						}
					}
					if (!satisfied)
						break;
				}
				if (satisfied)
				{
					print(rec, attrCount, 0, selAttrs, relations, attrInfo, result);
					results.push_back(result);
				}
			}

		}
	}
	else if (nRelations == 2)
	{
		if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[iCondition], relations, false))
		{
			std::cout << "Error to find correct attribute" << endl;
			return ERROR;
		}
		vector<string> printNames;
		for (int i = 0; i < attrCount[indexRelate]; i++)
		{
			bool print = false;
			for (auto e : selAttrs)
			{
				if (relations[indexRelate] == string(e.relName) && string(attrInfo[indexRelate][i].attrName) == string(e.attrName))
				{
					print = true;
					break;
				}
			}
			if (print)
				printNames.push_back(string(attrInfo[indexRelate][i].attrName));
		}
		for (int i = 0; i < attrCount[1 - indexRelate]; i++)
		{
			bool print = false;
			for (auto e : selAttrs)
			{
				if (relations[1 - indexRelate] == string(e.relName) && string(attrInfo[1 - indexRelate][i].attrName) == string(e.attrName))
				{
					print = true;
					break;
				}
			}
			if (print)
				printNames.push_back(string(attrInfo[indexRelate][i].attrName));
		}
		results.push_back(printNames);
		if (conditions[iCondition].bRhsIsAttr == 1 && conditions[iCondition].op == CompOp::EQ_OP)
		{
			set<pair<RID, RID>> recV;
			{
				if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[iCondition], relations, false))
				{
					std::cout << "Error to find correct attribute" << endl;
					return ERROR;
				}
				if (rc = findCorAttr(indexRelate2, indexAttr2, attrCount, attrInfo, conditions[iCondition], relations, true))
				{
					std::cout << "Error to find correct attribute" << endl;
					return ERROR;
				}
				string indexFileName1 = smm->getWork_Database() + "\\" + relations[indexRelate];
				if (rc = ixm->OpenIndex(indexFileName1.c_str(), indexAttr, ixIndexHandle))
				{
					std::cout << "Error to open Index " << indexAttr << endl;
					return ERROR;
				}
				string indexFileName = smm->getWork_Database() + "\\" + relations[indexRelate2];
				if (rc = ixm->OpenIndex(indexFileName.c_str(), indexAttr2, ixIndexHandle2))
				{
					std::cout << "Error to open Index " << indexAttr2 << endl;
					return ERROR;
				}
				if (rc = scan1.OpenScan(ixIndexHandle, NO_OP, (void*)(new int[1])))
				{
					std::cout << "Error to open ixscan1 \n";
					return ERROR;
				}
				if (rc = scan2.OpenScan(ixIndexHandle2, NO_OP, (void*)(new int[1])))
				{
					std::cout << "Error to open ixscan2 \n";
					return ERROR;
				}
				RID rid1, rid2;
				RM_Record rec1, rec2;
				int offset1 = getOffset(indexRelate, indexAttr, attrInfo);
				int offset2 = getOffset(indexRelate2, indexAttr2, attrInfo);
				if ((rc = scan1.GetNextEntry(rid1)))
				{
					std::cout << "Table 1 empty\n" << endl;
				}
				if (rc = rmFileHandle[indexRelate].getRec(rid1, rec1))
				{
					std::cout << "Error to get record\n";
				}
				if ((rc = scan2.GetNextEntry(rid2)))
				{
					std::cout << "Table 2 empty\n" << endl;
				}
				if (rc = rmFileHandle[indexRelate2].getRec(rid2, rec2))
				{
					std::cout << "Error to get record\n";
				}
				int judge = 0;
				while (true)
				{
					if (isRecordSatisfied((void*)(rec1.pData + attrCount[indexRelate] + offset1), CompOp::EQ_OP, (void*)(rec2.pData + attrCount[indexRelate2] + offset2), attrInfo[indexRelate][indexAttr].attrType))
					{
						recV.insert(make_pair(rid1, rid2));
						judge = 0;
					}
					else if (isRecordSatisfied((void*)(rec1.pData + attrCount[indexRelate] + offset1), CompOp::GT_OP, (void*)(rec2.pData + attrCount[indexRelate2] + offset2), attrInfo[indexRelate][indexAttr].attrType))
					{
						judge = -1;
					}
					else
					{
						judge = 1;
					}
					if (judge == 0)
					{
						if (rc = scan1.GetNextEntry(rid1))
						{
							break;
						}
						if (rc = rmFileHandle[indexRelate].getRec(rid1, rec1))
						{
							std::cout << "Error to get record\n";
						}
					}
					else if (judge == -1)
					{
						if (rc = scan2.GetNextEntry(rid2))
						{
							break;
						}
						if (rc = rmFileHandle[indexRelate2].getRec(rid2, rec2))
						{
							std::cout << "Error to get record\n";
						}
					}
					else
					{
						if (rc = scan1.GetNextEntry(rid1))
						{
							break;
						}
						if (rc = rmFileHandle[indexRelate].getRec(rid1, rec1))
						{
							std::cout << "Error to get record\n";
						}
					}
				}
			}
			{
				if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[iCondition], relations, false))
				{
					std::cout << "Error to find correct attribute" << endl;
					return ERROR;
				}
				if (rc = findCorAttr(indexRelate2, indexAttr2, attrCount, attrInfo, conditions[iCondition], relations, true))
				{
					std::cout << "Error to find correct attribute" << endl;
					return ERROR;
				}
				string indexFileName1 = smm->getWork_Database() + "\\" + relations[indexRelate];
				if (rc = ixm->OpenIndex(indexFileName1.c_str(), indexAttr, ixIndexHandle))
				{
					std::cout << "Error to open Index " << indexAttr << endl;
					return ERROR;
				}
				string indexFileName = smm->getWork_Database() + "\\" + relations[indexRelate2];
				if (rc = ixm->OpenIndex(indexFileName.c_str(), indexAttr2, ixIndexHandle2))
				{
					std::cout << "Error to open Index " << indexAttr2 << endl;
					return ERROR;
				}
				if (rc = scan1.OpenScan(ixIndexHandle, NO_OP, (void*)(new int[1])))
				{
					std::cout << "Error to open ixscan1 \n";
					return ERROR;
				}
				if (rc = scan2.OpenScan(ixIndexHandle2, NO_OP, (void*)(new int[1])))
				{
					std::cout << "Error to open ixscan2 \n";
					return ERROR;
				}
				RID rid1, rid2;
				RM_Record rec1, rec2;
				int offset1 = getOffset(indexRelate, indexAttr, attrInfo);
				int offset2 = getOffset(indexRelate2, indexAttr2, attrInfo);
				if ((rc = scan1.GetNextEntry(rid1)))
				{
					std::cout << "Table 1 empty\n" << endl;
				}
				if (rc = rmFileHandle[indexRelate].getRec(rid1, rec1))
				{
					std::cout << "Error to get record\n";
				}
				if ((rc = scan2.GetNextEntry(rid2)))
				{
					std::cout << "Table 2 empty\n" << endl;
				}
				if (rc = rmFileHandle[indexRelate2].getRec(rid2, rec2))
				{
					std::cout << "Error to get record\n";
				}
				int judge = 0;
				while (true)
				{
					if (isRecordSatisfied((void*)(rec1.pData + attrCount[indexRelate] + offset1), CompOp::EQ_OP, (void*)(rec2.pData + attrCount[indexRelate2] + offset2), attrInfo[indexRelate][indexAttr].attrType))
					{
						recV.insert(make_pair(rid1, rid2));
						judge = 0;
					}
					else if (isRecordSatisfied((void*)(rec1.pData + attrCount[indexRelate] + offset1), CompOp::GT_OP, (void*)(rec2.pData + attrCount[indexRelate2] + offset2), attrInfo[indexRelate][indexAttr].attrType))
					{
						judge = -1;
					}
					else
					{
						judge = 1;
					}
					if (judge == 0)
					{
						if (rc = scan2.GetNextEntry(rid2))
						{
							break;
						}
						if (rc = rmFileHandle[indexRelate2].getRec(rid2, rec2))
						{
							std::cout << "Error to get record\n";
						}
					}
					else if (judge == -1)
					{
						if (rc = scan2.GetNextEntry(rid2))
						{
							break;
						}
						if (rc = rmFileHandle[indexRelate2].getRec(rid2, rec2))
						{
							std::cout << "Error to get record\n";
						}
					}
					else
					{
						if (rc = scan1.GetNextEntry(rid1))
						{
							break;
						}
						if (rc = rmFileHandle[indexRelate].getRec(rid1, rec1))
						{
							std::cout << "Error to get record\n";
						}
					}
				}
			}
			for (auto e: recV)
			{
				RM_Record rec1, rec2;
				rmFileHandle[indexRelate].getRec(e.first, rec1);
				rmFileHandle[indexRelate2].getRec(e.second, rec2);
				bool satisfied = true;
				for (int i = 0; i < conditions.size(); i++)
				{
					if (i == iCondition) continue;
					if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[i], relations, false))
					{
						std::cout << "Error to find correct attribute" << endl;
						return ERROR;
					}
					if (rc = findCorAttr(indexRelate2, indexAttr2, attrCount, attrInfo, conditions[i], relations, true))
					{
						std::cout << "Error to find correct attribute" << endl;
						return ERROR;
					}
					int offset1 = getOffset(indexRelate, indexAttr, attrInfo);
					int offset2 = getOffset(indexRelate2, indexAttr2, attrInfo);
					if (!isRecordSatisfied((void*)(rec1.pData + attrCount[indexRelate] + offset1), conditions[i].op, (void*)(rec2.pData + attrCount[indexRelate2] + offset2), attrInfo[indexRelate][indexAttr].attrType))
					{
						satisfied = false;
						break;
					}
				}
				vector<string> result;
				if (satisfied)
				{
					print(rec1, attrCount, indexRelate, selAttrs, relations, attrInfo, result);
					print(rec2, attrCount, indexRelate2, selAttrs, relations, attrInfo, result);
					results.push_back(result);
				}
			}

		}
		else if(conditions[iCondition].bRhsIsAttr == 1)
		{
			vector<RM_Record> recV1;
			vector<RM_Record> recV2;
			RM_FileScan rmScan1, rmScan2;
			void * value = (void*)(new int[1]);
			if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[iCondition], relations, false))
			{
				std::cout << "Error to find correct attribute" << endl;
				return ERROR;
			}
			if (rc = findCorAttr(indexRelate2, indexAttr2, attrCount, attrInfo, conditions[iCondition], relations, true))
			{
				std::cout << "Error to find correct attribute" << endl;
				return ERROR;
			}
			if (rc = rmScan1.OpenScan(rmFileHandle[indexRelate], attrInfo[indexRelate][indexAttr].attrType, attrInfo[indexRelate][0].attrLength, 0, CompOp::NO_OP, value))
			{
				std::cout << "Error to open rmscan1 \n";
				return ERROR;
			}
			if (rc = rmScan2.OpenScan(rmFileHandle[indexRelate2], attrInfo[indexRelate2][indexAttr2].attrType, attrInfo[indexRelate2][0].attrLength, 0, CompOp::NO_OP, value))
			{
				std::cout << "Error to open rmscan2 \n";
				return ERROR;
			}

			//RM_Record rec;
			do {
				RM_Record rec;
				recV1.push_back(rec);
			} while (!rmScan1.GetNextRec(recV1[recV1.size() - 1]));

			do {
				RM_Record rec;
				recV2.push_back(rec);
			} while (!rmScan2.GetNextRec(recV2[recV2.size() - 1]));
			recV1.pop_back();
			recV2.pop_back();
			for (auto rec1 : recV1)
			{
				for (auto rec2 : recV2)
				{
					bool satisfied = true;
					for (int i = 0; i < conditions.size(); i++)
					{
						if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[i], relations, false))
						{
							std::cout << "Error to find correct attribute" << endl;
							return ERROR;
						}
						if (rc = findCorAttr(indexRelate2, indexAttr2, attrCount, attrInfo, conditions[i], relations, true))
						{
							std::cout << "Error to find correct attribute" << endl;
							return ERROR;
						}
						int offset1 = getOffset(indexRelate, indexAttr, attrInfo);
						int offset2 = getOffset(indexRelate2, indexAttr2, attrInfo);
						if (!isRecordSatisfied((void*)(rec1.pData + attrCount[indexRelate] + offset1), conditions[i].op, (void*)(rec2.pData + attrCount[indexRelate2] + offset2), attrInfo[indexRelate][indexAttr].attrType))
						{
							satisfied = false;
							break;
						}
					}
					vector<string> result;
					if (satisfied)
					{
						print(rec1, attrCount, indexRelate, selAttrs, relations, attrInfo, result);
						print(rec2, attrCount, indexRelate2, selAttrs, relations, attrInfo, result);
						results.push_back(result);
					}
				}
			}

		}
		else
		{
			if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[iCondition], relations, false))
			{
				std::cout << "Error to find correct attribute" << endl;
				return ERROR;
			}

			string indexFileName = smm->getWork_Database() + "\\" + relations[indexRelate];
			if (rc = ixm->OpenIndex(indexFileName.c_str(), indexAttr, ixIndexHandle))
			{
				std::cout << "Error to open Index " << indexAttr << endl;
				return ERROR;
			}
			int conditionAttrLength = attrInfo[indexRelate][indexAttr].attrLength;
			char* data = new char[conditionAttrLength];
			memset(data, 0, conditionAttrLength);
			int copyLength = 4;
			if (conditions[iCondition].rhsValue.type == STRING || conditions[iCondition].rhsValue.type == VARCHAR)
				copyLength = strlen((char*)conditions[iCondition].rhsValue.data) + 1;
			memcpy((void*)data, (void*)conditions[iCondition].rhsValue.data, copyLength);
			if (rc = scan1.OpenScan(ixIndexHandle, conditions[iCondition].op, data))
			{
				std::cout << "Error to Open scan\n" << endl;
				return rc;
			}
			RID rid;
			RM_Record rec1,rec2;
			indexRelate2 = 1 - indexRelate;
			indexAttr2 = 0;
			int realRelate1 = indexRelate;
			int realRelate2 = indexRelate2;
			string relation1 = relations[indexRelate];
			string relation2 = relations[indexRelate2];
			while (!(rc = scan1.GetNextEntry(rid)))
			{
				if (rc = rmFileHandle[realRelate1].getRec(rid, rec1))
				{
					std::cout << "Error to get Record\n";
					return rc;
				}
				RM_FileScan rmScan2;
				if (rc = rmScan2.OpenScan(rmFileHandle[realRelate2], attrInfo[indexRelate2][indexAttr2].attrType, attrInfo[indexRelate2][0].attrLength, 0, CompOp::NO_OP, new int[1]))
				{
					std::cout << "Error to open rmscan2 \n";
					return ERROR;
				}
				bool satisfied1 = true;
				for (int j = 0; j < conditions.size(); j++)
				{
					if (conditions[j].lhsAttr.relName != string(relation1))
						continue;
					if (conditions[j].bRhsIsAttr && conditions[j].rhsAttr.relName != string(relation1))
						continue;

					if (conditions[j].op == ISNULL_OP)
					{
						bool* nullValues = (bool*)rec1.pData;
						if (!nullValues[indexAttr])
						{
							satisfied1 = false;
							break;
						}
						nullValues = nullptr;
					}
					else if (conditions[j].op == NOTNULL_OP)
					{
						bool* nullValues = (bool*)rec1.pData;
						if (nullValues[indexAttr])
						{
							satisfied1 = false;
							break;
						}
						nullValues = nullptr;
					}
					else
					{
						if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[j], relations, false))
						{
							std::cout << "Error to find correct attribute" << endl;
							return ERROR;
						}
						int offset1 = getOffset(indexRelate, indexAttr, attrInfo);

						if (conditions[j].bRhsIsAttr)
						{

							if (rc = findCorAttr(indexRelate2, indexAttr2, attrCount, attrInfo, conditions[j], relations, true))
							{
								std::cout << "Error to find correct attribute" << endl;
								return ERROR;
							}
							int offset2 = getOffset(indexRelate2, indexAttr2, attrInfo);
							if (!isRecordSatisfied((void*)(rec1.pData + attrCount[indexRelate] + offset1), conditions[j].op, (void*)(rec1.pData + attrCount[indexRelate2] + offset2), attrInfo[indexRelate][indexAttr].attrType))
							{
								satisfied1 = false;
							}
						}
						else
						{
							if (!isRecordSatisfied((void*)(rec1.pData + attrCount[indexRelate] + offset1), conditions[j].op, conditions[j].rhsValue.data, attrInfo[indexRelate][indexAttr].attrType))
							{
								satisfied1 = false;
							}
						}
					}
					
				}
				if (satisfied1 == false)
					continue;
				while (!(rc = rmScan2.GetNextRec(rec2)))
				{
					bool satisfied = true;
					for (int j = 0; j < conditions.size(); j++)
					{
						if (conditions[j].lhsAttr.relName != string(relation2))
							continue;
						if (conditions[j].bRhsIsAttr && conditions[j].rhsAttr.relName != string(relation2))
							continue;

						if (conditions[j].op == ISNULL_OP)
						{
							bool* nullValues = (bool*)rec2.pData;
							if (!nullValues[indexAttr])
							{
								satisfied = false;
								break;
							}
							nullValues = nullptr;
						}
						else if (conditions[j].op == NOTNULL_OP)
						{
							bool* nullValues = (bool*)rec2.pData;
							if (nullValues[indexAttr])
							{
								satisfied = false;
								break;
							}
							nullValues = nullptr;
						}
						else
						{
							if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[j], relations, false))
							{
								std::cout << "Error to find correct attribute" << endl;
								return ERROR;
							}
							int offset1 = getOffset(indexRelate, indexAttr, attrInfo);

							if (conditions[j].bRhsIsAttr)
							{

								if (rc = findCorAttr(indexRelate2, indexAttr2, attrCount, attrInfo, conditions[j], relations, true))
								{
									std::cout << "Error to find correct attribute" << endl;
									return ERROR;
								}
								int offset2 = getOffset(indexRelate2, indexAttr2, attrInfo);
								if (!isRecordSatisfied((void*)(rec2.pData + attrCount[indexRelate] + offset1), conditions[j].op, (void*)(rec2.pData + attrCount[indexRelate2] + offset2), attrInfo[indexRelate][indexAttr].attrType))
								{
									satisfied = false;
								}
							}
							else
							{
								if (!isRecordSatisfied((void*)(rec2.pData + attrCount[indexRelate] + offset1), conditions[j].op, conditions[j].rhsValue.data, attrInfo[indexRelate][indexAttr].attrType))
								{
									satisfied = false;
								}
							}
						}

					}
					if (satisfied == false)
						continue;
					
					for (int i = 0; i < conditions.size(); i++)
					{
						if (i == iCondition) continue;
						if ((!conditions[i].bRhsIsAttr) || (conditions[i].lhsAttr.relName == conditions[i].rhsAttr.relName))
							continue;
						if (rc = findCorAttr(indexRelate, indexAttr, attrCount, attrInfo, conditions[i], relations, false))
						{
							std::cout << "Error to find correct attribute" << endl;
							return ERROR;
						}
						if (rc = findCorAttr(indexRelate2, indexAttr2, attrCount, attrInfo, conditions[i], relations, true))
						{
							std::cout << "Error to find correct attribute" << endl;
							return ERROR;
						}
						int offset1 = getOffset(indexRelate, indexAttr, attrInfo);
						int offset2 = getOffset(indexRelate2, indexAttr2, attrInfo);
						if (!isRecordSatisfied((void*)(rec1.pData + attrCount[indexRelate] + offset1), conditions[i].op, (void*)(rec2.pData + attrCount[indexRelate2] + offset2), attrInfo[indexRelate][indexAttr].attrType))
						{
							satisfied = false;
							break;
						}
					}
					vector<string> result;
					if (satisfied)
					{
						print(rec1, attrCount, realRelate1, selAttrs, relations, attrInfo, result);
						print(rec2, attrCount, realRelate2, selAttrs, relations, attrInfo, result);
						results.push_back(result);
					}
				}

			}
		}
	}

	for (int i = 0; i < nRelations; i++)
	{
		rmm->closeFile(rmFileHandle[i]);
	}
	
	for (auto rv : results)
	{
		for (auto rec : rv)
		{
			cout << setw(25) << std::left << rec;
		}
		cout << endl;
	}
	// clear workspace
	delete[]rmFileHandle;
	rmFileHandle = nullptr;
	ixm->CloseIndex(ixIndexHandle);

	return OK;
}

RC QL_Manager::print(RM_Record& record, int* attrCount, int nRelate, vector<RelAttr> selAttrs, vector<string> relations, AttrInfo** attrInfo, vector<string>& result)
{
	bool * nullValue = (bool*)record.pData;
	int attrOffset = 0;
	//vector<string> result;
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
			//std::cout << i << " : ";
			if (attrInfo[nRelate][i].attrType == AttrType::DINT)
			{
				//std::cout << *(int*)(record.pData + attrCount[nRelate] + attrOffset);
				result.push_back(std::to_string(*(int*)(record.pData + attrCount[nRelate] + attrOffset)));

			}
			else if (attrInfo[nRelate][i].attrType == AttrType::STRING)
			{
				//std::cout << (record.pData + attrCount[nRelate] + attrOffset);
				result.push_back(std::string(record.pData + attrCount[nRelate] + attrOffset));
			}
			else if (attrInfo[nRelate][i].attrType == AttrType::VARCHAR)
			{
				result.push_back(std::string(record.pData + attrCount[nRelate] + attrOffset));
				//std::cout << (record.pData + attrCount[nRelate] + attrOffset);
			}
			else
			{
				return ERROR;
			}
			//std::cout << "		";
		}
		else if (print)
			result.push_back("null");
		attrOffset += attrInfo[nRelate][i].attrLength;

	}
	nullValue = nullptr;
	//std::cout << endl;
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
	int iIndex = findCorAttr(attrCount, attributes, conditions[iCondition].lhsAttr.attrName.c_str());
	string indexFileName = smm->getWork_Database() + "\\" + relName;
	if (rc = ixm->OpenIndex(indexFileName.c_str(), iIndex, ixIndexHandle))
	{
		std::cout << "Error to open Index " << iIndex << endl;
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
	memset(data, 0, conditionAttrLength);
	int copyLength = 4;
	if (conditions[iCondition].rhsValue.type == STRING || conditions[iCondition].rhsValue.type == VARCHAR)
		copyLength = strlen((char*)conditions[iCondition].rhsValue.data)+1;
	memcpy((void*)data, (void*)conditions[iCondition].rhsValue.data, copyLength);
	if (rc = ixScan.OpenScan(ixIndexHandle, conditions[iCondition].op, data))
	{
		std::cout << "Error to Open scan\n" << endl;
		return rc;
	}

	// find all satiefied stored in mem
	RID rid;
	RM_Record record;
	recordsBuffer.clear(); std::vector<RID> rids;
	while (!(rc = ixScan.GetNextEntry(rid)))
	{
		if (isSatisifyConditions(attrCount, attributes, rmFileHandle, rid, record, conditions))
		{
			rids.push_back(rid);
			recordsBuffer.push_back(RM_Record(record.pData, record.recordSize, rid));
		}
	}

	// delete 
	std::vector<IX_IndexHandle> ixIndexHandles;
	ixm->CloseIndex(ixIndexHandle);
	for (size_t i = 0; i < attrCount; i++)
	{
		ixm->OpenIndex(indexFileName.c_str(), i, ixIndexHandle);
		ixIndexHandles.push_back(ixIndexHandle);
	}
	deleteEntrys(rids, recordsBuffer, rmFileHandle, ixIndexHandles);

	// close file
	rmm->closeFile(rmFileHandle);
	for (IX_IndexHandle ixIndexHandle : ixIndexHandles)
	{
		ixm->CloseIndex(ixIndexHandle);
	}
	return OK;
}

RC QL_Manager::Update(const char * relName, const std::vector<RelAttr>& updAttr, const std::vector<int> bIsValue, const std::vector<RelAttr>& rhsRelAttr, const std::vector<Value>& rhsValue, std::vector<Condition>& conditions)
{
	if (Delete(relName, conditions))
	{
		return ERROR;
	}
	int attrCount;  AttrInfo * attributes; 
	smm->GetTableAttrInfo(smm->getWork_Database().c_str(), relName, attrCount, attributes);

	// check AttrType
	bool attrError = false;
	for (size_t i = 0; i < bIsValue.size(); i++)
	{
		if (bIsValue[i])
		{
			if (rhsValue[i].type == DINT && !attributes[i].attrType == DINT)
			{
				attrError = true;
			}
			else if ((rhsValue[i].type == STRING || rhsValue[i].type == VARCHAR) && !attributes[i].attrType == STRING)
			{
				attrError = true;
			}
		}
	}
	if (attrError)
	{
		std::cout << "AttrType Not Correspond!\n";
		return ERROR;
	}

	// update records
	for (size_t i = 0; i < bIsValue.size(); i++)
	{
		if (bIsValue[i])
		{
			int corAttr = findCorAttr(attrCount, attributes, updAttr[i].attrName.c_str());
			int attrLength = rhsValue[i].type == DINT ? sizeof(int) : (attributes[corAttr].attrLength > strlen((char*)rhsValue[i].data)+1 ? strlen((char*)rhsValue[i].data)+1 : attributes[corAttr].attrLength);
			for  (RM_Record & record : recordsBuffer)
			{
				char *pData;  record.getData(pData); pData += attrCount;
				for (size_t j = 0; j < attrCount; j++)
				{
					if (j == corAttr)
					{
						memcpy(pData, rhsValue[i].data, attrLength);
					}
					pData += attributes[j].attrLength;
				}
			}
		}
	}
	
	// pack all values
	std::vector<Value> values;
	for (size_t i = 0; i < attrCount; i++)
	{
		Value value;
		value.type = attributes[i].attrType;
		values.push_back(value);
	}
	for (RM_Record & record : recordsBuffer)
	{
		char *pData; record.getData(pData); pData += attrCount;
		for (size_t i = 0; i < attrCount; i++)
		{
			values[i].data = pData;
			pData += attributes[i].attrLength;
		}
		Insert(relName, values.size(), values);
	}
	return OK;
}

bool QL_Manager::CheckAndPreprocess(const char * relName, const std::vector<Condition>& conditions, int & attrCount, AttrInfo *& attributes)
{
	// judge if database is open
	if (smm->getWork_Database().size() <= 0)
	{
		std::cout << "Database is not open\n";
		return false;
	}

	// judge if tables exist
	if (!smm->IsTableExists(relName))
	{
		std::cout << "table not exist" << endl;
		return false;
	}

	RC rc;

	// get attr info for relations
	if ((rc = smm->GetTableAttrInfo(smm->getWork_Database().c_str(), relName, attrCount, attributes)))
	{
		std::cout << "Error to get Table Attr Info\n";
		return false;
	}

	// judge if attrName exists
	for (Condition condition : conditions)
	{
		bool found1 = false, found2 = !condition.bRhsIsAttr;
		for (int k = 0; k < attrCount; k++)
		{
			if (!found1)
			{
				found1 = string(condition.lhsAttr.attrName) == string(attributes[k].attrName);
			}
			if (!found2)
			{
				found2 = string(condition.rhsAttr.attrName) == string(attributes[k].attrName);
			}
		}
		if (!found1 || !found2)
		{
			std::cout << "AtrrName Error\n";
			return false;
		}
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
		for (int i = 0; i < nConditions; i++)
		{
			if (conditions[i].op == LIKE_OP)
			{
				conditions[i].op = NO_OP;
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

bool QL_Manager::isSatisifyConditions(int attrCount, AttrInfo * attributes, RM_FileHandle & rmFileHandle, const RID & rid, RM_Record &record, const std::vector<Condition> & conditions)
{
	int nConditions = conditions.size();
	// find rid in rmm, put it in the record
	RC rc;
	if (rc = rmFileHandle.getRec(rid, record))
	{
		std::cout << "Error to get Record\n";
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
			else if (attributes[nAttr].attrType == AttrType::STRING || attributes[nAttr].attrType == AttrType::VARCHAR)
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
	return satisfied;
}

void QL_Manager::deleteEntrys(const std::vector<RID> & rids, const std::vector<RM_Record> & records, RM_FileHandle & rmFileHandle, std::vector<IX_IndexHandle> & ixIndexHandles)
{
	for (size_t i = 0; i < rids.size(); ++i)
	{
		rmFileHandle.deleteRec(rids[i]);
		char *pData; records[i].getData(pData);
		pData += ixIndexHandles.size();
		for (IX_IndexHandle ixIndexHandle : ixIndexHandles)
		{
			ixIndexHandle.DeleteEntry(pData, rids[i]);
			pData += ixIndexHandle.ixHead->attrLength;
		}
	}
}

int QL_Manager::findCorAttr(int attrCount, const AttrInfo * attributes, const char * attrName)
{
	bool found = false;
	int corAddr = 0;
	for (; corAddr < attrCount; corAddr++)
	{
		if (string(attrName) == string(attributes[corAddr].attrName))
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

std::string QL_Manager::ReplaceAll(std::string & str, const std::string & from, const std::string & to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

RC QL_Manager::findCorAttr(int& indexRelation, int& indexAttr, int* attrCount, AttrInfo ** attributes, Condition & condition, vector<string> relations, bool right)
{

	RelAttr relAttr = (right) ? (condition.rhsAttr) : condition.lhsAttr;
	for (int i = 0; i < relations.size(); i++)
	{
		if (string(relations[i]) == relAttr.relName)
		{
			for (int j = 0; j < attrCount[i]; j++)
			{
				if (string(attributes[i][j].attrName) == relAttr.attrName)
				{
					indexRelation = i;
					indexAttr = j;
					return OK;
				}
			}
		}
	}
	return ERROR;
}