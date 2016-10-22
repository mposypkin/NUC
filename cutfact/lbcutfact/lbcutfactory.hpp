/* 
 * File:   lbcutfactory.hpp
 * Author: medved
 *
 * Created on March 12, 2016, 6:56 PM
 */

#ifndef LBCUTFACTORY_HPP
#define LBCUTFACTORY_HPP

#include <cuts/totalcut.hpp>
#include <cutfact/common/cutfactory.hpp>
#include "boundsupp.hpp"

namespace NUC {

    /**
     * Cut factory base on objective lower bounds
     */
    template <class FT> class LBCutFactory : public CutFactory <FT> {
    public:

        /**
         * Constructor
         * @param eps tolearance
         * @param ubs upper bound supplier
         * @param lbs lowe bound supplier
         */
        LBCutFactory(FT eps, BoundSupplier<double>& ubs, BoundSupplier<double>& lbs) :
        mEps(eps), mUBSupp(ubs), mLBSupp(lbs) {
        }

        void getCuts(const snowgoose::Box<FT>& box, std::vector<std::shared_ptr <Cut <FT> > > &v) const {
            FT ub = mUBSupp.getBound(box);
            FT lb = mLBSupp.getBound(box);
            if (lb > ub - mEps) {
                // TotalCut<FT> *tc = new TotalCut <FT> (box);
                // std::shared_ptr< Cut<FT> > pc(tc);
                std::shared_ptr< Cut<FT> > pc = std::make_shared< TotalCut<FT> >(box);
                v.push_back(pc);
            }
        }

    private:
        FT mEps;
        BoundSupplier<double>& mUBSupp;
        BoundSupplier<double>& mLBSupp;
    };

}

#endif /* LBCUTFACTORY_HPP */

