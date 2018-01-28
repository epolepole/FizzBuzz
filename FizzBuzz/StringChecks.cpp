#include "stdafx.h"
#include "StringChecks.h"
#include <locale>         // std::locale, std::tolower



void StringChecks::Test()
{

}

void StringChecks::Play()
{
	{
		string a = "agua";
		string b = "oooaguaooo";
		string c = "oooaguooo";
		string d = "oooAaguooo";
		//cout << AInB(a, b) << endl;
		//cout << AInB(a, c) << endl;

		cout << AInBDisordered(a, d) << endl;	
	}
}

void StringChecks::Permute(char a[], int i, int n, set<string>& oPermutations)
{
	int j, temp;
	if (i == n) oPermutations.insert(string(a));
	else
	{
		for (j = i; j <= n; j++)
		{
			swap(a[i], a[j]);
			Permute(a, i + 1, n, oPermutations);
			swap(a[i], a[j]);	
		}
	}
}

string StringChecks::tolower(const std::string & a)
{
	std::locale loc;
	string low_string;
	for (std::string::size_type i = 0; i<a.length(); ++i)
		low_string.push_back(std::tolower(a[i], loc));
	return low_string;
}

bool StringChecks::AInB(const string & a, const string & b)
{
	string a_lower = tolower(a);
	string b_lower = tolower(b);
	return b_lower.find(a_lower) != string::npos;
}

set<string> StringChecks::FindCombinations(const string & a)
{

	return set<string>();
}

bool StringChecks::AInBDisordered(const string & a, const string & b)
{
	string a_lower = tolower(a);
	string b_lower = tolower(b);
	char *cstr = new char[a_lower.length() + 1];
	strcpy_s(cstr, a_lower.length() + 1, a_lower.c_str());
	set<string> aPermutations;
	Permute(cstr, 0, a_lower.length() - 1, aPermutations);
	bool found = false;
	for (auto aWord : aPermutations)
	{
		if (AInB(aWord, b_lower)) return true;
	}
	return false;
	delete[] cstr;
}
