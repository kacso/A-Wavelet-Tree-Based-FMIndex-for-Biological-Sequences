#include <conio.h>
#include <string>
#include <iostream>
#include "PrefixSum.h"

char *arr;

PrefixSum::PrefixSum(std::string word)
{
	int n = word.length();
	arr = new char[n];
	for (unsigned i = 0; i < word.length(); ++i)
	{
		char alpha = word.at(i);
		arr[i] = toupper(alpha);
		//std::cout << alpha << std::endl;
	}

	//applying the bubble sort
	for (int i = 1; i < n; i++)
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
}

int PrefixSum::count(char alpha){
	int numberBefore = std::distance(arr, std::find(arr, arr + (unsigned)strlen(arr), toupper(alpha)));

	return numberBefore;
}
