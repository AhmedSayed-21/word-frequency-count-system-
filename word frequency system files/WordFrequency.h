#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <queue>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct set_comparator
{
	bool operator()(const pair<int, string>& p1, const pair<int, string>& p2) const
	{
		if (p1.first != p2.first)
			return p1.first > p2.first;
		else
			return p1.second < p2.second;
	}
};

class WordFrequency
{
public:
	static void displayFrequencies(unordered_map<string, int> frequencies);
	static void calculateWordsFrequencies(unordered_map<string, int>& frequencies, string paragraph);
	static void decrementFrequencies(unordered_map<string, int>& frequencies, string completed_sentence);
	static void display_sorted_words(unordered_map<string, int> frequencies);
	static vector<string> AutoCompleteWords(unordered_map<string, int>& WordFrequency, string& word);
	static string AutoCorrectWords(unordered_map<string, int>& frequencies, string& word);
	static void SearchWord(unordered_map<string, int>& WordFrequency);
	static void appendFrequenciesToFile(unordered_map<string, int> frequencies, string file_name, string frequenciesType);

};

