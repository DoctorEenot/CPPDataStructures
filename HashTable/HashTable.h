#pragma once


void randomise_RandBuf();
unsigned long long Hash(unsigned char* data, size_t size);

struct Node {
	char* key;
	size_t key_length;
	bool inited;
	size_t occurances;
	Node() {
		inited = false;
	}
};


class HashTable {
private:
	Node* buckets;
	size_t amount_of_buckets;
	void expand();
public:
	HashTable() {
		amount_of_buckets = 1000;
		buckets = new Node[amount_of_buckets];
	}
	size_t get_amount() {
		return amount_of_buckets;
	}
	Node get_bucket_by_index(size_t i) {
		return buckets[i];
	}
	void insert(char*, size_t, size_t);
	Node* search(char*, size_t);
};

void read_from_file(HashTable*, char*);
