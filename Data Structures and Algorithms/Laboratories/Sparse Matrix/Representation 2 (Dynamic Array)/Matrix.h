#pragma once

typedef int TElem;
#define NULL_TELEM 0


struct ColumnValue {
    int column;
    TElem value;

    ColumnValue() {
        column = -1;
        value = 0;
    }

    friend bool operator < (ColumnValue & obj1, ColumnValue & obj2) {
        return obj1.column < obj2.column;
    }

    friend bool operator > (ColumnValue & obj1, ColumnValue & obj2) {
        return obj1.column > obj2.column;
    }

    friend bool operator == (ColumnValue & obj1, ColumnValue & obj2) {
        return obj1.column == obj2.column;
    }

    friend bool operator <= (ColumnValue & obj1, ColumnValue & obj2) {
        return obj1.column <= obj2.column;
    }

    friend bool operator >= (ColumnValue & obj1, ColumnValue & obj2) {
        return obj1.column >= obj2.column;
    }
};


class Matrix {
private:
    int no_of_lines;
    int no_of_columns;
    int lines_size;
    int* lines_array;
    int columnValue_size;
    int columnValue_capacity;
    ColumnValue* columnValue_array;
    void resize_columnValue_array();
    static int binarySearchColumnValue(ColumnValue *array, int left, int right, ColumnValue element);
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
