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

std::string Character::respondMarkov(const std::vector<std::string>& words)const{
	std::string res;
	std::set<int> checked;
	while(true){
		int next = rand()%words.size();
		if (checked.count(next))continue;	//既に調べた単語
		res = mtable.makeSentence(words[next]);
		if (!res.empty()) {
			//文生成成功
			break;
		}
		else {
			//nextの単語では文を続けられない
			checked.insert(next);
			if (checked.size() == words.size()) return "";	//与えられた単語での文生成不可能
		}
	}
	return res;
}



std::string Character::Respond(const std::string& input){
	analyzer.AnalyzeString(input);
	std::vector<std::string> words=analyzer.extractIndependent();//活用形をもっと豊富にしたいよね
	if(words.empty())return rulebase.respondRuleBase(input,words);
	std::string res = respondMarkov(words);
	return res.empty()?rulebase.respondRuleBase(input,words):res;
}