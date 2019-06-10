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
    ofstream f_parser;
    f_parser.open( fname, ios::in );
    
    
    string line = "";
    
    if( f_parser.is_open() )
    {
        getline( f_parser, line );
        istringstream token(line);
        
        
        
        
        
        
        
    }else
        printf("[Error] Unable to open/read %s.\n", fname.c_str());
    
}
