#include "WaveletTreeItem.h"
#include <stdio.h>
#include <string>

class WaveletTree{
private:
	WaveletTreeItem *root = NULL;
public:
	WaveletTree(std::string text);
	int getRank(char character, int index);
private:
	WaveletTreeItem* addChild(std::string text);
	
};