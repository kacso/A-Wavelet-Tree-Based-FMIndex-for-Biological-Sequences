#include "CompressedSuffixArray.h"
#include <cstring>
#include "LFTable.h"

CompressedSuffixArray::CompressedSuffixArray(unsigned compressionRatio){
  //	this->lfTable = lfTable;
	this->compressionRatio = compressionRatio > 0 ? compressionRatio : 1;
	//std::cout << "Compression ratio : " << compressionRatio << "\n";
	//	generateArray();
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

void CompressedSuffixArray::generateArray(LFTable *lfTable, WaveletTree **arr){
  //        std::cout << "suffix array1\n" << std::flush;

	int i = 0, strLast = arr[0]->length() - 1;
	std::cout << "Generating suffix array...\r" << std::flush;
	do{
	  //    std::cout << "Generating suffix array..." << i << "\r" <<std::flush;
		/**Store index if necessary*/
		if (i % compressionRatio == 0 || arr[i]->getChar(strLast) == '$'){
			suffixArray[i] = strLast - arr[i]->indexOf('$', 1);
		}

		++i;
	} while (i <= strLast);
	std::cout << "Generating suffix array: completed\n" << std::flush;
}

void CompressedSuffixArray::generateArray(){
    std::cout << "Generating suffix array...\r" << std::flush;
	unsigned bwtIndex = 0, sIndex = lfTable->getLengthLast() - 1;
	//	std::cout << "sIndex\n" << std::flush;
	char newChar = ' ';
	//while ((newChar = lfTable->getCharOfLast(bwtIndex)) != '\0' && newChar != '\0') {
	
	do{
	  //std::cout << "Generating suffix array: "<< sIndex << "   \r" << std::flush;
		newChar = lfTable->getCharLast(bwtIndex);
		unsigned rank = lfTable->getRankLast(newChar, bwtIndex);
		
		if (bwtIndex % compressionRatio == 0 || newChar == '$'){
			suffixArray[bwtIndex] = sIndex;
		}

		bwtIndex = lfTable->getIndexFirst(newChar, rank);

		if (bwtIndex < 0) break;

		--sIndex;
	} while (newChar != '$' && newChar != '\0' && sIndex > 0);
	std::cout << "Generating suffix array: completed\n"  << std::flush;
}
