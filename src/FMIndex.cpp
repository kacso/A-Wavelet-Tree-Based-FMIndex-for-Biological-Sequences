#include "FMIndex.h"

/**Algoritham from Wikipedia (http://en.wikipedia.org/wiki/FM-index#cite_note-opportunistic_2000-1)
	for find & count*/

int FMIndex::find(std::string substring){
	int start, end;

	count(start, end, substring);

	return suffixArray->getItem(start);
}

void FMIndex::count(int &start, int &end, std::string substring){
	int index = substring.length();
	char nextChar = substring[index--];
	start = lfTable->count(nextChar) + 1;
	end = lfTable->count(nextChar + 1);

	while (index >= 0){
		nextChar = substring[index--];
		start = lfTable->count(nextChar) + lfTable->getRank(nextChar, start - 1) + 1;
		end = lfTable->count(nextChar) + lfTable->getRank(nextChar, end);
	}
}