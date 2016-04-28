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
#include <cuts/savebox.hpp>
#include <cuts/excludeballcut.hpp>
#include "lpzgradsupp.hpp"

namespace NUC {

    /**
     * Cut factory based on Lipschitzian gradients
     */
    template <class FT> class LipGradCutFactory : public CutFactory <FT> {
    public:

        struct Options {
            static const unsigned int EXTRACT_BALL = 1;
        };

        /**
         * Constructor 
         * @param supp the reference to the supplier
         * @param f reference to the functor
         * @param box problem bounding box
         * @param delta tolerance to distinguish grad from 0
         */
        LipGradCutFactory(COMPI::Functor<FT>& f, const snowgoose::Box<FT>& box, LpzGradSupp<FT>& supp, FT delta = 1e-8) :
        mF(f), mBox(box), mGradSupp(supp), mDelta(delta), mOptions(Options::EXTRACT_BALL) {
            const int n = box.mDim;
            mX.alloc(n);
            mG.alloc(n);
            mLG.alloc(n);
        }

        void getCuts(const snowgoose::Box<FT>& box, std::vector<std::shared_ptr <Cut <FT> > >& v) const {
            const int n = mBox.mDim;
            snowgoose::Box<FT> nbox(n);
            snowgoose::BoxUtils::copy(box, nbox);
            FT r;
            auto comp = [&] () {
                snowgoose::BoxUtils::getCenter(nbox, (FT*) mX);
                r = snowgoose::BoxUtils::radius(nbox);
                mF.grad(mX, mG);
                mGradSupp.getLpzConst(box, mLG);
            };
            comp();
            bool totcut = false;
            bool savecut = false;
            for (int i = 0; i < n; i++) {
                FT lb = mG[i] - r * mLG[i];
                FT ub = mG[i] + r * mLG[i];
                if (lb >= mDelta) {
                    if (mBox.mA[i] == nbox.mA[i]) {
                        nbox.mB[i] = nbox.mA[i];
                        savecut = true;
                    } else
                        totcut = true;
                } else if (ub <= -mDelta) {
                    if (mBox.mB[i] == nbox.mB[i]) {
                        nbox.mA[i] = nbox.mB[i];
                        savecut = true;
                    } else
                        totcut = true;
                }

                if (totcut) {
                    auto tc = new TotalCut <FT> (box);
                    std::shared_ptr< Cut<FT> > pc(tc);
                    v.push_back(pc);
                    break;
                } else if (savecut) {
                    comp();
                }
            }
            if (savecut) {
                auto savebox = new NUC::SaveBoxCut<double>(box);
                savebox->pushBox(nbox);
                std::shared_ptr< NUC::Cut<FT> > pc(savebox);
                v.push_back(pc);
            } else if (mOptions & Options::EXTRACT_BALL) {
                r = 0;
                for (int i = 0; i < n; i++) {
                    FT nr = 0;
                    if (mLG[i] == 0)
                        continue;
                    if (mG[i] >= mDelta) {
                        nr = (mG[i] - mDelta) / mLG[i];
                    } else if (mG[i] <= -mDelta) {
                        nr = -(mG[i] + mDelta) / mLG[i];
                    }
                    if (nr > r)
                        r = nr;
                }
                // std::cout << "r = " << r << "\n";

                if (r > 0) {
                    auto exballcut = new NUC::ExcludeBallCut<FT>(nbox, r, mX);
                    std::shared_ptr< NUC::Cut<FT> > pc(exballcut);
                    v.push_back(pc);
                }
            }

        }

        unsigned int& getOptions() {
            return mOptions;
        }

    private:

        unsigned int mOptions;
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

