#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <mecab.h>
#include <memory>

#define CHECK(eval) if (! eval) { \
   const char *e = tagger ? tagger->what() : MeCab::getTaggerError(); \
   std::cerr << "Exception:" << e << std::endl; \
   return -1; }


bool isIndependent(int posid){
	if((10<=posid&&posid<=12)||(31<=posid))return true;
	else return false;
}

bool isNoun(int posid){
	if(36<=posid&&posid<=67)return true;
	else return false;
}

int main(int argc, char **argv) {
	std::string input;
	std::getline(std::cin, input);
	MeCab::Tagger* tagger=MeCab::createTagger("-d F:\\Programming\\lib\\Mecab\\dic\\ipadic");
	CHECK(tagger);

	const MeCab::Node* node = tagger->parseToNode(input.c_str());
	CHECK(node);

	for(; node; node=node->next){
		/*if(isIndependent(node->posid))std::cout<<"["<<node->posid<<"]";
		else std::cout<<std::string(node->surface).substr(0,node->length);*/
		if(isNoun(node->posid))std::cout<<std::string(node->surface).substr(0,node->length)<<std::endl;
/*		
    std::cout 
		<<std::string(node->surface).substr(0,node->length)
		//<< ' ' << node->feature
		//<< '\t' << (int)(node->surface - input.c_str())
	      //<< '\t' << (int)(node->surface - input.c_str() + node->length)
	      << '\t' << node->rcAttr	//右文脈ID
	      << '\t' << node->lcAttr	//左文脈ID
	      << '\t' << node->posid	//品詞ID
	      //<< '\t' << (int)node->char_type
	      //<< '\t' << (int)node->stat
	      //<< '\t' << (int)node->isbest
	      //<< '\t' << node->alpha
	      //<< '\t' << node->beta
	      //<< '\t' << node->prob
	      //<< '\t' << node->cost
		  << std::endl;*/
	}

	delete tagger;

	return 0;
}