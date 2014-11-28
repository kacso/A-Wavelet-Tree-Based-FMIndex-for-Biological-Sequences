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
	bool* bitString;
	int bitStringLength;

	WaveletTreeItem *leftChild = NULL;
	WaveletTreeItem *rightChild = NULL;

public:
	/**Constructor of WaveletTreeItem class*/
	WaveletTreeItem(char breakChar, bool* bitString, int bitStringLength) :
		breakChar(breakChar), bitString(bitString), bitStringLength(bitStringLength){};
};