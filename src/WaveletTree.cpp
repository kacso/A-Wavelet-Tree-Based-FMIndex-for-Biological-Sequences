#include "WaveletTree.h"
#include "WaveletTreeItem.h"

#include <iostream>

/**Constructor for WaveletTree class*/
WaveletTree::WaveletTree(std::string text){
	/**Create tree*/
	root = addChild(text);
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
	bool *bitString = nullptr;
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
		treeItem = new WaveletTreeItem(text[0], nullptr, 0);
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

bool* WaveletTree::createBitString(std::string text, char breakChar,
		std::string *leftText, std::string *rightText){
	unsigned cntLess = 0, cntHigh = 0;
	bool *bitString = (bool*)malloc(text.length() * sizeof(bool));

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

unsigned WaveletTree::getRank(char character, unsigned index){
	return getRank(character, index, root);
}

unsigned WaveletTree::getRank(char character, unsigned index, WaveletTreeItem *root){
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
			if (root->bitString[i] == 0){
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
			if (root->bitString[i] == 1){
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
	unsigned i = 0;
	for (; i < root->bitStringLength; ++i) {
		if (getRank(character, i) == rank) break;
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