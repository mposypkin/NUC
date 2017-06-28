#include <iostream>
#include <oneobj/contboxconstr/dejong.hpp>
#include "lbcutfactory.hpp"
#include "lpzbndsupp.hpp"
#include "recordsupp.hpp"



int main() {
    const int n = 2;
    const double L = .001;
    const double eps = 0.1;
    OPTITEST::DejongProblemFactory fact(n, -2, 4);
    COMPI::MPProblem<double> *mpp = fact.getProblem();
    auto pf = mpp->mObjectives.at(0);
    NUC::RecordSupplier<double> rs(2);
    NUC::LpzBoundSupplier<double> lplb(n, L, *pf);
    NUC::LBCutFactory<double> cf(eps, rs, lplb);
    std::vector<std::shared_ptr <NUC::Cut <double> > > cv;
    const snowgoose::Box<double>& bx = *(mpp->mBox);
    cf.getCuts(bx, cv);
    for(auto o : cv) {
        std::cout << "Cut of type: " << o.get()->toString() << "\n";
    }
    return 0;
}
