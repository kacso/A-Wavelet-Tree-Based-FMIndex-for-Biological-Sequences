#include "FMIndex.h"

/**Algoritham from Wikipedia (http://en.wikipedia.org/wiki/FM-index#cite_note-opportunistic_2000-1)
	for find & count*/

int FMIndex::find(std::string substring){
	int start, end;

	count(start, end, substring);
	if (start > end) return -1;
	return suffixArray->getItem(start);
}

int FMIndex::count(std::string substring){
	int start, end;
	count(start, end, substring);
	return end - start;
}

void FMIndex::count(int &start, int &end, std::string substring){
	int index = substring.length() - 1;
	char nextChar = substring[index--];
	start = lfTable->countLast(nextChar);  //+1
	
	end = lfTable->countLast(alphabet[mapAlphabet[nextChar] + 1]) - 1;

	while (index > 0){
		nextChar = substring[index--];
		start = lfTable->countLast(nextChar) + lfTable->getRankLast(nextChar, start - 1);
		end = lfTable->countLast(nextChar) + lfTable->getRankLast(nextChar, end) - 1;
	}
}