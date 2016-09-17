#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <regex>
#include "RuleBase.h"

RuleBase::RuleBase(void)
{
}

RuleBase::RuleBase(const std::string &path)
{
	std::ifstream ifs(path.c_str());
	std::string line;
	while(std::getline(ifs,line)){
		if(line[0]=='#')continue;
		serifs.push_back(line);
    }
}

RuleBase::~RuleBase(void)
{
}

std::string RuleBase::respondRuleBase(const std::string& input, const std::vector<std::string>& words){
	/*return randomChoice();*/
	std::string res=replyByWord(input,words);
	return res!=""?res:randomChoice();
}

std::string RuleBase::randomChoice(){
	int t = rand()%serifs.size();
	return serifs[t];
}

std::string RuleBase::replyByWord(const std::string &input, const std::vector<std::string> &words){
	std::regex re("(.+)(Ç∆ÇÕ|Ç¡Çƒ)(âΩ)?(Çæ|Ç≈Ç∑)?(Ç©)?(//?|ÅH)?");
