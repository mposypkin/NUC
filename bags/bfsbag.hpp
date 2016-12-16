/* 
 * File:   bfsbag.hpp
 * Author: medved
 *
 * Created on March 18, 2016, 3:29 PM
 */

#ifndef BFSBAG_HPP
#define	BFSBAG_HPP

#include <set>
#include <vector>
#include <algorithm>
#include "sub.hpp"
#include "subbag.hpp"

namespace NUC {
    


    /**
     * Best first search bag
     */
    template <class FT> class BFSBag : public SubBag <FT> {
    public:

        class Cmp {
        public:

            bool operator() (const Sub<FT>& s1, const Sub<FT>& s2) const {
                return (s1.mScore < s2.mScore);
            }
        };
        

        /**
         * Put a subproblem to the bag
         * @param sub subproblem
         */
        void putSub(Sub<FT>& sub) {
            mSubs.insert(sub);
        }

        /**
         * Retrieve and remove one ('next') subproblem from the bag
         * @return subproblem
         */
        Sub<FT> getSub() {
            typename std::multiset< Sub <FT>, Cmp>::iterator i = mSubs.begin();
            Sub<FT> s = *i;
            mSubs.erase(i);
            return s;
        }

        /**
         * Traverse the subproblems list and apply a function
         * @param f traversal function
         */
        void traverse(std::function<void (const Sub<FT>&) > f) {
            auto it = mSubs.begin();
            for (; it != mSubs.end(); it++)
                f(*it);
        }

        /**
         * Get size of a bag
         * @return size of a bag
         */
        unsigned int size() const {
            return mSubs.size();
        }
        
        /**
        * arrange collection of subs
        */ 
        void arrange(std::vector<Sub<FT>>& subs) const {
            std::sort(subs.begin(), subs.end(), Cmp());
        }

    private:

        std::multiset< Sub <FT>, Cmp > mSubs;

    };
}

#endif	/* BFSBAG_HPP */

