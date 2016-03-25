/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   solver.hpp
 * Author: mikhail
 *
 * Created on 21 марта 2016 г., 10:46
 */

#ifndef BASESOLVER_HPP
#define BASESOLVER_HPP

#include <vector>
#include <functional>

#include <bags/subbag.hpp>
#include <decomp/decomp.hpp>
#include <cutfact/common/cutfactory.hpp>

namespace NUC {

    /**
     * Non-uniform coverings basice solver
     */
    template <class FT> class BaseSolver {
    public:

        /**
         * Constructor
         * @param bag bag of tasks
         * @param decomp decomposer
         * @param cutfact Cut generator's factory
         */
        BaseSolver(SubBag<FT>& bag, Decomp<FT>& decomp, CutFactory<FT>& cutfact) :
        mBag(bag), mDecomp(decomp), mCutFact(cutfact) {
        }

        /**
         * Solve the problem
         */
        void solve() {
            while (mBag.size()) {
                Sub<FT> sub = mBag.getSub();
                for (auto f : mStepWatchers)
                    f(sub, *this);
            }
        }

        void addStepWatcher(std::function <  void(const Sub<FT>& sub, const BaseSolver<FT>& solver) > f) {
            mStepWatchers.push_back(f);
        }

    private:

        void eval(Sub<FT> sub) {
            std::cout << "Sub is processing\n";
        }

        SubBag<FT>& mBag;
        Decomp<FT>& mDecomp;
        CutFactory<FT>& mCutFact;   
        std::vector < std::function < void(const Sub<FT>& sub, const BaseSolver<FT>& solver)> > mStepWatchers;
    };

}

#endif /* BASESOLVER_HPP */

