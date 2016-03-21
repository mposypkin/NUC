/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   decomp.hpp
 * Author: mikhail
 *
 * Created on 21 марта 2016 г., 11:07
 */

#ifndef DECOMP_HPP
#define DECOMP_HPP

#include <box/box.hpp>

namespace NUC {
    
    /**
     * Common interface to decomposers (split 
     */
    template <class FT> class Decomp {
        public:
            
            /**
             * Modify (usually split) boxes in a list
             */
            virtual void split(std::vector<snowgoose::Box<class FT>>& boxes) = 0;
    };
}

#endif /* DECOMP_HPP */

