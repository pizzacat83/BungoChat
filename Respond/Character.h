#pragma once
/*requires:
#include <map>
#include <vector>
#include <string>
#include "MTable.h"
*/
class Character{
private:
    MTable mtable;
	Analyze analyzer;
	RuleBase rulebase;
	std::string respondMarkov(const std::vector<std::string>& words)const;
public:
    Character();
	~Character();
	Character(const std::string& MTablePath, const std::string& RuleBasePath);
    std::string Respond(const std::string& input);
};