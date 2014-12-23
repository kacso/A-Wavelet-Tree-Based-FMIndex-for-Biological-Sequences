#ifndef LFTable_H
#define LFTable_H

#include <stdio.h>
#include <string>
#include <conio.h>
#include <iostream>
#include "WaveletTree.h"

class LFTable{
private:
	std::string textFirst;
	std::string textLast;
	WaveletTree *treeFirst;
	WaveletTree *treeLast;
public:
	LFTable(std::string word);
	int countFirst(char sign);
	int countLast(char sign);
	int getRankFirst(char sign, int index);
	int getRankLast(char sign, int index);
};

#endif
