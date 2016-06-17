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

typedef std::map<std::pair<std::string, std::string>, std::vector<std::string>> TableType;
typedef std::vector<std::pair<std::string, std::string>> BeginningType;

#if _MSC_VER == 1500
#define unique_ptr auto_ptr
#endif

int main(int argc, char **argv) {
	std::string input;
	std::getline(std::cin, input);
	MeCab::Tagger* tagger=MeCab::createTagger("-d F:\\Programming\\lib\\Mecab\\dic\\ipadic");
	CHECK(tagger);

	const MeCab::Node* node = tagger->parseToNode(input.c_str());
	CHECK(node);

	TableType MTable;
	BeginningType beginnings;

	//テーブル生成
	for (; node; node = node->next) {
		if (node->stat == MECAB_BOS_NODE||node->prev->stat==MECAB_BOS_NODE||node->stat == MECAB_EOS_NODE) {
			continue;
		}
			std::string str2, str1, str0;
			str2 = std::string(node->prev->prev->surface).substr(0,node->prev->prev->length);
			str1 = std::string(node->prev->surface).substr(0,node->prev->length);
			str0 = std::string(node->surface).substr(0, node->length);

		if (node->prev->prev->stat == MECAB_BOS_NODE) {
			//beginnings->push_back(make_pair(str1, str0));
			MTable[std::make_pair("。",str1)].push_back(str0);
			continue;
		}
		else {
			//テーブル追加
			MTable[std::make_pair(str2, str1)].push_back(str0);

			//文頭語
			if (str2 == "。") {
				beginnings.push_back(make_pair(str1, str0));
			}

		}
	}
#if 0
	std::printf("%s\t%s", (*beginnings)[0].first.c_str(), (*beginnings)[0].second.c_str());
	for (auto it = beginnings->begin()+1; it != beginnings->end(); it++) {
		std::printf("\t%s\t%s", it->first.c_str(), it->second.c_str());
	}
#endif
	for (TableType::iterator it = MTable.begin(); it != MTable.end(); it++) {
		std::printf("%s\t%s", it->first.first.c_str(), it->first.second.c_str());
		for (std::vector<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			std::printf("\t%s", it2->c_str());
		}
		std::printf("\n");
	}
	delete tagger;

	return 0;
}