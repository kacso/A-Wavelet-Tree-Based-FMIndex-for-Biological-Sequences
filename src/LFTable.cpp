#include <conio.h>
#include <string>
#include <iostream>

#include "LFTable.h"
#include "PrefixSum.h"
#include "SuffixArray.h"
#include "HeapSort.h"
#include "Sort.h"

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
	char **arr;
	int n = word.length();


	std::cout << "Creating rotations...\r";

	arr = new char*[n];
	/*for (int i = 0; i<n; i++)
		arr[i] = new char[n + 1];
*/
	char* sentence = new char[n + 1];
	sentence[0] = '\0';
	strncat_s(sentence, n+1, word.c_str(), n);
	arr[0] = sentence;
	for (int i = 1; i < n; i++){
		//std::cout << "Creating rotations: " << i << "\r";
		word = word.back()+word.substr(0, n - 1);
		sentence = new char[n + 1];
		sentence[0] = '\0';
		strncat_s(sentence, n + 1, word.c_str(), n);
		arr[i] = sentence;
	}
	std::cout << "Creating rotations: completed\n";
	
	Sort *sort = new HeapSort();
	sort->sort(arr, n);
	delete sort;

	/**Genereate suffix Array*/
	suffixArray->generateArray(this, arr);

	std::cout << "Generating LF...\r";

	for (int i = 0; i < n; i++){
		//std::cout << "Generating LF: " << i << "\r";
		std::string str = arr[i];
		textFirst += str.at(0);
		textLast += str.back();
	}
	std::cout << "Generating LF: completed\n";

	std::cout << "Releasing allocated space...\r";
	/**Free allocated space*/
	for (int i = n - 1; i >= 0; --i){
		delete []arr[i];
	}
	delete []arr;
	std::cout << "Releasing allocated space: completed\n";
	//creating WaveletTree
	treeFirst = new WaveletTree(textFirst);
	treeLast = new WaveletTree(textLast);

	prefixSumFirst = new PrefixSum(textFirst);
	prefixSumLast = new PrefixSum(textLast);

	std::cout << "LF Table generated\n";
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