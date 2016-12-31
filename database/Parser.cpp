#include "Parser.h"
#include "query.h"
#include "pf_defines.h"
#include "QL_Manager.h"
#include <iostream>
#include <fstream>
using namespace hsql;
using namespace std;


vector<vector<string>> Parser::parseResults;
Parser::Parser()
{
	MyBitMap::initConst();
	fm = new FileManager();
	bpm = new BufPageManager(fm);
	rmm = new RM_Manager(fm, bpm);
	ixm = new IX_Manager(fm, bpm);
	smm = new SM_Manager(ixm, rmm);
	qlm = new QL_Manager(smm, ixm, rmm);
}

Parser::~Parser()
{
	delete fm;
	delete bpm;
	delete rmm;
	delete ixm;
	delete smm;
	delete qlm;
}

void Parser::parse()
{
	int ret = 1;
	std::string sqlQuery;
	while (ret)
	{
		cout << ">> ";
		getline(cin, sqlQuery);
		ret = parseSQL(sqlQuery);
		if (ret == 0)
		{
			for (auto e : IdMap::fileIDMap)
			{
				int index;
				BufType b = bpm->getPage(e.second, 0, index);
				File_Head* fileHead = (File_Head*)b;
				int pages = fileHead->numPages;
				//cout << e.first << endl;
				for (int i = 0; i < pages; i++)
				{
					b = bpm->getPage(e.second, i, index);
					bpm->markDirty(index);
					bpm->writeBack(index);
					b = bpm->getPage(e.second, i, index);
				}

			}
			//bpm->close();
			for (auto e : IdMap::fileIDMap)
			{
				//cout << e.first << endl;
				fm->closeFile(e.second);
			}
		}
	}
}

int Parser::parseSQL(std::string sql)
{
	SQLParserResult* result = SQLParser::parseSQLString(sql);
	if (result->isValid)
	{
		for (SQLStatement *stmt : result->statements)
		{
			
			switch (stmt->type())
			{
			case StatementType::kStmtSingle:
				if (!processSingle((SingleStatement *)stmt))
					return 0;
				break;
			case StatementType::kStmtCreate:
				processCreate((CreateStatement *)stmt);
				break;
			case StatementType::kStmtDrop:
				processDrop((DropStatement *)stmt);
				break;
			case kStmtSelect:
				processSelect((SelectStatement *) stmt);
				break;
			case kStmtInsert:
				processInsert((InsertStatement *) stmt);
				break;
			case kStmtUpdate:
				processUpdate((UpdateStatement *) stmt);
				break;
			case kStmtDelete:
				processDelete((DeleteStatement *) stmt);
				break;
			default:
				break;
			}
		}
	}
	else {
		cout << "SQL(s) is(are) not valid...\n";
	}
	return 1;
}

int Parser::processSingle(hsql::SingleStatement *stmt)
{
	int ret = 1;
	switch (stmt->type)
	{
	case (SingleStatement::kCreateDatabase):
		smm->CreateDb(stmt->name);
		break;
	case (SingleStatement::kDropDatabase):
		smm->DropDb(stmt->name);
		break;
	case (SingleStatement::kUseDatabase):
		smm->OpenDb(stmt->name);
		break;
	case (SingleStatement::kShowDatabase):
	{
		vector<string> files;
		getFiles("./_*", files);
		for (string file : files)
		{
			cout << "Database: " << file << "\n";
			cout << "Table:\n";
			bool hasTables = false;
			for (string table : smm->GetTables(file.c_str()))
			{
				hasTables = true;
				cout << table << "\n";
			}
			if (!hasTables) {
				cout << "No existing table. Please \"CREATE TABLE <tablename> ( columnlist );\"\n";
			}
		}
		break;
	}
	case (SingleStatement::kShowTable):
	{
		int attrCount = 0;
		AttrInfo *attributes = NULL;
		if (smm->GetTableAttrInfo(NULL, stmt->name, attrCount, attributes) == OK)
		{
			cout << "Table: " << stmt->name << "\n";
			cout << "Column:\n";
			for (size_t i = 0; i < attrCount; i++)
			{
				cout << "Name: " << attributes[i].attrName << "\tType: ";
				switch (attributes[i].attrType)
				{
				case AttrType::DINT:
					cout << "DINT";
					break;
				case AttrType::DFLOAT:
					cout << "DFLOAT";
					break;
				case AttrType::STRING:
					cout << "STRING";
					break;
				case AttrType::VARCHAR:
					cout << "VARCHAR";
					break;
				case AttrType::NUL:
					cout << "NUL";
					break;
				case AttrType::DDATE:
					cout << "DATE";
				default:
					break;
				}
				cout << "\n";
			}
			delete[] attributes;
		}
		break;
	}
	case (hsql::SingleStatement::kReadFile):
	{
		ifstream fin;
		string fileName =string(stmt->name) + ".sql";
		fin.open(fileName);
		if (fin)
		{
			string sqlQuery; string sql;
			while (getline(fin, sql))
			{
				sqlQuery += sql;
			}
			ret = parseSQL(sqlQuery);
			fin.close();
		}
		else
		{
			cout << fileName << " is not exists.\n";
		}

		break;
	}
	case (hsql::SingleStatement::kQuit):
		ret = 0;
	default:
		break;
	}
	return ret;
}

void Parser::processCreate(hsql::CreateStatement *stmt)
{
	AttrInfo *attributes = new AttrInfo[stmt->columns->size()];
	int i = 0;
	int primaryKeyIx = -1, checkInIx = -1;
	vector<string> checkInStrs;
	bool primaryKeyValid = stmt->primaryKey == NULL;
	bool checkInValid = stmt->checkIn == NULL;
	for (ColumnDefinition *column : *(stmt->columns))
	{
		attributes[i].attrName = column->name;
		attributes[i].attrType = (AttrType) column->type;
		switch (attributes[i].attrType)
		{
		case AttrType::STRING:
			attributes[i].attrLength = 256;
			break;
		case AttrType::VARCHAR:
			attributes[i].attrLength = column->width + 1;
			break;
		case AttrType::DDATE:
			attributes[i].attrLength = 15;
		default:
			attributes[i].attrLength = 4; // DFLOAT INT
			break;
		}
		attributes[i].notnull = column->notnull;
		if (!primaryKeyValid && strcmp(attributes[i].attrName, stmt->primaryKey) == 0)
		{
			primaryKeyIx = i;
			primaryKeyValid = true;
		}
		if (!checkInValid && strcmp(attributes[i].attrName, stmt->checkIn->relName) == 0)
		{
			checkInIx = i;
			checkInValid = true;
			for (Expr * expr : *(stmt->checkIn->checkInVec))
			{
				checkInStrs.push_back(expr->name);
			}
		}
		i += 1;
	}
	if (!primaryKeyValid)
	{
		cout << "Primary key is not valid." << endl;
		delete[] attributes;
		return;
	}
	if (!checkInValid)
	{
		cout << "Check in is not valid." << endl;
		delete[] attributes;
		return;
	}
	smm->CreateTable(stmt->tableName, stmt->columns->size(), attributes, primaryKeyIx, checkInIx, checkInStrs);
	delete[] attributes;
}

void Parser::processDrop(hsql::DropStatement *stmt)
{
	smm->DropTable(stmt->name);
}

void Parser::processInsert(hsql::InsertStatement *stmt){
	
	//stmt->values;
	int checkInIx; std::vector<string> checkInStrs;
	smm->GetCheckIn(checkInIx, checkInStrs);
	for(int i=0; i<stmt->values->size(); i++){
		vector<Value> myValues;
		for(int j=0; j<stmt->values->operator[](i)->size(); j++){
			auto localValue = stmt->values->operator[](i)->operator[](j);
			switch(localValue->type){
				case(kExprLiteralInt):{
					Value value;
					value.type = DINT;
					value.data = (void*)(new int(localValue->ival));//(void*)&localValue->ival;
					myValues.push_back(value);
					break;
				}
				case(kExprLiteralString):{

					Value value;
					value.type = STRING;
					value.data = (void*)new char[strlen(localValue->name) + 1];// localValue->name;
					memset(value.data, 0, strlen(localValue->name) + 1);
					memcpy(value.data, localValue->name, strlen(localValue->name) + 1);
					if (checkInIx == j)
					{
						bool found = false;
						for (string str : checkInStrs)
						{
							if (!found)
								found = str == string((char *)value.data);
						}
						if (!found)
						{
							cout << "Check In Failed in Ix " << checkInIx << endl;
							return;
						}
					}
					myValues.push_back(value);
					break;
				}
				case(kExprNull): {
					Value value;
					value.type = AttrType::NUL;
					value.data = (void*)(new int[1]);
					myValues.push_back(value);
					break;
				}
				default:
					break;
			}
		}
		switch(stmt->type){
			case(InsertStatement::kInsertValues):{
				//if (checkPK(stmt->tableName, myValues))
				//{
					qlm->Insert(stmt->tableName, myValues.size(), myValues);
				//}
				//else
				//{
				//	cout << "Primary Key Check Failed" << endl;
				//}

				break;
			}
			case(InsertStatement::kInsertSelect):
				break;
			default:
				break;
		}
	}
}


void Parser::processDelete(hsql::DeleteStatement *stmt){

	vector<Condition> conditions;
	const char * relName = stmt->tableName;
	packConditions(relName, stmt->whereClause, conditions);
	qlm->Delete(relName, conditions);
	
}

void Parser::processUpdate(hsql::UpdateStatement* stmt){
	vector<Condition> conditions;
	const char * relName = stmt->table->getName();
	packConditions(relName, stmt->whereClause, conditions);

	std::vector<RelAttr> updAttr;         // attribute to update
	std::vector<int> bIsValue;             // 0/1 if RHS of = is attribute/value
	std::vector<RelAttr> rhsRelAttr;      // attr on RHS of =
	std::vector<Value> rhsValue;          // value on RHS of =

	for (size_t i = 0; i < stmt->updates->size(); i++)
	{
		// upAttr
		RelAttr myUpdAttr;
		myUpdAttr.relName = relName;
		myUpdAttr.attrName = (*stmt->updates)[i]->column;
		updAttr.push_back(myUpdAttr);
		// bIsValue & rhsValue
		Value myRhsValue;
		switch ((*stmt->updates)[i]->value->type) {
		case(kExprLiteralInt): {
			myRhsValue.type = DINT;
			myRhsValue.data = &(*stmt->updates)[i]->value->ival;
			bIsValue.push_back(true);
			break;
		}
		case(kExprLiteralString): {
			myRhsValue.type = STRING;
			myRhsValue.data = (*stmt->updates)[i]->value->name;
			bIsValue.push_back(true);
			break;
		}
		default:
			bIsValue.push_back(false);
			break;
		}
		rhsValue.push_back(myRhsValue);
	}

	qlm->Update(relName, updAttr, bIsValue, rhsRelAttr, rhsValue, conditions);

}

void Parser::processSelect(hsql::SelectStatement* stmt){
	//selAttrs
	//RelAttr mySelAttrs[10000];
	vector<RelAttr> mySelAttrs;
	int nSelAttrs, nRelations, nConditions;
	vector<string> relations;
	vector<Condition> conditions;
	bool starExpr = false;
	for(int i=0; i<stmt->selectList->size(); i++){
		if ((*(stmt->selectList))[i]->type == ExprType::kExprStar)
		{
			starExpr = true;
			nSelAttrs = -1;
		}
	}
	if (stmt->fromTable == nullptr)
	{
		cout << "Error No from Tables\n";
	}
	//string relName = (*(stmt->fromTable->list))[0]->getName();
	string relName;
	if (stmt->fromTable->list)
		relName = string((*stmt->fromTable->list)[0]->getName());
	else
		relName = string(stmt->fromTable->getName());
	if (!starExpr)
	{
		
		for (int i = 0; i<stmt->selectList->size(); i++) {
			auto localExpr = (*(stmt->selectList))[i];
			if (!localExpr->table)
			{
				string table = relName;
				string attrName = localExpr->getName();
				mySelAttrs.push_back(RelAttr(table, attrName));
			}
			else
			{
				string table = localExpr->table;
				string attrName = localExpr->getName();
				mySelAttrs.push_back(RelAttr(table, attrName));
			}
		}
		nSelAttrs = stmt->selectList->size();
	}
	if (stmt->whereClause)
	{
		packConditions(relName.c_str(), stmt->whereClause, conditions);
	}

	if (stmt->fromTable->list)
		for (int i = 0; i < stmt->fromTable->list->size(); i++) {
			relations.push_back(string(stmt->fromTable->list->at(i)->getName()));
		}
	else
		relations.push_back(relName);
	nRelations = relations.size();
	nConditions = conditions.size();
	qlm->Select(nSelAttrs, mySelAttrs, nRelations, relations, nConditions, conditions, stmt);
}

void Parser::packConditions(const char * relName, std::vector<hsql::Expr*>* whereClause, std::vector<Condition> & conditions)
{
	for (int i = 0; i < whereClause->size(); i++)
	{
		auto localValue = (*whereClause)[i];
		Condition localCondition;
		if (localValue->expr->hasTable())
		{
			localCondition.lhsAttr = RelAttr(localValue->expr->table, localValue->expr->getName());
		}
		else
			localCondition.lhsAttr = RelAttr(relName, localValue->expr->getName());
		localCondition.op = CompOp::NO_OP;
		switch (localValue->op_type)
		{
		case(hsql::Expr::OperatorType::NOT_EQUALS):
			localCondition.op = CompOp::NE_OP;
			break;
		case(hsql::Expr::OperatorType::SIMPLE_OP):
			if (localValue->op_char == '=')
				localCondition.op = CompOp::EQ_OP;
			else if (localValue->op_char == '>')
				localCondition.op = CompOp::GT_OP;
			else if (localValue->op_char == '<')
				localCondition.op = CompOp::LT_OP;
			else if (localValue->op_char == 'y')
				localCondition.op = CompOp::ISNULL_OP;
			else if (localValue->op_char == 'n')
				localCondition.op = CompOp::NOTNULL_OP;
			break;
		case(hsql::Expr::OperatorType::LESS_EQ):
			localCondition.op = CompOp::LE_OP;
			break;
		case(hsql::Expr::OperatorType::GREATER_EQ):
			localCondition.op = CompOp::GE_OP;
			break;
		case(hsql::Expr::OperatorType::LIKE):
			localCondition.op = CompOp::LIKE_OP;
			break;
		}

		if (localValue->expr2->isLiteral())
		{
			localCondition.bRhsIsAttr = 0;
			Value tempValue;
			if (localValue->expr2->type == ExprType::kExprLiteralInt)
			{
				tempValue.data = (void*)&localValue->expr2->ival;
				tempValue.type = AttrType::DINT;
			}
			else if (localValue->expr2->type == ExprType::kExprLiteralString)
			{
				tempValue.data = (void*)localValue->expr2->getName();
				tempValue.type = AttrType::STRING;
			}
			else if (localValue->expr2->type == ExprType::kExprNull)
			{
				tempValue.data = (void*)(new int[1]);
				tempValue.type = AttrType::NUL;
			}
			localCondition.rhsValue = tempValue;
			if (localCondition.op == CompOp::LIKE_OP)
			{
				// replace other regex identifier
				vector<string> regexIds = { "\\", "(", ")", "?", ":", "[", "]", "*", "+","^", "$", "|" };
				string givenValue = string((char *)localValue->expr2->name);
				for (string regexId : regexIds)
				{
					ReplaceAll(givenValue, regexId, "\\" + regexId);
				}
				// translate sql to regex
				ReplaceAll(givenValue, "_", "(.)");
				ReplaceAll(givenValue, "%", "(.)*");
				// find match
				char * data = new char[givenValue.size() + 1];
				memcpy(data, givenValue.c_str(), givenValue.size());
				data[givenValue.size()] = '\0';
				delete[] localCondition.rhsValue.data;
				localCondition.rhsValue.data = (void*)data;
			}
		}
		else
		{
			localCondition.bRhsIsAttr = 1;
			if (localValue->expr2->hasTable())
			{
				localCondition.rhsAttr = RelAttr(string(localValue->expr2->table), string(localValue->expr2->getName()));
			}
			else
				localCondition.rhsAttr = RelAttr(relName, string(localValue->expr2->getName()));
		}

		conditions.push_back(localCondition);
	}
}

void Parser::getFiles(string path, vector<string>& files)
{
	WIN32_FIND_DATA f;
	HANDLE h = FindFirstFile(path.c_str(), &f);

	if (h == INVALID_HANDLE_VALUE) { return; }

	do
	{
		const char * name = f.cFileName;

		if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) { continue; }

		//char filePath[1024];
		//sprintf(filePath, "%s%s%s", path, "\\", name);

		files.push_back(name);
	} while (FindNextFile(h, &f));
	FindClose(h);
}

std::string Parser::ReplaceAll(std::string & str, const std::string & from, const std::string & to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

bool Parser::checkPK(const char * relName, const vector<Value> & values)
{
	// get all attrInfos
	int attrCount;
	AttrInfo * attributes = NULL;
	int primaryKeyIx;
	smm->GetTableAttrInfo(smm->getWork_Database().c_str(), relName, attrCount, attributes, primaryKeyIx);
	if (primaryKeyIx == -1)
	{
		return true;
	}
	// open Handle
	RC rc;
	IX_IndexHandle ixIndexHandle;
	string indexFileName = smm->getWork_Database() + "\\" + relName;
	if (rc = ixm->OpenIndex(indexFileName.c_str(), primaryKeyIx, ixIndexHandle))
	{
		//cout << "Error to open Index " << primaryKeyIx << endl;
		return false;
	}
	// open scan
	IX_IndexScan ixScan;
	if (rc = ixScan.OpenScan(ixIndexHandle, EQ_OP, values[primaryKeyIx].data))
	{
		//cout << "Error to Open scan\n" << endl;
		return rc;
	}
	// find duplicate
	RID rid;
	if (rc = ixScan.GetNextEntry(rid))
	{
		return true;
	}
	else
	{
		return false;
	}
}



