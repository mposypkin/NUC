/* 
 * File:   lpzbndsupp.hpp
 * Author: medved
 *
 * Created on March 14, 2016, 7:28 PM
 */

#ifndef LPZBNDSUPP_HPP
#define	LPZBNDSUPP_HPP

#include <box/boxutils.hpp>
#include "boundsupp.hpp"

namespace NUC {

    /**
     * Lipschitzian lower bound supplier
     */
    template <class FT> class LpzBoundSupplier {
    public:

        /**
         * Constructor
         * @param lpz Lipschitzian constant
         */
        LpzBoundSupplier(FT lpz) : mLpz(lpz) {
            
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
            FT lb = v - r * mL;
            
        }

    private:
        FT mL;

    };



}

#endif	/* LPZBNDSUPP_HPP */

