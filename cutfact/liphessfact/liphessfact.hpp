/* 
 * File:   liphessfact.hpp
 * Author: medved
 *
 * Created on April 10, 2016, 4:45 PM
 */

#ifndef LIPHESSFACT_HPP
#define LIPHESSFACT_HPP

#include <functor.hpp>
#include <box/box.hpp>
#include <box/boxutils.hpp>
#include <cutfact/common/cutfactory.hpp>
#include <common/smartptr.hpp>
#include <cuts/totalcut.hpp>
#include <cuts/savebox.hpp>
#include <cuts/excludeballcut.hpp>
#include "lpzhesssupp.hpp"

namespace NUC {

    /**
     * Cut factory based on Lipschitzian hessian
     */
    template <class FT> class LipHessCutFactory : public CutFactory <FT> {
    public:

        /**
         * Constructor 
         * @param supp the reference to the supplier
         * @param f reference to the functor
         * @param box problem bounding box
         * @param delta tolerance to distinguish grad from 0
         */
        LipHessCutFactory(COMPI::Functor<FT>& f, const snowgoose::Box<FT>& box, LpzHessSupp<FT>& supp, FT delta = 1e-8) : mF(f), mBox(box), mHessSupp(supp), mDelta(delta) {
            const int n = box.mDim;
            const int nn = n * n;
            mX.alloc(n);
            mH.alloc(nn);
            mLH.alloc(nn);
        }

        void getCuts(const snowgoose::Box<FT>& box, std::vector<std::shared_ptr <Cut <FT> > >& v) const {
            const int n = mBox.mDim;
            snowgoose::Box<FT> nbox(n);
            snowgoose::BoxUtils::copy(box, nbox);
            FT r;
            auto comp = [&] () {
                snowgoose::BoxUtils::getCenter(nbox, (FT*) mX);
                r = snowgoose::BoxUtils::radius(nbox);
                mF.hess(mX, mH);
                mHessSupp.getLpzConst(box, mLH);
            };
            comp();
            std::vector< snowgoose::Box<FT> > boxv;
            boxv.push_back(nbox);
            bool savecut = false;
            for (int i = 0; i < n; i++) {
                int ii = i + i * n;
                FT lb = mH[ii] - r * mLH[ii];
                FT ub = mH[ii] + r * mLH[ii];
                if (ub < -mDelta) {
                    savecut = true;
                    std::vector< snowgoose::Box<FT> > nbx;
                    while (!boxv.empty()) {
                        snowgoose::Box<FT> bx = boxv.back();
                        boxv.pop_back();
                        if (bx.mA[i] == mBox.mA[i]) {
                            snowgoose::Box<FT> bxa(n);
                            snowgoose::BoxUtils::copy(bx, bxa);
                            bxa.mB[i] = bxa.mA[i];
                            nbx.push_back(bxa);
                        } 
                        if (bx.mB[i] == mBox.mB[i]) {
                            snowgoose::Box<FT> bxb(n);
                            snowgoose::BoxUtils::copy(bx, bxb);
                            bxb.mA[i] = bxb.mB[i];
                            nbx.push_back(bxb);
                        }
                    }
                    boxv = nbx;
                } else {

                }
                if (boxv.empty()) {
                    auto tc = new TotalCut <FT> (box);
                    std::shared_ptr< Cut<FT> > pc(tc);
                    v.push_back(pc);
                    break;
                }
            }

            if (savecut) {
                auto savebox = new NUC::SaveBoxCut<double>(box);
                for (auto b : boxv) {
                    savebox->pushBox(b);
                }
                std::shared_ptr< NUC::Cut<FT> > pc(savebox);
                v.push_back(pc);
            }

            /*
            r = 0;
            for (int i = 0; i < n; i++) {
                FT nr = 0;
                if (mLH[i] == 0)
                    continue;
                if (mH[i] >= mDelta) {
                    nr = (mH[i] - mDelta) / mLH[i];
                } else if (mH[i] <= -mDelta) {
                    nr = -(mH[i] + mDelta) / mLH[i];
                }
                if (nr > r)
                    r = nr;
            }
            std::cout << "r = " << r << "\n";
             */
#if 0            
            if (r > 0) {
                auto exballcut = new NUC::ExcludeBallCut<FT>(nbox, r, mX);
                std::shared_ptr< NUC::Cut<FT> > pc(exballcut);
                v.push_back(pc);
            }
#endif            
        }

        COMPI::Functor<FT>& mF;
        const snowgoose::Box<FT>& mBox;
        LpzHessSupp<FT>& mHessSupp;
        snowgoose::SmartArrayPtr<FT> mX;
        snowgoose::SmartArrayPtr<FT> mH;
        snowgoose::SmartArrayPtr<FT> mLH;
        FT mDelta;
    };
}


#endif /* LIPHESSFACT_HPP */

