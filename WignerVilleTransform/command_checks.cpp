#include "command.h"
#include <fstream>
#include <sstream>

using namespace std;

template <typename T>
bool typeCheck(string strToCheck, T base)
{
	char* p = 0;

	if (typeid(base) == typeid(double&))
	{
		strtod(strToCheck.c_str(), &p);
	}

	if (typeid(base) == typeid(int&))
	{
		_strtoi64(strToCheck.c_str(), &p, 0);
	}

	if (*p)
	{
		cout << "Parameter [" << strToCheck << "] is not a(n) " << typeid(base).name() << "\n";
		return false;
	}

	return true;
}

bool commandCheck(string inputCommand, vector <string>& commandSplitted, bool isReaded)
{
	if (inputCommand[0] == '\0') // Проверка на пустую строку
	{
		return false;
	}

	bool isCorrect = false;
	bool isHelp = false;
	stringstream stringStream(inputCommand);
	string word;

	while (stringStream >> word)
	{
		commandSplitted.push_back(word);
	}

	isHelp = helpArgumentCheck(commandSplitted);
	if (isHelp)
	{
		getHelp(commandSplitted);
		return false; // Чтобы не происходил вызов commandParse из main.cpp
	}

	if (commandSplitted[0] == "wvt")
	{
		isCorrect = computeCommandCheck(commandSplitted);

		if (!isCorrect)
		{
			return false;
		}

		return true;
	}

	if (commandSplitted[0] == "open")
	{
		isCorrect = openCommandCheck(commandSplitted);

		if (!isCorrect)
		{
			return false;
		}

		return true;
	}

	if (commandSplitted[0] == "save")
	{
		isCorrect = saveCommandCheck;

		if (!isCorrect)
		{
			return false;
		}

		return true;
	}

	if (commandSplitted[0] == "pwvt")
	{
		isCorrect = computeCommandCheck(commandSplitted);

		if (!isCorrect)
		{
			return false;
		}

		return true;
	}

	if (commandSplitted[0] == "spwvt")
	{
		isCorrect = computeCommandCheck(commandSplitted);

		if (!isCorrect)
		{
			return false;
		}

		return true;
	}

	if (commandSplitted[0] == "plot")
	{
		return true;
	}

	if (commandSplitted[0] == "clear")
	{
		return true;
	}

	if (commandSplitted[0] == "?")
	{
		return true;
	}

	cout << "Unknown command '" << commandSplitted[0] << "'" << "\n";
	return false;
}

inline bool openCommandCheck(vector <string>& commandSplitted)
{
	string supportedExtension = ".txt";

	if (commandSplitted.size() == 2)
	{
		int pos = commandSplitted[1].find(supportedExtension);

		if (pos == -1)
		{
			cout << "File extension not supported" << "\n";
			cout << "Supported file extensions: " << supportedExtension << "\n";
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		cout << "Use:" << "\n";
		cout << "	open <filename>" << "\n";
		cout << "Supported file extensions: " << supportedExtension << "\n";
		return false;
	}
}

inline bool computeCommandCheck(vector <string>& commandSplitted)
{
	bool isCorrect;

	if ((commandSplitted.size() <= 1) || (commandSplitted.size() >= 5))
	{
		cout << "Use:" << "\n";
		cout << "	" << commandSplitted[0] << " <fs> [nTimeWindow] [nFreqWindow]" << "\n";
		cout << "Type 'help' to get more information" << "\n";
		return false;
	}

	isCorrect = typeCheck(commandSplitted[1], 0.0);
	if (!isCorrect) return false;

	if (commandSplitted.size() == 3)
	{
		isCorrect = typeCheck(commandSplitted[2], 0);
		if (!isCorrect) return false;
	}

	if (commandSplitted.size() == 4)
	{
		isCorrect = typeCheck(commandSplitted[2], 0);
		if (!isCorrect) return false;

		isCorrect = typeCheck(commandSplitted[3], 0);
		if (!isCorrect) return false;
	}

	return true;
}

inline bool saveCommandCheck()
{
	return true;
}

inline bool helpArgumentCheck(vector <string> commandSplitted)
{
	if (commandSplitted.size() != 1)
	{
		if (commandSplitted[1] == "HELP")
		{
			return true;
		}
	}

	return false;
}