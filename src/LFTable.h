#ifndef LFTable_H
#define LFTable_H
#include <string>
#include "IOcc.h"

class LFTable{
public:
	LFTable(std::string *text);
	std::string count(std::string word);
	int getRank(char character, int index);
	IOcc *getLast();
	IOcc *getFirst();
};
#endif
