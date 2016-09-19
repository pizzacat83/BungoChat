#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <regex>
#include <tuple>
#include "RuleBase.h"

RuleBase::RuleBase(void)
{
}

RuleBase::RuleBase(const std::string &regexpath, const std::string& serifpath):serifs(52)
{
	
}

int sigtonum(char c){
	return std::islower(c)?c-'a':26+c-'A';
}

void RuleBase::LoadRegex(const std::string& regexpath){
	std::ifstream ifs(regexpath.c_str());
	std::string line;
	char sig, type;
	while(ifs>>sig>>type,ifs.ignore(),std::getline(ifs,line)){
		if(line.empty())continue;
		std::wstring wline;
		widen(line,wline);
		regexset tmp={sigtonum(sig), type, std::tr1::wregex(wline)};
		re.push_back(tmp); 
    }
}


void RuleBase::LoadSerif(const std::string& serifpath){
	std::ifstream ifs(serifpath.c_str());
	std::string sig, line;
	while(ifs>>sig,ifs.ignore(),std::getline(ifs,line)){
		for(std::string::iterator it=sig.begin();it!=sig.end(); ++it){
			serifs[sigtonum(*it)].push_back(line);
		}
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
	//std::tr1::wregex re(L"((あなた|貴方|アナタ|君|きみ|キミ|お前|おまえ|てめえ|てめー|テメー|手前|おめえ|貴様|きさま|あんた|アンタ)(の)?)?(お|御)?(名前|なまえ|名)(((は|って)?(何(なん)?(だ|((です|でしょう|である|であります|でありましょう)(か?)))?)?)|((を)?(教え|おしえ)((て|ろ)(ください|くれ)?(さ|ね|よ|よね)?|よ)))(\\?|？|。)?");
	std::wstring winput;
	widen(input,winput);
	/*if(std::tr1::regex_match(winput,re)){
		return"名前はまだ無い。";
	}*/
	long long int res=0;
	std::wstring whentype;
	for(std::vector<regexset>::iterator it=re.begin(); it!=re.end(); ++it){
		if(it->type=='m'){
			res|=int(std::tr1::regex_match(winput,re))<<it->signum;
		}
		if(it->type=='s'){
			res|=int(std::tr1::regex_search(winput,re))<<it->signum;
		}
		if(it->type=='t'){
			std::tr1::match_results<std::wstring> matches;
			res|=int(std::tr1::regex_search(winput,re,matches)<<it->signum;
			whentype=matches.str(1);
			if(whentype==L"いつ")whentype="";
			else whentype.substr(1);
		}
	}
if(res&0x1fc){
  //質問された
  if(!serifs[1].empty()){
    len=serifs[1].size();
    int t=rand()%len;
    return serifs[1][t];
  }
}
  

	return "";
}