/* 
 * File:   lbcutfactory.hpp
 * Author: medved
 *
 * Created on March 12, 2016, 6:56 PM
 */

#ifndef LBCUTFACTORY_HPP
#define	LBCUTFACTORY_HPP

#include <cuts/totalcut.hpp>
#include <cutfact/common/cutfactory.hpp>

namespace NUC {
    
    /**
     * Cut factory base on objective lower bounds
     */
    template <class FT> class LBCutFactory : public CutFactory <FT> {
        public:
            
        void getCuts(const snowgoose::Box<FT>& box, std::vector<std::shared_ptr <Cut <FT> > > &v) const {
            TotalCut<FT> *tc = new TotalCut <FT> (box);
            std::shared_ptr< Cut<FT> > pc(tc);
            v.push_back(pc);
        }
    };
    
}

#endif	/* LBCUTFACTORY_HPP */

