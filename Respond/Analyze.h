#pragma once

class Analyze{
private:
	bool isNoun(const MeCab::Node * node);
	bool isIndependent(const MeCab::Node * node);
    
    std::string str;
    const MeCab::Node *BOSnode;
    MeCab::Tagger* tagger;
    
public:
    Analyze();
    ~Analyze();
    void AnalyzeString(const std::string& input);
    std::vector<std::string> extractNoun();
    std::vector<std::string> extractIndependent();

    
};