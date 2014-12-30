#include "CompressedSuffixArray.h"


CompressedSuffixArray::CompressedSuffixArray(LFTable *lfTable){
	this->lfTable = lfTable;
	generateArray();
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
			++newI;

			/**Find new character from LF table*/
			newChar = lfTable->getCharOfLast(bwtIndex);

			/**Get rank of character*/
			unsigned rank = lfTable->getRankLast(newChar, bwtIndex);

			/**Get new bwtIndex*/
			bwtIndex = lfTable->indexOfFirst(newChar, rank);
		} while (suffixArray.count(bwtIndex) == 0);
		//std::cout << "Item calculated\n";
		return newI + suffixArray[bwtIndex];
	}
}

void CompressedSuffixArray::generateArray(){
	std::cout << "Generating suffix array\n";
	int bwtIndex = 0, sIndex = lfTable->lengthOfLast() - 1;
	char newChar;
	//while ((newChar = lfTable->getCharOfLast(bwtIndex)) != '\0' && newChar != '\0') {
	do{
		newChar = lfTable->getCharOfLast(bwtIndex);
		unsigned rank = lfTable->getRankLast(newChar, bwtIndex);

		/**Store index if necessary*/
		if (bwtIndex % compressionRatio == 0 || newChar == '$'){
			suffixArray[bwtIndex] = sIndex;
		}

		/**Find next bwt*/
		bwtIndex = lfTable->indexOfFirst(newChar, rank);

		if (bwtIndex < 0) break;

		--sIndex;
	} while (newChar != '$' && newChar != '\0');
	std::cout << "Suffix array generated\n";
}