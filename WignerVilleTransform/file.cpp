#include <iostream>
#include <fstream>
#include <sstream>
#include "file.h"

using namespace std;

void fileOpenAndRead(vector <double> &dataParsed, OpeningOpts &openingOpts)
{
	int pos = openingOpts.filename.find(':');
	if (pos == -1)
	{
		openingOpts.filename = "input\\" + openingOpts.filename;
	}

	ifstream inputFile(openingOpts.filename);
	openingOpts.isReaded = false;


	if (inputFile.is_open())
	{
		cout << "File opened successfully" << "\n";
		openingOpts.isReaded = inputDataParse(dataParsed, inputFile);
		inputFile.close();
	}
	else
	{
		cout << "Could not open the file" << "\n";
	}
}

void fileSave(WVT &wvt, SavingOpts& savingOpts)
{
	int pos = savingOpts.filename.find(':');
	if (pos == -1)
	{
		savingOpts.filename = "output\\" + savingOpts.filename;
	}
	ofstream outputFile(savingOpts.filename);

	if (outputFile.is_open())
	{
		for (int i = 0; i <= wvt.nWin - 1; i++)
		{
			for (int j = 0; j < wvt.nTimeWins - 1; j++)
			{
				outputFile << *(wvt.wvtData + wvt.nWin * j + i) << ", ";
			}
			outputFile << "\n";
		}
	}
}

bool inputDataParse(vector <double> &dataParsed, ifstream& inputFile)
{
	double inputData;
	vector <double> tempData;

	try
	{
		while (inputFile >> inputData)
		{
			tempData.push_back(inputData);
		}

		if (tempData.size() >= 2)
		{
			dataParsed = tempData;
			cout << "File readed successfully" << "\n";
			cout << tempData.size() << " counts have been read" << "\n";
			tempData.clear();

			return true;
		}
		else
		{
			cout << "File reading failed. Data file is too short" << "\n";
			tempData.clear();

			return false;
		}
	}
	catch (const char* msg)
	{
		cout << "Reading data from file failed" << "\n";
		return false;
	}
}
