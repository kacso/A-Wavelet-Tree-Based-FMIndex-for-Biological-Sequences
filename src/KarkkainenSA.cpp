#include "KarkkainenSA.h"
#include "esa.hxx"

KarkkainenSA::KarkkainenSA(std::string word) {
	std::cout << "Generating suffix array...\r";
	int alphaSize = 0x100;  // This can be very large
	int nodeNum = 0;

	std::vector<char> T(word.begin(), word.end());
	int n = T.size();
	std::vector<int>  SA(n);
	std::vector<int>  L(n);     // left boundaries of internal node
	std::vector<int>  R(n);     // right boundaries of internal node 
	std::vector<int>  D(n);     // depths of internal node
	if (esaxx(T.begin(), SA.begin(),
		L.begin(), R.begin(), D.begin(),
		n, alphaSize, nodeNum) == -1){
		exit(-2);
	}
	suffixArray = SA;
	L.empty();
	R.empty();
	D.empty();
	T.empty();
	//SA.empty();
	std::cout << "Generating suffix array: completed\n";
}


unsigned KarkkainenSA::getItem(unsigned i) {
	if (i >= 0 && i < suffixArray.size()) {
		return suffixArray[i];
	}
	return -1;
}
