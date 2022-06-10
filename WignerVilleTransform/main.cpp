#include <iostream>
#include "command.h"

using namespace std;

void programStart()
{
	system("title Wigner-Ville transform");

	cout << "Wigner-Ville transform" << " [Version 1.0]" << "\n";
	cout << "(c) 2022" << "\n";
	cout << "Type ? for help" << "\n" << "\n";
}

int main()
{
	programStart();

	bool isCorrect = false;
	string inputCommand;
	vector <string> commandSplitted;
	WVT wvt = WVT();
	ComputingOpts wvtComputingOpts;
	PlottingOpts wvtPlottingOpts;
	SavingOpts wvtSavingOpts;
	OpeningOpts wvtOpeningOpts;

	while (true)
	{
		cout << ">>>";
		getline(cin, inputCommand);
		cout << "\n";

		isCorrect = commandCheck(inputCommand, commandSplitted, wvtOpeningOpts.isReaded);

		if (isCorrect)
		{
			commandParse(commandSplitted, wvtComputingOpts, wvtOpeningOpts, wvtPlottingOpts, wvtSavingOpts);
			commandExecute(commandSplitted[0], wvt, wvtComputingOpts, wvtOpeningOpts, wvtPlottingOpts, wvtSavingOpts);
		}

		commandSplitted.clear();
		cout << "\n";
	}

	return 0;
}

