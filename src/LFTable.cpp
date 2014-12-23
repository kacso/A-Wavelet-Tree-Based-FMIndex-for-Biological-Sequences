#include <conio.h>
#include <string>
#include <iostream>
#include "LFTable.h"
#include "PrefixSum.h"
#include "WaveletTree.h"
#include "WaveletTreeItem.h"

std::string textFirst;
std::string textLast;
WaveletTree *treeFirst;
WaveletTree *treeLast;

LFTable::LFTable(std::string word)
{
	word = word + '$';
	char **arr;
	int n = word.length();
	
	//dynamic memory allocation
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
}

int LFTable::countFirst(char sign){
	PrefixSum prefixSum(textFirst);
	int result = prefixSum.count(sign);
	return result;
}

int LFTable::countLast(char sign){
	PrefixSum prefixSum(textLast);
	int result = prefixSum.count(sign);
	return result;

}

int LFTable::getRankFirst(char sign, int index){
	int result = treeFirst->getRank(sign, index);
	return result;
}

int LFTable::getRankLast(char sign, int index){
	int result = treeLast->getRank(sign, index);
	return result;

}
