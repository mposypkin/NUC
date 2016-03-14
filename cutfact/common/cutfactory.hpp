/* 
 * File:   cutfactory.hpp
 * Author: medved
 *
 * Created on March 12, 2016, 6:19 PM
 */

#ifndef CUTFACTORY_HPP
#define	CUTFACTORY_HPP

#include <vector>
#include <memory>
#include <cuts/cut.hpp>
#include <box/box.hpp>

namespace NUC {
    
    /**
     * Abstract class for class factories
     */
    template <class FT> class CutFactory {
        public:
            /**
             * Retrieve cuts
             * @param box box to generate cuts for
             * @param v vector of cuts
             */
            virtual void getCuts(const snowgoose::Box<FT>& box, std::vector<std::shared_ptr <Cut <FT> > >& v) const = 0;
    };
    
}

#endif	/* CUTFACTORY_HPP */

