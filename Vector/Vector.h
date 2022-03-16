#pragma once
#include <iostream>
#include <fstream> 


struct Cell {
	/*Struct for representation of cell for Vector*/
	char* word;
	unsigned int length;
	size_t occurrences;
};

class Vector {
/// <summary>
///		Main class that stores Cells 
///		and realises inserting Cells, seraching Cells, removing Cells
/// </summary>
private:
	Cell* data;
	size_t actual_length;
	size_t filled_length;
	void enlarge();
public:
	Vector();
	Cell get_cell(size_t index);
	void insert(char* , size_t );
	void remove(char* , size_t);
	size_t search(char* , size_t);
	size_t amount_of_words();
	~Vector();
};

void read_from_file(Vector* vector, char* filename);


