#pragma once
//#include "parser.h"
#include "SM_Manager.h"
#include "RM_Manager.h"

struct RelAttr {
	RelAttr(string _relName, string _attrName):relName(_relName), attrName(_attrName) {}
	RelAttr() {}
	string relName;     // relation name (may be NULL) 
	string attrName;    // attribute name              
	//friend ostream &operator<<(ostream &s, const RelAttr &ra);
};

struct Value {
	~Value() { data = nullptr; }
	AttrType type;     // type of value               
	void     *data;    // value                       
	//friend ostream &operator<<(ostream &s, const Value &v);
};

struct Condition {
	RelAttr lhsAttr;      // left-hand side attribute                     
	CompOp  op;           // comparison operator                          
	int     bRhsIsAttr;   // TRUE if right-hand side is an attribute
						  //   and not a value
	RelAttr rhsAttr;      // right-hand side attribute if bRhsIsAttr = TRUE
	Value   rhsValue;     // right-hand side value if bRhsIsAttr = FALSE
	//friend ostream &operator<<(ostream &s, const Condition &c);
};

class QL_Manager {
public:

	QL_Manager(SM_Manager* smm, IX_Manager* ixm, RM_Manager* rmm);
	~QL_Manager();                         // Destructor

	RC Select(int           nSelAttrs,        // # attrs in Select clause
		vector<RelAttr>		selAttrs,       // attrs in Select clause
		int           nRelations,       // # relations in From clause
		vector<string>		relations, // relations in From clause
		int           nConditions,      // # conditions in Where clause
		vector<Condition> conditions);  // conditions in Where clause

	RC Insert(const char  *relName,           // relation to insert into
		int         nValues,            // # values to insert
		vector<Value> values);          // values to insert

	RC Delete(const char *relName,            // relation to delete from
		 std::vector<Condition> & conditions);  // conditions in Where clause
	RC Update(const char *relName,            // relation to update
		const RelAttr &updAttr,         // attribute to update
		const int bIsValue,             // 0/1 if RHS of = is attribute/value
		const RelAttr &rhsRelAttr,      // attr on RHS of =
		const Value &rhsValue,          // value on RHS of =
		 std::vector<Condition> & conditions);  // conditions in Where clause
	template<typename T>
	bool satisfiesCondition(T key, T value, CompOp op);
	SM_Manager* smm;
	IX_Manager* ixm;
	RM_Manager* rmm;
	int verbose = 2;
private:
	bool CheckAndPreprocess(const char * relName, std::vector<Condition> & conditions, int & attrCount, AttrInfo *& attributes);
	int findBestCondition(std::vector<Condition> & conditions);
	bool isSatisifyConditions(int attrCount, AttrInfo * attributes, RM_FileHandle & rmFileHandle, IX_IndexScan & scan, const RID & rid, RM_Record &record, std::vector<Condition> &  conditions, int deletemode);
	int findCorAttr(int attrCount, const AttrInfo * attributes, const Condition & condition);
	std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);

};
