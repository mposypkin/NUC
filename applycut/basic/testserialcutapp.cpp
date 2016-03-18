#include <cuts/totalcut.hpp>
#include <box/boxutils.hpp>
#include <common/sgerrcheck.hpp>
#include <iostream>
#include "serialcutapp.hpp"

void initBox(double r, snowgoose::Box<double>& box) {
    const int n = box.mDim;
    for (int i = 0; i < n; i++) {
        box.mA[i] = -r;
        box.mB[i] = r;       
    }
}

int main() {
    NUC::SerialCutApplicator<double> cutapp;
    std::vector<std::shared_ptr <NUC::Cut <double> > > cutv;
    const int n = 2;
    snowgoose::Box<double> cbox(n), box1(n), box2(n);
    initBox(2, cbox);
    initBox(1, box1);
    initBox(3, box2);
    std::vector< snowgoose::Box<double> > boxv;
    boxv.push_back(box1);
    boxv.push_back(box2);
    NUC::TotalCut<double> *tc = new NUC::TotalCut <double> (cbox);
    std::shared_ptr< NUC::Cut<double> > pc(tc);
    cutv.push_back(pc);
    std::cout << "BEFORE:\n";
    for(auto&& rf : boxv) {
        std::cout << snowgoose::BoxUtils::toString(rf) << "\n";
    }
    cutapp.applyCuts(cutv, boxv);
    std::cout << "AFTER:\n";
    for(auto&& rf : boxv) {
        std::cout << snowgoose::BoxUtils::toString(rf) << "\n";
    }
    SG_ASSERT(boxv.size() == 1);
}
