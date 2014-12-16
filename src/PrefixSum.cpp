#include <conio.h>
#include <string>
#include <iostream>
#include "PrefixSum.h"

std::string PrefixSum::count(std::string word){

	char *arr;

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
	
	std::string result;
	for (unsigned i = 0; i < word.length(); ++i)
	{
		char alpha = word.at(i);
		int numberBefore = std::distance(arr, std::find(arr, arr + n, toupper(alpha)));
		result = result + alpha + " " + std::to_string(numberBefore)+"\n";
	}
	
	return result;
}
