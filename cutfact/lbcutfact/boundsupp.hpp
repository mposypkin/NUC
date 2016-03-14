/* 
 * File:   boundsupp.hpp
 * Author: medved
 *
 * Created on March 14, 2016, 6:39 PM
 */

#ifndef BOUNDSUPP_HPP
#define	BOUNDSUPP_HPP

#include <box/box.hpp>

namespace NUC {
    
    /**
     * Abstract class for lower or upper bound supplier
     */
    template <class FT> class BoundSupplier {
        public:
            /**
             * Retrieve 
             * @param box to find the bound
             * @return bound
             */
            virtual FT getBound(const snowgoose::Box<FT>& box) = 0;
    };
    
}

#endif	/* BOUNDSUPP_HPP */

