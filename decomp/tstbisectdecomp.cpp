#include <iostream>
#include <common/sgerrcheck.hpp>
#include "bisectdecomp.hpp"

int main() {
    const int n =2;
    snowgoose::Box<double> box(n);
    for(int i = 0; i < n; i ++) {
        box.mA[i] = - (i + 1);
        box.mB[i] = i + 1;
    }
    std::vector< snowgoose::Box<double> > boxv;
    boxv.push_back(box);
    NUC::BisectDecomp<double> bisdec;
    bisdec.split(boxv);
    for(auto b : boxv) {
        std::cout << snowgoose::BoxUtils::toString(b) << "\n";
    }
    SG_ASSERT(boxv.size() == 2);
    return 0;
}



