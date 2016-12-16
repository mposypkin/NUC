/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   treewatchsolver.hpp
 * Author: Alexander Usov
 *
 * Created on December 14, 2016, 10:40 AM
 */

#ifndef TREEWATCHSOLVER_HPP
#define TREEWATCHSOLVER_HPP

#include <vector>
#include <functional>

#include "basesolver.hpp"
#include <bags/subbag.hpp>
#include <bags/idgen.hpp>
#include <decomp/decomp.hpp>
#include <cutfact/common/cutfactory.hpp>
#include <applycut/common/cutapplicator.hpp>

namespace NUC {

    /**
     * Non-uniform coverings basic solver with tree watch
     */
    template <class FT> class TreeWatchSolver : BaseSolver<FT> {
    public:

        /**
         * Constructor
         * @param bag bag of tasks
         * @param decomp decomposer
         * @param cutfact Cut generator's factory
         */
        TreeWatchSolver(SubBag<FT>& bag, Decomp<FT>& decomp, CutFactory<FT>& cutfact, CutApplicator<FT>& cutapp) :
        BaseSolver<FT>(bag, decomp, cutfact, cutapp) {
        }

        /**
         * Solve the problem
         */
        void solve() {
            while (BaseSolver<FT>::mBag.size() && !BaseSolver<FT>::mStopper(*this)) {
                Sub<FT> sub = BaseSolver<FT>::mBag.getSub();
                std::vector<std::shared_ptr <NUC::Cut <double> > > cv;
                BaseSolver<FT>::mCutFact.getCuts(sub.mBox, cv);
                std::vector< snowgoose::Box<FT> > bv;
                bv.push_back(sub.mBox);
                BaseSolver<FT>::mCutApp.applyCuts(cv, bv);
                BaseSolver<FT>::mDecomp.split(bv);
                std::vector<Sub<FT>> sv;
                for (auto bx : bv) {
                    Sub<FT> s(IdGen::GetId(), sub.mLayer + 1, sub.mScore, bx);
                    eval(s);
                    BaseSolver<FT>::mBag.putSub(s);
                    sv.push_back(s);
                }
                BaseSolver<FT>::mBag.arrange(sv);
            }
        }
    };
}

#endif /* TREEWATCHSOLVER_HPP */

