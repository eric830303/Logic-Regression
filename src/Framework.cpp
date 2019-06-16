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
            if( i <= input_var_ctr )    this->_v_str_Var_in.push_back(tmp_str);
            else                        this->_v_str_Var_out.push_back(tmp_str);
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
    
    //f_parser.open( in_file, ios::in );
    
    f_parser.open( "io_rel2.txt", ios::in );
    
    //------ Parse I/O Var Sequence --------------------------------//
    getline( f_parser, line );
    
    int i_Var_in_ctr = 0;
    int i_Var_out_ctr= 0;
    int i_Cube_ctr = 0;
    
    
    //------- Parse info --------------------------------------------//
    istringstream token(line);
    token >> i_Var_in_ctr >> i_Var_out_ctr >> i_Cube_ctr;
    
    //---- Double check -----
    assert( i_Var_in_ctr  == this->_v_str_Var_in.size() );
    assert( i_Var_out_ctr == this->_v_str_Var_out.size() );
    assert( i_Cube_ctr    != 0 );
    
    
    for( int i = 0; i < i_Var_out_ctr; i++ )
    {
        set <Cube*> * pset_cube_on  = new set <Cube*>;
        set <Cube*> * pset_cube_off = new set <Cube*>;
        this->_v_set_Var_out_on.push_back( pset_cube_on);
        this->_v_set_Var_out_off.push_back( pset_cube_off);
    }
    
    
    
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
            int i_value     = 0;
            int i_loop_ctr  = 0;
            Cube *pCube     = new Cube;
            while( token2 >> i_value )
            {
                if( i_loop_ctr < i_Var_in_ctr )
                {
                    Var_in *p_Var_in            = new Var_in;
                    p_Var_in->_b_value          = (i_value)? 1:0;
                    p_Var_in->_pr_code.first    = (i_value)? 0:1;
                    p_Var_in->_pr_code.second   = (i_value)? 1:0;
                    pCube->_v_Var_in.push_back(p_Var_in);
                }else
                {
                    int index = i_Var_out_ctr - i_loop_ctr;
                    if( i_value )
                        this->_v_set_Var_out_on.at( index )->insert( pCube );
                    else
                        this->_v_set_Var_out_off.at( index )->insert( pCube );
                }
                i_loop_ctr++;
            }
            this->_vCube.push_back(pCube);
        }
    }else
        printf( RED"[Error] " RST"Unable to open/read %s\n", in_file.c_str() );
}

bool mycompare( Cube*A, Cube*B ){ return (A->_i_weight > B->_i_weight); };

void framework::do_espresso_algorithm()
{
    for( auto const &cubes_onset: this->_v_set_Var_out_on )
    {
        vector<int> v_col_ctr;
        this->do_espresso_expand_calColumnCtr( v_col_ctr, cubes_onset );
        this->do_espresso_expand_calCubeWeigth( v_col_ctr, cubes_onset );
        sort( this->_vCube.begin(), this->_vCube.end(), mycompare );
        this->do_espresso_expand( cubes_onset ) ;
    }
    //----- DFT ------
    
    
    
}
//------------------------------------------//
// Calculate the count of on in each column,
// after truth table is encoded.
//------------------------------------------//
void framework::do_espresso_expand_calColumnCtr( vector<int> &v_col_ctr, set<Cube*>* const cube_onset)
{
    unsigned long i_Var_in_size = this->_v_str_Var_in.size() * 2;
    
    bool first = 1;
    for( unsigned long j = 0; j < i_Var_in_size; j++ )
    {
        int i_ctr = 0;
        if( first )
        {
            for( auto const & cube: *cube_onset )
                if( cube->_v_Var_in.at( int(j/2) )->_pr_code.first ) i_ctr++;
            
        }else
        {
            for( auto const & cube: *cube_onset )
                if( cube->_v_Var_in.at( int(j/2) )->_pr_code.second ) i_ctr++;
        }
        v_col_ctr.push_back( i_ctr );
        first = ! first;
    }
}
//----------------------------------------------------//
//  Calcuate weight of each cube, base on the given
//  set of on cubes.
//---------------------------------------------------//
void framework::do_espresso_expand_calCubeWeigth( vector<int>const& v_col_ctr, set<Cube*>* const cube_onset )
{
    unsigned long i_Var_in_size = this->_v_str_Var_in.size() * 2;
    assert( i_Var_in_size == v_col_ctr.size() );
    
    for( auto const & cube: this->_vCube )
    {
        cube->_i_weight = 0;//Initialized
        bool first = 1;
        int i_weight = 0;
        
        for( unsigned long j = 0; j < i_Var_in_size; j++ )
        {
            if( cube->_v_Var_in.at( int(j/2) )->_pr_code.first  &&  first ) i_weight += v_col_ctr.at(j);
            if( cube->_v_Var_in.at( int(j/2) )->_pr_code.second && !first ) i_weight += v_col_ctr.at(j);
            first = !first;
        }
        cube->_i_weight = i_weight;
    }
}

void framework::do_espresso_expand( set<Cube*> *cubes_onset )
{
    //-----Initialized ----------------//
    for( auto const &cube: *cubes_onset )
        cube->expanded = 0;
    //----- Heuristic -----------------//
    while( this->isAllCubeExpanded( cubes_onset ) )
    {
        for( auto &cube: *cubes_onset )
        {
            if( cube->expanded ) continue;
            bool del = this->do_espresso_expand_doExpandGivenCube( cube, cubes_onset);
            //One covered cube is deleted, due to the expanded cube.
            if( del )
            {
                sort( this->_vCube.begin(), this->_vCube.end(), mycompare );
                break;
            }
        }
    }
}
bool framework::isAllCubeExpanded( set<Cube*>* const cubes_onset )
{
    for( auto const &cube: *cubes_onset )
        if( !cube->expanded ) return 0;
    return 1;
}
//-------------------------------------------------//
// Expand the given cube, and delete the cubes covered
// by the expanded cube
//-------------------------------------------------//
bool framework::do_espresso_expand_doExpandGivenCube( Cube* cube, set<Cube *> * cube_onset )
{
    bool del = 0;
    
    //Iterate through encoded bits of cube representation.
    bool first = 1;
    unsigned long i_Var_in_size = cube->_v_Var_in.size()*2;
    
    pair <bool,bool> *p_encode = NULL ;
    bool * pbit = NULL;
    for( unsigned long j = 0; j < i_Var_in_size; j++ )
    {
        p_encode = &( cube->_v_Var_in.at( int(j/2) )->_pr_code );
        pbit     = ( first )? &(p_encode->first): &(p_encode->second);
        
        //Flip the bit from 0 to 1
        //Then, check validity
        //If valid, then delete covered cubes.
        if( (*pbit) )
            continue;
        else
        {
            *pbit = 1;
            if( !isCubeValidInOnSet( cube, cube_onset) )
                *pbit = 0;
            else if( isCubeCoverOtherCubes(cube, cube_onset))
                del = 1;
        }
        
        
        first = !first;
    }
    return del;
}
bool framework::isCubeValidInOnSet( Cube*, set<Cube*>* const )
{
    bool isValid = 0;
    return isValid;
}
bool framework::isCubeCoverOtherCubes( Cube*, set<Cube*>* const )
{
    bool isCover = 0;
    return isCover;
}
