/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lipsupp.hpp
 * Author: Mikhail Posypkin <mposypkin at gmail.com>
 *
 * Created on 27 апреля 2016 г., 15:14
 */

#ifndef LIPSUPP_HPP
#define LIPSUPP_HPP

#include <box/box.hpp>

namespace NUC {

    /**
     * Supplies Lipzshitzian constants for a function
     */
    template <class FT> class LipSupp {
    public:
        /**
         * Retrieve Lipschitzian constants for a function
         * @param box the source box
         * @return the Lipschitzian constant
         */
        virtual FT getLipConst(const snowgoose::Box<FT>& box) const = 0;

    };

}



#endif /* LIPSUPP_HPP */

