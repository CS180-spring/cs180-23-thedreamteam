
#include <iostream>
#include <fstream>
#include <cstdio>
#include "./src/document.h"
#include "./src/collection.h"
#include "rapidjson/document.h"

void addDocument();
void deleteDocument();
std::string get_file_name(const std::string& file_path);

int main() {
    int option;
    std::cout << "** GenericDB **" << std::endl;
    std::cout << "Choose from the following operations" << std::endl;
    std::cout << "1. Add a document to the database" << std::endl;
    std::cout << "2. Delete a document from the database" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "Enter option: ";
    std::cin >> option;

    
    switch(option){
        case(1): addDocument(); break;
        case(2): deleteDocument(); break;
    }


}

void addDocument() {
    std::cout << "Enter a file path to add to database" << std::endl;
    std::string filepath;
    std::cin >> filepath;

    std::cout << filepath << std::endl;
    std::ifstream inputfile(filepath);

    // std::cout << file.is_open() << std::endl;
    std::string filename = get_file_name(filepath);
    std::ofstream fout("./db/" + filename);

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

/* Extracts file name from PATH url via string manipulation.
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


// int main() {

//     std::string dataInput1 = "This is a data input for CS180!";
//     Document doc1(dataInput1);

//     std::string dataInput2 = "What do you call a bagel that can fly? A plain bagel.";
//     Document doc2(dataInput1);

//     std::string dataInput3 = "This is tedious";
//     Document doc3(dataInput1);

//     std::string collectionName = "files";
//     Collection documentCollection(collectionName);

//     documentCollection.addDoc(dataInput1);
//     documentCollection.addDoc(dataInput2);
//     documentCollection.addDoc(dataInput3);

//     documentCollection.printDocs();




// }

