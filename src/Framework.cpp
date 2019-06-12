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


//--------------- Color ---------------------------------------//
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

//---------------- Name Space ---------------------------------//
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

//-------------------------------------------------------------------//
//                  Call iogen to produce truth table
//-------------------------------------------------------------------//
void framework::caller_iogen( string blkbox, string input, string output )
{
    //---- The function has not been checked -------------------//
    string s_cmd = "./" + blkbox + " " + input + " " + output;
    system( s_cmd.c_str() );
    printf( "[Sys Call] %s \n", s_cmd.c_str() );
}

//-------------------------------------------------------------------//
//                  Parser to io_rel.txt (Default file name)
//-------------------------------------------------------------------//
void framework::parser_truth_table( string in_file )
{
    //---- The function has not been checked -------------------//
    ifstream f_parser;
    string line = "";
    
    f_parser.open( in_file, ios::in );
    
    //------ Parse I/O Var Sequence --------------------------------//
    getline( f_parser, line );
    
    
    //------ Parse 0/1 entry in Truth Table -------------------------//
    if( f_parser.is_open() )
    {
        
        while( getline( f_parser, line ) )
        {
            //To be continued here
            //Test
            printf("%s \n", line.c_str());
        }
    }else
        printf("[Error] Unable to open/read %s\n", in_file.c_str() );
}


