#include "command.h"

using namespace std;

void commandParse(vector <string>& commandSplitted, ComputingOpts& computingOpts, OpeningOpts& openingOpts,
	PlottingOpts& plottingOpts, SavingOpts& savingOpts)
{
	if (commandSplitted[0] == "wvt")
	{
		computingCommandParse(commandSplitted, openingOpts.nData, computingOpts);
	}

	if (commandSplitted[0] == "open")
	{
		openingCommandParse(commandSplitted, openingOpts);
	}

	if (commandSplitted[0] == "save")
	{
		savingCommandParse(commandSplitted, savingOpts);
	}

	if (commandSplitted[0] == "plot")
	{
		plottingCommandParse(commandSplitted, plottingOpts, openingOpts, computingOpts);
	}

	if (commandSplitted[0] == "pwvt")
	{
		computingCommandParse(commandSplitted, openingOpts.nData, computingOpts);
	}

	if (commandSplitted[0] == "spwvt")
	{
		computingCommandParse(commandSplitted, openingOpts.nData, computingOpts);
	}
}

void computingCommandParse(vector <string>& commandSplitted, int& dataSize, ComputingOpts& computingOpts)
{
	computingOpts.fs			=	stod(commandSplitted[1]); // command <fs>
	computingOpts.nTimeWindow	=	dataSize;
	computingOpts.nFreqWindow	=	0;

	if (commandSplitted.size() == 3) // command <fs> [nTimeWindow]
	{
		computingOpts.nTimeWindow = stoi(commandSplitted[2]);
	}

	if (commandSplitted.size() == 4) // command <fs> [nTimeWindow] [nFreqWindow]
	{
		computingOpts.nTimeWindow = stoi(commandSplitted[2]);
		computingOpts.nFreqWindow = stoi(commandSplitted[3]);
	}

	if (commandSplitted[0] == "wvt")
	{
		computingOpts.type = 0;
	}

	if (commandSplitted[0] == "pwvt")
	{
		computingOpts.type = 1;
	}

	if (commandSplitted[0] == "spwvt")
	{
		computingOpts.type = 2;

		if (dataSize % 2 == 0)
		{
			computingOpts.nFreqWindow = dataSize / 2;
		}
		else
		{
			computingOpts.nFreqWindow = (dataSize - 1) / 2;
		}
	}
}

inline void openingCommandParse(vector <string>& commandSplitted, OpeningOpts& openingOpts)
{
	openingOpts.filename = commandSplitted[1];
}

inline void plottingCommandParse(vector <string>& commandSplitted, PlottingOpts& plottingOpts, OpeningOpts& openingOpts, ComputingOpts& computingOpts)
{
	plottingOpts.filename = openingOpts.filename;
	plottingOpts.nTimeWindow = computingOpts.nTimeWindow;
	plottingOpts.fs = computingOpts.fs;
	plottingOpts.type = computingOpts.type;
}

inline void savingCommandParse(vector <string>& commandSplitted, SavingOpts& savingOpts)
{
	savingOpts.filename = commandSplitted[1];

	if (commandSplitted.size() == 3)
	{
		savingOpts.filetype = stoi(commandSplitted[3]);
	}
	else
	{
		savingOpts.filetype = 0;
	}
}