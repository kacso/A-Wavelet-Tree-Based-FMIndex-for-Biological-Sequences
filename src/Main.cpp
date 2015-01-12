#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include "FMIndex.h"

void printTree(WaveletTreeItem *root){
	if (root == nullptr || root->bitStringLength == 0) return;
	for (unsigned i = 0; i < root->bitStringLength; i++){
		std::cout << root->bitString[i];
	}
	std::cout << "\n";
	printTree(root->leftChild);
	printTree(root->rightChild);
}

int main(int argc, char* argv[]){
	/**Check number of parameteres*/
	if (argc < 3) {
		std::cerr << "Usage: " << argv[0] << " filename sequenceIdentifier\n";
		return 1;
	}

	/***Read parameters*/
	char* fileName = argv[1];
	char* sequenceID = argv[2];
	
	std::string text;
	std::ios::sync_with_stdio(false);

	/**Open stream*/
	std::ifstream stream;
	stream.open(fileName);

	if (!stream.is_open()) {
		/**Problem with opening file*/
		std::cout << "Unable to open file: " << fileName << std::endl;
		exit(2);
	}

	/**Read sequnce from file in text*/
	std::string line;
	bool readingFlag = false;
	while (getline(stream, line)) {
		/**Check if this is new sequence*/
		if (line.at(0) == '>') {
			/**If we were reading sequence before than this is end*/
			if (readingFlag) {
				break;
			}
			/**If not then check if this is right sequence*/
			if (line.find(sequenceID) != std::string::npos) {
				readingFlag = true;
				continue;
			}
		}
		/**If we are at right sequence than save it*/
		else if (readingFlag) {
			text += line;
		}
	}

	/**Close stream*/
	stream.close();

	/*std::string fileName;
	std::cout << "Enter file name:\n";
	std::cin >> fileName;*/
	//std::getline(std::cin, text);
	//std::ifstream in(fileName);

	//std::cout << "Stream opened\n" << std::flush;
	//std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

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

	clock_t begin = clock();

	FMIndex index = FMIndex(text);
	
	clock_t end = clock();

	std::cout << "Creating index time = " << (double)(end - begin) / CLOCKS_PER_SEC << "\n";

	//std::cout << "FMIndex sizeof: " << sizeof(index) << "\n";

	std::string search;
	while (1) {
		std::cout << "\nChoose option\n\n[1] : Count\n[2] : Find\n[0] : Exit\n";
		short option;
		std::cin >> option;

		if (option == 0) break;

		std::cout << "Enter search pattern: ";
		std::cin >> search;

		if (option == 1) {
			begin = clock();
			std::cout << "Count: " << std::flush << index.count(search) << "\n";

			end = clock();

			std::cout << "Count time = " << (double)(end - begin) / CLOCKS_PER_SEC << "\n" << std::flush;
		}
		else if (option == 2) {
			begin = clock();

			std::vector<unsigned> results = index.find(search);

			end = clock();

			std::cout << "                                   \rFind: " << std::flush;
			if (results.empty()){
				std::cout << "Can't find pattern: " << search << std::flush;
			}
			else{
				for (std::vector<unsigned>::iterator it = results.begin(); it != results.end(); ++it){
					std::cout << " " << *it;
				}
			}
			std::cout << "\n" << std::flush;


			std::cout << "Search time = " << (double)(end - begin) / CLOCKS_PER_SEC << "\n" << std::flush;
		}
	}

	return 0;
}
