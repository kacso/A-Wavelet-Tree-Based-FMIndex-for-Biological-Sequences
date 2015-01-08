//#include <conio.h>
#include <string.h>
#include <iostream>

#include "LFTable.h"
#include "PrefixSum.h"
#include "SuffixArray.h"
#include "WaveletHeapSort.h"
#include "Sort.h"
#include <exception>

WaveletTree *treeFirst;
WaveletTree *treeLast;
PrefixSum *prefixSumFirst;
PrefixSum *prefixSumLast;

LFTable::LFTable(std::string word, SuffixArray *suffixArray)
{
	std::cout << "Creating LF Table\n";
	
	std::string textFirst;
	std::string textLast;
        
	word = word + '$';
	//	char **arr;
	int n = word.length();

	WaveletTree **arr = createRotations(word, n);
	
	Sort *sort = new WaveletHeapSort();
	sort->sort(arr, n);
      	delete sort;

	createFirstAndLast(arr, textFirst, textLast);

	std::cout << "Releasing allocated space...\r";
	/**Free allocated space*/
	/*for (int i = n - 1; i >= 0; --i){
		arr[i]->~WaveletTree();
		delete []arr[i];
	}
	delete []arr;*/
	std::cout << "Releasing allocated space: completed\n";
	//creating WaveletTree
	treeFirst = new WaveletTree(textFirst);
	treeLast = new WaveletTree(textLast);

	/**Genereate suffix Array*/
	suffixArray->generateArray(this, arr);

	prefixSumFirst = new PrefixSum(textFirst);
	prefixSumLast = new PrefixSum(textLast);
		
	std::cout << "LF Table generated\n";
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
