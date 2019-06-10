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


using namespace std;

class Var;
//------------------ Main Class -----------------------//
class framework
{
//-----------------------------------------------------//
//            This is the top frameowrk
//-----------------------------------------------------//

private:
    string _io_info_fname    = "";
    string _output_ckt       = "circuit.v";
    vector <Var*> _vVar_int ;
    vector <Var*> _vVar_out ;
public:
    //------- Parser --------------------------------------//
    void parser_io_info( string input_file="io_info.txt" );
    void parser_truth_table( string input_file="io_rel.txt");
    //------- Caller --------------------------------------//
    void caller_iogen( string blkbox = "iogen", string input = "io_pat.txt", string output = "io_rel.txt" );
    
    bool argChecker( int argc, const char *argv[] );
    
    
    //----Set/Get-----------------------------------------//
    //void set_io_info_fname( string s ){ this->_io_info_fname = s; }
    //string get_io_info_fname(){ return this->_io_info_fname; }
    
    
};

class Var
{
    friend framework;
private:
    string symbol;
public:
    void set_symb( string s ){ this->symbol = s; }
    string get_symb( ){ return this->symbol; }
    
};





#endif /* Framework_hpp */
