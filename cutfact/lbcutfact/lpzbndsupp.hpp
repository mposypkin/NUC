/* 
 * File:   lpzbndsupp.hpp
 * Author: medved
 *
 * Created on March 14, 2016, 7:28 PM
 */

#ifndef LPZBNDSUPP_HPP
#define	LPZBNDSUPP_HPP

#include <box/boxutils.hpp>
#include <functor.hpp>
#include "boundsupp.hpp"

namespace NUC {

    /**
     * Lipschitzian lower bound supplier
     */
    template <class FT> class LpzBoundSupplier : public BoundSupplier <FT>{
    public:

        /**
         * Constructor
         * @param n problem dimension
         * @param lpz Lipschitzian constant
         * @param f Functor
         */
        LpzBoundSupplier(int n, FT lpz, COMPI::Functor<FT>& f) : mN(n), mL(lpz), mF(f) {
           mC = new FT[n] ;
        }
        
        ~LpzBoundSupplier() {
            delete[] mC;
        }
        
        /**
         * Set Lipschitzian constant
         * @param lpz Lipschitzian constant
         */
        void setLpz(FT lpz) {
            mL = lpz;
        }
        
        /**
         * Retrieve 
         * @param box to find the bound
         * @return bound
         */
        FT getBound(const snowgoose::Box<FT>& box) {
            FT r = snowgoose::BoxUtils::radius(box);            
            snowgoose::BoxUtils::getCenter(box, mC);
            FT v = mF.func(mC);
            FT lb = v - r * mL;            
            return lb;
        }

    private:
        FT mL;
        FT* mC;
        int mN;
        COMPI::Functor<FT>& mF;
    };



}

#endif	/* LPZBNDSUPP_HPP */

