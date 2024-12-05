#include "FileAVL.hpp"
#include "File.hpp"
#include <iostream>

inline void helpPushBack(std::vector<File*>& files, std::vector<File*>& result) {
    
}

inline void iterateInOrder(Node* root, std::vector<File*>& result , size_t min, size_t max) {
    //i would need the min and max because that is how we are gonna be able to determine what values will get added to the result
    //empty tree/base case/ no node to iterate
    if (root == nullptr) {
        return;
    }
    //recur left
    iterateInOrder(root->left_, result, min, max);
    //check if the current node size is in range
    std::cout<<"we are checking the root node now"<<std::endl;
    if(root->size_ >= min && root->size_ <= max) {
        //call a helper function with the parameters of the current node pointing to the files  and the result vector. 
        std::cout<<"we are about to call the helpPushBack function"<<std::endl;
        helpPushBack( root -> files_, result);
    }
    else{
        std::cout<<"the root node is not in range"<<std::endl;
    }
    //recur right
    iterateInOrder(root->right_, result, min, max);

}

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
    std::vector<File*> result;
    //because query is a member of the FILEAVL we got access to the node ptr and can send it to our helper function. 

    if (min > max) {
        //do post order traversal
    }
    else {
        //do in-order traversal
        std::cout<<"we are about to call the iterateInOrder function"<<std::endl;
        iterateInOrder( root_ , result , min , max);
    }

    return result;
}


int main() {
    std::cout << "Starting the main function." << std::endl;
    FileAVL tree;
    File firstFile;
    File secondFile( "hello.world" , "something");
    File thirdFile( "Bye.world" , "Kendrick Lamar");
    File fourthFile( "Hola.mundo" , "J.cole");
    File fifthFile( "Adios.mundo" , "Smi");
    File sixthFile( "Hello.mundo" , "Jhnathan43");
    File seventhFile("we.you" , "244gf");
    File * firstFilePtr = &firstFile;
    File * secondFilePtr = &secondFile;
    File * thirdFilePtr = &thirdFile;
    File * fourthFilePtr = &fourthFile;
    File * fifthFilePtr = &fifthFile;
    File * sixthFilePtr = &sixthFile;
    File * seventhFilePtr = &seventhFile;
    Folder1.push_back(firstFilePtr);
    Folder1.push_back(secondFilePtr);
    Folder2.push_back(thirdFilePtr);
    Folder2.push_back(fourthFilePtr);
    Folder2.push_back(fifthFilePtr);

    tree.insert(firstFilePtr);
    tree.insert(secondFilePtr);
    tree.insert(thirdFilePtr);
    tree.insert(fourthFilePtr);
    tree.insert(fifthFilePtr);
    tree.insert(sixthFilePtr);
    tree.insert(seventhFilePtr);
    tree.displayInOrder();
    tree.displayLevelOrder();

    // using the query function
    // std::vector<File*> result = tree.query(2,4);
    // for (auto file : result) {
    //     std::cout << file << std::endl;
    // }

    return 0;
}
