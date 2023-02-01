//
// Created by Caleb Moore on 3/2/21.
//

#ifndef INC_21S_PA02_PAGES_H
#define INC_21S_PA02_PAGES_H
#include "DSVector.h"
#include "DSString.h"

//class to store a key word and all the page nums it appears on
class pages{
private:
    //keyword for index entry
    DSString key;
    //DSVector of the page nums the key appears
    DSVector<int> locations;
public:
    pages();
    pages(const DSString& p);
    bool is_duplicate(int& r);
    void add(const int& r);
    DSString& get_key();
    int index_appearances();
    int& at(const int& r);
    void sorting();
};

#endif //INC_21S_PA02_PAGES_H
