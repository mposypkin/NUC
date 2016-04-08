/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lpzgradsupp.hpp
 * Author: Mikhail Posypkin <mposypkin at gmail.com>
 *
 * Created on 7 апреля 2016 г., 16:42
 */

#ifndef LPZGRADSUPP_HPP
#define LPZGRADSUPP_HPP

#include <box/box.hpp>

namespace NUC {

    /**
     * Supplies Lipzshitzian constants for gradient
     */
    template <class FT> class LpzGradSupp {
    public:
        /**
         * Retrieve Lipschitzian constants for gradient components
         * @param box the source box
         * @param lpzv the vector of Lipschitzian constants
         */
        virtual void getLpzConst(const snowgoose::Box<FT>& box, FT* lpzv) = 0;

    };

}

#endif /* LPZGRADSUPP_HPP */

