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

class Paragraph
{
public:
	static void DeleteFromParagraph(unordered_map<string, int>& frequencies, string& paragraph, unordered_map<string, int>& global);
	static void replaceSentence(unordered_map<string, int>& frequencies, string& paragraph, string old_sentence, string new_sentence, unordered_map<string, int>& global);
	static void continueWritingInParagraph(unordered_map<string, int>& WordFrequency, string& paragraph, unordered_map<string, int>& global);
	static void updateParagraph(unordered_map<string, int>& frequencies, string& paragraph, unordered_map<string, int>& global);
};

