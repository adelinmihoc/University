#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    // Complexity: Theta(1)
    this->no_of_lines = nrLines;
    this->no_of_columns = nrCols;
    this->root = nullptr;
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
    // Complexity: O(n)
    Triple t = Triple{i, j, NULL_TELEM};
	Node* current_node = root;
	bool found = false;
	while(current_node != nullptr && !found) {
	    if (current_node->information == t) {
	        t = current_node->information;
	        found = true;
	    } else if (current_node->information < t) {
            current_node = current_node->right_child;
	    } else {
            current_node = current_node->left_child;
	    }
	}
	return t.value;
}


TElem Matrix::modify(int i, int j, TElem e) {
    // Complexity: O(n)
    if (i < 0 || i > no_of_lines || j < 0 || j > no_of_columns) {
        throw std::exception();
    }
    if (e != NULL_TELEM) { // so adding or update
        // Complexity: O(n)
        Triple t = Triple{i, j, e};
        Node *new_node = new Node{t, nullptr, nullptr};
        if (root == nullptr) {
            root = new_node;
            return NULL_TELEM;
        } else { // search for it
            Node* current_node = root;
            while (current_node != nullptr) {
                if (current_node->information == t) {
                    TElem previous = current_node->information.value;
                    current_node->information = t; // we found it so just update
                    return previous;
                } else if (current_node->information < t) {
                    if (current_node->right_child == nullptr) {
                        // need to add to the right child of the current node
                        current_node->right_child = new_node;
                        return NULL_TELEM;
                    } else {
                        current_node = current_node->right_child;
                    }
                } else {
                    if (current_node->left_child == nullptr) {
                        current_node->left_child = new_node;
                        return NULL_TELEM;
                    } else {
                        current_node = current_node->left_child;
                    }
                }
            }
        }
    } else  { // so removing
        // Complexity: O(n)
        Triple t = Triple{i,j,e};
        if (root == nullptr) {
            return NULL_TELEM;
        }

        if (root != nullptr) {
            if (root->information == t) {
                t = root->information;
                // case 1
                if (root->left_child == nullptr && root->right_child == nullptr) {
                    root = nullptr;
                    return t.value;
                }
                // case 2
                if (root->left_child != nullptr && root->right_child == nullptr) {
                    Node* root_copy = root;
                    root = root->left_child;
                    delete root_copy;
                    return t.value;
                }
                if (root->left_child == nullptr && root->right_child != nullptr) {
                    Node* root_copy = root;
                    root = root->right_child;
                    delete root_copy;
                    return t.value;
                }
                // case 3
                if (root->left_child != nullptr && root->right_child != nullptr) {
                    Node *minimum_node = root->right_child;
                    while (minimum_node->left_child != nullptr) {
                        minimum_node = minimum_node->left_child;
                    }
                    Node* root_copy = root;
                    root = minimum_node;
                    delete root_copy;
                    delete minimum_node;
                    return t.value;
                }
            }
        }

        Node* current_node = root;
        Node* previous_node = nullptr;
        while (current_node != nullptr) {
            if (current_node->information == t) {
                // remove this - 3 cases
                // case 1: has no descendant
                if (current_node->right_child == nullptr && current_node->left_child == nullptr) {
                    if (previous_node->left_child == current_node) {
                        previous_node->left_child = nullptr;
                        t = current_node->information;
                        delete current_node;
                        return t.value;
                    } else if (previous_node->right_child == current_node) {
                        previous_node->right_child = nullptr;
                        t = current_node->information;
                        delete current_node;
                        return t.value;
                    }
                }
                // case 2: has one descendant
                // the descendant is left child
                if (current_node->right_child == nullptr && current_node->left_child != nullptr) {
                    if (previous_node->left_child == current_node) {
                        previous_node->left_child = current_node->left_child;
                        t = current_node->information;
                        delete current_node;
                        return t.value;
                    } else if (previous_node->right_child == current_node) {
                        previous_node->right_child = current_node->left_child;
                        t = current_node->information;
                        delete current_node;
                        return t.value;
                    }
                }
                // the descendant is the right child
                if (current_node->right_child != nullptr && current_node->left_child == nullptr) {
                    if (previous_node->left_child != nullptr) {
                        if (previous_node->left_child == current_node) {
                            previous_node->left_child = current_node->right_child;
                            t = current_node->information;
                            delete current_node;
                            return t.value;
                        }
                    }
                    if (previous_node->right_child != nullptr) {
                        if (previous_node->right_child == current_node) {
                            previous_node->right_child = current_node->right_child;
                            t = current_node->information;
                            delete current_node;
                            return t.value;
                        }
                    }
                }
                // case 3: has two descendants
                if (current_node->right_child != nullptr && current_node->left_child != nullptr) {
                    //find the minimum of the right subtree
                    Node* minimum_node = current_node->right_child;
                    while (minimum_node->left_child != nullptr) {
                        minimum_node = minimum_node->left_child;
                    }
                    t = current_node->information;
                    current_node = minimum_node;
                    delete minimum_node;
                    return t.value;
                }
            } else if (current_node->information < t){
                previous_node = current_node;
                current_node = current_node->right_child;
            } else {
                previous_node = current_node;
                current_node = current_node->left_child;
            }
        }
        // if we ended up her it means there is no element to be removed
        return t.value;
    }
    return NULL_TELEM;
}
