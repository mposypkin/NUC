/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cuttypes.hpp
 * Author: mikhail
 *
 * Created on 10 марта 2016 г., 13:48
 */

#ifndef CUTTYPES_HPP
#define CUTTYPES_HPP

namespace NUC {
    
    /**
     * Class to store cut types
     */
    enum class CutTypes {        
        /**
         * Total cut, to cut the whole box
         */
        Total,
        
        /**
         * Cut half-space
         */
        Linear,

        /**
         * Cut out the internity of a ball
         */
        InnerBall,
        
        /**
         * Cut out the outer part of a ball (save the internity
         */
        OuterBall,
             
        /**
         * Cut the internity of a box
         */
        InnerBox,
        
        /**
         * Cut the outer part of box (save the internity)
         */
        OuterBox
    };

}

#endif /* CUTTYPES_HPP */

