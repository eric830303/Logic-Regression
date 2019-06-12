//
//  Framework.cpp
//  LogicRegression
//
//  Created by TienHungTseng on 2019/6/7.
//  Copyright © 2019 Eric Tseng. All rights reserved.
//
#include "Framework.hpp"


//--------------- Color ---------------------------------------//
#define RED     "\x1b[31m"
#define GRN     "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RST     "\x1b[0m"

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
        
        for( int i = 1; i <= input_var_ctr + output_var_ctr; i++ )
        {
            string tmp_str = "";
            token2 >> tmp_str;
            if( i <= input_var_ctr )    this->_vVar_int.push_back(tmp_str);
            else                        this->_vVar_out.push_back(tmp_str);
        }
    }else
        printf( RED"[Error] " RST"Unable to open/read %s.\n", fname.c_str());
    
}

//-------------------------------------------------------------------//
//                  Call iogen to produce truth table
//-------------------------------------------------------------------//
void framework::caller_iogen( string blkbox, string input, string output )
{
    //---- The function has not been checked -------------------//
    string s_cmd = "./" + blkbox + " " + input + " " + output;
    system( s_cmd.c_str() );
    printf( RED"[Sys Call]" RST" %s \n", s_cmd.c_str() );
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
    
    int i_Var_in_ctr = 0;
    int i_Var_out_ctr= 0;
    int i_Cube_ctr = 0;
    
    
    //------- Parse info --------------------------------------------//
    istringstream token(line);
    token >> i_Var_in_ctr >> i_Var_out_ctr >> i_Cube_ctr;
    
    //----Debug-----
    assert( i_Var_out_ctr == this->_vVar_int.size() );
    assert( i_Var_in_ctr  == this->_vVar_out.size() );
    assert( i_Cube_ctr    != 0 );
    
    
    //------- Parse Var & Double Check ------------------------------//
    getline( f_parser, line );
    //--- Double Check ----------------//
    //To be continued..
    
    
    //------ Parse 0/1 entry in Truth Table -------------------------//
    if( f_parser.is_open() )
    {
        while( getline( f_parser, line ) )
        {
            istringstream token2(line);
            int i_value = 0;
            int i_loop_ctr =0;
            Cube *pCube = new Cube;
            while( token2 >> i_value )
            {
                Var *pVar = new Var;
                pVar->_b_value = (i_value)?(true):(false);
                if( i_loop_ctr < i_Var_in_ctr ) pCube->_v_Var_in.push_back(pVar);
                else                            pCube->_v_Var_out.push_back(pVar);
                
                //----- DFT ------------
                //To be continued...
                
                i_loop_ctr++;
            }
            this->_vCube.push_back(pCube);
            //To be continued here
            //Test
            printf("%s \n", line.c_str());
        }
    }else
        printf( RED"[Error] " RST"Unable to open/read %s\n", in_file.c_str() );
}


