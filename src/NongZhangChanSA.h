#ifndef NongZhangChanSA_H
#define NongZhangChanSA_H

#include "SuffixArray.h"
#include <map>

class NongZhangChanSA : public SuffixArray{
private:
	std::map<unsigned, int> suffixArray;
public:
	NongZhangChanSA(std::string word);
	virtual unsigned getItem(unsigned i);
private:
	void generateArray(std::string word, std::map<unsigned, int> &suffixArray);
	bool getType(std::string word, std::vector<bool> t, unsigned i);
	void BToEnd(std::map<char, int> &B, std::map<char, unsigned> alphabet, unsigned n);
	void BToStart(std::map<char, int> &B, std::map<char, unsigned> alphabet, unsigned n);
};

#endif
