#include "WordFrequency.h"
#include "Utils.h"
#include "WordRank.h"

void WordFrequency::displayFrequencies(unordered_map<string, int> frequencies)
{
	cout << "====================================" << endl;
	cout << left << setw(15) << "[Word]"
		<< "|" << right << setw(21) << "[Frequency] " << endl;
	cout << "====================================" << endl;

	unordered_map<string, int>::iterator it;

	for (it = frequencies.begin(); it != frequencies.end(); it++)
	{
		cout << left << setw(15) << it->first << "|" << right << setw(15) << it->second << endl;
		cout << "------------------------------------" << endl;
	}
}

void WordFrequency::appendFrequenciesToFile(unordered_map<string, int> frequencies, string file_name, string frequenciesType)
{
	ofstream outfile(file_name, std::ofstream::app);
	if (!outfile.is_open())
	{
		cout << "can't open file for writing" << endl;
		return;
	}
	outfile << "=========== " << frequenciesType << " =============" << endl;
	outfile << "====================================" << endl;
	outfile << left << setw(15) << "[Word]"
		<< "|" << right << setw(21) << "[Frequency] " << endl;
	outfile << "====================================" << endl;

	unordered_map<string, int>::iterator it;

	for (it = frequencies.begin(); it != frequencies.end(); it++)
	{
		outfile << left << setw(15) << it->first << "|" << right << setw(15) << it->second << endl;
		outfile << "------------------------------------" << endl;
	}
	outfile << "\n###########################################################################" << endl;
	outfile.close();
}


void WordFrequency::calculateWordsFrequencies(unordered_map<string, int>& frequencies, string paragraph)
{
	Utils::removePunctuation(paragraph);
	Utils::toLowercase(paragraph);

	stringstream words(paragraph);
	string word;
	while (words >> word)
	{
		frequencies[word]++;
	}
}

void WordFrequency::decrementFrequencies(unordered_map<string, int>& frequencies, string completed_sentence)
{
	Utils::removePunctuation(completed_sentence);
	stringstream replaced_sentence(completed_sentence);
	string old_word;
	while (replaced_sentence >> old_word)
	{
		if (frequencies[old_word] == 1)
		{
			frequencies.erase(old_word);
		}
		else if (frequencies[old_word] > 1)
		{
			frequencies[old_word]--;
		}
	}
}

string WordFrequency::AutoCorrectWords(unordered_map<string, int>& frequencies, string& word)
{
	priority_queue<pair<int, string>> WordsToComplete;

	for (auto& w : frequencies)
	{
		if (w.first.find(word) != string::npos)
		{
			WordsToComplete.push(make_pair(w.second, w.first));
		}
	}

	if (WordsToComplete.empty())
	{
		return "";
	}
	else
	{
		return WordsToComplete.top().second;
	}
}

void WordFrequency::SearchWord(unordered_map<string, int>& WordFrequency)
{
	string wordToSearch;

	cout << "Enter the word to search: ";
	cin >> wordToSearch;
	Utils::toLowercase(wordToSearch);

	int option;
	cout << "1. Use Auto completeion \n"
		"2. Use Auto correction  \n";

	while (true)
	{
		cin >> option;

		if (option == 1)
		{
			auto found = WordFrequency.find(wordToSearch);
			if (found != WordFrequency.end())
			{
				cout << "Frequency of '" << wordToSearch << "': " << WordFrequency[wordToSearch] << endl;
				return;
			}
			else
			{
				vector<string> suggestionWords = AutoCompleteWords(WordFrequency, wordToSearch);
				if (!suggestionWords.empty())
				{
					string completedWord;
					cout << "Words You Can Mean ." << endl;
					for (int i = 0; i < suggestionWords.size(); i++)
					{
						cout << i + 1 << ". " << suggestionWords[i] << endl;
					}
					cout << suggestionWords.size() + 1 << ".  another word " << endl;

					int choice;
					cout << "Enter your choice (1-" << suggestionWords.size() + 1 << "): ";
					while (true)
					{
						cin >> choice;

						if (choice >= 1 && choice <= suggestionWords.size() + 1)
						{
							if (choice != suggestionWords.size() + 1)
							{
								completedWord = suggestionWords[choice - 1];
								cout << "Frequency of '" << completedWord << "': " << WordFrequency[completedWord] << endl;
								return;
							}
							else
							{
								cout << "# enter the correct word .\n";
								cin >> completedWord;
								Utils::toLowercase(completedWord);
								wordToSearch = completedWord;
								auto found = WordFrequency.find(completedWord);
								if (found != WordFrequency.end())
								{
									cout << "Frequency of '" << completedWord << "': " << WordFrequency[completedWord] << endl;
									return;
								}
								break;
							}
						}
						else
						{
							cout << "Invalid choice!" << endl;
						}
					}
				}
			}
			cout << " word (" << wordToSearch << ") not found . \n";
			break;
		}
		else if (option == 2)
		{
			string correctedWord = AutoCorrectWords(WordFrequency, wordToSearch);
			Utils::toLowercase(correctedWord);

			auto it = WordFrequency.begin();

			while (it != WordFrequency.end())
			{
				if (it->first == correctedWord)
				{
					if (correctedWord == wordToSearch)
					{
						cout << "Frequency of '" << correctedWord << "': " << WordFrequency[correctedWord] << endl;
						return;
					}
					else
					{
						cout << "Do yon mean '" << correctedWord << "' (y/n) ? \n";
						char choice;
						while (true)
						{
							cin >> choice;
							if (choice == 'y' || choice == 'Y')
							{
								cout << "Frequency of '" << correctedWord << "': " << WordFrequency[correctedWord] << endl;
								return;
							}
							else if (choice == 'n' || choice == 'N')
							{
								cout << "# Enter the correct word #\n";
								cin >> correctedWord;
								Utils::toLowercase(correctedWord);
								wordToSearch = correctedWord;
								it = WordFrequency.begin();
								break;
							}
							else
							{
								cout << " invalid choice , Enter yes or No . \n";
							}
						}
						continue;
					}
				}

				it++;
			}
			cout << " word (" << wordToSearch << ") not found . \n";
			break;
		}
		else
		{
			cout << "invalid choice , enter 1 or 2 \n";
		}
	}
}

void WordFrequency::display_sorted_words(unordered_map<string, int> frequencies)
{
	vector<pair<pair<string, int>, int>> editrank = WordRank::generateRankedVector(frequencies);

	for (int i = 0; i < editrank.size(); i++)
	{
		cout << editrank[i].first.first << " " << "with frequency: " << editrank[i].first.second << endl;
	}
}

vector<string> WordFrequency::AutoCompleteWords(unordered_map<string, int>& WordFrequency, string& word)
{

	set<pair<int, string>, set_comparator> WordsToComplete;

	for (auto& w : WordFrequency)
	{
		if (w.first.find(word) != string::npos)
		{
			WordsToComplete.insert(make_pair(w.second, w.first));
		}
	}

	vector<string> suggestionWords;

	for (auto& words : WordsToComplete)
	{
		suggestionWords.push_back(words.second);
	}
	return suggestionWords;
}