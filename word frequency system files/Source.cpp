#include "Utils.h"
#include "WordFrequency.h"
#include "FileOperations.h"
#include "Paragraph.h"
#include "WordRank.h"
#include "WordFrequency.h"

using namespace std;


int main()
{
	unordered_map<string, int> global;
	unordered_map<string, int> frequencies;
	unordered_map<string, int> frequencies2;
	string global_paragraph = FileOperations::readParagraphFromFile("wordf.txt");
	string filename = "";

	string paragraph;
	string paragraph2;
	bool changed;

	int choice, choice2;
	bool flag = false; // initialize flag to false
	int fcounter = 0;
	int ccounter = 0;

	while (true)
	{
		cout << "Choose an option:" << endl;

		cout << "1. Read paragraph from console" << endl;
		cout << "2. Read paragraph from file" << endl;
		cout << "3. Display the frequencies of each word" << endl;
		cout << "4. Display Global frequencies for each word" << endl;

		cout << "5. Display the global rank of entered word" << endl;
		cout << "6. Search for a word and display its global frequency" << endl;

		cout << "7. Display the rank of entered word" << endl;
		cout << "8. Display the rank of all words" << endl;
		cout << "9. Display sorted words with thier frequencies" << endl;

		cout << "10. Search for a word and display its frequency" << endl;
		cout << "11. update paragraph" << endl;
		cout << "12. continue writing in paragraph" << endl;
		cout << "13. to Exit\n";

		cout << ">>";
		cin >> choice;
		cin.ignore(); // Ignore the newline character in the input buffer
		cout << endl;

		if (choice == 1)
		{

			paragraph = Utils::readParagraphFromConsole();
			Utils::toLowercase(paragraph);
			Utils::removePunctuation(paragraph);

			WordFrequency::calculateWordsFrequencies(frequencies, paragraph);
			WordFrequency::calculateWordsFrequencies(global, paragraph);
			WordFrequency::calculateWordsFrequencies(global, global_paragraph);
			WordFrequency::appendFrequenciesToFile(global, "app.log", "Global - Console");

			changed = false;
			ccounter++;
			cout << "Paragraph read from console: " << paragraph << endl;
		}
		else if (choice == 2)
		{
			cout << "Enter the filename: ";
			while (filename == "")
			{
				getline(cin, filename);
			}

			paragraph2 = FileOperations::readParagraphFromFile(filename);
			Utils::toLowercase(paragraph2);
			Utils::removePunctuation(paragraph2);

			WordFrequency::calculateWordsFrequencies(frequencies2, paragraph2);
			WordFrequency::calculateWordsFrequencies(global, paragraph2);
			WordFrequency::calculateWordsFrequencies(global, global_paragraph);
			WordFrequency::appendFrequenciesToFile(global, "app.log", "Global - File");

			changed = false;
			fcounter++;

			cout << "Paragraph read from file: " << paragraph2 << endl;
		}
		else if (choice == 3)
		{
			cout << "1. from console: " << endl;
			cout << "2. from file: " << endl;

			cin >> choice2;
			cin.ignore(); // to ignore the next input \n in the buffer
			switch (choice2)
			{
			case 1:
				if (frequencies.empty())
				{
					WordFrequency::calculateWordsFrequencies(frequencies, paragraph);

					if (global.empty())
					{
						WordFrequency::calculateWordsFrequencies(global, paragraph);
						WordFrequency::calculateWordsFrequencies(global, global_paragraph);
					}
				}

				flag = true;
				break;
			case 2:
				flag = false;
				if (frequencies2.empty())
				{
					WordFrequency::calculateWordsFrequencies(frequencies2, paragraph2);

					if (global.empty())
					{
						WordFrequency::calculateWordsFrequencies(global, paragraph2);
						WordFrequency::calculateWordsFrequencies(global, global_paragraph);
					}
				}
				break;
			}

			WordFrequency::displayFrequencies(flag ? frequencies : frequencies2);
			(flag ? ccounter++ : fcounter++);
			if (flag && !changed && fcounter > 1)
			{
				frequencies.clear();
				global.clear();
			}
			else if (!flag && !changed && ccounter > 1)
			{
				frequencies2.clear();
				global.clear();
			}
		}
		else if (choice == 4)
		{
			if (global.empty())
			{
				WordFrequency::calculateWordsFrequencies(global, paragraph);
				WordFrequency::calculateWordsFrequencies(global, paragraph2);
				WordFrequency::calculateWordsFrequencies(global, global_paragraph);
			}
			WordFrequency::displayFrequencies(global);
		}
		else if (choice == 5)
		{
			string word;
			if (global.empty())
			{
				WordFrequency::calculateWordsFrequencies(global, paragraph);
				WordFrequency::calculateWordsFrequencies(global, paragraph2);
				WordFrequency::calculateWordsFrequencies(global, global_paragraph);
			}

			cout << "enter the word to display its rank" << endl;
			cin >> word;
			Utils::toLowercase(word);
			cin.ignore();
			WordRank::displayrank(global, word);
		}
		else if (choice == 6)
		{
			if (global.empty())
			{
				WordFrequency::calculateWordsFrequencies(global, paragraph);
				WordFrequency::calculateWordsFrequencies(global, paragraph2);
				WordFrequency::calculateWordsFrequencies(global, global_paragraph);
			}

			WordFrequency::SearchWord(global);
		}
		else if (choice == 7)
		{

			string word;
			cout << "1. from console: " << endl;
			cout << "2. from file: " << endl;

			cin >> choice2;
			cin.ignore();
			switch (choice2)
			{
			case 1:
				if (frequencies.empty())
					WordFrequency::calculateWordsFrequencies(frequencies, paragraph);
				cout << "enter the word to display its rank" << endl;
				cin >> word;
				WordRank::displayrank(frequencies, word);
				// frequencies.clear();
				break;
			case 2:
				if (frequencies2.empty())
					WordFrequency::calculateWordsFrequencies(frequencies2, paragraph2);
				cout << "enter the word to display its rank" << endl;
				cin >> word;
				WordRank::displayrank(frequencies2, word);
				// frequencies2.clear();
				break;

			default:
				// handle any other value of choice2
				cout << "Invalid choice2. Please choose either 1 or 2." << endl;
				break;
			}
		}
		else if (choice == 8)
		{
			cout << "1. from console: " << endl;
			cout << "2. from file: " << endl;
			cin >> choice2;
			switch (choice2)
			{
			case 1:
				if (frequencies.empty())
					WordFrequency::calculateWordsFrequencies(frequencies, paragraph);
				WordRank::display_rank_of_all_words(frequencies);
				// frequencies.clear();
				break;
			case 2:
				if (frequencies2.empty())
					WordFrequency::calculateWordsFrequencies(frequencies2, paragraph2);

				WordRank::display_rank_of_all_words(frequencies2);
				// frequencies2.clear();
				break;

			default:
				// handle any other value of choice2
				cout << "Invalid choice2. Please choose either 1 or 2." << endl;
				break;
			}
		}
		else if (choice == 9)
		{
			cout << "1. from console: " << endl;
			cout << "2. from file: " << endl;
			cin >> choice2;
			switch (choice2)
			{
			case 1:
				if (frequencies.empty())
					WordFrequency::calculateWordsFrequencies(frequencies, paragraph);
				WordFrequency::display_sorted_words(frequencies);

				// frequencies.clear();
				break;
			case 2:
				if (frequencies2.empty())
					WordFrequency::calculateWordsFrequencies(frequencies2, paragraph2);

				WordFrequency::display_sorted_words(frequencies2);
				// frequencies2.clear();
				break;

			default:
				// handle any other value of choice2
				cout << "Invalid choice2. Please choose either 1 or 2." << endl;
				break;
			}
		}
		else if (choice == 10)
		{
			cout << "1. from console: " << endl;
			cout << "2. from file: " << endl;
			cin >> choice2;
			switch (choice2)
			{
			case 1:
				if (frequencies.empty())
					WordFrequency::calculateWordsFrequencies(frequencies, paragraph);
				WordFrequency::SearchWord(frequencies);
				// frequencies.clear();
				break;
			case 2:
				if (frequencies2.empty())
					WordFrequency::calculateWordsFrequencies(frequencies2, paragraph2);
				WordFrequency::SearchWord(frequencies2);
				// frequencies2.clear();
				break;

			default:
				// handle any other value of choice2
				cout << "Invalid choice2. Please choose either 1 or 2." << endl;
				break;
			}
		}
		else if (choice == 11)
		{

			cout << "1. from console: " << endl;
			cout << "2. from file: " << endl;
			cin >> choice2;
			switch (choice2)
			{
			case 1:
				Paragraph::updateParagraph(frequencies, paragraph, global);
				WordFrequency::appendFrequenciesToFile(frequencies, "app.log", "Local - Console");
				WordFrequency::appendFrequenciesToFile(global, "app.log", "Global - Console");
				break;
			case 2:
				Paragraph::updateParagraph(frequencies2, paragraph2, global);
				WordFrequency::appendFrequenciesToFile(frequencies2, "app.log", "Local - File");
				WordFrequency::appendFrequenciesToFile(global, "app.log", "Global - File");
				//FileOperations::WritingInFile(paragraph2, filename);
				// frequencies2.clear();
				break;

			default:
				// handle any other value of choice2
				cout << "Invalid choice2. Please choose either 1 or 2." << endl;
				break;
			}
		}
		else if (choice == 12)
		{
			cout << "1. from console: " << endl;
			cout << "2. from file: " << endl;
			cin >> choice2;
			cin.ignore();
			switch (choice2)
			{
			case 1:
				if (frequencies.empty())
					WordFrequency::calculateWordsFrequencies(frequencies, paragraph);
				Paragraph::continueWritingInParagraph(frequencies, paragraph, global);
				WordFrequency::appendFrequenciesToFile(frequencies, "app.log", "Local - Console");
				WordFrequency::appendFrequenciesToFile(global, "app.log", "Global - Console");
				// frequencies.clear();
				break;
			case 2:
				if (frequencies2.empty())
					WordFrequency::calculateWordsFrequencies(frequencies2, paragraph2);
				Paragraph::continueWritingInParagraph(frequencies2, paragraph2, global);
				WordFrequency::appendFrequenciesToFile(frequencies2, "app.log", "Local - File");
				WordFrequency::appendFrequenciesToFile(global, "app.log", "Global - File");
				// frequencies2.clear();
				break;

			default:
				// handle any other value of choice2
				cout << "Invalid choice2. Please choose either 1 or 2." << endl;
				break;
			}
		}
		else if (choice == 13)
		{		 
			cout << "1. Save & Exit\n";
			cout << "2. Exit\n";
			int option;
			cin >> option;
			cin.ignore();
			
			switch (option)
			{
			case 1:
				cout << "1. from console: " << endl;
				cout << "2. from file: " << endl;
				cin >> choice2;
				cin.ignore();
				switch (choice2)
				{
				case 1:
					if (!paragraph.empty()) {
						FileOperations::WritingInFile(paragraph, "current_input_console.txt");
						FileOperations::WritingInFile(paragraph, "wordf.txt");
						cout << "File changed successfuly" << endl;
					}
					break;
				case 2:
					if (!paragraph2.empty()) {
						FileOperations::WritingInFile(paragraph2, "current_input.txt");
						FileOperations::WritingInFile(paragraph2, "wordf.txt");
						cout << "File changed successfuly" << endl;
					}
					break;
				default:
					cout << "Invalid choice. Please choose either 1 or 2." << endl;
					break;
				}
			default:
				return 0;
			}
		}
		else
		{
			cout << "Invalid choice. Exiting..." << endl;
			break;
		}
	}

	return 0;
}