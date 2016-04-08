/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lipgradfact.hpp
 * Author: Mikhail Posypkin <mposypkin at gmail.com>
 *
 * Created on 7 апреля 2016 г., 16:52
 */

#ifndef LIPGRADFACT_HPP
#define LIPGRADFACT_HPP

#include <functor.hpp>
#include <box/box.hpp>
#include <box/boxutils.hpp>
#include <cutfact/common/cutfactory.hpp>
#include <common/smartptr.hpp>
#include <cuts/totalcut.hpp>
#include "lpzgradsupp.hpp"

namespace NUC {

    /**
     * Cut factory based on Lipschitzian gradients
     */
    template <class FT> class LipGradCutFactory : public CutFactory <FT> {
    public:

        /**
         * Constructor 
         * @param supp the reference to the supplier
         * @param f reference to the functor
         * @param box problem bounding box
         * @param delta tolerance to distinguish grad from 0
         */
        LipGradCutFactory(COMPI::Functor<FT>& f, const snowgoose::Box<FT>& box, LpzGradSupp<FT>& supp, FT delta = 1e-8) : mF(f), mBox(box), mGradSupp(supp), mDelta(delta) {
            const int n = box.mDim;
            mX.alloc(n);
            mG.alloc(n);
            mLG.alloc(n);
        }

        void getCuts(const snowgoose::Box<FT>& box, std::vector<std::shared_ptr <Cut <FT> > >& v) const {
            const int n = mBox.mDim;

            snowgoose::BoxUtils::getCenter(box, (FT*) mX);
            FT r = snowgoose::BoxUtils::radius(box);
            mF.grad(mX, mG);
            mGradSupp.getLpzConst(box, mLG);
            bool totcat = false;
            for (int i = 0; i < n; i++) {
                FT lb = mG[i] - r * mLG[i];
                FT ub = mG[i] + r * mLG[i];
                if (lb > mDelta) {
                    totcat = true;
                } else if (ub < -mDelta) {
                    totcat = true;
                }
                if (totcat) {
                    TotalCut<FT> *tc = new TotalCut <FT> (box);
                    std::shared_ptr< Cut<FT> > pc(tc);
                    v.push_back(pc);
                }
            }
        }

        COMPI::Functor<FT>& mF;
        const snowgoose::Box<FT>& mBox;
        LpzGradSupp<FT>& mGradSupp;
        snowgoose::SmartArrayPtr<FT> mX;
        snowgoose::SmartArrayPtr<FT> mG;
        snowgoose::SmartArrayPtr<FT> mLG;
        FT mDelta;
    };
}

#endif /* LIPGRADFACT_HPP */

