#ifndef WaveletTree_H
#define WaveletTree_H

#include "WaveletTreeItem.h"
#include <stdio.h>
#include <string>
#include "IOcc.h"

class WaveletTree : public IOcc{
private:
	WaveletTreeItem *root = nullptr;
public:
	WaveletTree(std::string text);
	virtual int getRank(char character, int index);
	//WaveletTreeItem* getRoot();
private:
	WaveletTreeItem* addChild(std::string text);
	int getRank(char character, int index, WaveletTreeItem *root);
	char getMiddleChar(std::string text);
	bool* createBitString(std::string text, char breakChar,
		std::string *leftText, std::string *rightText);
};
#endif