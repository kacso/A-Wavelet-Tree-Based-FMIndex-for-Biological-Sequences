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

	//applying the bubble sort
	for (int i = 1; i<n; i++)
	{
		for (int j = 0; j<n - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				char tmp;
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
	return 1;
}
