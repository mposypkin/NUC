#include <limits>
#include <bags/bfsbag.hpp>
#include <cutfact/lbcutfact/lpzbndsupp.hpp>
#include <cutfact/lbcutfact/recordsupp.hpp>
#include <cutfact/lbcutfact/lbcutfactory.hpp>
#include <decomp/bisectdecomp.hpp>
#include <oneobj/contboxconstr/dejong.hpp>
#include <c++/4.9.2/bits/stl_vector.h>

#include "basesolver.hpp"

int main() {
    const int n = 2;
    const double L = .001;
    const double eps = 0.1;

    // Setup problem
    OPTITEST::DejongProblemFactory fact(n, -2, 4);
    COMPI::MPProblem<double> *mpp = fact.getProblem();

    //Setup bag of sub problems
    NUC::Sub<double> s(0, std::numeric_limits<double>::max(), *(mpp->mBox));
    NUC::BFSBag<double> bag;
    bag.putSub(s);

    //Setup Cut Factory
    NUC::RecordSupplier<double> rs(std::numeric_limits<double>::max());
    COMPI::Functor<double>* pf = mpp->mObjectives.at(0);
    NUC::LpzBoundSupplier<double> lplb(n, L, *pf);
    NUC::LBCutFactory<double> cf(eps, rs, lplb);

    // Setup decomposer
    NUC::BisectDecomp<double> bisdec;

    // Setup solver
    NUC::BaseSolver<double> solver(bag, bisdec, cf);

    //Setup step watchers
    auto tf = [](const NUC::Sub<double>& s, const NUC::BaseSolver<double>& slv) {
        std::cout << "Sub: \n";
        std::cout << "Score = " << s.mScore;
        std::cout << "\n Layer = " << s.mLayer;
        std::cout << "\n Box = " << snowgoose::BoxUtils::toString(s.mBox) << "\n";
    };
    
    solver.addStepWatcher(tf);

    // Run solver
    solver.solve();


    return 0;
}


