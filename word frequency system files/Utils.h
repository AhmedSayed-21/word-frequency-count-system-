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

class Utils
{
public:
	static void toLowercase(string& str);
	static void removePunctuation(string& str);
	static string AutoCompleteSentence(string& sentence, string& paragraph);
	static string printMessage(string message);
	static string readParagraphFromConsole();
};