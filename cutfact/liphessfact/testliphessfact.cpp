#include <iostream>
#include <common/utilmacro.hpp>
#include <oneobj/contboxconstr/alufpent.hpp>
#include "lpzhesssupp.hpp"
#include "liphessfact.hpp"

class APHessSupp : public NUC::LpzHessSupp <double> {
public:

    void getLpzConst(const snowgoose::Box<double>& box, double* lpzv) {
        double a = box.mA[0];
        double b = box.mB[0];
        lpzv[0] = 6 * SGMAX(SGABS(a), SGABS(b));
        lpzv[1] = 0;
        lpzv[2] = 0;
        lpzv[3] = 0;
    }

};

void initbox(snowgoose::Box<double>& box) {
    const int n = box.mDim;
    for (int i = 0; i < n; i++) {
        box.mA[i] = -2;
        box.mB[i] = 2;
    }
}

void initcbox(snowgoose::Box<double>& box) {
    const int n = box.mDim;
    for (int i = 0; i < n; i++) {
        box.mA[i] = -0.1;
        box.mB[i] = 0.1;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    const int n = 2;
    OPTITEST::AluffiPentiniObjective obj;
    APHessSupp hsupp;
    snowgoose::Box<double> box(n);
    snowgoose::Box<double> cbox(n);
    initbox(box);
    initcbox(cbox);
    NUC::LipHessCutFactory<double> hfact(obj, box, hsupp);
    std::vector<std::shared_ptr <NUC::Cut <double> > > cv;
    hfact.getCuts(cbox, cv);
    for(auto o : cv) {
        std::cout << "Cut of type: " << o.get()->toString() << "\n";
    }
    return 0;
}

