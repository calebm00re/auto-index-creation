//
// Created by Caleb Moore on 3/2/21.
//

#include "pages.h"

//check to see if a page number already exists in the DSVector they are stored in
bool pages::is_duplicate(int &r) {
    for(int i = 0; i < locations.get_size(); i++){
        if(locations[i] == r){
            return true;
        }
    }
    return false;
}

//adds a page number to the locations DSVector
void pages::add(const int &r) {
    locations.push_back(r);
}

//constructs a page objects making the key = the passed argument
pages::pages(const DSString &p) {
    key = p;
}

//default constructor
pages::pages() {
}

//returns the key of the page
DSString &pages::get_key() {
    return key;
}

//returns the amount of pages the key shows up on or number so far added to the locations dsvector
int pages::index_appearances() {
    return locations.get_size();
}

//returns the page number at locations of the index passed as 'r'
int &pages::at(const int &r) {
    return locations[r];
}

//sorts the vector of locations therefore numerically ordering their appearances
void pages::sorting() {
    locations.sort();
}
