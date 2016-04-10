/* 
 * File:   compcutfact.hpp
 * Author: medved
 *
 * Created on April 9, 2016, 10:33 AM
 */

#ifndef COMPCUTFACT_HPP
#define	COMPCUTFACT_HPP

#include <cutfact/common/cutfactory.hpp>
#include <vector>

namespace NUC {

    /**
     * Combines several cut factories
     */
    template <class FT> class CompositeCutFactory : public CutFactory <FT> {
    public:

        void getCuts(const snowgoose::Box<FT>& box, std::vector<std::shared_ptr <Cut <FT> > > &v) const {
            for(auto fact : mCF) {
                fact->getCuts(box, v);
            }
        }

        /**
         * Adds factory 
         * @param cf added factory
         */
        void addFactory(const CutFactory<FT>*   cf) {
            mCF.push_back(cf);
        }
    private:
        
        std::vector<const  CutFactory<FT>* >  mCF;
    };

}

#endif	/* COMPCUTFACT_HPP */

