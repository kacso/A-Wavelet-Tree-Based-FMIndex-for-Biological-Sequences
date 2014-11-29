#include "WaveletTree.h"
#include "WaveletTreeItem.h"

/**Constructor for WaveletTree class*/
WaveletTree::WaveletTree(std::string text){
	/**Create tree*/
	root = addChild(text);
}

WaveletTreeItem* WaveletTree::addChild(std::string text){
	/**Check if text is not empty*/
	if (!text.empty){
		return NULL;
	}
	WaveletTreeItem *treeItem;
	int textLength = text.length();
	char breakChar = getMiddleChar(text);
	int cntLess = 0, cntHigh = 0;
	bool *bitString = (bool*)malloc(textLength * sizeof(bool));
	std::string leftText = NULL, rightText = NULL;


	/**Create bitString*/
	for (int i = 0; i <= textLength; i++){
		if (text[i] < breakChar){
			cntLess++;
			bitString[i] = false;
			leftText.append((const char*)text[i]);
		}
		else {
			cntHigh++;
			bitString[i] = true;
			rightText.append((const char*)text[i]);
		}
	}

	if (cntHigh != cntLess){
		treeItem = new WaveletTreeItem(breakChar, bitString, textLength);
		(*treeItem).leftChild = addChild(leftText);
		(*treeItem).rightChild = addChild(rightText);
	}
	/**We get to leafs*/
	else {
		treeItem = new WaveletTreeItem(text[0], NULL, 0);
	}
	return treeItem;
}

char getMiddleChar(std::string text){
	unsigned sum = 0;
	for (int i = 0; i < text.length(); i++){
		sum += text[i];
	}
	return sum / text.length();
}

int WaveletTree::getRank(char character, int index){
	return getRank(character, index, root);
}

int WaveletTree::getRank(char character, int index, WaveletTreeItem *root){
	/**Check input arguments*/
	if (root == NULL || index < 0 || index > root->bitStringLength){
		return -1;
	}
	/**We are at leaf, so current index is rank of bitString*/
	if (character == root->breakChar){
		return index;
	}
	/**Find new index and look for rank in subtree*/
	else if (character < root->breakChar){
		int i, newIndex = 0;
		for (i = 0; i <= index; i++){
			if (root->bitString[i] == 0){
				newIndex++;
			}
		}
		return getRank(character, newIndex, root->leftChild);
	}
	else{
		int i, newIndex = 0;
		for (i = 0; i <= index; i++){
			if (root->bitString[i] == 1){
				newIndex++;
			}
		}
		return getRank(character, newIndex, root->rightChild);
	}
}