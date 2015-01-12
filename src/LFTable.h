#ifndef LFTable_H
#define LFTable_H

#include <stdio.h>
#include <string>
#include <iostream>
#include "IOcc.h"
#include "PrefixSum.h"
#include "WaveletTree.h"

class SuffixArray;

class LFTable{
private:
	IOcc *treeFirst;
	IOcc *treeLast;
	PrefixSum *prefixSumFirst;
	PrefixSum *prefixSumLast;
	std::string createF(std::string word, SuffixArray *suffixArray);
	std::string createL(std::string word, SuffixArray *suffixArray);

public:
	LFTable(std::string word, SuffixArray *suffixArray);
	int countFirst(char sign);
	int countLast(char sign);
	int getRankFirst(char sign, int index);
	int getRankLast(char sign, int index);
	char getCharFirst(unsigned index);
	char getCharLast(unsigned index);
	unsigned getIndexFirst(char character, unsigned rank);
	unsigned getIndexLast(char character, unsigned rank);
	unsigned getLengthFirst();
	unsigned getLengthLast();
	unsigned getAlphabet(char *&arr);
};

#endif
