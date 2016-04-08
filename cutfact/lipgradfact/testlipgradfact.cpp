/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <oneobj/contboxconstr/alufpent.hpp>
#include <common/interval.hpp>
#include "lpzgradsupp.hpp"
#include "lipgradfact.hpp"

class APSupp : public NUC::LpzGradSupp <double> {
public:

    void getLpzConst(const snowgoose::Box<double>& box, double* lpzv) {
        double a = box.mA[0];
        double b = box.mB[0];
        snowgoose::Interval<double>::degree(2, a, b, &a, &b);
        a *= 3;
        b *= 3;
        a -= 1;
        b -= 1;
        lpzv[0] = SGMAX(SGABS(a), SGABS(b));
        lpzv[1] = 0;
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
        box.mA[i] = 1;
        box.mB[i] = 2;
    }
}

int main() {
    const int n = 2;
    OPTITEST::AluffiPentiniObjective obj;
    APSupp gsupp;
    snowgoose::Box<double> box(n);
    snowgoose::Box<double> cbox(n);
    initbox(box);
    initcbox(cbox);
    NUC::LipGradCutFactory<double> lfact(obj, box, gsupp);
    std::vector<std::shared_ptr <NUC::Cut <double> > > cv;
    lfact.getCuts(cbox, cv);
    for(auto o : cv) {
        std::cout << "Cut of type: " << o.get()->about() << "\n";
    }
    return 0;
}
