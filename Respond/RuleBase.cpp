#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <random>
#include <regex>
#include <tuple>
#include "RuleBase.h"

void widen(const std::string &src, std::wstring &dest) {
	wchar_t *wcs = new wchar_t[src.length() + 1];
	mbstowcs(wcs, src.c_str(), src.length() + 1);
	dest = wcs;
	delete [] wcs;
}

void narrow(const std::wstring &src, std::string &dest) {
	char *mbs = new char[src.length() * MB_CUR_MAX + 1];
	wcstombs(mbs, src.c_str(), src.length() * MB_CUR_MAX + 1);
	dest = mbs;
	delete [] mbs;
}


RuleBase::RuleBase(void)
{
}

RuleBase::RuleBase(const std::string &regexpath, const std::string& serifpath):serifs(52)
{
	LoadRegex(regexpath);
	LoadSerif(serifpath);
	
}

int sigtonum(char c){
	return islower(c)?c-'a':26+c-'A';
}

void RuleBase::LoadRegex(const std::string& regexpath){
	std::ifstream ifs(regexpath.c_str());
	std::string line;
	std::string sig, type;
	std::wstring wline,regsrc;
	std::tr1::wregex re(L"^(.+)\\t(.+)\\t(.+)$");
	std::tr1::wsmatch matches;
	while(/*ifs>>sig>>type,ifs.ignore(),*/std::getline(ifs,line)){
		if(line.empty())continue;
		std::wstring wline;
		widen(line,wline);
		if(!std::tr1::regex_match(wline,matches,re))continue;
		narrow(matches.str(1),sig);
		narrow(matches.str(2),type);
		regsrc=matches.str(3);
		regexset tmp={sigtonum(sig[0]), type[0], std::tr1::wregex(regsrc)};
		this->re.push_back(tmp); 
    }
}


void RuleBase::LoadSerif(const std::string& serifpath){
	std::ifstream ifs(serifpath.c_str());
	std::string sig, serif,line;
	std::wstring wline;
	std::tr1::wregex re(L"^(.*)\\t(.+)$");
	std::tr1::wsmatch matches;
	while(/*ifs>>sig,ifs.ignore(),*/std::getline(ifs,line)){
		widen(line,wline);
		std::tr1::regex_match(wline, matches, re);
		narrow(matches.str(1), sig);
		narrow(matches.str(2), serif);
		for(std::string::iterator it=sig.begin();it!=sig.end(); ++it){
			serifs[sigtonum(*it)].push_back(serif);
		}
    }
}

RuleBase::~RuleBase(void)
{
}

std::string RuleBase::respondRuleBase(const std::string& input, const std::vector<std::string>& words){
	/*return randomChoice();*/
	std::string res=replyByWord(input,words);
	if(res!="")return res;
	if(!(rand()%6))return randomChoice();
	return "";
}

std::string RuleBase::randomChoice(){
	int t = rand()%serifs[0].size();
	return serifs[0][t];
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
			res|=int(std::tr1::regex_match(winput,it->re))<<it->signum;
		}
		if(it->type=='s'){
			res|=int(std::tr1::regex_search(winput,it->re))<<it->signum;
		}
		if(it->type=='t'){
			std::tr1::wsmatch matches;
			res|=int(std::tr1::regex_search(winput,matches,it->re))<<it->signum;
			whentype=matches.str(1);
			if(whentype==L""||whentype==L"いつ")whentype=L"";
			else whentype = whentype.substr(1);
		}
	}
	/*if(res&(1<<('i'-'a'))){
		
	}*/
	
	if(res&0x1fc){
	//質問された
		for(int i = 2; i<9; ++i){
			if(res&(long long(1)<<i)){
				int len=serifs[i].size();
				int limit = int(RAND_MAX*atan(float(len)/30)/acos(0.0));
				if(rand()<limit){
					//既定の答えを返す
					return serifs[i][rand()%len];
				}
			}
		}
		if(!serifs[1].empty()){
			int len=serifs[1].size();
			int t=rand()%len;
			if(!(rand()%6))return serifs[1][t];
		}
	}
  

	return "";
}