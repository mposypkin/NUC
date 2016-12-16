/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   subbag.hpp
 * Author: mikhail
 *
 * Created on 18 марта 2016 г., 14:47
 */

#ifndef SUBBAG_HPP
#define SUBBAG_HPP

#include <functional>
#include "sub.hpp"

namespace NUC {
    
    /**
     * The abstract class for possible bags to store subproblems
     */
    template <class FT> class SubBag {
        public:
            
            /**
             * Put a subproblem to the bag
             * @param sub subproblem
             */
            virtual void putSub(Sub<FT>& sub) = 0;
            
            /**
             * Retrieve and remove one ('next') subproblem from the bag
             * @return subproblem
             */
            virtual Sub<FT> getSub() = 0;
            
            /**
             * Traverse the subproblems list and apply a function
             * @param f traversal function
             */
            virtual void traverse(std::function<void (const Sub<FT>&)> f) = 0;
            
            /**
             * Get size of a bag
             * @return size of a bag
             */
            virtual unsigned int size() const = 0;
            
            /**
             * arrange collection of subs
             */ 
            virtual void arrange(std::vector<Sub<FT>>& subs) const = 0;
            
    };
}

#endif /* SUBBAG_HPP */

