#include <RcppArmadillo.h>
#include <RcppArmadilloExtensions/sample.h>
#include <algorithm>

using namespace Rcpp;



int grblend(arma::mat &, uint, arma::mat, arma::uvec, double);
int grcreep(arma::mat &, uint, double size, double);
int grmutat(arma::mat &, uint, double);

// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
arma::mat opt_geneticrealcpp(arma::mat parents, int n, int iterations, arma::uvec pidx)
{
    // parents is a matrix with each row being a vector of the design points
    //  with the first n being the first variable, the second n being the second
    //  varaible etc.
    // n is the design size
    // iterations is the number of iterations of the genetic algorithm
    // pidx is just 1:M where M is number of parents (easier to pass than write
    //  in c++!

    int M = parents.n_cols;

    arma::uvec second_parent;

    arma::mat children = parents;

    int iter, child;

    for (iter=0; iter<M; ++iter)
    {
        second_parent = RcppArmadillo::sample(pidx, M, false);

        children = parents;

        for (child=0; child<M; ++child)
        {
            grblend(children, child, parents, second_parent, 0);
            grcreep(children, child, .3, 0);
            grmutat(children, child, .5);
        }

    // start by hardcoding a linear model ~X1 + X2


    }

    return children;
}

int grblend(arma::mat & children, uint child, arma::mat parents, arma::uvec parent2, double alpha)
{
    int i;

    for (i=0; i<children.n_rows; ++i)
    {
        if (R::runif(0, 1) < alpha)
        {
            children(i, child) = parents(i, parent2[i]);
        }
    }
    return 0;
}

int grcreep(arma::mat & children, uint child, double size, double alpha)
{
    int i;

    for (i=0; i<children.n_rows; ++i)
    {
        if (R::runif(0, 1) < alpha)
        {
            children(i, child) = children(i, child) + R::rnorm(0, size);
            if (children(i, child) > 1)
            {
                children(i, child) = 1;
            }
            else if (children(i, child) < -1)
            {
                children(i, child) = -1;
            }
        }
    }
}

int grmutat(arma::mat & children, uint child, double alpha)
{
    int i;

    for (i=0; i<children.n_rows; ++i)
    {
        if (R::runif(0, 1) < alpha)
        {
            children(i, child) = R::runif(-1, 1);
        }
    }
}
