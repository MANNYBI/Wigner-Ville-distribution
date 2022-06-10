#include <cmath>

bool winKaiser(double*& w, const int& nWin, const double& param)
{
	double x;
	double y;
	double L;
	double num;
	double den = __std_smf_cyl_bessel_i(0, param);

	if (nWin % 2 == 0)
	{
		L = (double)nWin / 2.0;
	}
	else
	{
		L = (double)(nWin - 1) / 2.0;
	}

	for (int i = 0; i <= nWin - 1; i++)
	{
		x = 2.0 * ((double)i - L) / nWin;
		y = param * sqrt(1.0 - x * x);
		num = __std_smf_cyl_bessel_i(0, y);
		w[i] = num / den;
	}

	return true;
}