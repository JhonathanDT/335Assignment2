#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp"
#include <iostream>

inline void helpPushBack(std::vector<File*>& files, std::vector<File*>& result) {
    //we need to insert all files from the files vector into the result vector
    for (auto& file : files) {
        result.push_back(file);
    }
    // std::cout<<"we have successfully pushed back all the files"<<std::endl;
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
    // std::cout<<"we are checking the root node now"<<std::endl;
    if(root->size_ >= min && root->size_ <= max) {
        //call a helper function with the parameters of the current node pointing to the files  and the result vector. 
        // std::cout<<"we are about to call the helpPushBack function"<<std::endl;
        helpPushBack( root -> files_, result);
    }
    // else{
    //     std::cout<<"the root node is not in range"<<std::endl;
    // }
    //recur right
    iterateInOrder(root->right_, result, min, max);

}

inline void iteratePostOrder( Node* root, std::vector<File*>& result, size_t min, size_t max) {
    //empty tree/base case/ no node to iterate
    if (root == nullptr) {
        return;
    }
    //recur left
    iteratePostOrder(root->left_, result, min, max);
    //recur right
    iteratePostOrder(root->right_, result, min, max);
    //check if the current node size is in range
    if(root->size_ >= min && root->size_ <= max) {
        //call a helper function with the parameters of the current node pointing to the files  and the result vector. 
        helpPushBack( root -> files_, result);
    }
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
        // std::cout<< "the min is greater than the max.Calling the Post Order" <<std::endl;
        iteratePostOrder( root_ , result , max , min);
    }
    else {
        //do in-order traversal
        // std::cout<<"we are about to call the iterateInOrder function"<<std::endl;
        iterateInOrder( root_ , result , min , max);
    }

    return result;
}

//we will need to first make all letters of the filename lowercase and then we will need to split the string by the '.' character and then we will need to add the file to the fileTrie
void FileTrie::addFile(File* file) {
    std::cout<<"we are adding a file to the fileTrie"<<std::endl;
    std::string name = file->getName();
    for (auto& x : name) { 
        x = tolower(x); 
    } 
    //success at changing to lower case
    std::cout << name;
    //create the root node 
    FileTrieNode* curr = head;
    //iterate through the Trie tree
    for( auto& c : name){
        if( curr->next[c] == nullptr){
            //if a node for current character does not exist make a new node
            FileTrieNode* newNode = new FileTrieNode(); 
            curr->next[c] = newNode;
        }
        curr = curr->next[c];
    }
}
//to test use the matching and the stored and map to see what files are accurateley falling in the nodes. 
FileTrie::FileTrie() {
    head = new FileTrieNode();
}
FileTrie::~FileTrie() {
    std::cout << "Deleting the fileTrie" << std::endl;
    delete head;
}

int main() {
    std::cout << "Starting the main function." << std::endl;
    // FileAVL tree;
    std::vector<File> fileObjects = {
        {"document1.txt", "This is the content of document1."},
        {"image1.png", "Binary data representing an image."},
        {"script1.js", "console.log('Hello, World!');"},
        {"spreadsheet1.xlsx", "Placeholder data for an Excel file."},
        {"presentation1.pptx", "Slide deck information goes here."},
        {"config1.ini", "[Settings]\noption=true"},
        {"data1.csv", "Name, Age, City\nAlice, 30, New York\nBob, 25, Boston"},
        {"archive1.zip", "Compressed archive of files."},
        {"readme.md", "# Read Me\nThis is a markdown file."},
        {"program1.cpp", "#include <iostream>\nint main() { std::cout << \"Hello\"; return 0; }"},
        {"style1.css", "body { background-color: #f0f0f0; }"},
        {"index.html", "<!DOCTYPE html>\n<html>\n<head><title>Page</title></head>\n<body>Content</body>\n</html>"},
        {"audio1.mp3", "Binary data for an audio file."},
        {"video1.mp4", "Binary data for a video file."},
        {"log1.log", "2024-12-05 10:00:00 INFO Starting application."},
        {"script2.py", "print('Python script example')"},
        {"notes1.rtf", "Rich Text Format notes with styling."},
        {"database1.db", "Binary data for an SQLite database."},
        {"vector1.svg", "<svg xmlns='http://www.w3.org/2000/svg' width='100' height='100'><circle cx='50' cy='50' r='40' /></svg>"},
        {"report1.pdf", "Binary data for a PDF document."},
        {"config2.json", "{\"setting1\": true, \"setting2\": 42}"},
        {"game1.exe", "Binary executable for a game."},
        {"script3.sh", "#!/bin/bash\necho 'Shell script example'"},
        {"notes2.docx", "Placeholder content for a Word document."},
        {"diagram1.dwg", "Binary data for an AutoCAD diagram."},
        {"font1.ttf", "Binary data for a TrueType font."},
        {"backup1.tar", "Compressed tarball of backup files."},
        {"template1.dotx", "Template for a Word document."},
        {"spreadsheet2.ods", "OpenDocument spreadsheet data."},
        {"project1.gradle", "buildscript { repositories { mavenCentral() } }"}
    };
    
    File* fifthFilePtr = &fileObjects[4];
    File* firstFilePtr = &fileObjects[0];
    // File* secondFilePtr = new File(fileObjects[1]);
    // File* thirdFilePtr = new File(fileObjects[2]);
    // File* fourthFilePtr = new File(fileObjects[3]);
    // File* sixthFilePtr = new File(fileObjects[5]);
    
    FileTrie firstTrie;
    firstTrie.addFile(firstFilePtr);

    return 0;
}
