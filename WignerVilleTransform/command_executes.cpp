#include <fstream>
#include "file.h"
#include "plot.h"

using namespace std;

void commandExecute(const string& commandName, WVT& wvt, ComputingOpts& computingOpts, OpeningOpts& openingOpts,
	PlottingOpts& plottingOpts, SavingOpts& savingOpts)
{
	if (commandName == "wvt")
	{
		computeExecute(openingOpts.isReaded, wvt, commandName, computingOpts);
	}

	if (commandName == "pwvt")
	{
		computeExecute(openingOpts.isReaded, wvt, commandName, computingOpts);
	}

	if (commandName == "spwvt")
	{
		computeExecute(openingOpts.isReaded, wvt, commandName, computingOpts);
	}

	if (commandName == "open")
	{
		wvt.srcData.clear();
		cout << "Opening " << openingOpts.filename << "\n";
		fileOpenAndRead(wvt.srcData, openingOpts);
		openingOpts.nData = wvt.srcData.size();
	}

	if (commandName == "save")
	{
		if (wvt.isComputed)
		{
			fileSave(wvt, savingOpts);

			cout << "Saving complete" << "\n";
		}
		else
		{
			cout << "No computed data. You should to compute the transform first" << "\n";
		}
	}

	if (commandName == "?")
	{
		getHelp();
	}

	if (commandName == "clear")
	{
		system("cls");
		cout << "The command line is cleared" << "\n";
	}

	if (commandName == "plot")
	{
		if (wvt.isComputed)
		{
			heatmapPlot(wvt, plottingOpts);
		}
		else
		{
			cout << "No computed data. You should to compute the transform first" << "\n";
		}
	}
}

void computeExecute(bool isReaded, WVT& wvt, const string& commandName, ComputingOpts& computingOpts)
{
	if (isReaded)
	{
		wvt.clear();
		coutComputingParameters(commandName, computingOpts);
		wvt.compute(computingOpts.type, computingOpts.fs, computingOpts.nTimeWindow, computingOpts.nFreqWindow);
		cout << "Computing was completed successfully" << endl;
	}
	else
	{
		cout << "No readed data. You should to open the data file first" << "\n";
		cout << "" << "\n";
	}
}

void coutComputingParameters(const string& commandName, const ComputingOpts& computingOpts)
{
	cout << "Computing " << commandName << " with the next parameters : " << "\n";
	cout << "Sampling frequency:	     " << computingOpts.fs << "\n";

	switch (computingOpts.type)
	{
	case 0:
	{
		cout << "FFT length:		     " << computingOpts.nTimeWindow << "\n";
		break;
	}
	case 1:
	{
		cout << "Time window length:	     " << computingOpts.nTimeWindow << "\n";
		cout << "Using window function:       " << "Kaiser" << "\n";
		break;
	}
	case 2:
	{
		cout << "Time window length:	     " << computingOpts.nTimeWindow << "\n";
		cout << "Using window function:       " << "Kaiser" << "\n";
		cout << "Frequency window length:     " << computingOpts.nTimeWindow << "\n";
		cout << "Using window function:       " << "Kaiser" << "\n";
		break;
	}
	}

	cout << "\n" << "Computing..." << "\n";

}
