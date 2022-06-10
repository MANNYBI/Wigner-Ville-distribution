#ifndef FILE_H
#define FILE_H
#include "command.h"

void fileOpenAndRead(std::vector <double>& DataParsed, OpeningOpts &openingOpts);
void fileSave(WVT& wvt, SavingOpts& savingOpts);
bool inputDataParse(std::vector <double>& dataParsed, std::ifstream& inputFile);

#endif