/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <oneobj/contboxconstr/alufpent.hpp>
#include "lpzgradsupp.hpp"

class APSupp : public NUC::LpzGradSupp <double> {
    public:
    void getLpzConst(const snowgoose::Box<double>& box, double* lpzv) {
        const int n = box.mDim;
        for(int i = 0; i < n; i ++) {
            // TMP
            lpzv[i] = 1.;
        }
    }
};

int main() {
    OPTITEST::AluffiPentiniObjective obj;
    return 0;
}
