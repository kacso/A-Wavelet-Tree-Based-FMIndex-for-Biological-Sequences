#include <conio.h>
#include <string>
#include <iostream>
#include "LFTable.h"
#include "PrefixSum.h"
#include "WaveletTree.h"
#include "WaveletTreeItem.h"

WaveletTree *treeFirst;
WaveletTree *treeLast;
PrefixSum *prefixSumFirst;
PrefixSum *prefixSumLast;

LFTable::LFTable(std::string word)
{
	std::string textFirst;
	std::string textLast;
	word = word + '$';
	char **arr;
	int n = word.length();
	arr = new char*[n];
	for (int i = 0; i<n; i++)
		arr[i] = new char[n];
	
	char* sentence = new char[n];
	sentence[0] = '\0';
	strncat_s(sentence, n+1, word.c_str(), n);
	arr[0] = sentence;
	for (int i = 1; i < n; i++){
		word = word.back()+word.substr(0, n - 1);
		sentence = new char[n];
		sentence[0] = '\0';
		strncat_s(sentence, n + 1, word.c_str(), n);
		arr[i] = sentence;
	}
		

	//applying the bubble sort
	for (int i = 1; i<n; i++)
	{
		for (int j = 0; j<n - i; j++)
		{
			if (_strcmpi(arr[j], arr[j + 1])>0)
			{
				char*tmp;
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}

	
	for (int i = 0; i < n; i++){
		std::string str = arr[i];
		textFirst += str.at(0);
		textLast += str.back();
	}

	//creating WaveletTree
	treeFirst = new WaveletTree(textFirst);
	treeLast = new WaveletTree(textLast);

	prefixSumFirst = new PrefixSum(textFirst);
	prefixSumLast = new PrefixSum(textLast);
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
