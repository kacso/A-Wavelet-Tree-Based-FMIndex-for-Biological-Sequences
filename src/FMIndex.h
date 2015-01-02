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
		unsigned size = mapAlphabet.size();
		this->alphabet = new char[size];
		unsigned i = 0;
		for (std::map<char, unsigned>::iterator it = mapAlphabet.begin(); it != mapAlphabet.end(); ++it) {
			alphabet[i++] = it->first;
		}
		std::sort(alphabet, alphabet + size);

		mapAlphabet.erase(mapAlphabet.begin(), mapAlphabet.end());

		for (unsigned i = 0; i < size; ++i){
			mapAlphabet[alphabet[i]] = i;
		}

		/**Create new LF table and suffix array*/
		lfTable = new LFTable(text);
		
		std::cout << "LFTable size: " << sizeof(*lfTable) << "\n";
		suffixArray = new CompressedSuffixArray(lfTable, 4);
		std::cout << "SuffixArray size: " << sizeof(*suffixArray) << "\n";
		std::cout << "FMIndex created\n";
		std::cout << "FMIndex size: " << sizeof(*this) << "\n";
	}

	std::vector<unsigned> find(std::string substring);
	int count(std::string substring);
private:
	void count(int &start, int &end, std::string substring);
};


#endif