#ifndef FMIndex_H
#define FMIndex_H

#include "LFTable.h"
#include "SuffixArray.h"
#include "CompressedSuffixArray.h"
#include <string>
#include <vector>
#include <algorithm>    // std::sort

class FMIndex{
private:
	LFTable *lfTable;
	SuffixArray *suffixArray;
	char *alphabet = nullptr;
	std::map<char, unsigned> mapAlphabet;
	
public:
	FMIndex(std::string text);

	std::vector<unsigned> find(std::string substring);
	int count(std::string substring);
private:
	void count(int &start, int &end, std::string substring);
};


#endif
