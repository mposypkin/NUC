/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   recordsupp.hpp
 * Author: mikhail
 *
 * Created on 15 марта 2016 г., 10:54
 */

#ifndef RECORDSUPP_HPP
#define RECORDSUPP_HPP

#include "boundsupp.hpp"

namespace NUC {

    /**
     * Record storage and upper bound supplier
     */
    template <class FT> class RecordSupplier : public BoundSupplier <FT> {
    public:

        /**
         * Constructor
         * @param rv initial record value
         */
        RecordSupplier(FT rv) : mRv(rv), mX(nullptr) {
        }

        /**
         * Set new record value
         * @param rv new record value
         */
        void setRv(FT rv) {
            mRv = rv;
        }

        /**
         * Update record value
         * @param rv new record value
         */
        void updateRv(FT rv) {
           if (rv < mRv)
                mRv = rv;
        }
        
        /**
         * Update record value
         * @param rv new record value
         * @param x point for new record value
         */
        void updateRv(FT rv, FT * x) {
            if (rv < mRv)
            {
                mRv = rv;
                mX=x;
            }
        }

        /**
         * Retrieve 
         * @param box to find the bound
         * @return bound
         */
        FT getBound(const snowgoose::Box<FT>& box) {
            return mRv;
        }
        
        /**
         * Retrieve 
         * @return record point
         */
        FT* getPoint() {
            return mX;
        }

    private:
        FT mRv;
        FT *mX;
    };
}

#endif /* RECORDSUPP_HPP */

