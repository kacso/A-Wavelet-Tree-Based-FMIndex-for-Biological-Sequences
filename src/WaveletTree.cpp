#include "WaveletTree.h"
#include "WaveletTreeItem.h"

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <math.h>

/**Constructor for WaveletTree class*/
WaveletTree::WaveletTree(std::string text){
	/**Create tree*/
	root = addChild(text);

	/**Sort alphabet*/
	alphabetList.sort();
}

WaveletTree::~WaveletTree(){

}

WaveletTreeItem* WaveletTree::addChild(std::string text){
	/**Check if text is not empty*/
	if (text.empty() == 1){
		return nullptr;
	}
	WaveletTreeItem *treeItem;
	//int textLength = text.length();
	char breakChar = getMiddleChar(text);
	unsigned cntLess = 0, cntHigh = 0;
	std::vector<bool> bitString;
	std::string leftText, rightText;

	/**Create bitString*/
	bitString = createBitString(text, breakChar, &leftText, &rightText);

	if (leftText.length() > 0 && rightText.length() > 0) {
		//std::cout << "Adding normal; " << text << "\n";
		treeItem = new WaveletTreeItem(breakChar, bitString, text.length());
		(*treeItem).leftChild = addChild(leftText);
		(*treeItem).rightChild = addChild(rightText);
	}
	else if (checkText(leftText)) {
		//std::cout << "left > 0; " << text << "\n";
		--breakChar;
		/**Create bitString*/
		bitString = createBitString(text, breakChar, &leftText, &rightText);

		treeItem = new WaveletTreeItem(breakChar, bitString, text.length());
		(*treeItem).leftChild = addChild(leftText);
		(*treeItem).rightChild = addChild(rightText);
	}
	else if (checkText(rightText)) {
		//std::cout << "right > 0; " << text << "\n";
		++breakChar;
		/**Create bitString*/
		bitString = createBitString(text, breakChar, &leftText, &rightText);

		treeItem = new WaveletTreeItem(breakChar, bitString, text.length());
		(*treeItem).leftChild = addChild(leftText);
		(*treeItem).rightChild = addChild(rightText);
	}
	/**We get to leafs*/
	else {
		//std::cout << "leaf; " << text << "\n";
		treeItem = new WaveletTreeItem(text[0], bitString, 0);

		/**Add char to alphabet*/
		alphabetList.push_back(text[0]);
	}
	return treeItem;
}

char WaveletTree::getMiddleChar(std::string text){
	float sum = 0;
	char flag = 0;
	for (unsigned i = 0; i < text.length(); ++i){
		if (text[i] != '$') {
			sum += text[i];
		}
		else {
			flag = 1;
		}
	}
	return (char)ceil(sum / (text.length() - flag));
}

std::vector<bool> WaveletTree::createBitString(std::string text, char breakChar,
		std::string *leftText, std::string *rightText){
	unsigned cntLess = 0, cntHigh = 0;
	std::vector<bool> bitString(text.length());// = (bool*)malloc(text.length() * sizeof(bool));

	for (unsigned i = 0; i < text.length(); ++i){
		if (text[i] < breakChar){
			++cntLess;
			bitString[i] = false;
			(*leftText) += text[i];
		}
		else {
			++cntHigh;
			bitString[i] = true;
			(*rightText) += text[i];
		}
	}
	return bitString;
}

/*unsigned WaveletTree::getRank(char character, unsigned index){
	return getRank(character, index, root);
}*/

/**Loop*/
unsigned WaveletTree::getRank(char character, unsigned index){
	WaveletTreeItem *parent = root;
	unsigned retVal = -1;
	while (parent != nullptr && index >= 0){
		/**We are at leaf, so current index is rank of bitString*/
		if (parent->bitStringLength == 0){
			if (parent->breakChar == character) return index + 1;
			else return 0;
		}
		/**Find new index and look for rank in subtree*/
		else if (character < parent->breakChar){
			unsigned i, newIndex = 0;
			index = index > parent->bitStringLength ? parent->bitStringLength : index;
			for (i = 0; i <= index; ++i){
				if (parent->bitString[i] == false){
					++newIndex;
				}
			}
			if (newIndex == 0) return 0;
			//return getRank(character, newIndex - 1, parent->leftChild);
			index = newIndex - 1;
			parent = parent->leftChild;
		}
		else{
			unsigned i, newIndex = 0;
			index = index > parent->bitStringLength ? parent->bitStringLength : index;
			for (i = 0; i <= index; i++){
				if (parent->bitString[i] == true){
					++newIndex;
				}
			}
			if (newIndex == 0) return 0;
			//return getRank(character, newIndex - 1, parent->rightChild);
			index = newIndex - 1;
			parent = parent->rightChild;
		}
	}
	return retVal;
}

unsigned WaveletTree::getRank(char character, unsigned index, WaveletTreeItem *root){
	std::cout << "Recursion!\n";
	/**Check input arguments*/
	if (root == nullptr || index < 0){
		return -1;
	}
	/**We are at leaf, so current index is rank of bitString*/
	if (root->bitStringLength == 0){
		if (root->breakChar == character) return index + 1;
		else return 0;
	}
	/**Find new index and look for rank in subtree*/
	else if (character < root->breakChar){
		unsigned i, newIndex = 0;
		index = index > root->bitStringLength ? root->bitStringLength : index;
		for (i = 0; i <= index; ++i){
			if (root->bitString[i] == false){
				++newIndex;
			}
		}
		if (newIndex == 0) return 0;
		return getRank(character, newIndex - 1, root->leftChild);
	}
	else{
		unsigned i, newIndex = 0;
		index = index > root->bitStringLength ? root->bitStringLength : index;
		for (i = 0; i <= index; i++){
			if (root->bitString[i] == true){
				++newIndex;
			}
		}
		if (newIndex == 0) return 0;
		return getRank(character, newIndex - 1, root->rightChild);
	}
}

char WaveletTree::getChar(unsigned index){
	return getChar(index, root);
}

char WaveletTree::getChar(unsigned index, WaveletTreeItem *root){
	if (root->bitStringLength == 0)
		return root->breakChar;
	if (index > root->bitStringLength)
		return '\0';
	unsigned newBiggerIndex = 0;
	unsigned newSmallerIndex = 0;
	for (unsigned i = 0; i < index; ++i){
		if (root->bitString[i] == true){
			++newBiggerIndex;
		}
		else {
			++newSmallerIndex;
		}
	}
	if (root->bitString[index] == true)
		return getChar(newBiggerIndex, root->rightChild);
	else
		return getChar(newSmallerIndex, root->leftChild);
}

unsigned WaveletTree::indexOf(char character, unsigned rank){
	unsigned i = rank - 1;
	unsigned curRank;
	for (; i < root->bitStringLength; i += rank - curRank) {
		curRank = getRank(character, i);
		//if (getRank(character, i) == rank) break;
		if (curRank == rank) break;
	}
	return i;
}

unsigned WaveletTree::length(){
	return root->bitStringLength;
}

bool WaveletTree::checkText(std::string text){
	if (text.length() <= 0) return false;
	char tmp = text[0];
	for (unsigned i = 1; i < text.length(); ++i){
		if (tmp != text[i]) return true;
	}
	return false;
}

unsigned WaveletTree::getAlphabet(char *&arr){
	unsigned size = alphabetList.size();
	arr = new char[alphabetList.size()];
	std::list<char>::iterator it = alphabetList.begin();
	for (unsigned i = 0; i < size; ++i, ++it){
		arr[i] = *it;
	}
	return size;
}

std::string WaveletTree::toString(){
	std::string asString;
	for (unsigned i = 0; i < root->bitStringLength; ++i){
		asString += getChar(i);
	}
	return asString;
}