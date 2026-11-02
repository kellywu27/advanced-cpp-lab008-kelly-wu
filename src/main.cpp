// created a main.cpp to fix error
#include <iostream>

#include "project/binary_search_tree.h"

int main() {
    BinarySearchTree tree;
    for (int value : {50, 30, 70, 20, 40, 60, 80}) {
        tree.insert(value);
    }

    std::cout << "In order:";
    for (int value : tree.inorderTraversal()) {
        std::cout << ' ' << value;
    }
    std::cout << "\nSize: " << tree.size() << "\nHeight: " << tree.height() << '\n';
    return 0;
}