#ifndef FMIndex_H
#define FMIndex_H

#include "LFTable.h"
#include "SuffixArray.h"
#include "CompressedSuffixArray.h"
#include <string>

class FMIndex{
private:
	LFTable *lfTable;
	SuffixArray *suffixArray;
	
public:
	FMIndex(std::string *text){
		/**Add terminating char*/
		text += '$';

		/**Create new LF table and suffix array*/
		lfTable = new LFTable(text);
		suffixArray = new CompressedSuffixArray(lfTable);
	}

	int find(std::string substring);
	int count(std::string substring);
private:
	void count(int &start, int &end, std::string substring);
};


#endif