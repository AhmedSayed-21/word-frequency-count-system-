#include "FileOperations.h"

string FileOperations::readParagraphFromFile(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Failed to open file: " << filename << endl;
		return "";
	}

	string paragraph;
	string line;
	while (getline(file, line))
	{
		paragraph += line + "\n";
	}
	file.close();

	if (paragraph.empty())
	{
		cout << "Error reading paragraph from file: " << filename << endl;
		return "";
	}

	return paragraph;
}

int FileOperations::WritingInFile(string paragraph, string file_name)
{
	ofstream outfile(file_name, std::ofstream::app);
	if (!outfile.is_open())
	{
		cout << "can't open file for writing" << endl;
		return -1;
	}

	outfile << paragraph << endl;
	outfile.close();
	return 0;
}
