//
//  Framework.cpp
//  LogicRegression
//
//  Created by TienHungTseng on 2019/6/7.
//  Copyright © 2019 Eric Tseng. All rights reserved.
//

#include "Framework.hpp"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//--------------- Arg Checker ---------------------------------//
bool framework::argChecker( int argc, const char *argv[] )
{
    if( argc < 4 )
    {
        printf("The arg count is less than 4\n");
        printf("./lrg io_info.txt iogen circuit.v\n");
        return false;
    }
    
    this->_io_info_fname = argv[1];
    this->_output_ckt = argv[3];
    
    return true;
}
//--------------- Parser of "io_info.txt" ---------------------//
void framework::parser_io_info( string fname )
{
    ifstream f_parser;
    f_parser.open( fname, ios::in );
    
    
    string line = "";
    int input_var_ctr = 0;
    int output_var_ctr = 0;
    if( f_parser.is_open() )
    {
        getline( f_parser, line );
        istringstream token1(line);
        token1 >> input_var_ctr >> output_var_ctr;
        
        getline( f_parser, line );
        istringstream token2(line);
        string tmp_str = "";
        for( int i = 1; i <= input_var_ctr + output_var_ctr; i++ )
        {
            Var* vPtr = new Var();
            token2 >> tmp_str;
            vPtr->set_symb(tmp_str);
            
            if( i <= input_var_ctr )    this->_vVar_int.push_back(vPtr);
            else                        this->_vVar_out.push_back(vPtr);
        }
        /*
        //---------- DFT -----------------------------------------
        for( auto const &v: this->_vVar_int )
            printf("%s ", v->get_symb().c_str() );
        
        for( auto const &v: this->_vVar_out )
            printf("%s ", v->get_symb().c_str() );
        */
        
        
        
    }else
        printf("[Error] Unable to open/read %s.\n", fname.c_str());
    
}
