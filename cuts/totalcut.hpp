/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   totalcut.hpp
 * Author: mikhail
 *
 * Created on 10 марта 2016 г., 13:45
 */

#ifndef TOTALCUT_HPP
#define TOTALCUT_HPP

#include "cut.hpp"

namespace NUC {

    /**
     * The cut that eliminates the whole box
     */
    template <class FT> class TotalCut : public Cut <FT> {
        public:
            
        TotalCut(const snowgoose::Box<FT>& box) :
        Cut <FT> (CutTypes::Total, box) {

        }

        std::string about() const {
            return "Total cut\n";
        }
    };

}
#endif /* TOTALCUT_HPP */

