#include "CompressedSuffixArray.h"

#define compressionRatio 1

CompressedSuffixArray::CompressedSuffixArray(LFTable *lfTable){
	this->lfTable = lfTable;
	generateArray();
}

unsigned CompressedSuffixArray::getItem(unsigned i){
	if (suffixArray.count(i) == 1)
		return suffixArray[i];
	else{
		char newChar;
		unsigned bwtIndex, newBwtIndex = i;
		unsigned newI = 0;
		do{
			++newI;
			bwtIndex = newBwtIndex;

			/**Find new character from LF table*/
			newChar = (lfTable->getLast())->getChar(bwtIndex);

			/**Get rank of character*/
			unsigned rank = (lfTable->getLast())->getRank(newChar, bwtIndex);

			/**Get new bwtIndex*/
			newBwtIndex = (lfTable->getFirst())->indexOf(newChar, rank);

		} while (newChar != '$' && suffixArray.count(bwtIndex) == 0);
		return newI + suffixArray[bwtIndex];
	}
}

void CompressedSuffixArray::generateArray(){
	int bwtIndex = 0, sIndex = (lfTable->getLast())->length();
	char newChar;
	while ((newChar = (lfTable->getLast())->getChar(bwtIndex) != '$')) {
		unsigned rank = (lfTable->getLast())->getRank(newChar, bwtIndex);
		
		/**Store index if necessary*/
		if (sIndex % compressionRatio == 0){
			suffixArray[sIndex] = rank;
		}

		/**Find next bwt*/
		bwtIndex = (lfTable->getFirst())->indexOf(newChar, rank);

		--sIndex;
	}
}