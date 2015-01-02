#include <conio.h>
#include <string>
#include <iostream>

#include "LFTable.h"
#include "PrefixSum.h"
#include "WaveletTree.h"
#include "WaveletTreeItem.h"

IOcc *treeFirst;
IOcc *treeLast;
PrefixSum *prefixSumFirst;
PrefixSum *prefixSumLast;

LFTable::LFTable(std::string word)
{
	std::cout << "Creating LF Table\n";
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
		std::cout << "Creating rotations: " << i << "\r";
		word = word.back()+word.substr(0, n - 1);
		sentence = new char[n];
		sentence[0] = '\0';
		strncat_s(sentence, n + 1, word.c_str(), n);
		arr[i] = sentence;
	}
	std::cout << "Creating rotations: completed\n";

	//applying the bubble sort
	/*bool flag = true;
	for (int i = 1; i<n && flag; i++)
	{
		flag = false;
		for (int j = 0; j<n - i; j++)
		{
			std::cout << i << ", " << j << "\r";
			if (_strcmpi(arr[j], arr[j + 1])>0)
			{
				char*tmp;
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = true;
			}
		}
	}*/
	
	//build_maxheap(arr, n);
	heapsort(arr, n);
	
	
	for (int i = 0; i < n; i++){
		std::cout << "Generating LF: " << i << "\r";
		std::string str = arr[i];
		textFirst += str.at(0);
		textLast += str.back();
	}
	std::cout << "Generating LF: completed\n";

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

/**Danijel
	Implementation of heap sort
*/
// Heap sort - setting heap
void LFTable::max_heapify(char **arr, int i, int n) {
	int j = 2 * i;
	char *item = arr[i];
	while (j <= n) {
		if ((j < n) && (_strcmpi(arr[j], arr[j + 1]) < 0)) j++;
		if (_strcmpi(item, arr[j]) >= 0) break;
		arr[j / 2] = arr[j];
		j *= 2;
	}
	arr[j / 2] = item;
}

// Heap sort - initial heap
void LFTable::build_maxheap(char **arr, int n) {
	for (int i = n / 2; i >= 0; --i)
		max_heapify(arr, i, n);
}

// Heap sort 
void LFTable::heapsort(char **arr, int n) {
	build_maxheap(arr, n - 1);
	for (int i = n - 1; i > 0;) {
		std::cout << "Sorting: " << i << "\r";
		switchItmes(arr[0], arr[i]);
		max_heapify(arr, 0, --i);
	}
	std::cout << "Sorting: completed\n";
}

void LFTable::switchItmes(char *&x, char *&y){
	char *tmp = x;
	x = y;
	y = tmp;
}
