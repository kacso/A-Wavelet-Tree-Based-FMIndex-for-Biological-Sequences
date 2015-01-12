#ifndef PrefixSum_H
#define PrefixSum_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <map>

class PrefixSum{
private:
	std::map<char, unsigned> prefixArray;
public:
	PrefixSum(std::string word);
	int count(char alpha);
};

#endif
