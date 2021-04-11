#pragma once

typedef int TElem;
#define NULL_TELEM 0


struct Triple {
    int line;
    int column;
    TElem value;
    friend bool operator<(Triple t1, Triple t2) {
        if (t1.line < t2.line) {
            return true;
        } else if (t1.line > t2.line) {
            return false;
        } else {
            return t1.column < t2.column;
        }
    }
    friend bool operator>(Triple t1, Triple t2) {
        if (t1.line > t2.line) {
            return true;
        } else if (t1.line < t2.line) {
            return false;
        } else {
            return t1.column > t2.column;
        }
    }
    friend bool operator==(Triple t1, Triple t2) {
        return (t1.line == t2.line && t1.column == t2.column);
    }
};

struct Node {
    Triple information;
    Node* left_child;
    Node* right_child;
};

class Matrix {
private:
    Node* root;
    int no_of_lines;
    int no_of_columns;
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
