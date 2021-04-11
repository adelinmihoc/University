#include "Matrix.h"
#include <exception>


Matrix::Matrix(int nrLines, int nrCols) {
    // Complexity: theta(1)
    this->no_of_columns = nrCols;
    this->no_of_lines = nrLines;
    this->capacity = 2;
    this->size = 0;
    this->matrix = new Triple[this->capacity];
}


int Matrix::nrLines() const {
    // Complexity: theta(1)
    return this->no_of_lines;
}


int Matrix::nrColumns() const {
    // Complexity: theta(1)
    return this->no_of_columns;
}


TElem Matrix::element(int i, int j) const {
    // Complexity: O(log n)
    if (i < 0 || i > this->no_of_lines || j < 0 || j > no_of_columns) {
        throw std::exception();
    }

    Triple searchElement;
    searchElement.line = i;
    searchElement.column = j;

    int position = binarySearch(this->matrix, 0, this->size - 1, searchElement);
    if (position == -1) {
        return NULL_TELEM;
    }
    else {
        return this->matrix[position].value;
    }
}


TElem Matrix::modify(int i, int j, TElem e) { // this function does not remove elements because... :)
    // Complexity: // there can be an improvement in the best-case complexity (can be Theta(1)) NO NEED FOR SEARCH
    //             // if we check first if:
    //             // the new triple (i, j, e) is bigger than the last element, case in which we just add it at the end.
    //             // or if the matrix is empty.
    //             // (but ain't nobody got time for that)
    //      Best: O(log n) // if the element exists and only needs to be modified (just the search for it)
    //      Average: O(n)
    //      Worst: O(n) // if the element needs to be added
    if (i < 0 || i > this->no_of_lines || j < 0 || j > no_of_columns) {
        throw std::exception();
    }

    Triple searchElement;
    searchElement.line = i;
    searchElement.column = j;

    // Search for the element
    // Complexity: O(log n)
    int position = binarySearch(this->matrix, 0, this->size - 1, searchElement);

    if (position != -1) { // if the triple exists
        int previousValue = this->matrix[position].value;
        this->matrix[position].value = e;
        return previousValue;
    }
    else { // if the triple doesn't exist, add it
        if (this->size == this->capacity) {
            resize();
        }

        Triple element;
        element.line = i;
        element.column = j;
        element.value = e;

        // no elements in the matrix
        // Complexity: Theta(1)
        if (this->size == 0) {
            this->matrix[0] = element;
            this->size += 1;
            return NULL_TELEM;
        }

        // element needs to be in first position
        // Complexity: Theta(n)
        if (element < this->matrix[0]) {
            for (int l = 0; l < this->size; l++) {
                std::swap(this->matrix[l], element);
            }
            // element will be equal with the last element from matrix after swaps
            this->matrix[this->size] = element;
            this->size += 1;
            return NULL_TELEM;
        }

        // element needs to be in the last position
        // Complexity: Theta(1)
        if (element > this->matrix[this->size - 1]) {
            this->matrix[this->size] = element;
            this->size += 1;
            return NULL_TELEM;
        }

        // not first not last position
        // Complexity: Theta(n)
        for (int k = 1; k < this->size; k++) {
            if (element < this->matrix[k] && element > this->matrix[k - 1]) {
                for (int l = k; l < this->size; l++) {
                    std::swap(this->matrix[l], element);
                }
                // element will be equal with the last element from matrix after swaps
                this->matrix[this->size] = element;
                this->size += 1;
                return NULL_TELEM;
            }
        }
    }
}


void Matrix::resize() {
    // Complexity: theta(n)
    int new_capacity = this->capacity * 2;
    Triple* new_matrix;
    Triple* old_matrix;

    old_matrix = this->matrix;
    new_matrix = new Triple[new_capacity];

    for (int i = 0; i < this->capacity; i++) {
        new_matrix[i] = old_matrix[i];
    }

    delete[] this->matrix;
    this->matrix = new_matrix;
    this->capacity = new_capacity;
}


int Matrix::binarySearch(Triple *array, int left, int right, Triple element) {
    // Complexity: O(log n)
    if (left <= right) {
        int middle = left + (right - left) / 2;

        if (array[middle] == element) {
            return middle;
        }

        if (array[middle] > element) {
            return binarySearch(array, left, middle - 1, element);
        }

        return binarySearch(array, middle + 1, right, element);
    }

    return -1; // elem not in array
}
