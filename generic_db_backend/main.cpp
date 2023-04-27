
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <filesystem>
//#include "rapidjson/document.h"


namespace fs = std::__fs::filesystem;


void addDocument();
void deleteDocument();
void addCollection();
void getCollectionList(std::vector<std::string>& collectionList);
std::string get_file_name(const std::string& file_path);


int main() {
    int option;


    std::cout << "** GenericDB **" << std::endl;
    std::cout << "Choose from the following operations" << std::endl;
    std::cout << "1. Add a document to the database" << std::endl;
    std::cout << "2. Delete a document from the database" << std::endl;
    std::cout << "3. Create a collection" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "Enter option: ";
    std::cin >> option;

    switch(option){
        case(1): addDocument(); break;
        case(2): deleteDocument(); break;
        case(3): addCollection(); break;
    }
    
}

void addDocument() {
    std::cout << "Enter a file path to add to database" << std::endl;
    std::string filepath;
    std::cin >> filepath;

    std::cout << filepath << std::endl;
    std::ifstream inputfile(filepath);

    std::vector<std::string> collectionList;
    getCollectionList(collectionList);

    if(collectionList.size() == 0) {
        std::cout << "No collections found. Must insert a document into a collection." << std::endl;
        addCollection();
    }
    
    std::string collectionChoice;

    std::cout << "Select one of the following collections to insert document into." << std::endl;
    for(unsigned int i =0; i < collectionList.size(); ++i) {
        std::cout << collectionList.at(i) << " ";
    }
    std::cout << "\n\n";
    std::cin >> collectionChoice;

    // std::cout << file.is_open() << std::endl;
    std::string filename = get_file_name(filepath);
    std::ofstream fout("./db/" + collectionChoice + "/" + filename);

    std::string line;
    while (getline(inputfile, line)) {
        fout << line << std::endl;
    }
}

void deleteDocument() {
    std::cout << "Enter the file to delete from database (ex: test.json)" << std::endl;
    std::string filepath;
    std::cin >> filepath;
    
    std::string filepathFormat = "./db/" + filepath;

    const char* file = filepathFormat.c_str();

    if (std::remove(file) != 0) {
        // If the file deletion fails, print an error message
        std::perror("Error deleting file");
    }
    else{
        std::printf("File deleted successfully\n");
    }

}

/*
Allows user to add collections to the database (db) file.
*/
void addCollection() {
    std::string collectionname;

    std::cout << "Enter a name for the new collection: ";
    std::cin >> collectionname;

    std::string parent_directory_path = "./db";

    std::string new_collection_path = parent_directory_path + "/" + collectionname;

    if (mkdir(new_collection_path.c_str(), 0777) == -1) {
        std::cerr << "Error creating directory!\n";
        exit(1);
    }

    std::cout << "Collection created successfully!" << std::endl;
}

/* 
Extracts file name from PATH url via string manipulation.
Ex. file_path = /Users/alishaikh/Desktop/test.json
RETURNS: test.json
*/
std::string get_file_name(const std::string& file_path) {
  size_t last_slash_index = file_path.find_last_of("/\\");
  if (last_slash_index == std::string::npos) {
    return file_path;
  }
  return file_path.substr(last_slash_index + 1);
}

/*
Populates pass by reference vector with list of all collections in the database.
*/
void getCollectionList(std::vector<std::string>& collectionList) {
    fs::path path_to_dir("./db");
     for (const auto& entry : fs::directory_iterator(path_to_dir))
    {
        if (entry.is_directory())
        {
             collectionList.push_back(entry.path().filename().string());
        }
    }
}

void getFileList (std::vector<std::string>& fileList, const std::string& collectionName){

}
/**
 * Search database for contents given file and collection name
 * 1. Display all existing collections to chose from 
 * 2. Display all files in collection to chose from 
 * 3. Search for content in file 
*/
void searchDatabase(){
    std::string collectionName;
    std::vector<std::string> collectionList;

    std::cout << "Here are all the avaliable collections: ";
    getCollectionList(collectionList); 

    for (unsigned int i =0; i < collectionList.size(); i++){
        std::cout << collectionList.at(i) << " "; 
    }
    std::cout << "Here are a list of files under that collection: "; 

    std::cout << "Enter a name of the collection searching for: ";
    std::cin >> collectionName;

}