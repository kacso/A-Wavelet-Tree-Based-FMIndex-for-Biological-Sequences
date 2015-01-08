#ifndef WaveletTreeItem_H
#define WaveletTreeItem_H

#include <vector>

/**WaveletTreeItem defines structure of element in wavelet tree.
Variables:
	breakChar : defines middle character in string
	bitString : array of boolean values of string (according to breakChar)
	bitStringLength : length of string
	leftChild : pointer to left child of element
	rightChild : pointer to right child of element
*/

class WaveletTreeItem{
public:
	char breakChar;
	unsigned bitStringLength;

	std::vector<bool> bitString;

	WaveletTreeItem *leftChild = nullptr;
	WaveletTreeItem *rightChild = nullptr;

public:
	/**Constructor of WaveletTreeItem class*/
	WaveletTreeItem(char breakChar, std::vector<bool> bitString, int bitStringLength) :
		breakChar(breakChar), bitString(bitString), bitStringLength(bitStringLength){};
};
#endif
