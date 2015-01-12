#include <string.h>
#include <iostream>

#include "LFTable.h"
#include "PrefixSum.h"
#include "SuffixArray.h"

/**Contructor of object
* [in] word : string on which table will be generated
* [in] suffixArray : reference to suffix array of word
*/
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

/**Creates last columns of lf table as string
* [in] word : string on which table will be generated
* [in] suffixArray : reference to suffix array of word
* [out] last column
*/
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

/**Creates first columns of lf table as string
* [in] word : string on which table will be generated
* [in] suffixArray : reference to suffix array of word
* [out] first column
*/
std::string LFTable::createF(std::string word, SuffixArray *suffixArray){
	std::string first;
	for (unsigned i = 0; i < word.length(); ++i){
		first += word.at(suffixArray->getItem(i));
	}
	return first;
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
