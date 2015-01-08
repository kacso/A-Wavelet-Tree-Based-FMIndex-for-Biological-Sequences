#ifndef WaveletTree_H
#define WaveletTree_H

#include "WaveletTreeItem.h"
#include <stdio.h>
#include <string>
#include "IOcc.h"
#include <list>

class WaveletTree : public IOcc{
private:
	WaveletTreeItem *root = nullptr;
	std::list<char> alphabetList;
public:
	WaveletTree(std::string text);
	~WaveletTree();
	virtual unsigned getRank(char character, unsigned index);
	virtual char getChar(unsigned index);
	virtual unsigned indexOf(char character, unsigned rank);
	virtual unsigned length();
	virtual unsigned getAlphabet(char *&arr);
	std::string toString();
private:
	WaveletTreeItem* addChild(std::string text);
	unsigned getRank(char character, unsigned index, WaveletTreeItem *root);
	char getMiddleChar(std::string text);
	std::vector<bool> createBitString(std::string text, char breakChar,
		std::string *leftText, std::string *rightText);
	char getChar(unsigned index, WaveletTreeItem *root);
	bool checkText(std::string text);
};
#endif
