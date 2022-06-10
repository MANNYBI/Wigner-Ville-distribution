#pragma once
#ifndef WVT_H
#define WVT_H
#include <complex>
#include <fftw3.h>
#include <vector>
#include <cmath>
#include "window_functions.h"

#define RE 0
#define IM 1

class WVT
{
public:
	std::vector <double>		srcData;
	double*						wvtData;
	bool						isComputed;
	int							nTimeWins;
	int							nWin;
	double						fs;
	double						maxAmplitude;
	double						minAmplitude;

	WVT()
	{
		isComputed = false;
		nTimeWins = 0;
		nWin = 0;
		fs = 0;
		maxAmplitude = 0;
		minAmplitude = 0;
	}

	void clear()
	{
		free(wvtData);
		isComputed		=	false;
		nTimeWins		=	0;
		nWin			=	0;
		fs				=	0;
		maxAmplitude	=	0;
		minAmplitude	=	0;
	}

	void compute(const int& type, const double& _fs, const int& _nWin, const int& nFreqWin)
	{
		fs = _fs;
		nWin = _nWin;

		int		nData	= srcData.size();
		int		size	= nData + nWin;

		double* timeWin;
		double* freqWin;

		if (type != 0)
		{
			timeWin = (double*)_malloca(sizeof(double) * nWin);
			winKaiser(timeWin, nWin, 20);
		}

		fftw_complex* pseudoComplexSrc = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * size);
		fftw_complex* complexSrc = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * size);

		createComplexRe0(pseudoComplexSrc, nData, nWin);
		hilbertTransform(size, pseudoComplexSrc, complexSrc, size);
		fftw_free(pseudoComplexSrc);

		fftw_complex* complexSrcConj = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * size);
		complexConjugate(size, complexSrc, complexSrcConj);

		nTimeWins = nData + 1;
		fftw_complex** tempWVT = (fftw_complex**)fftw_malloc(sizeof(fftw_complex*) * nTimeWins);
		for (int i = 0; i <= nTimeWins - 1; i++)
		{
			tempWVT[i] = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nWin);
		}

		for (int i = 0; i <= nTimeWins - 1; i++)
		{
			if (nData % 2 == 0)
			{
				for (int j = 0; j <= nWin - 2; j++)
				{
					//TODO: ѕопробовать перегрузить операторы 
					tempWVT[i][j][RE] = complexSrc[j + i][RE] * complexSrcConj[nWin + i - j - 2][RE] - complexSrc[i + j][IM] * complexSrcConj[nWin + i - j - 2][IM];
					tempWVT[i][j][IM] = complexSrc[j + i][RE] * complexSrcConj[nWin + i - j - 2][IM] + complexSrc[i + j][IM] * complexSrcConj[nWin + i - j - 2][RE];
				}
				tempWVT[i][nWin - 1][RE] = complexSrc[nWin + i - 1][RE] * complexSrcConj[nWin + i - 1][RE] - complexSrc[nWin + i - 1][IM] * complexSrcConj[nWin + i - 1][IM];
				tempWVT[i][nWin - 1][IM] = complexSrc[nWin + i - 1][RE] * complexSrcConj[nWin + i - 1][IM] + complexSrc[nWin + i - 1][IM] * complexSrcConj[nWin + i - 1][RE];

				if (type != 0)
				{
					timeFiltering(timeWin, *&tempWVT[i]);
				}

				circShift((*&tempWVT[i]), nWin / 2 - 1, nWin);
			}
			else
			{
				for (int j = 0; j <= nWin - 1; j++)
				{
					//cout << "Nothing" << "\n";
				}
			}
		}

		fftw_free(complexSrcConj);
		fftw_free(complexSrc);

		if (type == 2)
		{
			freqWin = (double*)_malloca(sizeof(double) * nTimeWins);
			creatFreqWin(freqWin, nTimeWins, 20);
			freqFiltering(freqWin, tempWVT);
		}

		for (int i = 0; i <= nTimeWins - 1; i++)
		{
			fftw_plan planForward = fftw_plan_dft_1d(nWin, *&tempWVT[i], *&tempWVT[i], FFTW_FORWARD, FFTW_ESTIMATE);
			fftw_execute(planForward);
			fftw_destroy_plan(planForward);
		}

		wvtData = (double*)malloc(sizeof(double) * nTimeWins * nWin);
		maxAmplitude = tempWVT[0][0][RE];
		minAmplitude = tempWVT[0][0][RE];

		for (int i = 0; i <= nWin - 1; i++)
		{
			for (int j = 0; j <= nTimeWins - 1; j++)
			{
				*(wvtData + nWin * j + i) = tempWVT[j][i][RE];
				if (tempWVT[j][i][RE] > maxAmplitude)
				{
					maxAmplitude = tempWVT[j][i][RE];
				}

				if (tempWVT[j][i][RE] < minAmplitude)
				{
					minAmplitude = tempWVT[j][i][RE];
				}
			}
		}

		maxAmplitude = ceil(maxAmplitude);
		minAmplitude = floor(minAmplitude);

		for (int i = 0; i <= nTimeWins - 1; i++)
		{
			fftw_free(tempWVT[i]);
		}
		fftw_free(tempWVT);

		isComputed = true;
	}
private:
	void createComplexRe0(fftw_complex*& complexDataOut, const int& nData, const int& nWin)
	{
		int firstPos;

		if (nWin % 2 == 0)
		{
			firstPos = nWin / 2;
		}
		else
		{
			firstPos = (nWin - 1) / 2;
		}

		int lastPos = firstPos + nData - 1;
		int size = nWin + nData;

		for (int i = 0; i <= size - 1; i++)
		{
			complexDataOut[i][RE] = 0;
			complexDataOut[i][IM] = 0;

			if ((i >= firstPos) && (i <= lastPos))
			{
				complexDataOut[i][RE] = srcData[i - firstPos];
				complexDataOut[i][IM] = 0;
			}
		}
	}

	void complexConjugate(const int& nData, fftw_complex*& dataIn, fftw_complex*& dataOut)
	{
		for (int i = 0; i <= nData - 1; i++)
		{
			dataOut[i][RE] = dataIn[i][RE];
			dataOut[i][IM] = -dataIn[i][IM];
		}
	}

	void hilbertTransform(const int& nData, fftw_complex*& dataIn, fftw_complex*& dataOut, const double& fs)
	{
		fftw_plan planForward = fftw_plan_dft_1d(nData, dataIn, dataOut, FFTW_FORWARD, FFTW_ESTIMATE);
		fftw_execute(planForward);
		fftw_destroy_plan(planForward);

		int* h = new int[nData];
		int hnData = nData / 2 - 1;

		h[0] = 1;
		h[hnData + 1] = 1;

		for (int i = 1; i <= hnData; i++)
		{
			h[i] = 2;
		}

		for (int i = hnData + 1; i <= nData - 1; i++)
		{
			h[i] = 0;
		}

		for (int i = 0; i <= nData - 1; i++)
		{
			dataOut[i][RE] *= h[i];
			dataOut[i][IM] *= h[i];
		}

		delete[] h;

		fftw_plan plan_backward = fftw_plan_dft_1d(nData, dataOut, dataOut, FFTW_BACKWARD, FFTW_ESTIMATE);
		fftw_execute(plan_backward);
		fftw_destroy_plan(plan_backward);

		for (int i = 0; i <= nData - 1; i++)
		{
			dataOut[i][RE] /= fs;
			dataOut[i][IM] /= fs;
		}
	}

	inline void circShift(fftw_complex*& dataIn, const int& K, const int& size)
	{
		std::rotate(dataIn, dataIn + K, dataIn + size);
	}

	void timeFiltering(double*& w, fftw_complex*& data)
	{
		for (int i = 0; i <= nWin - 1; i++)
		{
			data[i][RE] *= w[i];
			data[i][IM] *= w[i];
		}
	}

	void creatFreqWin(double*& w, const int& nTimeWins, const double& param)
	{
		int N;

		if (nTimeWins % 2 == 0)
		{
			N = nTimeWins / 2;
		}
		else
		{
			N = (nTimeWins - 1) / 2;
		}

		double* tempW = (double*)_malloca(sizeof(double) * N);
		winKaiser(tempW, N, param);
		std::rotate(tempW, tempW + N / 2 - 1, tempW + N);


		for (int i = 0; i <= N - 1; i++)
		{
			w[i] = tempW[i];
		}

		for (int i = N; i <= nTimeWins - 1; i++)
		{
			w[i] = tempW[i - N];
		}

		//free(tempW);
	}

	void freqFiltering(double*& w, fftw_complex**& data)
	{
		fftw_complex* tempColumn = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nTimeWins);

		for (int i = 0; i <= nWin - 1; i++)
		{
			for (int j = 0; j <= nTimeWins - 1; j++)
			{
				tempColumn[j][RE] = data[j][i][RE];
				tempColumn[j][IM] = data[j][i][IM];
			}

			fftw_plan planForward = fftw_plan_dft_1d(nTimeWins, *&tempColumn, *&tempColumn, FFTW_FORWARD, FFTW_ESTIMATE);
			fftw_execute(planForward);
			fftw_destroy_plan(planForward);

			for (int j = 0; j <= nTimeWins - 1; j++)
			{
				tempColumn[j][RE] *= w[j];
				tempColumn[j][IM] *= w[j];
			}

			fftw_plan planBackward = fftw_plan_dft_1d(nTimeWins, *&tempColumn, *&tempColumn, FFTW_BACKWARD, FFTW_ESTIMATE);
			fftw_execute(planBackward);
			fftw_destroy_plan(planBackward);

			for (int j = 0; j <= nTimeWins - 1; j++)
			{
				data[j][i][RE] = tempColumn[j][RE] / fs;
				data[j][i][IM] = tempColumn[j][IM] / fs;
			}
		}

		fftw_free(tempColumn);
	}

};

#endif // !WVT_H
