#include <limits>
#include <bags/bfsbag.hpp>
#include <cutfact/lbcutfact/lbcutfactory.hpp>
#include <oneobj/contboxconstr/dejong.hpp>

#include "basesolver.hpp"

int main() {
    const int n = 2;
    const double L = .001;
    const double eps = 0.1;

    OPTITEST::DejongProblemFactory fact(n, -2, 4);
    COMPI::MPProblem<double> *mpp = fact.getProblem();
    NUC::Sub<double> s(0, std::numeric_limits<double>::max(), *(mpp->mBox));
    NUC::BFSBag<double> bag;
    bag.putSub(s);


    return 0;
}


