#include "totalcut.hpp"

int main() {
    const int n = 2;
    snowgoose::Box<double> bx(n);
    NUC::TotalCut<double> tcut(bx);    
    return 0;
}

