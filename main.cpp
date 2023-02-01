#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>
#include "Indexer.h"

#include "DSVector.h"

int main(int argc, char** data) {

    //run the index maker with 4 command line arguments
    if (argc == 4) {
        //main code for running program
        Indexer indexer;
        //the function names are self explanatory as to what they do
        indexer.learn_keys(data[2]);
        indexer.check_book(data[1]);
        indexer.sort_entries();
        indexer.sort_page_nums();
        indexer.make_index(data[3]);
        //indexer.print_vectors();
    }
    //run the catch with zero arguments
    else if(argc == 1){
        Catch::Session().run();

    }
    //otherwise, ask for the correct number
    else{
        std::cout << "please give the correct number of command line arguments" << std::endl;
    }
    return 0;

}