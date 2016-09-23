#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <random>
#include <ctime>
#include <Mecab.h>
#include <regex>
#include "MTable.h"
#include "Analyze.h"
#include "RuleBase.h"
#include "Character.h"
#include "Main.h"


int main(){
	setlocale(LC_CTYPE, "");
	srand((unsigned) time(NULL));
    //mtRand=std::mt19937(devRand());
	Character * sensei = new Character(std::string("F:\\Programming\\Desktop\\cpp\\Bungo\\Bungo_2008\\aozora\\kokoro\\kokoro.markov"), "F:\\Programming\\Desktop\\cpp\\Bungo\\Bungo_2008\\Respond\\RuleBasePatterns.rx" , std::string("F:\\Programming\\Desktop\\cpp\\Bungo\\Bungo_2008\\aozora\\kokoro\\kokoro_serif.txt"));
    //std::cout<<mt.startSentence("下人")<<std::endl;
	while(1){
		std::string line;
		std::cout<<"ぴざきゃっと:　　　";
		std::getline(std::cin, line);
		std::cout<<"しょうもないもの:　"<<sensei->Respond(std::string(line))<<std::endl;
	}
	/*std::string line="いやいや";
	for(int i = 0; i<50; ++i){
		line=sensei->Respond(line);
		std::cout<<line<<std::endl;;
	}*/
	delete sensei;
    return 0;
}
