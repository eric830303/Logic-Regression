//
//  Cube.hpp
//  CAD Contest Pjt
//
//  Created by TienHungTseng on 2019/6/12.
//  Copyright © 2019 Eric Tseng. All rights reserved.
//

#ifndef Cube_hpp
#define Cube_hpp

#include <stdio.h>
#include "Framework.hpp"
#include <set>
class Cube;

using namespace std;

//----------- Input Varariables ----------------------------------//
class Var_in
{
protected:
    //string _s_symbol;
    bool _b_value;
    pair<bool,bool> _pr_code;
public:
    void set_bvalue( bool b ){ this->_b_value = b; }
    bool get_bvalue( ){ return this->_b_value; }
    
    friend class framework;
    friend class Cube;
};

//----------- Output Varariables ----------------------------------//
class Var_out
{
protected:
    set <Cube*> s_cube_on;
    set <Cube*> s_cube_off;
private:
    friend class framework;
    friend class Cube;
};



class Cube
{
protected:
    vector <Var_in*>    _v_Var_in;
    //vector <Var_out*>   _v_Var_out;
public:
    int _i_weight = 0;//Used while expanding
    bool expanded = false;
    friend class Var;
    friend class framework;
    
};



#endif /* Cube_hpp */
