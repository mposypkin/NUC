#include "totalcut.hpp"
#include "savebox.hpp"

int main() {
    const int n = 2;
    snowgoose::Box<double> bx(n);
    NUC::TotalCut<double> tcut(bx);   
    NUC::SaveBoxCut<double> savebox(bx);
    savebox.getBoxes().push_back(bx);
    return 0;
}

