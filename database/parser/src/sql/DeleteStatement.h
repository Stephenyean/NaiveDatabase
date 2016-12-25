#ifndef __DELETE_STATEMENT_H__
#define __DELETE_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {
    /**
     * Represents SQL Delete statements.
     * Example: "DELETE FROM students WHERE grade > 3.0"
     *
     * Note: if (expr == NULL) => delete all rows (truncate)
     */
    struct DeleteStatement : SQLStatement {
        DeleteStatement() :
            SQLStatement(kStmtDelete),
            tableName(NULL),
            whereClause(NULL) {};

        virtual ~DeleteStatement() {
            delete tableName;
            delete whereClause;
        }

        char* tableName;
        std::vector<Expr*>* whereClause;
    };

} // namespace hsql
#endif