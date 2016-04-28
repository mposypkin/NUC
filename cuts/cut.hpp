/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cut.hpp
 * Author: mikhail
 *
 * Created on 10 марта 2016 г., 13:25
 */

#ifndef CUT_HPP
#define CUT_HPP

#include <string>
#include <box/box.hpp>
#include "cuttypes.hpp"

namespace NUC {

    /**
     * Generic abstract class for storing cuts
     */
    template <class FT> class Cut {
    public:

        CutTypes getType() const {
            return mType;
        }
        
        const snowgoose::Box<FT>& getBox() const {
            return mBox;
        }

        /**
         * Get description
         * @return description
         */
        virtual std::string toString () const {
            return "Unnamed cut";
        }
        
    protected:

        /**
         * Constructor
         * @param type cut's type
         * @param mBox a box where the cut is valid
         */
        Cut(CutTypes type, const snowgoose::Box<FT>& box)
        : mType(type), mBox(box) {
        }

        /**
         * Cut's type
         */
        CutTypes mType;

        /**
         * A box where the cut is valid
         */
        const snowgoose::Box<FT> mBox;

    };

}

#endif /* CUT_HPP */

