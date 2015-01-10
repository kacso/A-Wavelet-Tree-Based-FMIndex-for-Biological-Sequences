#ifndef CompressedSuffixArray_H
#define CompressedSuffixArray_H

#include "SuffixArray.h"
#include <map>

class CompressedSuffixArray : public SuffixArray{
private:
	LFTable *lfTable;
	std::map<unsigned, unsigned> suffixArray;
	unsigned compressionRatio = 1;
public:
	CompressedSuffixArray(unsigned compressionRatio);
	void generateArray(LFTable *lfTable, WaveletTree **arr);
	virtual unsigned getItem(unsigned i);

private:
	void generateArray();
};

#endif
