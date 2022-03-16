#include "Vector.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream> 


Vector::Vector() {
	actual_length = 1000;
	filled_length = 0;
	data = new Cell[actual_length];
}

Vector::~Vector() {
	delete[] data;
}

void Vector::enlarge() {
	/// <summary>
	/// Enlarges Vector.data by 1000 
	/// </summary>
	actual_length += 1000;
	Cell* buffer = new Cell[actual_length];
	memcpy(buffer, data, sizeof(Cell) * filled_length);
	free(data);
	data = buffer;
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

size_t Vector::search(char* query, 
					size_t length, 
					size_t start, 
					size_t end) {
	/// <summary>
	/// binary search for searching cell in data
	/// </summary>
	/// <param name="query"></param>
	/// <param name="length"></param>
	/// <param name="start"></param>
	/// <param name="end"></param>
	/// <returns>
	/// cell index, where Cell.word == query
	/// </returns>
	if (end >= start) {
		size_t mid = start + (end - start) / 2;
		char cmp = compare((unsigned char*)query,
							length,
							(unsigned char*)data[mid].word,
							data[mid].length);
		if (cmp == 0) {
			return mid;
		}

		if (cmp == -1) {
			return search(query,length,start,mid-1);
		}

		return search(query, length, mid + 1, end);
	}

	return filled_length;
}



void Vector::insert(char* input, size_t length) {
	/// <summary>
	/// inserts input into data, if Cell with word input exists
	/// adds 1 to Cell.occurrences
	/// </summary>
	/// <param name="input"></param>
	/// <param name="length"></param>
	if (filled_length >= actual_length) {
		enlarge();
	}
	int i;
	for (i = 0;
		(i < filled_length);
		i++) {

		char cmp = compare((unsigned char*)input, length,
			(unsigned char*)data[i].word, data[i].length);
		
		if (cmp == -1) {
			break;
		}
		else if (cmp == 0) {
			data[i + 1].occurrences += 1;
			return;
		}
		
	}

	memcpy(&data[i+1], &data[i], sizeof(Cell) * (filled_length-(i)));
	data[i].word = (char*)malloc(length);
	memcpy(data[i].word, input, length);
	data[i].occurrences = 1;
	data[i].length = length;
	filled_length += 1;
}

void Vector::remove(char* input, size_t length) {
	/*
	removes cell from vector
	searches it by the input string
	*/
	size_t cell_index = search(input, length,0,filled_length-1);
	if (cell_index == filled_length) {
		return;
	}
	delete data[cell_index].word;

	memcpy(&data[cell_index],
		&data[cell_index + 1],
		((filled_length - 1) - cell_index) * sizeof(Cell));
	filled_length -= 1;

}

void read_from_file(Vector* vector, char* filename) {
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

Cell Vector::get_cell(size_t index) {
	// returns cell by the index
	return data[index];
}

size_t Vector::amount_of_words() {
	return filled_length;
}

size_t Vector::find_cell(char* query, size_t length) {
	/// <summary>
	/// convinient wrapper for Vector::search function
	/// </summary>
	/// <param name="query"></param>
	/// <param name="length"></param>
	/// <returns></returns>
	return search(query,length,0,filled_length-1);
}