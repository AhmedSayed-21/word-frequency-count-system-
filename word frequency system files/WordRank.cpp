#include "WordRank.h"
#include "WordFrequency.h"

vector<pair<pair<string, int>, int>> WordRank::generateRankedVector(unordered_map<string, int>& frequencies)
{
	int rank = 1;
	vector<pair<pair<string, int>, int>> editrank;
	priority_queue<pair<int, string>> pq;
	unordered_map<string, int>::iterator it;
	for (it = frequencies.begin(); it != frequencies.end(); it++)
	{
		pq.push(make_pair((*it).second, (*it).first));
	}
	while (!pq.empty())
	{
		pair<string, int> key = make_pair(pq.top().second, pq.top().first);
		editrank.push_back(make_pair(key, rank));
		rank++;
		pq.pop();
	}
	for (int i = 0; i < editrank.size() - 1; i++)
	{
		if (editrank[i].first.second == editrank[i + 1].first.second)
		{
			editrank[i + 1].second = editrank[i].second;
		}
		else
		{
			editrank[i + 1].second = editrank[i].second + 1;
		}
	}
	return editrank;
}

void WordRank::displayrank(unordered_map<string, int> frequencies, string word)
{

	vector<pair<pair<string, int>, int>> editrank = generateRankedVector(frequencies);
	char choice;
	string selectedword;
	unordered_map<string, int> search_for_rank;
	for (int i = 0; i < editrank.size(); i++)
	{
		search_for_rank[editrank[i].first.first] = editrank[i].second;
	}
	auto it = search_for_rank.find(word);
	if (it == search_for_rank.end())
	{
		vector<string> suggestionWords = WordFrequency::AutoCompleteWords(frequencies, word);
		cout << "NOT Found \n you can write this:-\n";
		for (auto s : suggestionWords)
		{
			cout << s << " -- ";
		}
		cout << "\nDo you want to choose from them? (Y/N)\n";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			cout << "Enter  the word \n";
			cin >> selectedword;
			cout << "(" << selectedword << ")" << " with rank " << search_for_rank[selectedword] << endl;
		}
		else if (choice == 'n' || choice == 'N')
		{
			cout << "not found \n";
		}
	}
	else
	{
		cout << "(" << word << ")" << " with rank " << search_for_rank[word] << endl;
	}
}

void WordRank::display_rank_of_all_words(unordered_map<string, int> frequencies)
{
	vector<pair<pair<string, int>, int>> editrank = generateRankedVector(frequencies);

	for (int i = 0; i < editrank.size(); i++)
	{
		cout << editrank[i].first.first << " " << "with rank: " << editrank[i].second << endl;
	}
}
