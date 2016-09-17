#include <map>
#include <vector>
#include <string>
#include <random>
#include <set>
#include <mecab.h>
#include "MTable.h"
#include "Analyze.h"
#include "RuleBase.h"
#include "Character.h"

Character::Character(void){
}

Character::Character(const std::string& MTablePath, const std::string& RuleBasePath):mtable(MTablePath), rulebase(RuleBasePath){
}

Character::~Character(void){
}





std::string Character::Respond(const std::string& input){
	analyzer.AnalyzeString(input);
	std::vector<std::string> words=analyzer.extractIndependent();//活用形をもっと豊富にしたいよね
	/*if(words.empty())return rulebase.respondRuleBase(input,words);
	std::string res = mtable.respondMarkov(words);
	return res.empty()?rulebase.respondRuleBase(input,words):res;*/
	return rulebase.respondRuleBase(input,words);
}