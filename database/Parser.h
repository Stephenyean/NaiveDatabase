#pragma once
#include "RecordManager.h"
#include "IX_Manager.h"
#include "SM_Manager.h"
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
private:
	FileManager *fm;
	BufPageManager *bpm;
	RM_Manager *rmm;
	IX_Manager *ixm;
	SM_Manager *smm;
};

