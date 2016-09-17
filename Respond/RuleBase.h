#pragma once
/*requires:
#include <vector>
#include <string>
*/

class RuleBase
{
private:
	std::vector<std::string> serifs;
	std::string randomChoice();
	std::string replyByWord(const std::string& input, const std::vector<std::string>& words);
public:
	RuleBase(void);
	RuleBase(const std::string &path);
	~RuleBase(void);
	std::string respondRuleBase(const std::string& input, const std::vector<std::string>& words);
};
