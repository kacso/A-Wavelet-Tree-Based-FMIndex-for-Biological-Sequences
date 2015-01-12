/**************************************************************
* Suffix Array is implemented with
* Nong-Zhang-Chan algorithm
***************************************************************/

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
	void BToEnd(std::map<unsigned char, int> &B, std::map<unsigned char, unsigned> alphabet, unsigned n);
	void BToStart(std::map<unsigned char, int> &B, std::map<unsigned char, unsigned> alphabet, unsigned n);

	void generateArray(std::vector<unsigned> word, std::map<unsigned, int> &suffixArray);
	bool getType(std::vector<unsigned> word, std::vector<bool> t, unsigned i);
	void BToEnd(std::map<unsigned, int> &B, std::map<unsigned, unsigned> alphabet, unsigned n);
	void BToStart(std::map<unsigned, int> &B, std::map<unsigned, unsigned> alphabet, unsigned n);
};

#endif
