#include <iostream>
#include <oneobj/contboxconstr/dejong.hpp>
#include <cutfact/common/recrepository.hpp>
#include <common/utilmacro.hpp>
#include "lipsupp.hpp"
#include "lipcutfact.hpp"

static const double LC = 2;

class DejongLipSupp : public NUC::LipSupp<double> {
public:

    /**
     * Retrieve Lipschitzian constants for a function
     * @param box the source box
     * @param lip the Lipschitzian constant
     */
    double getLipConst(const snowgoose::Box<double>& box) const {
        double lipconst = LC;        
        return lipconst;
    }
};

void initbox(snowgoose::Box<double>& box) {
    const int n = box.mDim;
    for (int i = 0; i < n; i++) {
        box.mA[i] = -2;
        box.mB[i] = 2;
    }
}

int main() {
    const int n = 2;
    const double eps = 0.1;
    OPTITEST::DejongObjective obj(n);
    DejongLipSupp lipsupp;
    NUC::RecRepository<double> rr(n);
    snowgoose::Box<double> box(n);
    initbox(box);
    const double delta = 0.1;
    NUC::LipCutFactory<double> lcf(obj, box, lipsupp, rr, delta);
    std::vector<std::shared_ptr <NUC::Cut <double> > > cv;
    lcf.getCuts(box, cv);
    for(auto o : cv) {
        std::cout << "Cut of type: " << o.get()->toString() << "\n";
    }
    SG_ASSERT(cv.size() == 1);
    SG_ASSERT(cv.at(0)->getType() == NUC::CutTypes::ExcludeBall);
    SG_ASSERT(((NUC::ExcludeBallCut<double>*)(cv.at(0).get()))->mR == (delta/LC));
    return 0;
}
