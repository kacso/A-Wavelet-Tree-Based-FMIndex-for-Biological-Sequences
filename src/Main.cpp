#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "WaveletTree.h"
#include "WaveletTreeItem.h"
#include "FMIndex.h"
#include "PrefixSum.h"


void printTree(WaveletTreeItem *root){
	if (root == nullptr || root->bitStringLength == 0) return;
	for (unsigned i = 0; i < root->bitStringLength; i++){
		std::cout << root->bitString[i];
	}
	std::cout << "\n";
	printTree(root->leftChild);
	printTree(root->rightChild);
}

int main(){
	std::ios::sync_with_stdio(false);
	std::string fileName;
	std::cout << "Enter file name:\n";
	std::cin >> fileName;
	//std::getline(std::cin, text);
	std::ifstream in(fileName);
	std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

	//LFTable lfTable = LFTable(text);

/*	SuffixArray *sArray = new CompressedSuffixArray(&lfTable);
	
	for (unsigned i = 0; i <= text.length(); ++i){
		std::cout << "Array[" << i << "] = " << sArray->getItem(i) << "\n";
	}*/

	/*text += '$';
	IOcc *tree =  new WaveletTree(text);
	//printTree(tree->getRoot());

	for (unsigned i = 0; i < text.length(); i++){
		std::cout << "(A, " << i <<")" << tree->getRank('A', i) << "\n";
		std::cout << "(C, " << i << ")" << tree->getRank('C', i) << "\n";
		std::cout << "(G, " << i << ")" << tree->getRank('G', i) << "\n";
		std::cout << "(T, " << i << ")" << tree->getRank('T', i) << "\n";

		std::cout << "Char at index " << i << ": " << tree->getChar(i) << "\n";
	}*/

	//std::cout << "Count: " << (new PrefixSum(text))->count('C') << "\n";
	//std::cout << "Count: " << lfTable.countLast('C') << "\n";

	FMIndex *index = new FMIndex(text);
	std::string search;
	while (1){
		std::cout << "Enter search pattern: ";
		std::cin >> search;
		std::cout << "Count: " << index->count(search) << "\n";
		std::cout << "Find: ";
		std::vector<unsigned> results = index->find(search);
		if (results.empty()){
			std::cout << "Can't find pattern: " << search;
		}
		else{
			for (std::vector<unsigned>::iterator it = results.begin(); it != results.end(); ++it){
				std::cout << " " << *it;
			}
		}
		std::cout << "\n";
	}

	return 0;
}
