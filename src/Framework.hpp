//
//  Framework.hpp
//  LogicRegression
//
//  Created by TienHungTseng on 2019/6/7.
//  Copyright © 2019 Eric Tseng. All rights reserved.
//

#ifndef Framework_hpp
#define Framework_hpp


//----------------- Library ----------------------------//
#include <stdio.h>
#include <string>
#include <vector>
#include "Cube.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <set>

using namespace std;

class Var;
class Cube;
//------------------ Main Class -----------------------//
class framework
{
//-----------------------------------------------------//
//            This is the top frameowrk
//-----------------------------------------------------//

private:
    string _io_info_fname    = "";
    string _output_ckt       = "circuit.v";
    vector <string> _v_str_Var_in  ;
    vector <string> _v_str_Var_out ;
    vector <Cube*> _vCube   ;
    vector <Var_out*> _v_Var_out;
public:
    //------- Parser --------------------------------------//
    void parser_io_info( string input_file="io_info.txt" );
    void parser_truth_table( string in="io_rel.txt");
    //------- Caller --------------------------------------//
    void caller_iogen( string blkb = "iogen", string in = "in_pat.txt", string put = "io_rel.txt" );
    
    //------- Espresso Algorithm --------------------------//
    void do_espresso_algorithm();
    void do_espresso_expand_calColumnCtr( vector<int>&, Var_out* );
    void do_espresso_expand_calCubeWeigth( vector<int> const &, Var_out*);
    void do_espresso_expand( Var_out* );
    bool do_espresso_expand_doExpandGivenCube( Cube*, Var_out* );
    void do_espresso_reduce();
    //------- Dumper for Log -------------------------------//
    void dump_expanded_cover();//To do, please refer to p.73
    
    //-------- Other Func ---------------------------------//
    bool argChecker( int argc, const char *argv[] );
    bool isAllCubeExpanded( set<Cube*>* const );
    bool isCubeValidInOnSet( Cube*, Var_out* );
    bool isCubeCoverOtherCubes( Cube*, Var_out*);
    
    //----Set/Get-----------------------------------------//
    //void set_io_info_fname( string s ){ this->_io_info_fname = s; }
    //string get_io_info_fname(){ return this->_io_info_fname; }
    
    
};
#endif /* Framework_hpp */
