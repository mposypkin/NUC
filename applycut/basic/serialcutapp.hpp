/* 
 * File:   serialcutapp.hpp
 * Author: medved
 *
 * Created on March 16, 2016, 3:14 PM
 */

#ifndef SERIALCUTAPP_HPP
#define	SERIALCUTAPP_HPP

#include <common/sgerrcheck.hpp>
#include <box/boxutils.hpp>
#include <cuts/cuttypes.hpp>
#include <applycut/common/cutapplicator.hpp>

namespace NUC {
    
    /**
     * Serial cut applicator: applies cuts one by one
     */
    template <class FT> class SerialCutApplicator : public CutApplicator <FT> {
        public:

            void applyCuts(const std::vector<std::shared_ptr <Cut <FT> > >& cutv, std::vector<snowgoose::Box<FT>>& boxv) {
                for(auto icut : cutv) {
                    auto ibox = boxv.begin();
                    for(;ibox != boxv.end(); ) {
                        if(icut->getType() == CutTypes::Total) {
                            if(snowgoose::BoxUtils::isSubBox(icut->getBox(), *ibox)) {
                                ibox = boxv.erase(ibox);
                                continue;
                            }
                        } else {
                            SG_ERROR_REPORT("Unknow cut type");
                        }
                        ibox ++;
                    }
                }
            }
    };
    
}


#endif	/* SERIALCUTAPP_HPP */

