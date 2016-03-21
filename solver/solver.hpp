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

#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <bags/subbag.hpp>
namespace NUC {

    /**
     * Non-uniform coverings solver
     */
    template <class FT> class Solver {
    public:

       Solver (SubBag<FT>& bag) : mBag(bag) 
       {           
       }
       
    private:
        SubBag<FT>& mBag;
    };

}

#endif /* SOLVER_HPP */

