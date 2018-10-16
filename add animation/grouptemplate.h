#ifndef GROUPTEMPLATE_H_
#define GROUPTEMPLATE_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <boost\regex.hpp>
#include <boost\algorithm\string.hpp>
#include "compute.h"
#include "furniture.h"

typedef std::set<std::string> setstr;
typedef std::vector<std::string> vecstr;
typedef std::unordered_map<std::string, int> id;
typedef std::unordered_map<std::string, std::string> SSMap;
typedef std::unordered_map<std::string, std::unordered_map<std::string, std::string>> ImportContainer;

struct groupTemplate
{
private:
	id eventid;
	id variableid;
	std::string filename;
	vecstr templatelines;
	newAnimLock* atomicLock;
	ImportContainer* newImport;
	std::string format;
	std::string strID;
	int nextFunctionID;
	SSMap IDExist;
	std::shared_ptr<master> subFunctionIDs;
	std::vector<std::vector<std::shared_ptr<animationInfo>>> groupAnimInfo;

public:
	groupTemplate(vecstr groupfunctionformat);
	void getFunctionLines(std::shared_ptr<vecstr> functionline, std::string behaviorFile, std::string formatname, std::vector<int>& stateID,
		std::shared_ptr<master> newSubFunctionIDs, std::vector<std::vector<std::shared_ptr<animationInfo>>> newGroupAnimInfo, int nFunctionID,
		ImportContainer& import, id eventid, id variableID,
		std::string masterFormat, newAnimLock& atomicLock, int groupCount = 0);
	void stateReplacer(std::string& line, std::string filename, std::string statenum, int ID, int stateID, int linecount, int groupMulti);
	void processing(std::string& line, std::string filename, std::string masterFormat, int linecount, id eventid, id variableid, int groupMulti = -1,
		int optionMulti = -1, int animMulti = -1, std::string multiOption = "");
	inline void newID();
	void setZeroEvent(std::string eventname);
	void setZeroVariable(std::string variablename);
};

struct ExistingFunction
{
private:
	bool m_hasGroup;
	int* nextFunctionID;
	ImportContainer* newImport;
	std::string strID;
	std::string format;
	SSMap IDExist;
	std::shared_ptr<master> subFunctionIDs;
	std::vector<std::vector<std::shared_ptr<animationInfo>>> groupAnimInfo;
	id eventid;
	id variableid;

public:
	vecstr groupExistingFunctionProcess(int curFunctionID, vecstr existingFunctionLines, std::shared_ptr<master> newSubFunctionIDs,
		std::vector<std::vector<std::shared_ptr<animationInfo>>> newGroupAnimInfo, std::string format, ImportContainer& import, id newEventID, id newVariableID,
		int& nFunctionID, bool hasMaster, bool hasGroup, setstr templateGroup, bool ignoreGroup);
	void processing(std::string& line, std::string filename, int curFunctionID, int linecount, id eventid, id variableid, int groupMulti, int optionMulti = -1,
		int animMulti = -1, std::string multiOption = "");
	inline void newID();
	void setZeroEvent(std::string eventname);
	void setZeroVariable(std::string variablename);

};

inline bool isPassed(int condition, std::unordered_map<int, bool> IsConditionOpened);
vecstr GetOptionInfo(std::string line, std::string format, std::string filename, int numline, std::vector<std::vector<std::shared_ptr<animationInfo>>> groupAnimInfo,
	bool allowNoFixAnim, bool isCondition, int groupMulti = -1, int animMulti = -1, int optionMulti = -1, std::string multiOption = "");
void nonGroupOptionInfo(vecstr& optionInfo, std::string line, std::string format, std::string filename, int numline,
	std::vector<std::vector<std::shared_ptr<animationInfo>>> groupAnimInfo, bool allowNoFixAnim, bool isCondition, int groupMulti, int animMulti, int optionMulti,
	std::string multiOption);
void optionLimiter(vecstr optionInfo, std::string line, std::string format, std::string filename, int numline,
	std::vector<std::vector<std::shared_ptr<animationInfo>>> groupAnimInfo, int open, bool isCondition, int curGroup, int curOrder, int limiter, int optionMulti);
std::string optionOrderProcess(std::string line, std::string format, std::string filename, int numline, int groupMulti, int lastOrder, bool isCondition,
	bool allowNoFixAnim);

#endif