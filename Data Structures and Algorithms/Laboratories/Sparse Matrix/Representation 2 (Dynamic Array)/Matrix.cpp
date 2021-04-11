#include "Matrix.h"
#include <exception>
#include <iostream>


Matrix::Matrix(int nrLines, int nrCols) {
    // Complexity: Theta(1)
    this->no_of_lines = nrLines;
    this->no_of_columns = nrCols;
    this->lines_size = nrLines + 1;
    this->lines_array = new int[this->lines_size]; // fixed sized array
    for (int i = 0; i < this->lines_size; i++) {
        this->lines_array[i] = 0; // all elements are NULL_TELEM that means no columnValues and no lines
    }
    this->columnValue_size = 0;
    this->columnValue_capacity = 2;
    this->columnValue_array = new ColumnValue[this->columnValue_capacity];
}


int Matrix::nrLines() const {
    // Complexity: Theta(1)
    return this->no_of_lines;
}


int Matrix::nrColumns() const {
    // Complexity: Theta(1)
    return this->no_of_columns;
}


TElem Matrix::element(int i, int j) const {
    // Complexity: Best-case: Theta(1)
    //             Average-case: O(log n)
    //             Worst-case: O(log n)
    /*if (i == 101 && j == 0) {
        std::cout << lines_array[i] << " " << lines_array[i + 1] << "\n";
        for (int k = lines_array[i]; k < lines_array[i + 1]; k++) {
            std::cout << columnValue_array[k].column << " " << columnValue_array[k].value << " \n";
        }
    }*/
    if (i < 0 || i > this->no_of_lines || j < 0 || j > this->no_of_columns) {
        throw std::exception();
    }

    //Complexity: Theta(1) no columns means no element
    if (this->lines_array[i] == this->lines_array[i + 1]) {
        return NULL_TELEM;
    }
    // calculate the position of the columnValue
    // Complexity: O(log n) n it's the number of actual saved columns from i row
    ColumnValue searchElement;
    searchElement.column = j;
    int columnValue_position = binarySearchColumnValue(this->columnValue_array, this->lines_array[i], this->lines_array[i + 1] - 1, searchElement);
    if (columnValue_position != -1) {
        // just get the element
        return this->columnValue_array[columnValue_position].value;
    }
    else {
        // element doesn't exist
        return NULL_TELEM;
    }
}


TElem Matrix::modify(int i, int j, TElem e) {
    // Complexity: hell knows
    if (i < 0 || i > this->no_of_lines || j < 0 || j > this->no_of_columns) {
        throw std::exception();
    }
    // if element exists just modify it
    if (element(i, j) != NULL_TELEM) {
        // modify it
        // search for it's column position
        ColumnValue searchElement;
        searchElement.column = j;
        int columnValue_position = binarySearchColumnValue(this->columnValue_array, this->lines_array[i],
                                                           this->lines_array[i + 1] - 1, searchElement);
        TElem previous = this->columnValue_array[columnValue_position].value;
        this->columnValue_array[columnValue_position].value = e; // modify
        return previous;
    }
    else {
        // needs to be added
        // shit
        if (this->columnValue_size == this->columnValue_capacity) { // some resize
            resize_columnValue_array();
        }
        // create new elementS
        ColumnValue new_element;
        new_element.column = j;
        new_element.value = e;
        // move all elements a position to the right starting from the next line
        // so for the columns for the current line we have an empty space (last one before the next line)
        for (int k = this->lines_array[i + 1] + 1; k < this->columnValue_size + 1; k++) {
            this->columnValue_array[k] = this->columnValue_array[k - 1];
        }
        // increase the size of the columnValue cos' of the permutation above
        this->columnValue_size += 1;
        // in the lines array simulate adding the new column (all values starting with the next line are increased by 1)
        for (int k = i + 1; k < this->lines_size; k++) {
            this->lines_array[k] += 1;
        }
        // search for the correct position in the columnValue array to add the new column
        // // // special case // // //
        // there are no other columns there
        if (this->lines_array[i + 1] - this->lines_array[i] == 1) {
            this->columnValue_array[this->lines_array[i]] = new_element;
        }
        // first case it needs to be the first column:
        if (new_element < this->columnValue_array[this->lines_array[i]]) {
            // swap 'em all
            for (int k = this->lines_array[i]; k < this->lines_array[i + 1]; k++) {
                std::swap(new_element, this->columnValue_array[k]);
            }
            return NULL_TELEM;
        }
        // second case it's the last column:
        if (new_element > this->columnValue_array[this->lines_array[i + 1] - 2]) { // -1 cos' of the pos in line arr and -1 again cos the actual last element is a copy of the first element in the next line cos' of the permutation
            // little swap
            std::swap(new_element, this->columnValue_array[this->lines_array[i + 1] - 1]);
            return NULL_TELEM;
        }
        // third case the new element needs to be added somewhere in the middle of the current columns
        // search for it
        for (int k = this->lines_array[i] + 1; k < this->lines_array[i + 1]; k++) {
            if (new_element > this->columnValue_array[k - 1] && new_element < this->columnValue_array[k]) {
                // so if position found swap the rest of the columns to put the element in place
                for (int l = k; l < this->lines_array[i + 1]; l++) {
                    std::swap(new_element, this->columnValue_array[l]);
                }
                return NULL_TELEM;
            }
        }
    }
    return NULL_TELEM;
}


void Matrix::resize_columnValue_array() {
    int new_capacity = 2 * this->columnValue_capacity;
    ColumnValue* new_array;
    ColumnValue* old_array;

    new_array = new ColumnValue[new_capacity];
    old_array = this->columnValue_array;

    for (int i = 0; i < this->columnValue_capacity; i++) {
        new_array[i] = old_array[i];
    }

    delete[] this->columnValue_array;
    this->columnValue_array = new_array;
    this->columnValue_capacity = new_capacity;
}


int Matrix::binarySearchColumnValue(ColumnValue *array, int left, int right, ColumnValue element) {
    // Complexity: O(log n)
    if (left <= right) {
        int middle = left + (right - left) / 2;

        if (array[middle] == element) {
            return middle;
        }

        if (array[middle] > element) {
            return binarySearchColumnValue(array, left, middle - 1, element);
        }

        return binarySearchColumnValue(array, middle + 1, right, element);
    }

    return -1; // elem not in array
}
