#include "CompressedSuffixArray.h"


CompressedSuffixArray::CompressedSuffixArray(unsigned compressionRatio){
	//this->lfTable = lfTable;
	this->compressionRatio = compressionRatio > 0 ? compressionRatio : 1;
	//std::cout << "Compression ratio : " << compressionRatio << "\n";
	//generateArray();
}

unsigned CompressedSuffixArray::getItem(unsigned i){
	//std::cout << "Getting item " << i << " ...\n";
	if (suffixArray.count(i) == 1){
		//std::cout << "Item in array\n";
		return suffixArray[i];
	}
	else{
		//std::cout << "Calculating item...\n";
		char newChar;
		unsigned bwtIndex = i, newBwtIndex = i;
		unsigned newI = 0;
		do{
			//std::cout << i << "\r";
			++newI;

			/**Find new character from LF table*/
			newChar = lfTable->getCharLast(bwtIndex);

			/**Get rank of character*/
			unsigned rank = lfTable->getRankLast(newChar, bwtIndex);

			/**Get new bwtIndex*/
			bwtIndex = lfTable->getIndexFirst(newChar, rank);
		} while (suffixArray.count(bwtIndex) == 0);
		//std::cout << "Item calculated\n";
		return newI + suffixArray[bwtIndex];
	}
}

void CompressedSuffixArray::generateArray(LFTable *lfTable, char **arr){
	this->lfTable = lfTable;

	int i = 0, strLast = strlen(arr[0]) - 1;
	do{
		std::cout << "Generating suffix array: " << i << "   \r";

		/**Store index if necessary*/
		if (i % compressionRatio == 0 || arr[i][strLast - 1] == '$'){
			suffixArray[i] = strLast - (strchr(arr[i], '$') - arr[i]);
		}

		++i;
	} while (i <= strLast);
	std::cout << "Generating suffix array: completed\n";
}

void CompressedSuffixArray::generateArray(){
	//std::cout << "Generating suffix array\n";
	unsigned bwtIndex = 0, sIndex = lfTable->getLengthLast() - 1;
	char newChar = ' ';
	//while ((newChar = lfTable->getCharOfLast(bwtIndex)) != '\0' && newChar != '\0') {
	
	do{
		std::cout << "Generating suffix array: "<< sIndex << "   \r";
		newChar = lfTable->getCharLast(bwtIndex);
		unsigned rank = lfTable->getRankLast(newChar, bwtIndex);

		/**Store index if necessary*/
		if (bwtIndex % compressionRatio == 0 || newChar == '$'){
			suffixArray[bwtIndex] = sIndex;
		}

		/**Find next bwt*/
		bwtIndex = lfTable->getIndexFirst(newChar, rank);

		if (bwtIndex < 0) break;

		--sIndex;
	} while (newChar != '$' && newChar != '\0' && sIndex > 0);
	std::cout << "Generating suffix array: completed\n";
}