#include "Parser.h"
#include <fstream>
using namespace hsql;

Parser::Parser()
{
	fm = new FileManager();
	bpm = new BufPageManager(fm);
	rmm = new RM_Manager(fm, bpm);
	ixm = new IX_Manager(fm, bpm);
	smm = new SM_Manager(ixm, rmm);
}

Parser::~Parser()
{
	delete fm;
	delete bpm;
	delete rmm;
	delete ixm;
	delete smm;
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
			case StatementType::kStmtSelect:
				break;
			case StatementType::kStmtInsert:
				break;
			case StatementType::kStmtUpdate:
				break;
			case StatementType::kStmtDelete:
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
			attributes[i].attrLength = column->width;
			break;
		default:
			attributes[i].attrLength = 4; // DFLOAT INT
			break;
		}
		attributes[i].notnull = column->notnull;
		i += 1;
	}
	smm->CreateTable(stmt->tableName, stmt->columns->size(), attributes);
	delete[] attributes;
}

void Parser::processDrop(hsql::DropStatement *stmt)
{
	smm->DropTable(stmt->name);
}
