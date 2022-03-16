#include <iostream>
#include <ctime>
#include <fstream> 
#include "HashTable.h"



unsigned char RandBuf[256];


void randomise_RandBuf() {//must be called first
    srand(time(0));
    for (int i = 0; i < 256; i++) {
        RandBuf[i] = rand();
    }
}

// creates hash from data
unsigned long long Hash(unsigned char* data, size_t size) {

    unsigned long long to_return = 0;
    unsigned char h1, h2;
    size_t counter = 0;

    h1 = *data;
    h2 = *data + 1;
    counter++;
    while (counter < size) {
        h1 = RandBuf[h1 ^ data[counter]];
        h2 = RandBuf[h2 ^ data[counter]];
        to_return += ((unsigned long long)h1 << 54) | (unsigned long long)h2;
        counter++;
    }
    return to_return;
}

// compares if a == b
bool compare(char* a, size_t a_length,
             char* b, size_t b_length){
    if (a_length != b_length) {
        return false;
    }
    for (size_t i = 0; i < a_length; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

// adds additional buckets to hashtable 
// places all data in new places
void HashTable::expand() {
    Node* buf = new Node[amount_of_buckets+10000];
    //memcpy(buf,buckets,amount_of_buckets*sizeof(Node));
    Node* temp = buckets;
    //free(buckets);
    buckets = buf;
    size_t prev_amount = amount_of_buckets;
    amount_of_buckets += 10000;
    for (size_t i = 0; i < prev_amount; i++) {
        if (!temp[i].inited) {
            continue;
        }
        insert(temp[i].key,temp[i].key_length,temp[i].occurances);
    }
    free(temp);
}

// inserts data into specific bucket
// bucket is chosen by hash function, if bucket is not empty will 
// add data in first found empty bucket
void HashTable::insert(char* key, size_t length, size_t occ=1) {
    unsigned long long index_to_place = Hash((unsigned char*)key, length)%amount_of_buckets;
    while (buckets[index_to_place].inited) {
        if (compare(key, length, buckets[index_to_place].key, buckets[index_to_place].key_length)) {
            buckets[index_to_place].occurances += 1;
            return;
        }
        index_to_place++;
        if (index_to_place == amount_of_buckets) {
            expand();
        }
    }
    buckets[index_to_place].inited = true;
    buckets[index_to_place].occurances = occ;
    buckets[index_to_place].key = new char[length];
    memcpy(buckets[index_to_place].key,key,length);
    buckets[index_to_place].key_length = length;

}

// searches for bucket with same key
Node* HashTable::search(char* key, size_t length) {
    unsigned long long index = Hash((unsigned char*)key, length)%amount_of_buckets;
    while (buckets[index].inited && index<amount_of_buckets) {
        if (compare(key, length, buckets[index].key, buckets[index].key_length)) {
            return &buckets[index];
        }
        index++;
    }
    return nullptr;
}


void read_from_file(HashTable* vector, char* filename) {
    /*
    Function to read data from file
    and insert it into vector
    */
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file - '"
            << filename << "'" << std::endl;
        return;
    }
    char* buf = new char[512];
    unsigned int word_size = 0;
    char read_char;
    while (file.get(read_char)) {
        if ((read_char < 48) ||
            (read_char > 57 && read_char < 65) ||
            (read_char > 90 && read_char < 97) ||
            (read_char > 122)) {

            if (word_size > 0) {
                vector->insert((char*)buf, word_size);
                word_size = 0;
            }
        }
        else {
            if (read_char > 64 && read_char < 91) {
                read_char += 32;
            }
            buf[word_size] = read_char;
            word_size += 1;
        }
    }
    file.close();
}