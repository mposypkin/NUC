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
#include <applycut/common/cutapplicator.hpp>

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
        BaseSolver(SubBag<FT>& bag, Decomp<FT>& decomp, CutFactory<FT>& cutfact, CutApplicator<FT>& cutapp) :
        mBag(bag), mDecomp(decomp), mCutFact(cutfact), mCutApp(cutapp) {
        }

        /**
         * Solve the problem
         */
        void solve() {
            while (mBag.size()) {
                Sub<FT> sub = mBag.getSub();
                stepWatch(sub);
                std::vector<std::shared_ptr <NUC::Cut <double> > > cv;
                mCutFact.getCuts(sub.mBox, cv);
                std::vector< snowgoose::Box<FT> > bv;
                bv.push_back(sub.mBox);
                mCutApp.applyCuts(cv, bv);
                mDecomp.split(bv);
                for (auto bx : bv) {
                    Sub<FT> s(sub.mLayer + 1, sub.mScore, bx);
                    eval(s);
                    mBag.putSub(s);
                }
            }
        }

        /**
         * Adds new step watcher
         * @param f new step callback function
         */
        void addStepWatcher(std::function < void(const Sub<FT>& sub, const BaseSolver<FT>& solver) > f) {
            mStepWatchers.push_back(f);
        }

        /**
         * Adds new subproblem evaluator
         * @param f subproblem evaluator
         */
        void addSubEval(std::function < void(Sub<FT>& sub) > f) {
            mSubEvals.push_back(f);
        }

    private:

        void stepWatch(Sub<FT>& sub) {
            for (auto f : mStepWatchers)
                f(sub, *this);
        }

        void eval(Sub<FT>& sub) {
            for (auto f : mSubEvals)
                f(sub);
        }

        SubBag<FT>& mBag;
        Decomp<FT>& mDecomp;
        CutFactory<FT>& mCutFact;
        CutApplicator<FT>& mCutApp;
        std::vector < std::function < void(const Sub<FT>& sub, const BaseSolver<FT>& solver)> > mStepWatchers;
        std::vector < std::function < void(Sub<FT>& sub)> > mSubEvals;
    };

}

#endif /* BASESOLVER_HPP */

