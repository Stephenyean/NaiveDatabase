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
		const std::vector<RelAttr> &updAttr,         // attribute to update
		const std::vector<int> bIsValue,             // 0/1 if RHS of = is attribute/value
		const std::vector<RelAttr> &rhsRelAttr,      // attr on RHS of =
		const std::vector<Value> &rhsValue,          // value on RHS of =
		 std::vector<Condition> & conditions);  // conditions in Where clause
	template<typename T>
	bool satisfiesCondition(T key, T value, CompOp op);
	SM_Manager* smm;
	IX_Manager* ixm;
	RM_Manager* rmm;
	int verbose = 2;
private:
	bool CheckAndPreprocess(const char * relName, const std::vector<Condition> & conditions, int & attrCount, AttrInfo *& attributes);
	int findBestCondition(std::vector<Condition> & conditions);
	bool isSatisifyConditions(int attrCount, AttrInfo * attributes, RM_FileHandle & rmFileHandle, const RID & rid, RM_Record &record, const std::vector<Condition> &  conditions);
	void deleteEntrys(const std::vector<RID> & rids, const std::vector<RM_Record> & records, RM_FileHandle & rmFileHandle, std::vector<IX_IndexHandle> & ixIndexHandles);
	int findCorAttr(int attrCount, const AttrInfo * attributes, const char * attrName);
	std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);
	std::vector<RM_Record> recordsBuffer;
};
