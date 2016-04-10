#include "totalcut.hpp"
#include "savebox.hpp"
#include "excludeballcut.hpp"

int main() {
    const int n = 2;
    snowgoose::Box<double> bx(n);
    NUC::TotalCut<double> tcut(bx);   
    NUC::SaveBoxCut<double> savebox(bx);
    savebox.pushBox(bx);
    double c[n];
    NUC::ExcludeBallCut<double> exclbox(bx, 10, c);
    return 0;
}

