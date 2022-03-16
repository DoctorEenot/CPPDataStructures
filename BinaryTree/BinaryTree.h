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

    // val is the key or the value that
    // has to be added to the data part
    Node(char* val, size_t length)
    {
        data.word = (char*)malloc(length);
        memcpy(data.word,val,length);
        data.length = length;
        data.occurrences = 1;

        // Left and right child for node
        // will be initialized to null
        left = NULL;
        right = NULL;
    }
};


class BinaryTree {
private:
    Node* root = nullptr;
    Node* insert(Node* root_node, char*, size_t);
    Node* search(Node*, char*, size_t);
    Node* searchKey(Node*, char*, size_t, Node*&);
    Node* Delete(struct Node* root,
                        char* key,
                        size_t key_length);
    void preorder(Node* root_node);
    void inorder(Node*);
    void postorder(Node*);
public:
    Node* get_root() { return root; }
    void insert(char*, size_t);
    Node* search(char*, size_t);
    void remove(char*, size_t);
    void preorder();
    void inorder();
    void postorder();
};

void read_from_file(BinaryTree* vector, char* filename);