#pragma once
#include <string>
#include <iostream>
#include <set>

using namespace std;

class StringChecks
{
public:
	static void Test();
	static void Play();
	static bool AInBDisordered(const string & a, const string & b);
	static bool AInB(const string & a, const string & b);
private:
	static set<string> FindCombinations(const string & a);
	static void Permute(char a[], int i, int n, set<string>& oPermutations);
	static string tolower(const std::string & a);

};


