#pragma once
#include "RM_Manager.h"
#include "IX_Manager.h"
#include "SM_Manager.h"
#include "QL_Manager.h"
#include "parser\src\SQLParser.h"
#include "parser\src\sqlhelper.h"
class Parser
{
public:
	Parser();
	~Parser();
	void parse();
	int parseSQL(std::string sql);
	int processSingle(hsql::SingleStatement *stmt);
	void processCreate(hsql::CreateStatement *stmt);
	void processDrop(hsql::DropStatement *stmt);
	void processInsert(hsql::InsertStatement *stmt);
	void processDelete(hsql::DeleteStatement *stmt);
	void processUpdate(hsql::UpdateStatement* stmt);
	void processSelect(hsql::SelectStatement* stmt);

private:
	QL_Manager* qlm;
	FileManager *fm;
	BufPageManager *bpm;
	RM_Manager *rmm;
	IX_Manager *ixm;
	SM_Manager *smm;
	
};

