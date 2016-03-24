/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   solver.hpp
 * Author: mikhail
 *
 * Created on 21 марта 2016 г., 10:46
 */

#ifndef BASESOLVER_HPP
#define BASESOLVER_HPP

#include <bags/subbag.hpp>
#include <decomp/decomp.hpp>
#include <cutfact/common/cutfactory.hpp>

namespace NUC {

    /**
     * Non-uniform coverings basice solver
     */
    template <class FT> class BaseSolver {
    public:

       BaseSolver (SubBag<FT>& bag, Decomp<FT>& decomp, CutFactory<FT>& cutfact) : 
        mBag(bag), mDecomp(decomp), mCutFact(cutfact) 
       {           
       }
       
        
        
    private:
        SubBag<FT>& mBag;
        Decomp<FT>& mDecomp;
        CutFactory<FT>& mCutFact;
    };

}

#endif /* BASESOLVER_HPP */

