#include <conio.h>
#include <string>
#include <iostream>

int main()
{
	char *arr;
	//prompting user to input word
	std::string word;
	std::cout << "ENTER THE WORD \n";
	std::cin >> word;

	int n = word.length();
	arr = new char[n];
	for (unsigned i = 0; i<word.length(); ++i)
	{
		char alpha = word.at(i);
		arr[i] = alpha;
		std::cout << alpha << std::endl;
	}
	return 1;
}
