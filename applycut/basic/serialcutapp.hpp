/* 
 * File:   serialcutapp.hpp
 * Author: medved
 *
 * Created on March 16, 2016, 3:14 PM
 */

#ifndef SERIALCUTAPP_HPP
#define SERIALCUTAPP_HPP

#include <common/sgerrcheck.hpp>
#include <box/boxutils.hpp>
#include <cuts/cuttypes.hpp>
#include <cuts/savebox.hpp>
#include <applycut/common/cutapplicator.hpp>

namespace NUC {

    /**
     * Serial cut applicator: applies cuts one by one
     */
    template <class FT> class SerialCutApplicator : public CutApplicator <FT> {
    public:

        void applyCuts(const std::vector<std::shared_ptr <Cut <FT> > >& cutv, std::vector<snowgoose::Box<FT>>&boxv) {
            std::vector<snowgoose::Box < FT>> resbox;
            for (auto icut : cutv) {
                auto ibox = boxv.begin();
                for (; ibox != boxv.end();) {
                    if (icut->getType() == CutTypes::Total) {
                        if (snowgoose::BoxUtils::isSubBox(icut->getBox(), *ibox)) {
                            ibox = boxv.erase(ibox);
                            continue;
                        }
                    } else if (icut->getType() == CutTypes::SaveBox) {
                        const SaveBoxCut<FT>* sbc = dynamic_cast<const SaveBoxCut<FT>*> (icut.get());
                        snowgoose::Box<FT> bx(*ibox);
                        ibox = boxv.erase(ibox);
                        applySaveBox(*sbc, bx, resbox);
                        continue;
                        //for(auto bx : )
                    } else {
                        SG_ERROR_REPORT("Unknow cut type");
                    }
                    ibox++;
                }
            }
            boxv.insert(boxv.end(), resbox.begin(), resbox.end());
        }

    private:

        void applySaveBox(const SaveBoxCut<FT>& sbc,
                const snowgoose::Box<FT>& box,
                std::vector<snowgoose::Box<FT>>&boxv) {
            for (auto bx : sbc.getBoxes()) {
                int n = bx.mDim;
                snowgoose::Box<FT> nb(n);
                snowgoose::BoxUtils::copy(bx, nb);
                boxv.push_back(nb);
            }

        }
    };

}


#endif /* SERIALCUTAPP_HPP */

