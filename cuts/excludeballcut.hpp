/* 
 * File:   excludeballcut.hpp
 * Author: medved
 *
 * Created on April 10, 2016, 12:01 PM
 */

#ifndef EXCLUDEBALLCUT_HPP
#define	EXCLUDEBALLCUT_HPP

#include "cut.hpp"

namespace NUC {

    /**
     * The cut that eliminates the whole box
     */
    template <class FT> class ExcludeBallCut : public Cut <FT> {
    public:

        /**
         * Constructor 
         * @param box box for the cut
         * @param r ball's radius
         * @param cntr ball's center
         */
        ExcludeBallCut(const snowgoose::Box<FT>& box, FT r,  FT * const cntr) :
        Cut <FT> (CutTypes::ExcludeBall, box), mR(r), mC(new FT[box.mDim]) {
            const int n = box.mDim;
            for (int i = 0; i < n; i++) {
                mC[i] = cntr[i];
            }
        }

        ~ExcludeBallCut() {
            delete[] mC;
        }

        std::string about() const {
            return "Exclude ball cut\n";
        }

         FT * const mC;
         const FT mR;
    };

}

#endif	/* EXCLUDEBALLCUT_HPP */

