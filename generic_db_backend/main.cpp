#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
namespace fs = std::__fs::filesystem;

void addDocument();
void deleteDocument();
void createDocument();
void addCollection();

void getCollectionList(std::vector<std::string> &collectionList);
std::string get_file_name(const std::string &file_path);
void getFileList(std::vector<std::string> &fileList, const std::string &collectionName);
void searchDatabase();
void updateDocument();
void searchParameter();
void handleSearchRequest(const std::string &, const std::vector<std::string> &, const std::string &);
void viewCurrCollectAndFiles();

int main()
{
    int option;

    bool displayMenu = true;

    while (displayMenu)
    {
        std::cout << "\n** GenericDB **" << std::endl;
        std::cout << "Choose from the following operations:" << std::endl;
        std::cout << "1. Add a document to the database" << std::endl;
        std::cout << "2. Delete a document from the database" << std::endl;
        std::cout << "3. Create a collection" << std::endl;
        std::cout << "4. Search for file in collection" << std::endl;
        std::cout << "5. Search for a specific parameter" << std::endl;
        std::cout << "6. Create a document" << std::endl;
        std::cout << "7. Update a document" << std::endl;
        std::cout << "8. View current collections and files" << std::endl;
        std::cout << "20. Exit" << std::endl;
        std::cout << "......................................." << std::endl;
        std::cout << "Enter option: ";
        std::cin >> option;
        std::cout << "\n\n";

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
            searchParameter();
            break;
        case (6):
            createDocument();
            break;
        case (7):
            updateDocument();
            break;
        case (8):
            viewCurrCollectAndFiles();
            break;
        case (20):
            displayMenu = false;
            break;
        default:
            std::cout << "Unrecognized choice. Try again and input another number." << std::endl
                      << std::endl;
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

    /**
     * 2 ways to add: (if already in program --> can just upload name of file),
     * or add actual pathway to file on computer
     */
    std::cout << "Enter a file path to add to database: ";
    std::string filepath;
    std::cin >> filepath;

    std::cout << "\nThe file name or path that you've entered: ";
    std::cout << filepath << std::endl;

    // checking for correct file extension (.json)
    if (filepath.find(".json") != std::string::npos)
    {
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
    else 
    {
        std::cout << "\nThat was not a JSON file! Please upload JSON files only with the .json extension included." << std::endl;
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

    std::cout << "Collection created successfully!" << std::endl
              << std::endl;
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

    std::cout << "Here are all the available collections: ";
    getCollectionList(collectionList);
    for (unsigned int i = 0; i < collectionList.size(); i++)
    {
        std::cout << collectionList.at(i) << " ";
    }
    std::cout << "\n\n";

    std::cout << "Enter a name of the collection searching for: ";
    std::cin >> collectionName;

    std::cout << "Here are a list of files under that collection: \n\n";
    getFileList(filesInCollection, collectionName);

    std::cout << "\nSelect a file to view (without the quotation marks): ";
    std::cin >> fileName;

    //\generic_db_backend\db\searchFile\test.json

    pathToFileName = "./db/" + collectionName + "/" + fileName + ".json";

    std::ifstream file(pathToFileName);
    // file.open(pathToFileName, std::fstream::in);
    if (!file)
    {
        std::cout << "Error opening file. Check again if there are any contents in the file, if the file exists, or if it's a json file.\n";
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

    std::cout << "Enter the contents of the JSON document (type END on a new line to finish):" << std::endl;
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

    std::cout << "\nEnter a filename for the JSON file: ";
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
    std::cout << "\n\nSelect one of the following collections to insert document into.\n";
    std::cout << "Here are the current collections in our database:\n\n";

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

void updateDocument()
{
    std::string collectionName;
    std::string fileName;
    std::string pathToFileName;
    std::string line;
    std::vector<std::string> collectionList;
    std::vector<std::string> filesInCollection;

    std::cout << "First, we must locate the document to update.\n";
    getCollectionList(collectionList);
    if (collectionList.size() == 0)
    {
        std::cout << "No collections found. Please create a collection and document first.\n\n";
        return;
    }
    else
    {
        std::cout << "Here are all the available collections: \n";
        for (unsigned int i = 0; i < collectionList.size(); i++)
        {
            std::cout << collectionList.at(i) << " ";
        }
        std::cout << "\n\n";

        std::cout << "Enter the collection that the document is stored in: ";
        std::cin >> collectionName;

        std::cout << "Here are a list of files under that collection:\n";
        getFileList(filesInCollection, collectionName);

        std::cout << "Select a file to view/update: ";
        std::cin >> fileName;

        pathToFileName = "./db/" + collectionName + "/" + fileName + ".json";
        std::ifstream file(pathToFileName);
        if (!file)
        {
            std::cout << "Error opening file\n";
        }

        while (getline(file, line))
        {
            std::cout << line << std::endl;
        }
        std::cout << "Enter the new text for the document (type END on a new line to finish): \n";
        std::string json;
        std::string input_line;
        while (std::getline(std::cin, input_line))
        {
            if (input_line == "END")
            {
                break;
            }
            if (!json.empty())
            {
                json += '\n';
            }
            json += input_line;
        }
        std::cout << "\n\n";
        std::ofstream fout(pathToFileName);
        fout << json;
        fout.close();
    }
}

void searchParameter()
{
    std::string collectionName;
    std::string fileName;
    std::string pathToFileName;
    std::string line;
    std::vector<std::string> collectionList;
    std::vector<std::string> filesInCollection;
    std::string parameter;

    std::cout << "First, we must locate the document to update.\n";
    getCollectionList(collectionList);
    if (collectionList.size() == 0)
    {
        std::cout << "No collections found. Please create a collection and document first.\n\n";
        return;
    }

    std::cout << "Here are all the available collections: \n";
    for (unsigned int i = 0; i < collectionList.size(); i++)
    {
        std::cout << collectionList.at(i) << " ";
    }
    std::cout << "\n\n";

    std::cout << "Enter the collection that the document is stored in: ";
    std::cin >> collectionName;

    std::cout << "Here are a list of files under that collection:\n";
    getFileList(filesInCollection, collectionName);

    std::cout << "Select a file to search (without the quotation marks included): ";
    std::cin >> fileName;
    pathToFileName = "./db/" + collectionName + "/" + fileName + ".json";
    std::ifstream file(pathToFileName);
    if (!file)
    {
        std::cout << "Error opening file\n";
    }

    std::cout << "\n\n";

    std::cout << "Enter parameter you would like to search for: (ex. employee.name)" << std::endl;
    std::cin >> parameter;
    std::vector<std::string> paramList;

    std::istringstream iss(parameter);
    std::string substring;
    while (std::getline(iss, substring, '.'))
    {
        paramList.push_back(substring);
    }

    handleSearchRequest(parameter, paramList, pathToFileName);
}

void handleSearchRequest(const std::string &param, const std::vector<std::string> &paramList, const std::string &pathToFile)
{
    std::ifstream ifs(pathToFile);

    json j = json::parse(ifs);

    for (int i = 0; i < paramList.size(); ++i)
    {
        if (j.contains(paramList.at(i)))
        {
            j = j[paramList.at(i)];
        }
        else
        {
            std::cout << "could not find parameter" << std::endl;
            return;
        }
    }

    std::cout << "\n\n";
    std::cout << "FOUND!" << std::endl;
    std::cout << param << ": " << j << std::endl;
    std::cout << "\n\n";
}

/**
 * function that displays all the current collections
 * also displays any files that resides within those collections
 * if no collections exist --> an error will occur
 */
void viewCurrCollectAndFiles()
{
    std::vector<std::string> collectionList;
    getCollectionList(collectionList);

    if (collectionList.size() != 0) // when there are collections that exist
    {
        std::cout << "Here are the current collections and files that reside within them: " << std::endl;

        // outputs all existing collections separated by a newline
        for (unsigned int i = 0; i < collectionList.size(); ++i)
        {
            std::vector<std::string> filesInCurrCollection;

            std::cout << "Collection Name: " << collectionList.at(i) << std::endl;

            std::cout << "Files in " << collectionList.at(i) << ": ";
            getFileList(filesInCurrCollection, collectionList.at(i));

            std::cout << "\n\n";
        }
    }
    else // executes when there's no collections or files
    {
        std::cout << "There are currently no existing collections or files." << std::endl;
        std::cout << "Please create some collections and files before trying this option again!" << std::endl;
    }
}