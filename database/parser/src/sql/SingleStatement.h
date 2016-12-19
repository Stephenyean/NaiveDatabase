#ifndef __SINGLE_STATEMENT_H__
#define __SINGLE_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {
	/**
	 * Represents SQL Single statements.
	 * Example: "Single DATABASE/TABLE name"
	 */
	struct SingleStatement : SQLStatement {
		enum SingleType {
			kCreateDatabase,
			kDropDatabase,
			kUseDatabase,
			kShowDatabase,
			kShowTable
		};

		SingleStatement(SingleType type) :
			SQLStatement(kStmtSingle),
			type(type),
			name(NULL) {};

		virtual ~SingleStatement() {
			delete name;
		}

		SingleType type;
		const char* name;
	};

} // namespace hsql
#endif