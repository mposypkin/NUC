/* 
 * File:   cutapplicator.hpp
 * Author: medved
 *
 * Created on March 16, 2016, 2:36 PM
 */

#ifndef CUTAPPLICATOR_HPP
#define	CUTAPPLICATOR_HPP

#include <memory>
#include <box/box.hpp>
#include <cuts/cut.hpp>

namespace NUC {
    
    /**
     * Basic class for cut applicators
     */
    template <class FT> class CutApplicator {
        public:
            /**
             * Apply cuts to the boxes in a vector
             * @param cutv vector of cuts
             * @param boxv initial and resulting vector of boxes 
             */
            virtual void applyCuts(const std::vector<std::shared_ptr <Cut <FT> > >& cutv, std::vector<snowgoose::Box<FT>>& boxv) = 0;
    };
}

#endif	/* CUTAPPLICATOR_HPP */

