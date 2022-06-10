#include "command.h"

using namespace std;

void getHelp()
{
	cout << "To get information about a command, enter <command> HELP" << "\n";
	cout << "Available commands" << "\n";
	cout << "	" << "CLEAR	" << "Clears the command line" << "\n";
	cout << "	" << "OPEN	" << "Opens a file with input data" << "\n";
	cout << "	" << "PLOT	" << "Plots the transform result" << "\n";
	cout << "	" << "PWVT	" << "Computes the Wigner-Ville transform, " << "\n";
	cout << "	" << "		" << "using a time window function " << "\n";
	cout << "	" << "SAVE	" << "Saves the transform result" << "\n";
	cout << "	" << "SPWVT	" << "Computes the Wigner-Ville transform, using a time" << "\n";
	cout << "	" << "		" << "and frequency window function" << "\n";
	cout << "	" << "WVT	" << "Computes the Wigner-Ville transform" << "\n";
	cout << "\n";

	cout << "Example of using the program" << "\n";
	cout << "	" << "1. Add the input data file to the folder '(progarammDirectory)\input\'" << "\n";
	cout << "	" << "2. Run the programm" << "\n";
	cout << "	" << "Next, use the commands:" << "\n";
	cout << "	" << "3. open '(your filename).txt'" << "\n";
	cout << "	" << "4. wvt 1" << "\n";
	cout << "	" << "5. plot" << "\n";
	cout << "Notes" << "\n";
	cout << "	" << "By using command 'wvt 1' you got the normalized Wigner-Ville transform." << "\n";
	cout << "	" << "You can use 'pwvt' or 'spwvt' to get other types of transform." << "\n";
	cout << "	" << "If you want to get not normalized result, you should change" << "\n";
	cout << "	" << "parameter <fs> from 1 to your own." << "\n";

}

void getHelp(vector <string>& commandSplitted)
{
	if (commandSplitted[0] == "wvt")
	{
		cout << "Computes Wigner-Ville transform of input data without using window functions" << "\n\n";
		cout << "Usage: wvt <fs> [nTimeWindow]"  << "\n\n";
		cout << "Parameters:   " << "Type:  "  << "Necessity: " << "Descriprtion:"            << "\n\n";
		cout << "<fs>          " << "double "  << "yes	"       << "Sampling frequency in Hz" << "\n";
		cout << "[nTimeWindow] " << "int    "  << "no		"   << "Length of FFT"            << "\n";
	}
	else if (commandSplitted[0] == "open")
	{
		cout << "Opens the input data file" << "\n\n";
		cout << "Usage: open <filename>" << "\n\n";
		cout << "Parameters:   " << "Type:  " << "Necessity: " << "Descriprtion:" << "\n\n";
		cout << "<filename>    " << "string " << "yes        " << "Input data filename" << "\n";
	}
	else if (commandSplitted[0] == "save")
	{
		cout << "Saves the transform result" << "\n\n";
		cout << "Usage: save <filename> [type]" << "\n\n";
		cout << "Parameters:   " << "Type:  " << "Necessity: " << "Descriprtion:" << "\n\n";
		cout << "<filename>    " << "string " << "yes   " << "Output data filename" << "\n";
		cout << "[type]        " << "int    " << "no      " << "Type of output file" << "\n";
		cout << "                             0 - .txt, 1 - .png, 2 - .txt and .png" << "\n";
		cout << "                             default type - 0";
	}
	else if (commandSplitted[0] == "pwvt")
	{
		cout << "Computes  pseudo Wigner-Ville transform of input data with " << "\n";
		cout << "using time window function"   << "\n\n";
		cout << "Usage: pwvt <fs> [nTimeWindow]" << "\n\n";
		cout << "Parameters:   " << "Type:  "  << "Necessity: " << "Descriprtion:"                  << "\n\n";
		cout << "<fs>          " << "double "  << "yes	"      << "Sampling frequency in Hz"        << "\n";
		cout << "[nTimeWindow] " << "int    "  << "no		"  << "Length of Kaiser window and FFT" << "\n";
	}
	else if (commandSplitted[0] == "spwvt")
	{
		cout << "Computes  smoothed pseudo Wigner-Ville transform of input data with " << "\n";
		cout << "using time and frequency windows functions" << "\n\n";
		cout << "Usage: spwvt <fs> [nTimeWindow] [nFreqWindow]" << "\n\n";
		cout << "Parameters:   " << "Type:  " << "Necessity: " << "Descriprtion:"                      << "\n\n";
		cout << "<fs>          " << "double " << "yes	"      << "Sampling frequency in Hz"           << "\n";
		cout << "[nTimeWindow] " << "int    " << "no		"  << "Length of Kaiser window and FFT"    << "\n";
		cout << "[nFreqWindow] " << "int    " << "no        "  << " Length of Kaiser frequency window" << "\n";
	}
	else if (commandSplitted[0] == "?")
	{
		cout << "Display help message" << "\n";
	}
	else
	{
		cout << "Unknown command '" << commandSplitted[0] << "'\n";
	}
}
