/***********************************************************
* This suffix array is generated using Karkkainen algorithm
* and using external source code provided by Daisuke Okanohara
* avaible at http://code.google.com/p/esaxx/
*/

#include "SuffixArray.h"
#include <map>

class KarkkainenSA : public SuffixArray{
private:
	std::vector<int> suffixArray;
public:
	KarkkainenSA(std::string word);
	virtual unsigned getItem(unsigned i);
};
