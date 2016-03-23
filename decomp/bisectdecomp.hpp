/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bisectdecomposer.hpp
 * Author: mikhail
 *
 * Created on 23 марта 2016 г., 11:55
 */

#ifndef BISECTDECOMPOSER_HPP
#define BISECTDECOMPOSER_HPP

#include <box/boxutils.hpp>
#include "decomp.hpp"

namespace NUC {

    /**
     * Standard decomposer
     */
    template <class FT> class BisectDecomp : public Decomp<FT> {
    public:

        /**
         * Modify (usually split) boxes in a list
         */
        void split(std::vector< snowgoose::Box<FT> > &boxes) const {
            if(boxes.size() == 1) {
                snowgoose::Box<FT> sbox = boxes.at(0);                
                int n = sbox.mDim;      
                snowgoose::Box<FT> box1(n), box2(n);
                snowgoose::BoxUtils::divideByLongestEdge(sbox, box1, box2);
                boxes.pop_back();
                boxes.push_back(box1);
                boxes.push_back(box2);                
            }
        }
    };

}

#endif /* BISECTDECOMPOSER_HPP */

