#include "AVLTree.h"
#include <fstream> 
#include <iostream>


char compare(char* a,
			size_t a_size,
			char* b,
			size_t b_size) {
	/// <summary>
	/// takes 2 char arrays
	/// </summary>
	/// <param name="a"></param>
	/// <param name="a_size"></param>
	/// <param name="b"></param>
	/// <param name="b_size"></param>
	/// <returns>
	/// if a string < b string, then returns -1
	/// if a string == b string, then returns 0
	/// if a string > b string, then returns 1
	/// </returns>
	if (a_size == b_size) {
		for (size_t i = 0; i < a_size; i++) {
			if (a[i] > b[i]) {
				return 1;
			}
			else if (a[i] < b[i]) {
				return -1;
			}
		}
		return 0;
	}
	else if (a_size < b_size) {
		for (size_t i = 0; i < a_size; i++) {
			if (a[i] > b[i]) {
				return 1;
			}
			else if (a[i] < b[i]) {
				return -1;
			}
		}
		return -1;
	}
	else if (a_size > b_size) {
		for (size_t i = 0; i < b_size; i++) {
			if (a[i] > b[i]) {
				return 1;
			}
			else if (a[i] < b[i]) {
				return -1;
			}
		}
		return 1;
	}
}


int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(Node* N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


Node* AVLTree::rightRotate(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
        height(y->right)) + 1;
    x->height = max(height(x->left),
        height(x->right)) + 1;

    // Return new root
    return x;
}

Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int AVLTree::getBalance(Node* N) {
    if (N == nullptr) {
        return 0;
    }
    return height(N->left) - height(N->right);
}

Node* AVLTree::insert(Node* node, char* key, size_t key_size) {
    if (node == nullptr) {
        return new Node(key, key_size);
    }

	int cmp = compare(key,key_size,node->data.word,node->data.length);

	if (cmp == -1) {
		node->left = insert(node->left, key, key_size);
	}
	else if (cmp == 1) {
		node->right = insert(node->right, key, key_size);
	}
	else {
		node->data.occurrences += 1;
		return node;
	}

	int balance = getBalance(node);

	int cmp_left = 0;
	int cmp_right = 0;

	if (balance > 1 || balance < -1) {
		cmp_left = compare(key, key_size,
			node->left->data.word, node->left->data.length);
		cmp_right = compare(key, key_size,
			node->right->data.word, node->right->data.length);
	}

	if (balance > 1 && cmp_left == -1) {
		return rightRotate(node);
	}
	if (balance < -1 && cmp_right == 1) {
		return leftRotate(node);
	}
	if (balance > 1 && cmp_left == 1) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	if (balance < -1 && cmp_right == -1) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

void AVLTree::insert(char* key, size_t key_size) {
	root_node = insert(root_node, key, key_size);
}

void read_from_file(AVLTree* vector, char* filename) {
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




void AVLTree::preorder(Node* root_node) {
	if (root_node) {
		for (size_t char_index = 0; char_index < root_node->data.length; char_index++) {
			std::cout << root_node->data.word[char_index];
		}
		std::cout << " : " << root_node->data.occurrences << " | ";
		preorder(root_node->left);
		preorder(root_node->right);
	}
}

void AVLTree::preorder() {
	preorder(get_root());
}


void AVLTree::inorder(Node* root_node) {
	if (root_node) {
		inorder(root_node->left);
		for (size_t char_index = 0; char_index < root_node->data.length; char_index++) {
			std::cout << root_node->data.word[char_index];
		}
		std::cout << " : " << root_node->data.occurrences << " | ";

		inorder(root_node->right);
	}
}

void AVLTree::inorder() {
	inorder(get_root());
}


void AVLTree::postorder(Node* root_node) {
	if (root_node) {
		postorder(root_node->left);
		postorder(root_node->right);
		for (size_t char_index = 0; char_index < root_node->data.length; char_index++) {
			std::cout << root_node->data.word[char_index];
		}
		std::cout << " : " << root_node->data.occurrences << " | ";
	}
}

void AVLTree::postorder() {
	postorder(get_root());
}

Node* min_value_node(Node* node) {
	Node* current = node;
	while (current->left != nullptr) {
		current = current->left;
	}
	return current;
}

Node* AVLTree::Delete(Node* node, char* key, size_t key_size) {
	if (node == nullptr) {
		return node;
	}

	char cmp = compare(key, key_size, node->data.word, node->data.length);

	if (cmp == -1) {
		node->left = Delete(node->left, key, key_size);
	}
	else if (cmp == 1) {
		node->right = Delete(node->right, key, key_size);
	}
	else {
		if (node->left == nullptr ||
			node->right == nullptr) {
			Node* temp = node->left ? node->right : node->right;
			if (temp == nullptr) {
				temp = node;
				node = nullptr;
			}
			else {
				*node = *temp;
			}
			free(temp);
		}
		else {
			Node* temp = min_value_node(node->right);
			node->data = temp->data;
			node->right = Delete(node->right, temp->data.word, temp->data.length);
		}
	}

	if (node == nullptr) {
		return node;
	}
	node->height = 1 + max(height(node->left),
		height(node->right));

	int balance = getBalance(node);

	// Left Left Case 
	if (balance > 1 &&
		getBalance(node->left) >= 0) {

		return rightRotate(node);
	}

	// Left Right Case 
	if (balance > 1 &&
		getBalance(node->left) < 0)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Right Case 
	if (balance < -1 &&
		getBalance(node->right) <= 0) {
		return leftRotate(node);
	}

	// Right Left Case 
	if (balance < -1 &&
		getBalance(node->right) > 0)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

void AVLTree::remove(char* key, size_t key_size) {
	root_node = Delete(root_node, key, key_size);
}

Node* AVLTree::search(Node* node, char* val, size_t length) {
	if (!node) {
		return nullptr;
	}
	char cmp = compare(val,
					length,
					node->data.word,
					node->data.length);
	if (cmp == 0) {
		return node;
	}
	else if (cmp == -1) {
		return search(node->left, val, length);
	}
	else {
		return search(node->right, val, length);
	}
}

Node* AVLTree::search(char* key, size_t key_size) {
	return search(root_node,key,key_size);
}