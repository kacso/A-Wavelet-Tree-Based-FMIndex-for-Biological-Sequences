#include "FMIndex.h"
#include "KarkkainenSA.h"
/**Algoritham from Wikipedia (http://en.wikipedia.org/wiki/FM-index#cite_note-opportunistic_2000-1)
	for find & count*/

FMIndex::FMIndex(std::string text){
	std::cout << "Creating FMIndex\n" << std::flush;

	/**Add terminating char*/
	text += '$';

	/**Create suffix array*/
	suffixArray = new KarkkainenSA(text);

	/**Create new LF table*/
	lfTable = new LFTable(text, suffixArray);

	/**Get alphabet*/
	unsigned size = lfTable->getAlphabet(alphabet);

	for (unsigned i = 0; i < size; ++i){
		//std::cout << "Generating alphabet: " << i << "\t\r";
		mapAlphabet[alphabet[i]] = i;
	}

	std::cout << "Generating alphabet: completed\n" << std::flush;


	std::cout << "FMIndex created\n" << std::flush;
}

std::vector<unsigned> FMIndex::find(std::string substring){
	int start, end;

	count(start, end, substring);
	std::vector<unsigned> results(end - start + 1);

	/**No such substring*/
	if (start > end) return results;

	/**Return all substrings*/
	
	std::cout << "Generating results...\r" << std::flush;
	for (int i = start; i <= end; ++i){
		results[i - start] = suffixArray->getItem(i);
	}
	std::cout << "Generating results: completed\r" << std::flush;
	//return suffixArray->getItem(start);
	return results;
}

int FMIndex::count(std::string substring){
	int start, end, cnt;
	count(start, end, substring);
	cnt = end - start + 1;
	if (cnt < 0)
		return 0;
	else
		return cnt;
}

void FMIndex::count(int &start, int &end, std::string substring){
	int index = substring.length() - 1;
	char nextChar = substring[index--];

	if (mapAlphabet.count(nextChar) == 0){
		start = -1;
		end = -2;
		return;
	}
	
	start = lfTable->countLast(nextChar);  //+1

	if (mapAlphabet[nextChar] == mapAlphabet.size() - 1){
		end = lfTable->getLengthLast() - 1;
	}
	else{
		end = lfTable->countLast(alphabet[mapAlphabet[nextChar] + 1]) - 1;
	}
	while (index >= 0 && start <= end){
		nextChar = substring[index--];
		if (mapAlphabet.count(nextChar) == 0){
			start = -1;
			end = -2;
			return;
		}
		start = lfTable->countLast(nextChar) + lfTable->getRankLast(nextChar, start - 1);
		end = lfTable->countLast(nextChar) + lfTable->getRankLast(nextChar, end) - 1;
	}
}
