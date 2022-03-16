#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include "Vector.h"


using namespace std::chrono;

int main()
{
    Vector vector;
    char filename[] = "data.txt";
    read_from_file(&vector,filename);

    unsigned int random_index;
    char* query;
    size_t query_length;

    // getting start time of searching
    size_t start = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        ).count();
    size_t end;

    for (unsigned long i = 0; i < 1000; i++) {
        // getting random index
        random_index = rand() % vector.amount_of_words();

        // getting word with random index
        query = vector.get_cell(random_index).word;
        query_length = vector.get_cell(random_index).length;

        // actual searching in the vector with random word 
        size_t index = vector.find_cell(query, query_length);
    }

    // getting end time of searching
    end = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        ).count();

    std::cout << "milliseconds it took:" << end - start;

    random_index = rand() % vector.amount_of_words();

    // getting word with random index
    query = vector.get_cell(random_index).word;
    query_length = vector.get_cell(random_index).length;
    vector.remove(query,query_length);
    return 0;
}

