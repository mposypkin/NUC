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

#ifndef SAVEBOXCUT_HPP
#define SAVEBOXCUT_HPP

#include <vector>

#include "cut.hpp"

namespace NUC {

    /**
     * The cut that retains a list of boxes
     */
    template <class FT> class SaveBoxCut : public Cut <FT> {
        public:
            
        SaveBoxCut(const snowgoose::Box<FT>& box) :
        Cut <FT> (CutTypes::SaveBox, box) {

        }

        std::string about() const {
            return "Save box cut\n";
        }
        
        /**
         * Retrieve the list of boxes
         * @return list of boxes
         */
        std::vector< snowgoose::Box<FT> >& getBoxes() {
            return mBoxes;
        }
        
        private:
            
            std::vector< snowgoose::Box<FT> > mBoxes;
    };

}
#endif /* SAVEBOXCUT_HPP */

