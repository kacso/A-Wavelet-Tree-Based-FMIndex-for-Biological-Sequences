#ifndef LFTable_H
#define LFTable_H
#include <string>
#include "IOcc.h"

class LFTable{
public:
	LFTable(std::string *text);
	int count(char a);
	int getRank(char character, int index);
	IOcc *getLast();
	IOcc *getFirst();
};
#endif