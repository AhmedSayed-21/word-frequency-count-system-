#include "Paragraph.h"
#include "Utils.h"
#include "WordFrequency.h"

void Paragraph::DeleteFromParagraph(unordered_map<string, int>& frequencies, string& paragraph, unordered_map<string, int>& global)
{
	while (true)
	{
		cout << "1. Delete specific sentence \n"
			"2. Delete the paragraph \n";

		int choice;

		cin >> choice;
		cin.ignore();

		if (choice == 1)
		{
			string paragraph2 = paragraph;
			Utils::toLowercase(paragraph2);

			string sentenceToDelete = "";
			cout << "Enter the sentence to delete: ";
			while (sentenceToDelete == "")
			{
				getline(cin, sentenceToDelete);
			}
			Utils::toLowercase(sentenceToDelete);

			string completed_sentence = Utils::AutoCompleteSentence(sentenceToDelete, paragraph);
			Utils::toLowercase(completed_sentence);

			while (true)
			{
				size_t position = paragraph2.find(completed_sentence);
				if (position != string::npos && !completed_sentence.empty())
				{

					if (completed_sentence == sentenceToDelete)
					{
						WordFrequency::WordFrequency::decrementFrequencies(frequencies, completed_sentence);
						WordFrequency::WordFrequency::decrementFrequencies(global, completed_sentence);

						paragraph.erase(position, completed_sentence.length());

						cout << " deleted successfully .\n";
						return;
					}
					else
					{
						cout << "Do yon mean '" << completed_sentence << "' (y/n) ? \n";
						char choice;
						while (true)
						{
							cin >> choice;
							if (choice == 'y' || choice == 'Y')
							{
								WordFrequency::WordFrequency::decrementFrequencies(frequencies, completed_sentence);
								WordFrequency::WordFrequency::decrementFrequencies(global, completed_sentence);
								paragraph.erase(position, completed_sentence.length());
								cout << " deleted successfully .\n";
								return;
							}
							else if (choice == 'n' || choice == 'N')
							{
								cout << "# Enter the correct sentence #\n";
								cin.ignore();
								completed_sentence = "";
								while (completed_sentence == "")
								{
									getline(cin, completed_sentence);
								}
								Utils::toLowercase(completed_sentence);
								sentenceToDelete = completed_sentence;
								break;
							}
							else
							{
								cout << " invalid choice , Enter yes or no .\n";
							}
						}
					}
				}

				else
				{
					cout << "Sentence not found.\n";
					break;
				}
			}

			break;
		}

		else if (choice == 2)
		{

			frequencies.clear();
			paragraph.clear();
			cout << " deleted successfully .\n";
			break;
		}
		else
		{
			cout << " invalid choice , enter 1 or 2 . \n";
		}
	}
}

void Paragraph::replaceSentence(unordered_map<string, int>& frequencies, string& paragraph, string old_sentence, string new_sentence, unordered_map<string, int>& global)
{
	string tempParagraph = paragraph;
	Utils::toLowercase(tempParagraph);

	Utils::toLowercase(old_sentence);

	string completed_sentence = Utils::AutoCompleteSentence(old_sentence, paragraph);
	Utils::toLowercase(completed_sentence);

	while (true)
	{
		size_t position = tempParagraph.find(old_sentence);

		if (position != string::npos && !completed_sentence.empty())
		{
			if (completed_sentence == old_sentence)
			{
				paragraph.replace(position, completed_sentence.length(), new_sentence);

				Utils::removePunctuation(new_sentence);
				Utils::toLowercase(new_sentence);

				Utils::removePunctuation(completed_sentence);

				WordFrequency::decrementFrequencies(frequencies, completed_sentence);
				WordFrequency::decrementFrequencies(global, completed_sentence);

				WordFrequency::calculateWordsFrequencies(frequencies, new_sentence);
				WordFrequency::calculateWordsFrequencies(global, new_sentence);

				cout << " Edited successfully . \n";
				return;
			}
			else
			{
				cout << "Do yon mean '" << completed_sentence << "' (y/n) ? \n";
				char choice;
				while (true)
				{
					cin >> choice;
					if (choice == 'y' || choice == 'Y')
					{
						cin.ignore();
						cout << " enter the New sentece to edit : \n";
						new_sentence = "";
						while (new_sentence == "")
						{
							getline(cin, new_sentence);
						}

						paragraph.replace(position, completed_sentence.length(), new_sentence);

						Utils::removePunctuation(new_sentence);
						Utils::toLowercase(new_sentence);

						Utils::removePunctuation(completed_sentence);

						WordFrequency::decrementFrequencies(frequencies, completed_sentence);
						WordFrequency::decrementFrequencies(global, completed_sentence);

						WordFrequency::calculateWordsFrequencies(frequencies, new_sentence);

						cout << " Edited successfully . \n";
						return;
					}
					else if (choice == 'n' || choice == 'N')
					{
						cout << "# Enter the correct sentence #\n";
						cin.ignore();
						completed_sentence = "";
						while (completed_sentence == "")
						{
							getline(cin, completed_sentence);
						}

						Utils::toLowercase(completed_sentence);
						old_sentence = completed_sentence;
						break;
					}
					else
					{
						cout << " invalid choice , Enter 1 or 2 . \n";
					}
				}
			}
		}
		else
		{
			cout << "Sentence not found.\n";
			break;
		}
	}
}

void Paragraph::continueWritingInParagraph(unordered_map<string, int>& WordFrequency, string& paragraph, unordered_map<string, int>& global)
{
	cout << paragraph << endl;

	stringstream words;
	string line;

	cout << "Writing ... \n";
	while (true)
	{
		getline(cin, line);

		if (line.empty())
			break;

		words << line;
	}

	paragraph += "\n" + words.str();
	WordFrequency::calculateWordsFrequencies(global, words.str());

	WordFrequency::calculateWordsFrequencies(WordFrequency, words.str());
}

void Paragraph::updateParagraph(unordered_map<string, int>& frequencies, string& paragraph, unordered_map<string, int>& global)
{
	int choice;

	while (true)
	{
		cout << "1. Edit \n"
			"2. Delete \n";

		cin >> choice;

		if (choice == 1)
		{
			cin.ignore();
			//EditInParagraph(frequencies, paragraph);

			string old_sentence = Utils::printMessage("\tEnter the old sentece to edit : \n");
			string new_sentence = Utils::printMessage("\tEnter the new sentece to edit : \n");
			replaceSentence(frequencies, paragraph, old_sentence, new_sentence, global);

			break;
		}
		if (choice == 2)
		{
			cin.ignore();
			DeleteFromParagraph(frequencies, paragraph, global);
			break;
		}
		else
		{
			cout << "Invalid choice. enter 1 to write in paragraph , 2 to delete sentence .\n";
		}
	}
}
