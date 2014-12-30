#include <conio.h>
#include <string>
#include <iostream>
#include <map>
#include "PrefixSum.h"

std::map<char, unsigned> prefixArray;

PrefixSum::PrefixSum(std::string word)
{
	int n = word.length();
	for (unsigned i = 0; i < word.length(); ++i)
	{
		char alpha = toupper(word.at(i));
		if (prefixArray[alpha]>0) prefixArray[alpha] ++;
		else prefixArray[alpha] = 1;
	}

	unsigned count = 0;
	typedef std::map<char, unsigned>::iterator it_type;
	for (it_type iterator = prefixArray.begin(); iterator != prefixArray.end(); iterator++) {
		char sign = iterator->first;
		unsigned countBefore = iterator->second;
		unsigned tmp = prefixArray[sign];
		prefixArray[sign] = count;
		count += tmp;
	}
}

int PrefixSum::count(char alpha){
	return prefixArray[toupper(alpha)];
}
