
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <filesystem>
#include <algorithm>

namespace fs = std::__fs::filesystem;

void addDocument();
void deleteDocument();
void createDocument();
void addCollection();

void getCollectionList(std::vector<std::string> &collectionList);
std::string get_file_name(const std::string &file_path);
void getFileList(std::vector<std::string> &fileList, const std::string &collectionName);
void searchDatabase();

int main()
{
    int option;

    bool displayMenu = true;

    while(displayMenu) 
    {
        std::cout << "** GenericDB **" << std::endl;
        std::cout << "Choose from the following operations" << std::endl;
        std::cout << "1. Add a document to the database" << std::endl;
        std::cout << "2. Delete a document from the database" << std::endl;
        std::cout << "3. Create a collection" << std::endl;
        std::cout << "4. Search for file in collection" << std::endl;
        std::cout << "5. Create a document" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "Enter option: ";
        std::cin >> option;

        switch (option)
        {
        case (1):
            addDocument();
            break;
        case (2):
            deleteDocument();
            break;
        case (3):
            addCollection();
            break;
        case (4):
            searchDatabase();
            break;
        case (5):
            createDocument();
            break;
        }
    }
}

void addDocument()
{
    std::vector<std::string> collectionList;
    getCollectionList(collectionList);
    if (collectionList.size() == 0)
    {
        std::cout << "No collections found. Must insert a document into a collection." << std::endl;
        addCollection();
    }

    std::cout << "Enter a file path to add to database" << std::endl;
    std::string filepath;
    std::cin >> filepath;

    std::cout << filepath << std::endl;
    std::ifstream inputfile(filepath);

    std::string collectionChoice;

    std::cout << "Select one of the following collections to insert document into." << std::endl;
    for (unsigned int i = 0; i < collectionList.size(); ++i)
    {
        std::cout << collectionList.at(i) << " ";
    }
    std::cout << "\n\n";
    std::cin >> collectionChoice;

    // std::cout << file.is_open() << std::endl;
    std::string filename = get_file_name(filepath);
    std::ofstream fout("./db/" + collectionChoice + "/" + filename);

    std::string line;
    while (getline(inputfile, line))
    {
        fout << line << std::endl;
    }
}

void deleteDocument()
{
    std::cout << "Enter the file to delete from database (ex: [collectionname]/[filename])" << std::endl;
    std::string filepath;
    std::cin >> filepath;

    std::string filepathFormat = "./db/" + filepath;

    const char *file = filepathFormat.c_str();

    if (std::remove(file) != 0)
    {
        // If the file deletion fails, print an error message
        std::perror("Error deleting file");
    }
    else
    {
        std::printf("File deleted successfully\n");
    }
}

/*
Allows user to add collections to the database (db) file.
*/
void addCollection()
{
    std::string collectionname;

    std::cout << "Enter a name for the new collection: ";
    std::cin >> collectionname;

    std::string parent_directory_path = "./db";

    std::string new_collection_path = parent_directory_path + "/" + collectionname;

    if (mkdir(new_collection_path.c_str(), 0777) == -1)
    {
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
std::string get_file_name(const std::string &file_path)
{
    size_t last_slash_index = file_path.find_last_of("/\\");
    if (last_slash_index == std::string::npos)
    {
        return file_path;
    }
    return file_path.substr(last_slash_index + 1);
}

/*
Populates pass by reference vector with list of all collections in the database.
*/
void getCollectionList(std::vector<std::string> &collectionList)
{
    fs::path path_to_dir("./db");
    for (const auto &entry : fs::directory_iterator(path_to_dir))
    {
        if (entry.is_directory())
        {
            collectionList.push_back(entry.path().filename().string());
        }
    }
}

void getFileList(std::vector<std::string> &fileList, const std::string &collectionName)
{
    //  generic_db_backend\db\searchFile
    std::string pathToCollection = "./db/" + collectionName;
    for (auto &i : fs::directory_iterator(pathToCollection))
    {
        std::cout << i.path().filename() << std::endl;
    }
}

void printFileContent(const std::string fileName)
{
}
/**
 * Search database for contents given file and collection name
 * 1. Display all existing collections to chose from
 * 2. Display all files in collection to chose from
 * 3. Search for content in file
 */
void searchDatabase()
{
    std::string collectionName;
    std::string fileName;
    std::string pathToFileName;
    std::string line;
    std::vector<std::string> collectionList;
    std::vector<std::string> filesInCollection;

    std::cout << "Here are all the avaliable collections: ";
    getCollectionList(collectionList);
    for (unsigned int i = 0; i < collectionList.size(); i++)
    {
        std::cout << collectionList.at(i) << " ";
    }
    std::cout << "\n\n";

    std::cout << "Enter a name of the collection searching for: ";
    std::cin >> collectionName;

    std::cout << "Here are a list of files under that collection: ";
    getFileList(filesInCollection, collectionName);

    std::cout << "Select a file to view: ";
    std::cin >> fileName;

    //\generic_db_backend\db\searchFile\test.json

    pathToFileName = "./db/" + collectionName + "/" + fileName + ".json";

    std::ifstream file(pathToFileName);
    // file.open(pathToFileName, std::fstream::in);
    if (!file)
    {
        std::cout << "Error opening file\n";
    }

    while (getline(file, line))
    {
        std::cout << line << std::endl;
    }

    file.close();
}
void createDocument()
{
    std::string filename;
    std::string collectionChoice;

    std::cout << "Enter the contents of the JSON document (type END on a new line to finish)." << std::endl;
    std::string json;
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == "END")
        {
            break;
        }
        if (!json.empty())
        {
            json += '\n';
        }
        json += line;
    }

    std::cout << "Enter a filename for the JSON file: ";
    std::cin >> filename;
    filename = filename + ".json";

    std::vector<std::string> collectionList;
    getCollectionList(collectionList);

    if (collectionList.size() == 0)
    {
        std::cout << "No collections found. Please create a collection first.\n";
        addCollection();
        getCollectionList(collectionList);
    }
    std::cout << "Select a collection to store the file in." << std::endl;

    for (unsigned int i = 0; i < collectionList.size(); ++i)
    {
        std::cout << collectionList.at(i) << " ";
    }
    std::cout << "\n\n";
    while (1)
    {
        std::cin >> collectionChoice;
        if (std::find(collectionList.begin(), collectionList.end(), collectionChoice) != collectionList.end())
        {
            break;
        }
    }
    std::ofstream fout("./db/" + collectionChoice + "/" + filename);
    fout << json;
    fout.close();

    std::cout << "JSON file created successfully and stored in collection: " << collectionChoice << std::endl;
}
