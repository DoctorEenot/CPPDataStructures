#include "Vector.h"
#include <stdlib.h>
#include <string.h>


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
	memcpy(buffer,data,sizeof(Cell)*filled_length);
	free(data);
	data = buffer;
}



size_t Vector::search(char* query, size_t length) {
	/// <summary>
	///		Searches for Cell, where Cell.word == query
	/// </summary>
	/// <param name="query"></param>
	/// <param name="length"></param>
	/// <returns>
	/// Cell index
	/// </returns>
	size_t to_return = 0;
	bool found = false;
	for (to_return; to_return < filled_length; to_return++) {
		if (data[to_return].length != length) {
			continue;
		}
		found = true;
		for (unsigned int i = 0; i < length; i++) {
			if (query[i] != data[to_return].word[i]) {
				found = false;
				break;
			}
		}
		if (found) {
			return to_return;
		}
	}
	return to_return;
}

void Vector::insert(char* input, size_t length) {
	/// <summary>
	///		inserts input string into vector
	///		if no entry with string found
	///		creates new Cell into vector
	///		if input is already in vector
	///		increases Cell.occurrences by 1
	/// </summary>
	/// <param name="input"></param>
	/// <param name="length"></param>
	
	size_t cell_index = search(input,length);
	if (cell_index == filled_length) {
		if (filled_length == actual_length) {
			enlarge();
		}
		data[filled_length].word = (char*)malloc(length);
		data[filled_length].length = length;
		data[filled_length].occurrences = 1;
		memcpy(data[filled_length].word, input, length);
		filled_length += 1;
	}
	else {
		data[cell_index].occurrences += 1;
	}
}

void Vector::remove(char* input, size_t length) {
	/*
	removes cell from vector
	searches it by the input string
	*/
	size_t cell_index = search(input, length);
	if (cell_index == filled_length) {
		return;
	}
	delete &data[cell_index];

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