#ifndef LFTable_H
#define LFTable_H

#include <stdio.h>
#include <string>
#include <conio.h>
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

	/**Danijel*/
	void max_heapify(char** arr, int i, int n);
	void heapsort(char **arr, int n);
	void build_maxheap(char **arr, int n);
	void switchItmes(char *&x, char *&y);

public:
	LFTable(std::string word, SuffixArray *suffixArray);
	int countFirst(char sign);
	int countLast(char sign);
	int getRankFirst(char sign, int index);
	int getRankLast(char sign, int index);
	char LFTable::getCharFirst(unsigned index);
	char LFTable::getCharLast(unsigned index);
	unsigned LFTable::getIndexFirst(char character, unsigned rank);
	unsigned LFTable::getIndexLast(char character, unsigned rank);
	unsigned LFTable::getLengthFirst();
	unsigned LFTable::getLengthLast();
	unsigned getAlphabet(char *&arr);
};

#endif
