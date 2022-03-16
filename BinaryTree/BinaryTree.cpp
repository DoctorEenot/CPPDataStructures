#include "BinaryTree.h"
#include <fstream> 
#include <iostream>

void read_from_file(BinaryTree* vector, char* filename) {
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


char compare(unsigned char* a,
	size_t a_size,
	unsigned char* b,
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


Node* BinaryTree::insert(Node* root_node, char* val, size_t length) {
	if (!root_node) {
		return new Node(val, length);
	}

	char cmp = compare((unsigned char*)val,
					length,
					(unsigned char*)root_node->data.word,
					root_node->data.length);
	if (cmp==-1)
	{
		if (root_node->left != NULL)
			insert(root_node->left, val, length);
		else
		{
			root_node->left = new Node(val,length);
		}
	}
	else if (cmp==1)
	{
		if (root_node->right != NULL)
			insert(root_node->right, val, length);
		else
		{
			root_node->right = new Node(val,length);			
		}
	}
	else {
		root_node->data.occurrences += 1;
	}
	return root_node;
}


void BinaryTree::insert(char* val, size_t length) {
	root = insert(get_root(),val,length);
}

Node* BinaryTree::search(Node* root_node, char* val, size_t length) {
	if (!root_node) {
		return nullptr;
	}
	char cmp = compare((unsigned char*)val,
						length,
						(unsigned char*)root_node->data.word,
						root_node->data.length);
	if (cmp == 0) {
		return root_node;
	}
	else if (cmp == -1) {
		return search(root_node->left, val, length);
	}
	else {
		return search(root_node->right, val, length);
	}
}


Node* BinaryTree::search(char* val, size_t length) {
	return search(get_root(),val,length);
}

// Iterative function to search in the subtree rooted at `curr` and set its parent.
Node* BinaryTree::searchKey(Node* curr, 
							char* key,
							size_t key_length, 
							Node*& parent)
{


	char cmp = compare((unsigned char*)key,
						key_length,
						(unsigned char*)curr->data.word,
						curr->data.length);

	if (cmp == 1) {
		parent = curr;
		return searchKey(curr->right,key,key_length,parent);
	}
	else if (cmp == -1) {
		parent = curr;
		return searchKey(curr->left, key, key_length, parent);
	}
	else {
		return curr;
	}
}



Node* minValueNode(Node* node) {
	Node* current = node;
	while (current && current->left != nullptr) {
		current = current->left;
	}
	return current;
}

Node* BinaryTree::Delete(Node* node, 
						char* key, 
						size_t key_length) {
	if (node == nullptr) {
		return node;
	}

	char cmp = compare((unsigned char*)key,key_length,
						(unsigned char*)node->data.word,node->data.length);

	if (cmp == -1) {
		node->left = Delete(node->left, key, key_length);
	}
	else if (cmp == 1) {
		node->right = Delete(node->right, key, key_length);
	}
	else {
		if (node->left == nullptr and node->right == nullptr) {
			return nullptr;
		}else if(node->left == nullptr) {
			Node* temp = node->right;
			free(root);
			return temp;
		}
		else if (node->right == nullptr) {
			Node* temp = node->left;
			free(node);
			return temp;
		}

		Node* temp = minValueNode(node->right);
		node->data = temp->data;
		node->right = Delete(node->right, temp->data.word, temp->data.length);
	}
	return node;
}

void BinaryTree::remove(char* val, size_t length) {
	root = Delete(root,val,length);
}


void BinaryTree::preorder(Node* root_node) {
	if (root_node) {
		for (size_t char_index = 0; char_index < root_node->data.length; char_index++) {
			std::cout << root_node->data.word[char_index];
		}
		std::cout << " : " << root_node->data.occurrences << " | ";
		preorder(root_node->left);
		preorder(root_node->right);
	}
}

void BinaryTree::preorder() {
	preorder(get_root());
}


void BinaryTree::inorder(Node* root_node) {
	if (root_node) {
		inorder(root_node->left);
		for (size_t char_index = 0; char_index < root_node->data.length; char_index++) {
			std::cout << root_node->data.word[char_index];
		}
		std::cout << " : " << root_node->data.occurrences << " | ";
		
		inorder(root_node->right);
	}
}

void BinaryTree::inorder() {
	inorder(get_root());
}


void BinaryTree::postorder(Node* root_node) {
	if (root_node) {
		postorder(root_node->left);
		postorder(root_node->right);
		for (size_t char_index = 0; char_index < root_node->data.length; char_index++) {
			std::cout << root_node->data.word[char_index];
		}
		std::cout << " : " << root_node->data.occurrences << " | ";
	}
}

void BinaryTree::postorder() {
	postorder(get_root());
}
