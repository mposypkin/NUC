#include <iostream>
#include <box/boxutils.hpp>
#include <common/sgerrcheck.hpp>

#include "bfsbag.hpp"

const int n = 2;

int main() {

    snowgoose::Box<double> box(n);
    box.mA[0] = 0, box.mA[1] = 0, box.mB[0] = 1, box.mB[0] = 1;
    NUC::Sub<double> s1(1, 10, box), s2(2, 20, box), s3(3, 30, box), s4(4, 40, box);
    NUC::BFSBag<double> bag;
    bag.putSub(s1);
    bag.putSub(s2);
    bag.putSub(s3);
    bag.putSub(s4);
    auto tf = [](const NUC::Sub<double>& s) {
        std::cout << "Sub: \n";
        std::cout << "Score = " << s.mScore;
        std::cout << "\n Layer = " << s.mLayer;
        std::cout << "\n Box = " << snowgoose::BoxUtils::toString(s.mBox) << "\n";
    };
    bag.traverse(tf);
    SG_ASSERT(bag.size() == 4);
    return 0;
}