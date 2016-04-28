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
#include <sstream>
#include <box/boxutils.hpp>

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

        std::string toString() const {
            std::ostringstream os;
            os << "Save box cut with boxes ";
            for(auto box : mBoxes) {
                os << snowgoose::BoxUtils::toString(box);
            }
            return os.str();
        }
        
        /**
         * Retrieve the list of boxes
         * @return list of boxes
         */
        const std::vector< snowgoose::Box<FT> >& getBoxes() const {
            return mBoxes;
        }
        
        void pushBox(const snowgoose::Box<FT>& box) {
            mBoxes.push_back(box);
        }
        
        private:
            
            std::vector< snowgoose::Box<FT> > mBoxes;
    };

}
#endif /* SAVEBOXCUT_HPP */

