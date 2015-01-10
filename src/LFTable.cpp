//#include <conio.h>
#include <string.h>
#include <iostream>

#include "LFTable.h"
#include "PrefixSum.h"
#include "SuffixArray.h"
#include "WaveletHeapSort.h"
#include "Sort.h"
#include <exception>

LFTable::LFTable(std::string word, SuffixArray *suffixArray)
{
	std::cout << "Creating LF Table\n";
        
	//word = word + '$';

	std::string textFirst = createF(word, suffixArray);
	std::string textLast = createL(word, suffixArray);

	treeFirst = new WaveletTree(textFirst);
	treeLast = new WaveletTree(textLast);

	prefixSumFirst = new PrefixSum(textFirst);
	prefixSumLast = new PrefixSum(textLast);
		
	std::cout << "LF Table generated\n";
}

std::string LFTable::createL(std::string word, SuffixArray *suffixArray){
	std::string last;
	for (unsigned i = 0; i < word.length(); ++i){
		unsigned item = suffixArray->getItem(i);
		if (item == 0){
			last += '$';
		}
		else {
			last += word.at(item - 1);
		}
	}
	return last;
}

std::string LFTable::createF(std::string word, SuffixArray *suffixArray){
	std::string first;
	for (unsigned i = 0; i < word.length(); ++i){
		first += word.at(suffixArray->getItem(i));
	}
	return first;
}

WaveletTree** LFTable::createRotations(std::string word, unsigned n){
  std::cout << "Creating rotations...\r" << std::flush;

	WaveletTree **arr = nullptr;

	try{
		/**Create array of all rotations stored as WaveletTree*/
		arr = new WaveletTree*[n];

		/**Create rotations*/
		for (int i = 0; i < n; ++i){
		  //	  std::cout << "Creating rotations: " << i << "\r";
			/**Store current word as WaveletTree*/
			arr[i] = new WaveletTree(word);

			/**Make next rotation*/
			word = word.back() + word.substr(0, n - 1);
		}
	}
	catch (std::bad_alloc &e){
		std::cerr << "bad_alloc caught: " << e.what() << "\n";
		exit(-1);
	}

	std::cout << "Creating rotations: completed\n" << std::flush;
	return arr;
}

void LFTable::createFirstAndLast(WaveletTree **arr, std::string &textFirst, std::string &textLast){
  std::cout << "Generating LF...\r" << std::flush;
	
	unsigned n = arr[0]->length();
	/**Generate string from first and last column of all rotations*/
	for (unsigned i = 0; i < n; i++){
		textFirst += arr[i]->getChar(0);
		textLast += arr[i]->getChar(n - 1);
	}

	std::cout << "Generating LF: completed\n" << std::flush;
}

int LFTable::countFirst(char sign){
	return prefixSumFirst->count(sign);
}

int LFTable::countLast(char sign){
	return prefixSumLast->count(sign);

}

int LFTable::getRankFirst(char sign, int index){
	return treeFirst->getRank(sign, index);
}

int LFTable::getRankLast(char sign, int index){
	return treeLast->getRank(sign, index);

}

char LFTable::getCharFirst(unsigned index){
	return treeFirst->getChar(index);
}

char LFTable::getCharLast(unsigned index){
	return treeLast->getChar(index);
}

unsigned LFTable::getIndexFirst(char character, unsigned rank){
	return treeFirst->indexOf(character, rank);
}

unsigned LFTable::getIndexLast(char character, unsigned rank){
	return treeLast->indexOf(character, rank);
}

unsigned LFTable::getLengthFirst(){
	return treeFirst->length();
}

unsigned LFTable::getLengthLast(){
	return treeLast->length();
}

unsigned LFTable::getAlphabet(char *&arr){
	return treeLast->getAlphabet(arr);
}
