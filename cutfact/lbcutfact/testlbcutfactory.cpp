#include <iostream>
#include "lbcutfactory.hpp"


int main() {
    snowgoose::Box<double> bx;
    NUC::LBCutFactory<double> cf;
    std::vector<std::shared_ptr <NUC::Cut <double> > > cv;
    cf.getCuts(bx, cv);
    for(auto o : cv) {
        std::cout << "Cut of type: " << o.get()->about() << "\n";

    }
    return 0;
}
