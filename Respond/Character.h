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
	std::string respondMarkov(const std::vector<std::string>& words)const;
public:
    Character();
	~Character();
    Character(const std::string& path);
    std::string Respond(const std::string& input);
};