#include "WaveletTree.h"
#include "WaveletTreeItem.h"

/**Constructor for WaveletTree class*/
WaveletTree::WaveletTree(std::string text){
	/**Create tree*/
	text += '$';
	root = addChild(text);
}

/**TODO Problem when input text contains only the same characte!!!!!!!*/

WaveletTreeItem* WaveletTree::addChild(std::string text){
	/**Check if text is not empty*/
	if (text.empty() == 1){
		return nullptr;
	}
	WaveletTreeItem *treeItem;
	//int textLength = text.length();
	char breakChar = getMiddleChar(text);
	int cntLess = 0, cntHigh = 0;
	bool *bitString = nullptr;
	std::string leftText, rightText;

	/**Create bitString*/
	bitString = createBitString(text, breakChar, &leftText, &rightText);

	if (leftText.length() > 0 && rightText.length() > 0){
		treeItem = new WaveletTreeItem(breakChar, bitString, text.length());
		(*treeItem).leftChild = addChild(leftText);
		(*treeItem).rightChild = addChild(rightText);
	}
	/**We get to leafs*/
	else {
		treeItem = new WaveletTreeItem(text[0], nullptr, 0);
	}
	return treeItem;
}

char WaveletTree::getMiddleChar(std::string text){
	float sum = 0;
	for (unsigned i = 0; i < text.length() - 1; i++){
		sum += text[i];
	}
	return (char)ceil(sum / (text.length() - 1));
}

bool* WaveletTree::createBitString(std::string text, char breakChar,
		std::string *leftText, std::string *rightText){
	int cntLess = 0, cntHigh = 0;
	bool *bitString = (bool*)malloc(text.length() * sizeof(bool));

	for (unsigned i = 0; i < text.length(); i++){
		if (text[i] < breakChar){
			cntLess++;
			bitString[i] = false;
			(*leftText) += text[i];
		}
		else {
			cntHigh++;
			bitString[i] = true;
			(*rightText) += text[i];
		}
	}
	return bitString;
}

int WaveletTree::getRank(char character, int index){
	return getRank(character, index, root);
}

int WaveletTree::getRank(char character, int index, WaveletTreeItem *root){
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
		int i, newIndex = 0;
		index = index > root->bitStringLength ? root->bitStringLength : index;
		for (i = 0; i <= index; i++){
			if (root->bitString[i] == 0){
				newIndex++;
			}
		}
		if (newIndex == 0) return 0;
		return getRank(character, newIndex - 1, root->leftChild);
	}
	else{
		int i, newIndex = 0;
		index = index > root->bitStringLength ? root->bitStringLength : index;
		for (i = 0; i <= index; i++){
			if (root->bitString[i] == 1){
				newIndex++;
			}
		}
		if (newIndex == 0) return 0;
		return getRank(character, newIndex - 1, root->rightChild);
	}
}

WaveletTreeItem* WaveletTree::getRoot(){
	return root;
}