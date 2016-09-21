#pragma once
/*requires:
#include <vector>
#include <string>
#include <regex>
*/

struct regexset{
	char signum;
	char type;
	std::tr1::wregex re;
};

class RuleBase
{
private:
	std::vector<std::vector<std::string>> serifs;
	std::vector<regexset> re;
	void LoadRegex(const std::string& regexpath);
	void LoadSerif(const std::string& serifpath);
	std::string randomChoice();
	std::string replyByWord(const std::string& input, const std::vector<std::string>& words);
public:
	RuleBase(void);
	RuleBase(const std::string &regexpath, const std::string &serifpath);
	~RuleBase(void);
	std::string respondRuleBase(const std::string& input, const std::vector<std::string>& words);
};
