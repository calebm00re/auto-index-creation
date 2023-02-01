//
// Created by Caleb Moore on 2/28/21.
//

#ifndef INC_21S_PA02_INDEXER_H
#define INC_21S_PA02_INDEXER_H
#include "DSVector.h"
#include "DSString.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "pages.h"

//Indexer class used in reading in, analyzing, and outputting  keywords, books, and an index respectively
class Indexer{
private:
    //DSVector of unsorted pages
    DSVector<pages> entries;
    //DSVector of sorted pages
    DSVector<pages> final_index;

public:
    Indexer();
    void learn_keys(DSString key_file);
    void check_book(DSString book_file);
    void sort_entries();
    void sort_page_nums();
    void make_index(DSString output_name);
    void print_vectors();

};

#endif //INC_21S_PA02_INDEXER_H
