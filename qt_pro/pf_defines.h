#pragma once
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <utility>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <map>
#include <cassert>

const int ATTRNAME_LENGTH = 30;
const int RELNAME_LENGTH = 30;

#define EPS 1e-6
#define MAXSTRINGLENGTH 255
#define MAXNAME 255
enum CompOp {
	NO_OP,
	EQ_OP,
	LT_OP,
	GT_OP,
	LE_OP,
	GE_OP,
	NE_OP,
	LIKE_OP,
	ISNULL_OP,
	NOTNULL_OP
};

enum RC_Return {
	OK,
	IX_NO_SUCH_INDEX,
	ERROR,
	QL_NULL_ERROR,
	QL_TABLE_NOT_EXIST_ERROR,
	QL_INCORRECT_ATTR_COUNT,
	QL_INCORRECT_ATTR_TYPE,
	QL_INCORRECT_ATTR_NAME,
	QL_DATABASE_NOT_OPEN,
	PF_CLOSEDFILE,
	UNKNOWN_ERROR,
	CREATE_ERROR,
	OPEN_ERROR,
	DROP_ERROR,
	LOAD_PAGE_ERROR,
	DISPOSE_ERROR,
	ADDPAGE_ERROR,
	REMOVEPAGE_ERROR,
	FORCEPAGE_ERROR,
	WRONG_PAGE_NUMBER,
	TOO_LONG_RECORD,
	INVALID_RID,
	INVALID_RECORD,
	EXPANDING_EMPTY_FILE,
	OPERATION_ON_HEAD_PAGE,
	NO_RID_IN_RECORD,
	INVALID_PAGE,
	NOT_FOUND,
	ATTRIBUTE_CATALOG_OPEN_ERROR,
	SYSTEM_CATALOG_OPEN_ERROR,
	ATTRIBUTE_CATALOG_CLOSE_ERROR,
	SYSTEM_CATALOG_CLOSE_ERROR,
	TABLE_CREATE_ERROR,
	NO_OPENING_DATABASE_ERROR
};

enum AttrType {
	DINT,
	DFLOAT,
	STRING,
	VARCHAR,
	DDATE,
	STAR,
	NUL,

};