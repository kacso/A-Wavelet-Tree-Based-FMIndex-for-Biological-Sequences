#include "NongZhangChanSA.h"

NongZhangChanSA::NongZhangChanSA(std::string word){
	generateArray(word, suffixArray);
}

void NongZhangChanSA::generateArray(std::string word, std::map<unsigned, int> &suffixArray){
	std::cout << "Generating SA...\r" << std::flush;
	std::vector<bool> t(word.length());
	
	std::map<unsigned char, unsigned> alphabet;

	/**Classify unsigned characters as S or L type in t*/
	for (int i = word.length() - 1; i >= 0; --i) {
		t[i] = getType(word, t, i);

		/**Generating alphabet*/
	/*	if (alphabet.count(word.at(i)) == 0) {
			alphabet[word.at(i)] = 1;
		}
		else {*/
			++alphabet[word.at(i)];
	//	}

	}

	/**Find all LMS substrings in S and store in P*/
	std::map<int, int> P1;

	for (unsigned i = 1; i < word.length(); ++i) {
		if (t[i] == true && t[i - 1] == false || i == word.length() - 1){
			//P1.insert(P1.end(), i);
			P1[i] = -1;
		}
	}

	/**Generate bucket array*/
	std::map<unsigned char, int> B;
	
	BToEnd(B, alphabet, alphabet.size());

	/**Set all elements of SA to -1*/
	for (unsigned i = 0; i < word.length(); ++i) {
		suffixArray[i] = -1;
	}

	/**Sort LMS: step1*/
	for (std::map<int, int>::iterator it = P1.begin(); it != P1.end(); ++it) {
		if (it->first < 0) continue;
		suffixArray[B[word.at(it->first)]--] = it->first;
	}

	/**Sort LMS: step2*/
	/**Set B[k] on start of k subfield*/
	BToStart(B, alphabet, alphabet.size());

	/**Fill empty elements of suffix array*/
	for (unsigned i = 0; i < word.length(); ++i) {
		if (suffixArray[i] > 0) {
			int k = suffixArray[i] - 1;
			/**S[SA[i]-1] is L-type?*/
			if (t[k] == false) {
				suffixArray[B[word.at(k)]++] = k;
			}
		}
	}

	/**Sort LMS: step3*/
	/**Move B[k] to end*/
	BToEnd(B, alphabet, alphabet.size());

	/**Fill rest of elements of suffix array*/
	for (int i = word.length() - 1; i >= 0; --i) {
		if (suffixArray[i] > 0) {
			unsigned k = suffixArray[i] - 1;
			if (t[k] == true) {
				suffixArray[B[word.at(k)]--] = k;
			}
		}
	}

	/**Name each LMS-substring in S by its bucket*/

	unsigned z = 0;
	bool allUnique = true;
	/**Save for $*/
	P1[suffixArray[0]] = z;
	for (unsigned i = 1; i < word.length(); ++i) {
		if (P1.count(suffixArray[i]) == 1) {
			bool flag = false;
			auto it = P1.find(suffixArray[i]);

			/**Check edge values*/
			auto itPrev = P1.find(suffixArray[i - 1]);
			if (itPrev == P1.end() || ++it == P1.end()) {
				P1[suffixArray[i]] = ++z;
				continue;
			}

			/**Return iterator to i-th element*/
			--it;

			/**Loop from P1[i] (--it)to P1[i+1] (++it)*/
			int max = (++it)->first - (--it)->first;
			
			for (unsigned j = 1; j <= max; ++j) {
				/**Check if unsigned characters are same*/
				/**Check if index is to big*/
				int n1 = it->first + j;
				int n2 = itPrev->first + j;
				if (n1 >= word.length() || n2 >= word.length()) {
					break;
				}

				if (word.at(n1) == word.at(n2)){
					/**Return iterator to P[i]*/
					//++it;
					/**Check if type is same*/
					
					if (t[n1] == t[n2]) {
						//++it;
						flag = true;
						continue;
					}
				}
				flag = false;
				break;
			}

			if (flag) {
				P1[suffixArray[i]] = z;
				allUnique = false;
			}
			else {
				P1[suffixArray[i]] = ++z;
			}
		}
	}

	std::map<unsigned, int> suffixArray1;

	/**Recursion*/
	if (allUnique) {
		/**Directly compute SA1 from S1
		* SA1[S1[i]] = i
		*/
		int i = 0;
		for (std::map<int, int>::iterator it = P1.begin(); it != P1.end(); ++it, ++i) {
			if (it->second < 0) continue;
			suffixArray1[it->second] = i;
		}

	}
	else {
		/**SA-IS(S1, SA1) -> Fire a recursive call*/
		/**Save S1 as string*/
		/*std::string S1;
		for (std::map<int, int>::iterator it = P1.begin(); it != P1.end(); ++it) {
			S1 += it->second;
		}*/
		std::vector<unsigned> S1(P1.size());
		unsigned i = 0;
		for (std::map<int, int>::iterator it = P1.begin(); it != P1.end(); ++i, ++it) {
			S1[i] = it->second;
		}
		/**Recursion call*/
		generateArray(S1, suffixArray1);
	}

	/**Induce SA from SA1*/
	/**Set all elements of SA to -1*/
	for (int i = 0; i < word.length(); ++i) {
		suffixArray[i] = -1;
	}

	/**Find end of buckets B[k] */
	BToEnd(B, alphabet, alphabet.size());

	/**Go through SA1 and put P2[SA1[i]] to the and of appropriate suffix*/
	for (std::map<unsigned, int>::iterator it = suffixArray1.end(); it != suffixArray1.begin(); ) {
		--it;
		//int index = it->second;
		if (it->second < 0) continue;
		/**Access right element of P1*/
		auto pit = P1.begin();
		for (unsigned i = 0; i < it->second; ++i, ++pit);
		suffixArray[B[word.at(pit->first)]--] = pit->first;
	}

	/**InduceSAI*/
	/**Sort LMS: step2*/
	/**Set B[k] on start of k subfield*/
	BToStart(B, alphabet, alphabet.size());

	/**Fill empty elements of suffix array*/
	for (unsigned i = 0; i < word.length(); ++i) {
		if (suffixArray[i] > 0) {
			int k = suffixArray[i] - 1;
			/**S[SA[i]-1] is L-type?*/
			if (t[k] == false) {
				suffixArray[B[word.at(k)]++] = k;
			}
		}
	}

	/**Sort LMS: step3*/
	/**Move B[k] to end*/
	BToEnd(B, alphabet, alphabet.size());

	/**Fill rest of elements of suffix array*/
	for (int i = word.length() - 1; i >= 0; --i) {
		if (suffixArray[i] > 0) {
			int k = suffixArray[i] - 1;
			if (t[k] == true) {
				suffixArray[B[word.at(k)]--] = k;
			}
		}
	}

	std::cout << "Generating SA: completed\n" << std::flush;
}

/**Determines if unsigned char is S or L type.
*  Returns true if S type and false if L type.
*/
bool NongZhangChanSA::getType(std::string word, std::vector<bool> t, unsigned i){
	/**Last unsigned char is always S type*/
	if (i == word.length() - 1){
	//if (word.at(i) == '$' || word.at(i) == '\0') {
		return true;
	}

	/**S[i] < S[i+1] -> S type*/
	if (word.at(i) < word.at(i + 1)) {
		return true;
	}
	/**S[i] > S[i+1] -> L type*/
	else if (word.at(i) > word.at(i + 1)) {
		return false;
	}
	/**S[i] = S[i+1] -> type sam as type of S[i+1]*/
	else {
		return t[i + 1];
	}
}

void NongZhangChanSA::BToEnd(std::map<unsigned char, int> &B, std::map<unsigned char, unsigned> alphabet, unsigned n) {
	std::map<unsigned char, unsigned>::iterator it = alphabet.begin();
	B[it->first] = it->second - 1;
	std::map<unsigned char, unsigned>::iterator exIt = it++;
	for (unsigned i = 1; i < n; ++i, ++it) {
		B[it->first] = it->second + B[exIt->first];
		exIt = it;
	}
}

void NongZhangChanSA::BToStart(std::map<unsigned char, int> &B, std::map<unsigned char, unsigned> alphabet, unsigned n) {
	std::map<unsigned char, unsigned>::iterator it = alphabet.begin();
	B[it->first] = 0;
	std::map<unsigned char, unsigned>::iterator exIt = it++;
	for (unsigned i = 1; i < n; ++i, ++it) {
		B[it->first] = exIt->second + B[exIt->first];
		exIt = it;
	}
}

unsigned NongZhangChanSA::getItem(unsigned i){
	if (suffixArray.count(i) == 1){
		return suffixArray[i];
	}
	return -1;
}







void NongZhangChanSA::generateArray(std::vector<unsigned> word, std::map<unsigned, int> &suffixArray){
	std::vector<bool> t(word.size());

	std::map<unsigned, unsigned> alphabet;

	/**Classify unsigned characters as S or L type in t*/
	for (int i = word.size() - 1; i >= 0; --i) {
		t[i] = getType(word, t, i);

		/**Generating alphabet*/
		/*	if (alphabet.count(word.at(i)) == 0) {
		alphabet[word.at(i)] = 1;
		}
		else {*/
		++alphabet[word.at(i)];
		//	}

	}

	/**Find all LMS substrings in S and store in P*/
	std::map<int, int> P1;

	for (unsigned i = 1; i < word.size(); ++i) {
		if (t[i] == true && t[i - 1] == false || i == word.size() - 1){
			//P1.insert(P1.end(), i);
			P1[i] = -1;
		}
	}

	/**Generate bucket array*/
	std::map<unsigned, int> B;

	BToEnd(B, alphabet, alphabet.size());

	/**Set all elements of SA to -1*/
	for (unsigned i = 0; i < word.size(); ++i) {
		suffixArray[i] = -1;
	}

	/**Sort LMS: step1*/
	for (std::map<int, int>::iterator it = P1.begin(); it != P1.end(); ++it) {
		if (it->first < 0) continue;
		suffixArray[B[word.at(it->first)]--] = it->first;
	}

	/**Sort LMS: step2*/
	/**Set B[k] on start of k subfield*/
	BToStart(B, alphabet, alphabet.size());

	/**Fill empty elements of suffix array*/
	for (unsigned i = 0; i < word.size(); ++i) {
		if (suffixArray[i] > 0) {
			int k = suffixArray[i] - 1;
			/**S[SA[i]-1] is L-type?*/
			if (t[k] == false) {
				suffixArray[B[word.at(k)]++] = k;
			}
		}
	}

	/**Sort LMS: step3*/
	/**Move B[k] to end*/
	BToEnd(B, alphabet, alphabet.size());

	/**Fill rest of elements of suffix array*/
	for (int i = word.size() - 1; i >= 0; --i) {
		if (suffixArray[i] > 0) {
			unsigned k = suffixArray[i] - 1;
			if (t[k] == true) {
				suffixArray[B[word.at(k)]--] = k;
			}
		}
	}

	/**Name each LMS-substring in S by its bucket*/

	unsigned z = 0;
	bool allUnique = true;
	/**Save for $*/
	P1[suffixArray[0]] = z;
	for (unsigned i = 1; i < word.size(); ++i) {
		if (P1.count(suffixArray[i]) == 1) {
			bool flag = false;
			auto it = P1.find(suffixArray[i]);

			/**Check edge values*/
			auto itPrev = P1.find(suffixArray[i - 1]);
			if (itPrev == P1.end() || ++it == P1.end()) {
				P1[suffixArray[i]] = ++z;
				continue;
			}

			/**Return iterator to i-th element*/
			--it;

			/**Loop from P1[i] (--it)to P1[i+1] (++it)*/
			int max = (++it)->first - (--it)->first;

			for (unsigned j = 1; j <= max; ++j) {
				/**Check if unsigned characters are same*/
				/**Check if index is to big*/
				int n1 = it->first + j;
				int n2 = itPrev->first + j;
				if (n1 >= word.size() || n2 >= word.size()) {
					break;
				}

				if (word.at(n1) == word.at(n2)){
					/**Return iterator to P[i]*/
					//++it;
					/**Check if type is same*/

					if (t[n1] == t[n2]) {
						//++it;
						flag = true;
						continue;
					}
				}
				flag = false;
				break;
			}

			if (flag) {
				P1[suffixArray[i]] = z;
				allUnique = false;
			}
			else {
				P1[suffixArray[i]] = ++z;
			}
		}
	}

	std::map<unsigned, int> suffixArray1;

	/**Recursion*/
	if (allUnique) {
		/**Directly compute SA1 from S1
		* SA1[S1[i]] = i
		*/
		int i = 0;
		for (std::map<int, int>::iterator it = P1.begin(); it != P1.end(); ++it, ++i) {
			if (it->second < 0) continue;
			suffixArray1[it->second] = i;
		}

	}
	else {
		/**SA-IS(S1, SA1) -> Fire a recursive call*/
		/**Save S1 as string*/
		std::vector<unsigned> S1(P1.size());
		unsigned i = 0;
		for (std::map<int, int>::iterator it = P1.begin(); it != P1.end(); ++i, ++it) {
			S1[i] = it->second;
		}
		/**Recursion call*/
		generateArray(S1, suffixArray1);
	}

	/**Induce SA from SA1*/
	/**Set all elements of SA to -1*/
	for (int i = 0; i < word.size(); ++i) {
		suffixArray[i] = -1;
	}

	/**Find end of buckets B[k] */
	BToEnd(B, alphabet, alphabet.size());

	/**Go through SA1 and put P2[SA1[i]] to the and of appropriate suffix*/
	for (std::map<unsigned, int>::iterator it = suffixArray1.end(); it != suffixArray1.begin();) {
		--it;
		//int index = it->second;
		if (it->second < 0) continue;
		/**Access right element of P1*/
		auto pit = P1.begin();
		for (unsigned i = 0; i < it->second; ++i, ++pit);
		suffixArray[B[word.at(pit->first)]--] = pit->first;
	}

	/**InduceSAI*/
	/**Sort LMS: step2*/
	/**Set B[k] on start of k subfield*/
	BToStart(B, alphabet, alphabet.size());

	/**Fill empty elements of suffix array*/
	for (unsigned i = 0; i < word.size(); ++i) {
		if (suffixArray[i] > 0) {
			int k = suffixArray[i] - 1;
			/**S[SA[i]-1] is L-type?*/
			if (t[k] == false) {
				suffixArray[B[word.at(k)]++] = k;
			}
		}
	}

	/**Sort LMS: step3*/
	/**Move B[k] to end*/
	BToEnd(B, alphabet, alphabet.size());

	/**Fill rest of elements of suffix array*/
	for (int i = word.size() - 1; i >= 0; --i) {
		if (suffixArray[i] > 0) {
			int k = suffixArray[i] - 1;
			if (t[k] == true) {
				suffixArray[B[word.at(k)]--] = k;
			}
		}
	}
}



bool NongZhangChanSA::getType(std::vector<unsigned> word, std::vector<bool> t, unsigned i){
	/**Last unsigned char is always S type*/
	if (i == word.size() - 1){
		//if (word.at(i) == '$' || word.at(i) == '\0') {
		return true;
	}

	/**S[i] < S[i+1] -> S type*/
	if (word.at(i) < word.at(i + 1)) {
		return true;
	}
	/**S[i] > S[i+1] -> L type*/
	else if (word.at(i) > word.at(i + 1)) {
		return false;
	}
	/**S[i] = S[i+1] -> type sam as type of S[i+1]*/
	else {
		return t[i + 1];
	}
}

void NongZhangChanSA::BToEnd(std::map<unsigned, int> &B, std::map<unsigned, unsigned> alphabet, unsigned n) {
	std::map<unsigned, unsigned>::iterator it = alphabet.begin();
	B[it->first] = it->second - 1;
	std::map<unsigned, unsigned>::iterator exIt = it++;
	for (unsigned i = 1; i < n; ++i, ++it) {
		B[it->first] = it->second + B[exIt->first];
		exIt = it;
	}
}

void NongZhangChanSA::BToStart(std::map<unsigned, int> &B, std::map<unsigned, unsigned> alphabet, unsigned n) {
	std::map<unsigned, unsigned>::iterator it = alphabet.begin();
	B[it->first] = 0;
	std::map<unsigned, unsigned>::iterator exIt = it++;
	for (unsigned i = 1; i < n; ++i, ++it) {
		B[it->first] = exIt->second + B[exIt->first];
		exIt = it;
	}
}
