#include "discpp.h"
#include "plot.h"

//using namespace std;

void heatmapPlot(WVT& wvt, PlottingOpts& plottingOpts)
{
    Dislin g;

    int     timeAxis;
    int     freqAxis = wvt.nWin;
    char    temp[50];

    if (wvt.fs != 1)
    {
        timeAxis = wvt.nTimeWins;
    }
    else
    {
        timeAxis = wvt.nTimeWins - 1;
    }

    g.winapp("windows");
    g.scrmod(plottingOpts.scrmod.c_str());
    g.metafl(plottingOpts.metafl.c_str());
    g.disini();
    g.pagera();
    g.errmod("all", "off");
    g.chacod("UTF8");
    g.winfnt(plottingOpts.winfnt.c_str());

    sprintf(temp, "File:  %s\n", plottingOpts.filename.c_str());
    g.paghdr(temp, " ", 3, 0);

    switch (plottingOpts.type)
    {
    case 0:
        g.titlin("Wigner-Ville transform", 1);
        break;
    case 1:
        g.titlin("Pseudo Wigner-Ville transform", 1);
        break;
    case 2:
        g.titlin("Smoothed pseudo Wigner-Ville transform", 1);
        break;
    }

    if (wvt.fs != 1)
    {
        sprintf(temp, "Sampling frequency: %.*f\n Hz", 1, wvt.fs);
        g.titlin(temp, 3);
        sprintf(temp, "FFT length: %d\n samples", wvt.nWin);
        g.titlin(temp, 4);

        g.name("Time, sec", "x");
        g.name("Frequency, Hz", "y");
    }
    else
    {
        sprintf(temp, "FFT length: %d\n samples", wvt.nWin);
        g.titlin(temp, 3);

        g.name("Samples", "x");
        g.name("Normalized frequency", "y");
    }

    g.name("Amplitude", "z");

    g.intax();
    g.autres(timeAxis, freqAxis);
    g.axspos(300, 1850);
    g.ax3len(2200, 1400, 1400);

    g.colran(plottingOpts.colormap[0], plottingOpts.colormap[1]);
    g.labdig(1, "x");
    g.labdig(1, "y");

    //    From dislin manual
    //    void graf3(float xa, float xe, float xor, float xstp, float ya, float ye, float yor, float ystp, float za, float ze, float zor, float zstp);
    //
    //    XA, XE	are the lowerand upper limits of the X - axis.
    //    XOR, XSTP	are the first X - axis label and the step between labels.
    //    YA, YE	are the lowerand upper limits of the Y - axis.
    //    YOR, YSTP	are the first Y - axis label and the step between labels.
    //    ZA, ZE	are the lowerand upper limits of the Z - axis.
    //    ZOR, ZSTP	are the first Z - axis label and the step between labels.*/

    double  XA     = 0.0;
    double  XE     = (timeAxis / wvt.fs);
    double  XOR    = 0.0;
    double  XSTP   = (0.2 * timeAxis / wvt.fs);
    double  YA     = 0;
    double  YE     = (wvt.fs / 2);
    double  YOR    = 0.0;
    double  YSTP   = (0.1 * wvt.fs / 2);
    int     ZA     = wvt.minAmplitude;
    int     ZE     = wvt.maxAmplitude;
    int     ZOR    = wvt.minAmplitude;
    double  ZSTP   = (abs(wvt.maxAmplitude) + abs(wvt.minAmplitude)) / 5;

    if (wvt.fs == 1)
    {
        YE = wvt.fs;
        YSTP = (0.1 * wvt.fs);
    }

    g.graf3(XA, XE, XOR, XSTP, YA, YE, YOR, YSTP, ZA, ZE, ZOR, ZSTP);

    g.crvmat(wvt.wvtData, timeAxis, freqAxis, 2, 2);

    g.height(45);
    g.title();
    g.disfin();
}