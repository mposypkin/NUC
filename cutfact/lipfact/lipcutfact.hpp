/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lipfact.hpp
 * Author: Mikhail Posypkin <mposypkin at gmail.com>
 *
 * Created on 27 апреля 2016 г., 15:27
 */

#ifndef LIPFACT_HPP
#define LIPFACT_HPP

#include <functor.hpp>
#include <box/box.hpp>
#include <box/boxutils.hpp>
#include <cutfact/common/cutfactory.hpp>
#include <common/smartptr.hpp>
#include <cuts/totalcut.hpp>
#include <cuts/savebox.hpp>
#include <cuts/excludeballcut.hpp>
#include <cutfact/common/recrepository.hpp>
#include "lipsupp.hpp"

namespace NUC {

    /**
     * Cut factory based on Lipschitzian gradients
     */
    template <class FT> class LipCutFactory : public CutFactory <FT> {
    public:

        struct Options {
            /**
             * Extract box
             */
            static const unsigned int EXTRACT_BALL = 1;
        };

        /**
         * Constructor 
         * @param supp the reference to the supplier
         * @param f reference to the functor
         * @param box problem bounding box
         * @param supp lipschitzian const supplier
         * @param rr Record repository
         * @param delta tolerance to distinguish grad from 0
         */
        LipCutFactory(COMPI::Functor<FT>& f, const snowgoose::Box<FT>& box, const LipSupp<FT>& supp, RecRepository<FT>& rr, FT delta = 1e-8) :
        mF(f), mBox(box), mLipSupp(supp), mRecRepository(rr), mDelta(delta), mOptions(Options::EXTRACT_BALL) {
            const int n = box.mDim;
            mX.alloc(n);
        }

        void getCuts(const snowgoose::Box<FT>& box, std::vector<std::shared_ptr <Cut <FT> > >& v) const {
            const int n = mBox.mDim;
            const FT lc = mLipSupp.getLipConst(box);
            snowgoose::BoxUtils::getCenter(box, (FT*) mX);
            const FT r = snowgoose::BoxUtils::radius(box);
            const FT fv = mF.func(mX);
            mRecRepository.updateRecord(fv, mX);
            const FT lb = fv - lc * r;
            if (lb >= (mRecRepository.getRecValue() - mDelta)) {
                auto tc = new TotalCut <FT> (box);
                std::shared_ptr< Cut<FT> > pc(tc);
                v.push_back(pc);
            } else if (mOptions & Options::EXTRACT_BALL) {
                if (lc > 0) {
                    FT rad = (fv - mRecRepository.getRecValue() + mDelta) / lc;
                    if (rad > 0) {
                        auto exballcut = new NUC::ExcludeBallCut<FT>(box, rad, mX);
                        std::shared_ptr< NUC::Cut<FT> > pc(exballcut);
                        v.push_back(pc);
                    }
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
        const LipSupp<FT>& mLipSupp;
        RecRepository<FT>& mRecRepository;
        snowgoose::SmartArrayPtr<FT> mX;
        FT mDelta;
    };
}

#endif /* LIPFACT_HPP */

