#pragma once
#include <stdlib.h>
#include <string.h>

struct Cell {
    /*Struct for representation of cell for Node*/
    char* word;
    unsigned int length;
    size_t occurrences;
};

struct Node {
    Cell data;
    struct Node* left;
    struct Node* right;
    size_t height;

    // val is the key or the value that
    // has to be added to the data part
    Node(char* val, size_t length)
    {
        data.word = (char*)malloc(length);
        memcpy(data.word, val, length);
        data.length = length;
        data.occurrences = 1;
        height = 1;

        // Left and right child for node
        // will be initialized to null
        left = nullptr;
        right = nullptr;
    }
};

int max(int, int);
int height(Node*);

class AVLTree {
private:
    Node* root_node = nullptr;

    Node* rightRotate(Node*);
    Node* leftRotate(Node*);
    int getBalance(Node*);
    Node* insert(Node*, char*, size_t);
    void preorder(Node*);
    void inorder(Node*);
    void postorder(Node*);
    Node* Delete(struct Node*,
        char* key,
        size_t key_length);
    Node* search(Node*, char*, size_t);
public:
    void insert(char*, size_t);
    void preorder();
    void inorder();
    void postorder();
    Node* get_root() { return root_node; }
    void remove(char*, size_t);
    Node* search(char*, size_t);
};


void read_from_file(AVLTree* vector, char* filename);