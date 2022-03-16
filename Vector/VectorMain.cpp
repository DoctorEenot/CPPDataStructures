#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Vector.h"
#include <chrono>

using namespace std::chrono;

int main()
{

    // filename:
    char filename[] = "small-file.txt";

    // Creating vector object:
    Vector vector = Vector();

    // reading data from file into vector:
    read_from_file(&vector, filename);

    // getting start time of searching
    size_t start = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        ).count();
    size_t end;

    unsigned int random_index;
    char* query;
    size_t query_length;

    // searching 1000 elements in the vector
    for (unsigned long i = 0; i < 1000; i++) {
        // getting random index
        random_index = rand() % vector.amount_of_words();

        // getting word with random index
        query = vector.get_cell(random_index).word;
        query_length = vector.get_cell(random_index).length;

        // actual searching in the vector with random word 
        size_t index = vector.search(query, query_length);
        std::cout << vector.get_cell(index).occurrences << std::endl;
    }

    // getting end time of searching
    end = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        ).count();
    
    std::cout << "milliseconds it took:" << end - start;

    // deletion Test
    random_index = rand() % vector.amount_of_words();
    query = vector.get_cell(random_index).word;
    query_length = vector.get_cell(random_index).length;
    vector.remove(query, query_length);

    return 0;
}

