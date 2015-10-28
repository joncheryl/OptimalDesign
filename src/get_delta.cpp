#include <RcppArmadillo.h>
#include <algorithm>

using namespace Rcpp;

arma::vec delta_common(arma::mat xpxinv, arma::mat row_in, arma::mat row_out)
{
    arma::mat diim = row_in * xpxinv * row_in.t();
    arma::mat doom = row_out * xpxinv * row_out.t();
    arma::mat diom = row_in * xpxinv * row_out.t();

    // Fedorov values as double
    double dii = diim(0, 0);
    double doo = doom(0, 0);
    double dio = diom(0, 0);

    double delta = ((1 + dii) * (1 - doo) + dio * dio - 1);

    arma::vec common(4);
    common(0) = delta;
    common(1) = dii;
    common(2) = doo;
    common(3) = dio;

    return common;
}

// compute change to D criterion given a change in the design matrix
double get_delta_d(arma::mat xpxinv, arma::mat row_in, arma::mat row_out)
{
    arma::vec common = delta_common(xpxinv, row_in, row_out);
    return common(0);
}

// compute change to A criterion given a change in the design matrix
double get_delta_a(arma::mat xpxinv, arma::mat row_in, arma::mat row_out)
{
    arma::vec common = delta_common(xpxinv, row_in, row_out);

    double delta_d = common(0);
    double dii = common(1);
    double dio = common(2);
    double doo = common(3);

    arma::mat phiiim = row_in * xpxinv * xpxinv * row_in.t();
    arma::mat phiiom = row_out * xpxinv * xpxinv * row_in.t();
    arma::mat phioim = row_in * xpxinv * xpxinv * row_out.t();
    arma::mat phioom = row_out * xpxinv * xpxinv * row_out.t();

    // convert phi values to double
    double phiii = phiiim(0, 0);
    double phiio = phiiom(0, 0);
    double phioi = phioim(0, 0);
    double phioo = phioom(0, 0);

    double delta = ( (1 - doo) * phiii + dio * (phiio + phioi) - (1 + dii) * phioo ) / (1 + delta_d);

    return delta;
}

// compute ESTIMATED change to g criterion given a change in the design matrix
double get_delta_g(double g_crit_old, arma::mat X, arma::mat U_can)
{
    arma::vec s;
    arma::mat U, V;
    arma::svd_econ(U, s, V, X, "right");
    s = 1 / s;

    arma::mat Dinv = arma::diagmat(s);

    arma::mat svd_thing = U_can * V * Dinv;
    svd_thing = svd_thing % svd_thing;
    arma::vec leverages = arma::sum(svd_thing, 1);
    double g_crit = leverages.max();

    return g_crit_old - g_crit;
}

// compute change to I criterion given a change in the design matrix
double get_delta_i(arma::mat xpxinv, arma::mat row_in, arma::mat row_out, arma::mat B)
{
    arma::vec common = delta_common(xpxinv, row_in, row_out);

    double delta_d = common(0);
    double dii = common(1);
    double dio = common(2);
    double doo = common(3);

    arma::mat phiiim = row_in * xpxinv * B * xpxinv * row_in.t();
    arma::mat phiiom = row_out * xpxinv * B * xpxinv * row_in.t();
    arma::mat phioim = row_in * xpxinv * B * xpxinv * row_out.t();
    arma::mat phioom = row_out * xpxinv * B * xpxinv * row_out.t();

    // convert phi values to double
    double phiii = phiiim(0, 0);
    double phiio = phiiom(0, 0);
    double phioi = phioim(0, 0);
    double phioo = phioom(0, 0);

    double delta = ( (1 - doo) * phiii + dio * (phiio + phioi) - (1 + dii) * phioo ) / (1 + delta_d);

    return delta;
}

// compute ESTIMATED change to g criterion given a change in the design matrix
// using gradient descent
double get_delta_gGD(double g_crit_old, arma::mat xpxinv, arma::mat row_in, arma::mat row_out, const int[] &primes)
{
    // estimated g_crit of new design
    double g_crit_temp;

    // get svd (called svdTemp) of designTemp
    
    // gradient descent svdTemp to a minimum (called minBest)
    
    double delta = g_crit_temp - g_crit_old;

    return delta;
}
