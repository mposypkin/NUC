/* 
 * File:   liphesssupp.hpp
 * Author: medved
 *
 * Created on April 10, 2016, 4:30 PM
 */

#ifndef LPZHESSSUPP_HPP
#define	LPZHESSSUPP_HPP


#include <box/box.hpp>

namespace NUC {

    /**
     * Supplies Lipzshitzian constants for gradient
     */
    template <class FT> class LpzHessSupp {
    public:
        /**
         * Retrieve Hessian constants for hessian components
         * @param box the source box
         * @param lpzv the vector of Hessian constants
         */
        virtual void getLpzConst(const snowgoose::Box<FT>& box, FT* lpzv) = 0;

    };

}
#endif	/* LPZHESSSUPP_HPP */

