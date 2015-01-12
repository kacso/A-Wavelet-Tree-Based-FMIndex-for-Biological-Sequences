#include "SuffixArray.h"
#include <map>

class SomeSA : public SuffixArray{
private:
	std::vector<int> suffixArray;
public:
	SomeSA(std::string word);
	virtual unsigned getItem(unsigned i);
};