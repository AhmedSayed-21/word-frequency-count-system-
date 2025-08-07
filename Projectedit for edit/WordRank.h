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

class WordRank
{
public:
    static vector<pair<pair<string, int>, int>> generateRankedVector(unordered_map<string, int>& frequencies);    
    static void displayrank(unordered_map<string, int> frequencies, string word);
    static void display_rank_of_all_words(unordered_map<string, int> frequencies);

};

