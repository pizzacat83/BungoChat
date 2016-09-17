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

void widen(const std::string &src, std::wstring &dest) {
	wchar_t *wcs = new wchar_t[src.length() + 1];
	mbstowcs(wcs, src.c_str(), src.length() + 1);
	dest = wcs;
	delete [] wcs;
}

std::string RuleBase::replyByWord(const std::string &input, const std::vector<std::string> &words){
	//std::regex re("(.+)(とは|って)(何)?(だ|です)?(か)?(//?|？)?");*/
	std::tr1::wregex re(L"((あなた|貴方|アナタ|君|きみ|キミ|お前|おまえ|てめえ|てめー|テメー|手前|おめえ|貴様|きさま|あんた|アンタ)(の)?)?(お|御)?(名前|なまえ|名)(((は|って)?(何(なん)?(だ|((です|でしょう|である|であります|でありましょう)(か?)))?)?)|((を)?(教え|おしえ)((て|ろ)(ください|くれ)?(さ|ね|よ|よね)?|よ)))(\\?|？|。)?");
	std::wstring winput;
	widen(input,winput);
	if(std::tr1::regex_match(winput,re)){
		return"名前はまだ無い。";
	}
	return "";
}