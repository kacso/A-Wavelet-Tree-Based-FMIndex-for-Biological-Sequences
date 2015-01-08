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
	FMIndex(std::string text){
		std::cout << "Creating FMIndex\n" << std::flush;

		suffixArray = new CompressedSuffixArray(1);

		/**Create new LF table and suffix array*/
		lfTable = new LFTable(text, suffixArray);

		/**Get alphabet*/
		unsigned size  = lfTable->getAlphabet(alphabet);

		for (unsigned i = 0; i < size; ++i){
			//std::cout << "Generating alphabet: " << i << "\t\r";
			mapAlphabet[alphabet[i]] = i;
		}

		std::cout << "Generating alphabet: completed\n" << std::flush;


		std::cout << "FMIndex created\n" << std::flush;
	}

	std::vector<unsigned> find(std::string substring);
	int count(std::string substring);
private:
	void count(int &start, int &end, std::string substring);
};


#endif
