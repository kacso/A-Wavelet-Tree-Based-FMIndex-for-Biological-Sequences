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
	virtual unsigned getRank(char character, unsigned index);
	virtual char getChar(unsigned index);
	virtual unsigned indexOf(char character, unsigned rank);
	virtual unsigned length();
private:
	WaveletTreeItem* addChild(std::string text);
	unsigned getRank(char character, unsigned index, WaveletTreeItem *root);
	char getMiddleChar(std::string text);
	bool* createBitString(std::string text, char breakChar,
		std::string *leftText, std::string *rightText);
	char getChar(unsigned index, WaveletTreeItem *root);
};
#endif