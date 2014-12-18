#ifndef PrefixSum_H
#define PrefixSum_H

#include <stdio.h>
#include <string>
#include <conio.h>
#include <iostream>

class PrefixSum{
private:
	char *arr;
public:
	PrefixSum(std::string word);
	int count(char alpha);
};

#endif
