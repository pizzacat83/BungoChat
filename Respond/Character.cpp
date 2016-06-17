#include <map>
#include <vector>
#include <string>
#include <random>
#include <mecab.h>
#include "MTable.h"
#include "Analyze.h"
#include "Character.h"

Character::Character(void){
}

Character::Character(const std::string& path):mtable(path){
}

Character::~Character(void){
}

std::string Character::respondMarkov(const std::string& word){
	return mtable.makeSentence(word);
}


std::string Character::Respond(const std::string& input){
	analyzer.AnalyzeString(input);
	std::vector<std::string> v=analyzer.extractIndependent();
	return mtable.makeSentence(v[rand()%v.size()]);
}