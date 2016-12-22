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
public:
    static IdGen& Instance()
    {
            static IdGen idGen;
            return idGen;
    }
    int Id()
    {
       return curr_id++;
    }

    IdGen(const IdGen& root) = delete;
    IdGen& operator=(const IdGen&) = delete;

private:        
    IdGen() : curr_id(1) {};    
    int curr_id;
};

class IdGenEnd
{
public:
    static IdGenEnd& Instance()
    {
            static IdGenEnd idGen;
            return idGen;
    }
    int Id()
    {
       return curr_id++;
    }

    IdGenEnd(const IdGenEnd& root) = delete;
    IdGenEnd& operator=(const IdGenEnd&) = delete;

private:        
    IdGenEnd() : curr_id(1) {};    
    int curr_id;
};

}

#endif /* IDGEN_HPP */

