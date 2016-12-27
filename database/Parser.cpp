#include "Parser.h"
#include "query.h"
#include "pf_defines.h"
#include "QL_Manager.h"
#include <iostream>
#include <fstream>
using namespace hsql;
using namespace std;



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
		cout << "Database: " << stmt->name << "\n";
		cout << "Table:\n";
		bool hasTables = false;
		for (string table : smm->GetTables(stmt->name))
		{
			hasTables = true;
			cout << table << "\n";
		}
		if (!hasTables) {
			cout << "No existing table. Please \"CREATE TABLE <tablename> ( columnlist );\"\n";
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
	int primaryKeyIx = -1;
	bool primaryKeyValid = stmt->primaryKey == NULL;
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
		i += 1;
	}
	if (!primaryKeyValid)
	{
		cout << "Primary key is not valid." << endl;
		delete[] attributes;
		return;
	}
	smm->CreateTable(stmt->tableName, stmt->columns->size(), attributes, primaryKeyIx);
	delete[] attributes;
}

void Parser::processDrop(hsql::DropStatement *stmt)
{
	smm->DropTable(stmt->name);
}

void Parser::processInsert(hsql::InsertStatement *stmt){
	
	//stmt->values;
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
					myValues.push_back(value);
					break;
				}
				default:
					break;
			}
		}
		switch(stmt->type){
			case(InsertStatement::kInsertValues):{
				qlm->Insert(stmt->tableName, myValues.size(), myValues);
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

	/*
	Condition myCondition[10000];
	for(int i=0; i<stmt->where->size(); i++){
		//condition
		tempCondition.lhsAttr = stmt->updates[i]->column;
		tempCondition.op = NO_OP;		//default no comparison(when value is a null pointer)
		switch(stmt->updates[i]->value->op_type){
			case(NOT_EQUALS):{
				tempCondition.op = NE_OP;
				break;
			}
			case(LESS_EQ):{
				tempCondition.op = LE_OP;
				break;
			}
			case(GREATER_EQ):{
				tempCondition.op = GE_OP;
				break;
			}
			default:
				break;
		}
		switch(stmt->updates[i]->value->op_char){
			case('='):{
				tempCondition.op = EQ_OP;
				break;
			}
			case('<'):{
				tempCondition.op = LT_OP;
				break;
			}
			case('>'):{
				tempCondition.op = GT_OP;
				break;
			}
		}
		tempCondition.bRhsIsAttr = FALSE;
		tempCondition.rhsAttr = NULL;
		tempCondition.rhsValue = stmt->updates[i]->value->expr2->fval;
		//updAttr
		
	}
	for(int i=0; i<stmt->updates->size(); i++){
		RelAttr myUpdAttr;
		myUpdAttr.relName = stmt->table;
		myUpdAttr.attrName = stmt->updates[i]->column;
		//rhsRelAttr
		RelAttr myRhsRelAttr;
		myRhsRelAttr.relName = stmt->table;
		myRhsRelAttr.attrName = stmt->updates[i]->column;
		//rhsValue
		Value myRhsValue;
		switch(stmt->updates[i]->value->type){
			case(kExprLiteralInt):{
				myRhsValue.type = DINT;
				myRhsValue.data = stmt->updates[i]->value->val;
				break;
			}
			case(kExprLiteralFloat):{
				myRhsValue.type = DFLOAT;
				myRhsValue.data = stmt->updates[i]->value->value;
				break;
			}
			case(kExprLiteralString):{
				myRhsValue.type = STRING;
				myRhsValue.data = stmt->updates[i]->value->value;
				break;
			}
			default:
				break;
		}
		qlm->Update(stmt->table, myUpdAttr, 1, myRhsRelAttr, myRhsValue, 1,myCondition);
	}
	*/
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
	qlm->Select(nSelAttrs, mySelAttrs, nRelations, relations, nConditions, conditions);
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
			localCondition.rhsValue = tempValue;
		}
		else
		{
			localCondition.bRhsIsAttr = 1;
			if (localValue->expr2->hasTable())
			{
				localCondition.lhsAttr = RelAttr(string(localValue->expr2->table), string(localValue->expr2->getName()));
			}
			else
				localCondition.lhsAttr = RelAttr(relName, string(localValue->expr2->getName()));
		}

		conditions.push_back(localCondition);
	}
}



