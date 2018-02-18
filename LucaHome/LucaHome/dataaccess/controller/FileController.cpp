#include "FileController.h"

FileController::FileController() {}

FileController::~FileController() {}

string FileController::ReadFile(string path)
{
	string content;
	ifstream file;

	file.open(path.c_str());

	if (file.is_open())
	{
		string line;
		while (!file.eof())
		{
			getline(file, line, '\n');
			content.append(line);
		}
	}
	else
	{
		syslog(LOG_CRIT, "Can't read file: %s", path.c_str());
	}

	file.close();

	return content;
}

vector<string> FileController::ReadFileList(string path)
{
	vector<string> contentList;
	ifstream file;

	file.open(path.c_str());

	if (file.is_open())
	{
		string line;
		while (!file.eof())
		{
			getline(file, line, '\n');
			contentList.push_back(line);
		}
	}
	else
	{
		syslog(LOG_CRIT, "Can't read file: %s", path.c_str());
	}

	file.close();

	return contentList;
}

bool FileController::SaveFile(string path, string content)
{
	bool success;
	ofstream file;
	file.open(path.c_str(), ios::out);

	if (file.is_open())
	{
		file << content;
		success = true;
	}
	else
	{
		syslog(LOG_ERR, "Can't write file: %s", path.c_str());
		success = false;
	}

	file.close();

	return success;
}
