#include <RcppArmadillo.h>
#include <algorithm>

using namespace Rcpp;
using namespace std;

// [[Rcpp::depends(RcppArmadillo)]]

double get_delta_g(double, arma::mat, arma::mat);
double get_delta_d(arma::mat, arma::mat, arma::mat);
double get_delta_a(arma::mat, arma::mat, arma::mat);
double get_delta_i(arma::mat, arma::mat, arma::mat, arma::mat);
arma::vec delta_common(arma::mat, arma::mat, arma::mat);

// [[Rcpp::export]]
arma::uvec opt_montecarlocpp(const arma::mat& Xc, arma::uvec current,
                             arma::uvec candidateidx, const arma::mat& Xe,
                             int crit, int iterations,
                             bool repeated)
{
    // Xc is the X matrix for all candidate points.
    // current is a vector of indexes to Xc to indicate which points are in
    //   the current design
    // candidateidx is a vector of indexes that are legal propositions for
    //   swapping with an element of current (all if repeated, all\current if
    //   not)
    // crit is the criteria of interest (1==D, 2==A, 3==G, 4==I)
    // iterations is the total number of iterations in the process
    // repeated is whether or not to allow candidate points to appear more than
    //   once in current.

    // index of candidateidx (legal set of indices) to insert
    int in_c;
    // index of Xc (complete candidate set) to insert
    int in;
    // index of current (to remove) out == current(out_c) - 1
    int out_c;
    // index of Xc (complete candidate set) to remove
    int out;

    // number of points in candidate set
    int N = candidateidx.n_rows;
    // number of design points to use
    int n = current.n_rows;

    // Swapping condition delta > 0 == good
    double delta;

    // initial design
    int designSize = 10;
    arma::mat X = arma::diagmat(designSize);

    //inital best design
    arma::mat designBest = X;

    // get svd (called svdTemp) of designBest
    // gradient descent svdTemp to a minimum (called minBest)
    int minBest;
    int minTemp;
    
    for (int iter = 0; iter < iterations; iter++)
    {
	// could do something different besides investigating random designs
	arma::designTemp = generateRandomDesign;
	
	// get svd (called svdTemp) of designTemp

	// gradient descent svdTemp to a minimum (called minTemp)

	if (minTemp < minBest)
	{
	    minBest = minTemp;
	    designBest = designTemp;
	}
	
    }

}
