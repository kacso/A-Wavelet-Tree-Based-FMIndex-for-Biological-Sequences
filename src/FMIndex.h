#ifndef FMIndex_H
#define FMIndex_H

#include "LFTable.h"
#include "SuffixArray.h"
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
		suffixArray = new SuffixArray(lfTable);
	}

	int findText(std::string substring);
};


#endif