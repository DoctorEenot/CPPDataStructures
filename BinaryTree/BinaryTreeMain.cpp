#include <iostream>
#include "BinaryTree.h"
#include <chrono>

using namespace std::chrono;

Cell* random_cell(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    if ((rand() % 2) == 1) {
        return &node->data;
    }
    else {
        Cell* to_return;
        if (rand() % 2 == 1) {
            to_return = random_cell(node->left);
        }
        else {
            to_return = random_cell(node->right);
        }
        if (to_return == nullptr) {
            return &node->data;
        }
    }
}


int main()
{
    BinaryTree tree;
    char filename[] = "small-file.txt";

    read_from_file(&tree,filename);

    char query[] = "this";

    tree.inorder();
    Cell queries[1000];
    unsigned int random_index;
    size_t query_length;
    Cell* node;

    for (unsigned int i = 0; i < 1000; i++) {
        node = random_cell(tree.get_root());
        queries[i] = *node;
    }


    // getting start time of searching
    size_t start = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        ).count();
    size_t end;

    for (unsigned int i = 0; i < 1000; i++) {
        Node* node = tree.search(queries[i].word, queries[i].length);
        std::cout << node->data.occurrences << std::endl;
    }

    // getting end time of searching
    end = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        ).count();

    std::cout << "milliseconds it took:" << end - start;

    tree.remove(query, strlen(query));
    tree.inorder();
    return 0;
}

