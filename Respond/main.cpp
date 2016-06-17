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
//using namespace std;

//map<pair<string, string>, vector<string>> MTable;
//vector<pair<string,string>> beginnings;

//std::random_device devRand; // 非決定的な乱数生成器
//std::mt19937 mtRand; //メルセンヌツイスタ
/*
void loadBeginnings(const string& line){
    stringstream sline;
    sline<<line;
    string w1,w2;
    while(sline>>w1&&sline>>w2){
        //printf("ok\n");
        //cout<<"load: "<<w1<<" "<<w2<<endl;
        beginnings.push_back(make_pair(w1,w2));
    }
}

void loadTableRow(const string& line){
    //stringの値渡しコスト
    stringstream sline;
//    cout<<line<<endl;
    sline<<line;
    string s1,s2,word;
    sline>>s1>>s2;
    //cout<<s1<<s2<<endl;
    vector<string> v;
    while(sline>>word){
        v.push_back(word);
        //cout<<word<<endl;
    }
    MTable[make_pair(s1,s2)]=v;
}

string makeSentence(const string& s1,const string& s2){
    //stringの値渡しコスト
    if(s2=="。")return std::move(s1+s2);
    pair<string,string> p=make_pair(s1,s2);
    if(MTable[p].size()==0)cout<<"no element: "<<s1<<" "<<s2<<endl;
    uniform_int_distribution<int> dist(0, MTable[p].size()-1);
    //cout<<dist(mtRand)<<endl;
    return std::move(s1+makeSentence(s2, MTable[p][dist(mtRand)]));
}

void printTable(){
    for(auto it=MTable.begin(); it!=MTable.end();it++){
        printf("%s %s ", it->first.first.c_str(), it->first.second.c_str());
        for(auto it2=it->second.begin(); it2!=it->second.end();it2++){
            printf("%s ", it2->c_str());
        }
        printf("\n");
    }
}


int main(void){
    // Here your code !
    string line;
    getline(cin,line);
    loadBeginnings(line);
    while(getline(cin,line)){
        loadTableRow(line);
    }
    //cout<<beginnings.size()<<endl;
    //printTable();
    uniform_int_distribution<int> dist(0, beginnings.size()-1);
    for(int i=0;i<100;i++){
        //try{
        //cout<<"begin:"<<a<<endl;
        pair<string,string> p=beginnings[dist(mtRand)];
        //printf("%s %s\n",p.first.c_str(),p.second.c_str());
        printf("%s\n", makeSentence(p.first,p.second).c_str());
        //}catch(...){
            
        //}
        
        
    }
    return 0;
}*/

int main(){
	srand((unsigned) time(NULL));
    //mtRand=std::mt19937(devRand());
    Character * sensei = new Character("F:\\aozora\\kokoro\\kokoro.markov");
    //std::cout<<mt.startSentence("下人")<<std::endl;
	std::cout<<sensei~>Respond("私")<<std::endl;
	delete sensei;
    return 0;
}
