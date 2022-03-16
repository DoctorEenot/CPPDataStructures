#include <iostream>
#include "HashTable.h"
#include <chrono>

using namespace std::chrono;

int main()
{
	char filename[] = "small-file.txt";
	HashTable hashtable;
	randomise_RandBuf();

	read_from_file(&hashtable, filename);

	//char query[] = "this";

	Node queries[1000];
	unsigned int random_index;
	size_t query_length;
	Node node;
	for (unsigned int i = 0; i < 1000; i++) {
		while (true) {
			random_index = rand() % hashtable.get_amount();
			node = hashtable.get_bucket_by_index(random_index);
			if (node.inited) {
				break;
			}
		}
		queries[i] = node;
	}

	// getting start time of searching
	size_t start = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		).count();
	size_t end;

	

	for (unsigned int i = 0; i < 1000; i++) {
		
		Node* node = hashtable.search(queries[i].key, queries[i].key_length);
		std::cout << node->occurances << std::endl;
	}

	// getting end time of searching
	end = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		).count();

	std::cout << "milliseconds it took:" << end - start;

	return 0;
}

