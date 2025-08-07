#include "Utils.h"


void Utils::toLowercase(string& str)
{
	string result;
	for (char c : str)
	{
		result += tolower(c);
	}
	str = result;
}

void Utils::removePunctuation(string& str)
{
	for (char& c : str)
	{
		if (!isalnum(c) && c != '\'' && !isspace(c))
		{
			c = ' ';
		}
	}
}

string Utils::AutoCompleteSentence(string& sentence, string& paragraph)
{
	string paragraph2 = paragraph;
	Utils::toLowercase(paragraph2);

	string completedSentence = sentence;

	size_t position = paragraph2.find(sentence);
	if (position != string::npos)
	{
		for (char& c : paragraph2.substr(position + sentence.length()))
		{
			if (c == ' ' || (!isalnum(c) && c != '\''))
				break;
			completedSentence += c;
		}
		return completedSentence;
	}
	else
	{
		return "";
	}
}

string Utils::printMessage(string message)
{
	string input;
	cout << message;
	while (input == "")
	{
		getline(cin, input);
	}
	return input;
}

string Utils::readParagraphFromConsole()
{
	string paragraph = "";
	cout << "Enter the paragraph: ";
	while (paragraph == "")
	{
		getline(cin, paragraph);
	}
	return paragraph;
}
