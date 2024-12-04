#include "FileAVL.hpp"
#include "File.hpp"
#include <iostream>

// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */
std::vector<File*> FileAVL::query(size_t min, size_t max) {
    //making sure that we got our range set so we are looking for files in the correct range [smallest -largest]
    if (min > max) {
        size_t temp = min;
        min = max;
        max = temp;
    }
    //this will hold all the files that fall in the range
    std::vector<File*> result;

    // Your code here.
    //traversing the tree and adding all the files that fall in the range to the result vector
    result = queryHelper(root, min, max, result);
    //returning the result vector
    return result;
}
//helper function for query
std::vector<File*> FileAVL::queryHelper(Node* node, size_t min, size_t max, std::vector<File*> result) {
    //base case if the node is null return the result vector
    if (node == nullptr) {
        return result;
    }
    //if the node's size is less than the min then we know that all the files in the left subtree are less than the min so we can just go right
    if (node->file->getSize() < min) {
        result = queryHelper(node->right, min, max, result);
    }
    //if the node's size is greater than the max then we know that all the files in the right subtree are greater than the max so we can just go left
    else if (node->file->getSize() > max) {
        result = queryHelper(node->left, min, max, result);
    }
    //if the node's size is in the range then we add it to the result vector and then go both left and right
    else {
        result.push_back(node->file);
        result = queryHelper(node->left, min, max, result);
        result = queryHelper(node->right, min, max, result);
    }
    return result;
}

int main( ) {
    
    std::cout<<"hello world"<<std::endl;
    return 0;
}