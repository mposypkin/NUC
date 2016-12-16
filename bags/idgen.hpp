/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   idgen.hpp
 * Author: Alexander Usov
 *
 * Created on December 15, 2016, 7:25 PM
 */

#ifndef IDGEN_HPP
#define IDGEN_HPP

namespace NUC {
    /**
     * Class for generation unique subproblem's id
     */
    class IdGen
    {
       private:
       static int curr_id;

       public: 
       static int GetId()
       {
          return curr_id++;
       }
    };
}

#endif /* IDGEN_HPP */

