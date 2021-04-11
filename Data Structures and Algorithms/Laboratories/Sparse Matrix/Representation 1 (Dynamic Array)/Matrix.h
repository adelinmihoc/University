#pragma once

#include <tuple>

typedef int TElem;
#define NULL_TELEM 0


struct Triple {
    int line;
    int column;
    TElem value;

    Triple() {
        this->line = -1;
        this->column = -1;
        this->value = 0;
    }

    friend bool operator < (const Triple & obj1, const Triple & obj2) {
        return std::tie(obj1.line, obj1.column) < std::tie(obj2.line, obj2.column);
    }

    friend bool operator > (const Triple & obj1, const Triple & obj2) {
        return std::tie(obj1.line, obj1.column) > std::tie(obj2.line, obj2.column);
    }

    friend bool operator == (const Triple & obj1, const Triple & obj2) {
        return std::tie(obj1.line, obj1.column) == std::tie(obj2.line, obj2.column);
    }

    friend bool operator <= (const Triple & obj1, const Triple & obj2) {
        return std::tie(obj1.line, obj1.column) <= std::tie(obj2.line, obj2.column);
    }

    friend bool operator >= (const Triple & obj1, const Triple & obj2) {
        return std::tie(obj1.line, obj1.column) >= std::tie(obj2.line, obj2.column);
    }
};


class Matrix {
private:
    Triple* matrix;
    int size;
    int capacity{};
    int no_of_lines;
    int no_of_columns;
    void resize();
    static int binarySearch(Triple arr[], int left, int right, Triple x);

public:
    //constructor
    Matrix(int nrLines, int nrCols);

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

};
