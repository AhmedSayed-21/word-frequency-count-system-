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

class FileOperations
{
public:
	static string readParagraphFromFile(const string& filename);
	static int WritingInFile(string paragraph, string file_name);

};

