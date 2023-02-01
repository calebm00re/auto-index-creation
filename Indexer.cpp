//
// Created by Caleb Moore on 2/28/21.
//

#include "Indexer.h"

//default constructor
Indexer::Indexer() {
    //does nothing because there is nothing to do
}

//function to read in the keywords to look for
void Indexer::learn_keys(DSString key_file) {
    //create input stream
    std::ifstream input;

    //make sure the file opens
    input.open(key_file.c_str());
    if(!input.is_open()) {
        std::cout << "input keys failed to open" << std::endl;
    }

    //go through the file until there is nothing left
    while(!input.eof()){
        //make a char* buffer to store the word(s) as DSStrings
        char* temp_key = new char[100];
        input.getline(temp_key, 100, '\n');
        DSString key(temp_key);
        delete[] temp_key;

        //dont push back if line is just blank
        if(key == ""){}

        //otherwise add the line as a key word/phrase
        else {
            //make it lower case for easier comparison
            key.lower();
            //make a new entry and add it to the vector
            pages page(key);
            entries.push_back(page);
        }
    }
    //close the input file
    input.close();
}

//this function is used in testing to see diffent aspects of the vectors
void Indexer::print_vectors() {
    //print out the key words and their size- the number of key words
    for(int i = 0; i < final_index.get_size(); i++){
        std::cout << final_index[i].get_key() << " [size: " << final_index[i].get_key().getLength() << "]" << " index appearances: " << final_index[i].index_appearances() << std::endl;
    }

    //print total size of keys
    std::cout << "size: " << final_index.get_size() << std::endl;
}

//travers the book and find pages of key word locations
void Indexer::check_book(DSString book_file) {
    //make input stream and open file from command arguments
    std::ifstream input;
    input.open(book_file.c_str());
    DSString curr_page;

    //remember the current page num
    int page_num;

    //make sure the file opens
    if(!input.is_open()) {
        std::cout << "input book failed to open" << std::endl;
    }

    //if it is go through it
    else {
        while (!input.eof()) {
            //make a buffer to turn into dsstring object for comparison
            char *temp = new char[100];
            input.getline(temp, 100, '\n');
            DSString line(temp);
            delete[] temp;

            //make sure line is not empty
            if (line == "") {
            }

            //check for new page after new line
            else if (line[0] == '<') {
                for (int i = 1; line[i] != '>'; i++) {
                    curr_page = line.substring(1, i);
                }

                //break if page number is "-1" to stop reading in info
                if (curr_page == "-1") {
                    break;
                }
                //make sure the page number is stored in a vector of ints for comparison and sorting
                page_num = curr_page.to_digit();
            }

            //if not a new page check for words
            else {
                //make it all lower case
                line.lower();
                int l = line.getLength();

                //go through key words on this line
                for (int i = 0; i < entries.get_size(); i++) {
                    //make sure key can fit into the current line
                    if (entries[i].get_key().getLength() <= l) {

                        //if key can fit in line check for matches
                        int kl = entries[i].get_key().getLength();
                        for (int j = 0; j < (l - kl + 1); j++) {

                            //compare all possibilities to avoid punctuation errors
                            DSString compare = line.substring(j, kl);

                            //check for a match at all combinations of the line
                            if (compare == entries[i].get_key()) {

                                //if it is a match add to pages list granted it is not a duplicate
                                if (!entries[i].is_duplicate(page_num)) {
                                    entries[i].add(page_num);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //close input file
    input.close();
}

//make the index output
void Indexer::make_index(DSString output_name) {
    //create the output stream and useful variables
    std::ofstream output;
    output.open(output_name.c_str());
    char curr_spot = ' ';
    int total = 0;
    bool space = false;

    //ensure file opens properly
    if(!output.is_open()) {
        std::cout << "output file failed to open" << std::endl;
    }

    //proceed with output if open
    else{
        //go through every page entry
        for(int i = 0; i < final_index.get_size(); i++){

            //ensure the entry will be going under the correct entry header i.e. "[a]" and if not add a new one
            char category = final_index[i].get_key()[0];
            if(category != curr_spot){
                curr_spot = category;
                if(space){
                    output << '\n';
                }
                curr_spot = toupper(curr_spot);
                output << "[" << curr_spot << "]" << '\n';
                curr_spot = tolower(curr_spot);
                space = true;
            }

            //send the indexed word to the output
            output << final_index[i].get_key() << ": " << final_index[i].at(0);

            //keep a total to divide the line in case too many pages exceed 70 cap
            total = final_index[i].get_key().getLength() + 2;
            total += final_index[i].at(0);

            //print page appearances in a loop
            for(int j = 1; j < final_index[i].index_appearances(); j++){
                output << ", ";
                total += 2;
                total += trunc(log10(final_index[i].at(j))) + 1;
                //send a line break if too long
                if(total > 69){
                    output << '\n';
                    total = 0;
                }
                output << final_index[i].at(j);
            }
            //break the entry
            output << '\n';
        }
    }
    output.close();
}

//to sort vector object pages for the index
void Indexer::sort_entries() {
    //create a temp object
    DSString temp = entries[0].get_key();
    int location = entries.get_size();
    int spot = 0;

    //check till the last one
    while (location > 1) {
        temp = entries[spot].get_key();
        for (int i = 0; i < location; i++) {
            if (entries[i].get_key() < temp) {
                temp = entries[i].get_key();
                spot = i;
            }
        }
        //add the next lowest to final entries vector
        final_index.push_back(entries[spot]);
        entries.erase_at(spot);
        //adjust variables
        spot = 0;
        location--;
    }
    //add the very last one
    final_index.push_back(entries[0]);
}

//sorts every vector on all the pages (sorts the appearances of page nums)
void Indexer::sort_page_nums() {
    int over = final_index.get_size();
    for(int i = 0; i < over; i++){
        final_index[i].sorting();
    }
}
