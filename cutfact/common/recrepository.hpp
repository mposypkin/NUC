/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   recrepository.hpp
 * Author: Mikhail Posypkin <mposypkin at gmail.com>
 *
 * Created on 28 апреля 2016 г., 11:44
 */

#ifndef RECREPOSITORY_HPP
#define RECREPOSITORY_HPP

#include <limits>

namespace NUC {

    /**
     * Repository for records
     */
    template <class FT> class RecRepository {

        public:
        /**
         * Constructor
         * @param n dimensionlaity
         * @param rv record value
         * @param rpoint record point
         */
        RecRepository(int n, FT rv = std::numeric_limits<FT>::max(), const FT* rpoint = nullptr)
        : mN(n), mRv(rv) {
            mRecPoint = new FT[n];
            for (int i = 0; i < n; i++) {
                if (rpoint != nullptr)
                    mRecPoint[i] = rpoint[i];
                else
                    mRecPoint[i] = 0;
            }
        }

        ~RecRepository() {
            delete [] mRecPoint;
        }

        /**
         * Retrieve record's value
         * @return record's value
         */
        FT getRecValue() const {
            return mRv;
        }

        /**
         * Retrieves the record point
         * @return record's point
         */
        FT* getRecPoint() const {
            return mRecPoint;
        }

        /**
         * Updates the record value if it is lower then the exiting one
         * @param newrv new recrod value
         * @param newpoint new record point
         */
        void updateRecord(FT newrv, const FT* newpoint) {
            if (newrv < mRv) 
                setRecord(newrv, newpoint);
        }

        /**
         * Forcefully sets the new record and new record value
         * even if the new one is worse that the previous
         * @param newrv new record value
         * @param newpoint new record point
         */
        void setRecord(FT newrv, const FT* newpoint) {
            mRv = newrv;
            for (int i = 0; i < mN; i++) {
                mRecPoint[i] = newpoint[i];
            }
        }


    private:

        int mN;
        FT mRv;
        FT* mRecPoint;
    };

}

#endif /* RECREPOSITORY_HPP */

