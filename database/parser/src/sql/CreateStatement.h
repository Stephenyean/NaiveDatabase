#ifndef __CREATE_STATEMENT_H__
#define __CREATE_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {
	/**
	* Represents definition of a table column
	*/
	struct ColumnDefinition {
		enum DataType {
			DINT,
			DFLOAT,
			STRING,
			VARCHAR
		};

		ColumnDefinition(char* name, DataType type, int64_t width, bool notnull) :
			name(name),
			type(type),
			width(width),
			notnull(notnull) {}


		virtual ~ColumnDefinition() {
			delete name;
		}


		char* name;
		DataType type;
		int64_t width; // when width = 0 means not define
		bool notnull;
	};

	/**
	* Represents SQL Create statements.
	* Example: "CREATE TABLE students (name TEXT, student_number INTEGER, city TEXT, grade DOUBLE)"
	*/
	struct CreateStatement : SQLStatement {
		enum CreateType {
			kTable,
			kTableFromTbl // Hyrise file format
		};

		CreateStatement(CreateType type) :
			SQLStatement(kStmtCreate),
			type(type),
			ifNotExists(false),
			filePath(NULL),
			tableName(NULL),
			primaryKey(NULL),
			columns(NULL) {};

		virtual ~CreateStatement() {
			delete columns;
			delete filePath;
			delete tableName;
		}

		CreateType type;

		bool ifNotExists;
		const char* filePath;
		const char* tableName;
		const char* primaryKey;
		std::vector<ColumnDefinition*>* columns;
	};

} // namespace hsql
#endif