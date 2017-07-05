/* 
 * File:   serialcutapp.hpp
 * Author: medved
 *
 * Created on March 16, 2016, 3:14 PM
 */

#ifndef SERIALCUTAPP_HPP
#define SERIALCUTAPP_HPP

#include <common/sgerrcheck.hpp>
#include <common/utilmacro.hpp>
#include <box/boxutils.hpp>
#include <cuts/cuttypes.hpp>
#include <cuts/savebox.hpp>
#include <cuts/excludeballcut.hpp>
#include <applycut/common/cutapplicator.hpp>

namespace NUC {

    /**
     * Serial cut applicator: applies cuts one by one
     */
    template <class FT> class SerialCutApplicator : public CutApplicator <FT> {
    public:

        void applyCuts(const std::vector<std::shared_ptr <Cut <FT> > >& cutv, std::vector<snowgoose::Box<FT >> &boxv) {
            std::vector < snowgoose::Box < FT >> resbox;
            for (auto icut : cutv) {
                typename std::vector < snowgoose::Box < FT >>::iterator ibox = boxv.begin();
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
                    } else if (icut->getType() == CutTypes::ExcludeBall) {
                        const ExcludeBallCut<FT>* ebc = dynamic_cast<const ExcludeBallCut<FT>*> (icut.get());
                        snowgoose::Box<FT> bx(*ibox);
                        ibox = boxv.erase(ibox);
                        applyExcludeBallCut(*ebc, bx, resbox);
                        continue;
                    } else {
                        SG_ERROR_REPORT("Unknow cut type");
                    }
                    ibox++;
                }
            }
            for (auto bb : resbox)
                boxv.push_back(bb);
        }

    private:

        void applySaveBox(const SaveBoxCut<FT>& sbc,
                const snowgoose::Box<FT>& box,
                std::vector<snowgoose::Box<FT >> &boxv) {
            for (auto bx : sbc.getBoxes()) {
                int n = bx.mDim;
                snowgoose::Box<FT> nb(n);
                //snowgoose::BoxUtils::copy(bx, nb);
                snowgoose::BoxUtils::intersect(box, bx, nb);
                boxv.push_back(nb);
            }
        }

        void applyExcludeBallCut(const ExcludeBallCut<FT>& ebc,
                const snowgoose::Box<FT>& box,
                std::vector<snowgoose::Box<FT >> &boxv) {
            int n = box.mDim;
            FT lmax = 0, amin = 0, bmax = 0;
            int imax;
            /* Search for best dimension to divide */
            FT rq = ebc.mR * ebc.mR;
            bool total = false;
            for (int i = 0; i < n; i++) {
                FT q = 0;
                for (int j = 0; j < n; j++) {
                    if (j != i) {
                        FT p = SGMAX(SGABS(box.mA[j] - ebc.mC[j]), SGABS(box.mB[j] - ebc.mC[j]));
                        q += p * p;
                    }
                }
                if (q < rq) {
                    FT h = sqrt(rq - q);
                    FT a = ebc.mC[i] - h;
                    FT b = ebc.mC[i] + h;

                    /** Compute intersection **/
                    FT an = SGMAX(a, box.mA[i]);
                    FT bn = SGMIN(b, box.mB[i]);

                    /** Check intersection **/
                    if (an > bn)
                        continue;

                    /** Check total elimination **/
                    if ((a < box.mA[i]) && (b > box.mB[i])) {
                        total = true;
                        break;
                    }

                    FT l = (bn - an) / (box.mB[i] - box.mA[i]);
                    if (l > lmax) {
                        imax = i;
                        lmax = l;
                        amin = a;
                        bmax = b;
                    }
                }
            }

            if (!total) {
                if (lmax > 0) {
                    if (amin >= box.mA[imax]) {
                        snowgoose::Box<FT> b(n);
                        snowgoose::BoxUtils::copy(box, b);
                        b.mB[imax] = SGMIN(amin, b.mB[imax]);
                        boxv.push_back(b);
                    }
                    if (bmax <= box.mB[imax]) {
                        snowgoose::Box<FT> b(n);
                        snowgoose::BoxUtils::copy(box, b);
                        b.mA[imax] = SGMAX(bmax, b.mA[imax]);
                        boxv.push_back(b);
                    }
                } else {
                    boxv.push_back(box);
                }
            }
        }
    };

}


#endif /* SERIALCUTAPP_HPP */

