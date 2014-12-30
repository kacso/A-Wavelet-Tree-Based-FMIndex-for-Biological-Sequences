#ifndef FMIndex_H
#define FMIndex_H

#include "LFTable.h"
#include "SuffixArray.h"
#include "CompressedSuffixArray.h"
#include <string>

#include <algorithm>    // std::sort

class FMIndex{
private:
	LFTable *lfTable;
	SuffixArray *suffixArray;
	char *alphabet;
	std::map<char, unsigned> mapAlphabet;
	
public:
	FMIndex(std::string text){
		std::cout << "Creating FMIndex\n";
		unsigned j = 0;
		/**createAlphabet*/
		for (unsigned i = 0; i < text.length(); ++i){
			if (mapAlphabet.count(text[i]) == 0) {
				mapAlphabet[text[i]] = j++;
			}
		}
		mapAlphabet['$'] = mapAlphabet.size();

		this->alphabet = new char[mapAlphabet.size()];
		unsigned i = 0;
		for (std::map<char, unsigned>::iterator it = mapAlphabet.begin(); it != mapAlphabet.end(); ++it) {
			alphabet[i++] = it->first;
		}
		std::sort(alphabet, alphabet + mapAlphabet.size());

		/**Create new LF table and suffix array*/
		lfTable = new LFTable(text);
		suffixArray = new CompressedSuffixArray(lfTable);
		std::cout << "FMIndex created\n";
	}

	int find(std::string substring);
	int count(std::string substring);
private:
	void count(int &start, int &end, std::string substring);
};


#endif