#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <random>
#include <ctime>
#include <Mecab.h>
#include "MTable.h"
#include "Analyze.h"
#include "Character.h"
#include "Main.h"


int main(){
	srand((unsigned) time(NULL));
    //mtRand=std::mt19937(devRand());
    Character * sensei = new Character("F:\\aozora\\kokoro\\kokoro.markov");
    //std::cout<<mt.startSentence("下人")<<std::endl;
	std::cout<<sensei~>Respond("私")<<std::endl;
	delete sensei;
    return 0;
}
