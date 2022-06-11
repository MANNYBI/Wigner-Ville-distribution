#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <vector>
#include <string>
#include "wvt.h"

#define VECTOR std::vector
#define STRING std::string

struct ComputingOpts
{
	int			type;			// 0 - wvt; 1 - pwvt; 2 -spwvt
	double		fs;				// Частота дискретизации
	int			nTimeWindow;	// Длина окна во временной области
	int			nFreqWindow;	// Длина окна в частотной области

	ComputingOpts() : type(0), fs(48000), nTimeWindow(2), nFreqWindow(0) {}
};

struct OpeningOpts
{
	STRING	filename;
	bool	isReaded;
	int		nData;

	OpeningOpts() : filename(""), isReaded(false), nData(2) {}
};

struct PlottingOpts
{
	int		type;
	STRING	filename;

	STRING	scrmod;
	STRING	metafl;
	STRING	winfnt;
	int		colormap[2];

	PlottingOpts() : type(0), filename(""), scrmod("auto"), metafl("xwin"),
					 winfnt("Courier New"), colormap{1, 220} {}
};

struct SavingOpts
{
	STRING filename;
	int	   filetype; // 0 - Тепловая карта; 1 - файл коэффициентов; 2 - оба файла //TODO: 0 и 2

	SavingOpts() : filename(""), filetype(1) {}
};

bool		commandCheck(STRING inputCommand, VECTOR <STRING>& commandSplitted, bool isReaded);
inline bool openCommandCheck(VECTOR <STRING>& commandSplitted);
inline bool saveCommandCheck();
inline bool computeCommandCheck(VECTOR <STRING>& commandSplitted);
inline bool helpArgumentCheck(VECTOR <STRING> commandSplitted);

void		commandParse(VECTOR <STRING>& commandSplitted, ComputingOpts& computingOpts, OpeningOpts& openingOpts,
						 PlottingOpts& plottingOPts, SavingOpts& savingOpts);
void		computingCommandParse(VECTOR <STRING>& commandSplitted, int& dataSize, ComputingOpts& computingOpts);
inline void openingCommandParse(VECTOR <STRING>& commandSplitted, OpeningOpts& openingOpts);
inline void savingCommandParse(VECTOR <STRING>& commandSplitted, SavingOpts& savingOpts);
inline void plottingCommandParse(VECTOR <STRING>& commandSplitted, PlottingOpts& plottingOpts, OpeningOpts& openingOpts, ComputingOpts& computingOpts);

void commandExecute(const STRING& commandName, WVT& wvt, ComputingOpts& computingOpts, OpeningOpts& openingOpts,
					PlottingOpts& plottingOpts, SavingOpts& savingOpts);
void computeExecute(bool isReaded, WVT& wvt, const STRING& commandName, ComputingOpts& computingOpts);
void coutComputingParameters(const STRING& commandName, const ComputingOpts& computingOpts);

void getHelp(VECTOR <STRING>& commandSplitted);
void getHelp();

#undef VECTOR
#undef STRING
#endif
