//
//  main.cpp
//  LogicRegression
//
//  Created by Tien-HungTseng on 2019/6/7.
//  Copyright © 2019 Eric Tseng. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "Framework.hpp"



using namespace std;


int main( int argc, const char * argv[] )
{
    framework *myFramework = new framework();
    
    //----------- Check Args --------------------------------//
    if( !myFramework->argChecker( argc, argv) )
    {
        delete myFramework;
        return -1;
    }
    //----------- Gen. Truth Table (Call iogen) --------------//
    myFramework->parser_io_info();
    myFramework->caller_iogen();
    myFramework->parser_truth_table();
    
    
    
    //-------- End the program ------------------------------//
    delete myFramework;
    return 0;
}
