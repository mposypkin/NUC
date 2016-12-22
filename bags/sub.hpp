/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sub.hpp
 * Author: mikhail
 *
 * Created on 18 марта 2016 г., 14:46
 */

#ifndef SUB_HPP
#define SUB_HPP

#include <box/box.hpp>

namespace NUC {
    
    /**
     * Class for subproblems
     */
    template <class FT> class Sub {        
        public: 
        /**
         * Constructor 
         * @param layer number of the subproblem's layer
         * @param score the subproblem's score
         * @param box the subproblem's box
         */
        Sub(long long int layer, FT score, const snowgoose::Box<FT>& box) : mId(0), mIdEnd(0), mLayer(layer), mScore(score), mBox(box) {            
        }
        
        /**
         * Constructor 
         * @param subproblem's id
         * @param layer number of the subproblem's layer
         * @param score the subproblem's score
         * @param box the subproblem's box
         */
        Sub(int id, long long int layer, FT score, const snowgoose::Box<FT>& box) : mId(id), mIdEnd(0), mLayer(layer), mScore(score), mBox(box) {            
        }
        
        /**
         * The subproblem's layer in the B&B tree
         */
        long long int mLayer;
        
        /**
         * The subproblem's score - the lower the better
         */
        FT mScore;
        
        /**
         * The subproblem's ID. 
         */
        int mId;
        
                /**
         * Death ID of subproblem . 
         */
        int mIdEnd;
        
        /**
         * Subproblem's box
         */
        const snowgoose::Box<FT> mBox;
    };
}

#endif /* SUB_HPP */

