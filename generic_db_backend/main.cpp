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
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "colormod.h"

#include "Add.h"
#include "Essential.h"
#include "Search.h"

using json = nlohmann::json;
namespace fs = std::filesystem;


void deleteDocument();
void createDocument();


void getCollectionList(std::vector<std::string> &collectionList);
std::string get_file_name(const std::string &file_path);
void getFileList(std::vector<std::string> &fileList, const std::string &collectionName);
void searchDatabase();
void updateDocument();
void updateDocumentValue();
void searchParameter();
void viewCurrCollectAndFiles();
void searchParameter();
void handleSearchRequest(const std::string &param, const std::vector<std::string> &paramList, json &j);
void printCollections(const std::vector<std::string> &colList);
void filter();
std::vector<std::string> convertToParamList(std::string param);

// Color::Modifier green(Color::FG_GREEN);
// Color::Modifier magenta(Color::FG_MAGENTA);
// Color::Modifier yellow(Color::FG_YELLOW);
// Color::Modifier def(Color::FG_DEFAULT);

int main()
{
    int option;

    bool displayMenu = true;
    bool welcome = true;
    std::string subChoice;
    bool isEnterPressed = false;

    std::cout << "Welcome to GenericDB" << std::endl;
    std::cout << "Our database offered a number of features to try!" << std::endl;
    std::cout << "To try, press your 'enter' key to prompt the menu." << std::endl;
    std::cout << "From the menu, enter a number to access a feature." << std::endl;
    welcome = false;

    std::string line;
    std::getline(std::cin, line);

    if (line.empty())
    {
        isEnterPressed = true;
    }

    while (isEnterPressed && displayMenu)
    {
        std::cout << "\n** GenericDB **" << std::endl;
        std::cout << "......................................." << std::endl;
        std::cout << "Choose from the following operations:" << std::endl;
        std::cout << "1. Add a document or collection to the database" << std::endl;
        std::cout << "2. Delete a document from the database" << std::endl;
        std::cout << "3. Search the database or collection" << std::endl;
        std::cout << "4. Update a document or value" << std::endl;
        std::cout << "5. Create a document" << std::endl;
        std::cout << "6. View current collections and files" << std::endl;
        std::cout << "7. Filter a document" << std::endl;
        std::cout << "8. View file in database" << std::endl; 
        std::cout << "9. Exit" << std::endl;
        std::cout << "......................................." << std::endl;
        std::cout << "Enter option: ";
        std::cin >> option;
        std::cout << "\n\n";

        switch (option)
        {
        case (1):
            std::cout << "What would you like to add to the database?" << std::endl;
            std::cout << "......................................." << std::endl;
            std::cout << "Press your 'a' key: to add a document" << std::endl;
            std::cout << "Press your 'b' key: to add a database" << std::endl;
            std::cout << "......................................." << std::endl;
            std::cin >> subChoice;

            // adds a document to the database
            if (subChoice == "a")
            {
                addDocument();
            }
            else if (subChoice == "b") // adds a collection to the database
            {
                addCollection();
            }
            break;
        case (2):
            deleteDocument();
            break;
        case (3):
            std::cout << "Press your 'a' key: to keyword in the database" << std::endl; //make this view database file 
            std::cout << "Press your 'b' key: to search for a parameter in the database" << std::endl;
            std::cin >> subChoice;

            // searches the database
            if (subChoice == "a")
            {
                searchKeywordInCollections();
            }
            else if (subChoice == "b") // searches for a specific thing in the database
            {
                searchParameter();
            }

            break;
        case (4):
            std::cout << "Press your 'a' key: to update a document" << std::endl;
            std::cout << "Press your 'b' key: to update a document value" << std::endl;
            std::cin >> subChoice;

            // updates entire document
            if (subChoice == "a")
            {
                updateDocument();
            }
            else if (subChoice == "b") // updates a document val
            {
                updateDocumentValue();
            }
            break;
        case (5):
            createDocument();
            break;
        case (6):
            viewCurrCollectAndFiles();
            break;
        case (7):
            filter();
            break;
        case (8): 
            searchDatabase(); 
        case (9):
            displayMenu = false;
            break;
        default:
            std::cout << "Unrecognized choice. Try again and input another number." << std::endl
                      << std::endl;
            break;
        }
    }
}



void deleteDocument()
{
    std::cout << "Enter the file to delete from database (ex: ["   << "collectionname"   << "]/["    << "filename"   << "])" << std::endl;
    std::string filepath;
    std::cin >> filepath;

    std::string filepathFormat = "./db/" + filepath;

    const char *file = filepathFormat.c_str();

    if (std::remove(file) != 0)
    {
        // If the file deletion fails, print an error message
        std::cout   << "File could not be deleted!\n";
        std::perror("Error deleting file");
    }
    else
    {
        std::printf("File deleted successfully\n");
    }
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
        std::cout    << i.path().filename() << " ";
    }
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
        std::cout   << collectionList.at(i) << " ";
    }
    // std::cout   << "\n\n";

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
        std::cout   << "Error opening file. Check again if there are any contents in the file, if the file exists, or if it's a json file.\n"; 
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
        std::cout   << "No collections found. Please create a collection first.\n"
                   ;
        addCollection();
        getCollectionList(collectionList);
    }
    std::cout << "\n\nSelect one of the following collections to insert document into.\n";
    std::cout << "Here are the current collections in our database:\n\n";

    for (unsigned int i = 0; i < collectionList.size(); ++i)
    {
        std::cout   << collectionList.at(i) << " ";
    }
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

    std::cout << "JSON file created successfully and stored in collection: "   << collectionChoice   << std::endl;
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
        std::cout   << "No collections found. Please create a collection and document first.\n\n"
                  ;
        return;
    }
    else
    {
        std::cout << "Here are all the available collections: \n";
        for (unsigned int i = 0; i < collectionList.size(); i++)
        {
            std::cout   << collectionList.at(i) << " ";
        }
        std::cout << std::endl; 
        std::cout << "\n\n";

        std::cout << "Enter the collection that the document is stored in: ";
        std::cin >> collectionName;

        std::cout << "Here are a list of files under that collection:\n";
        getFileList(filesInCollection, collectionName);

        std::cout << "\nSelect a file to view/update: ";
        std::cin >> fileName;

        pathToFileName = "./db/" + collectionName + "/" + fileName + ".json";
        std::ifstream file(pathToFileName);
        if (!file)
        {
            std::cout   << "Error opening file\n"
                       ;
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

void updateDocumentValue()
{
    std::string collectionName;
    std::string fileName;
    std::string line;
    std::string pathToFileName;
    std::vector<std::string> collectionList;
    std::vector<std::string> filesInCollection;

    std::cout << "First, we must locate the document to update.\n";
    getCollectionList(collectionList);
    if (collectionList.empty())
    {
        std::cout   << "No collections found. Please create a collection and document first.\n\n"
                   ;
        return;
    }
    else
    {
        std::cout << "Here are all the available collections: \n";
        for (const std::string &collection : collectionList)
        {
            std::cout   << collection << " ";
        }
        // std::cout   << "\n\n";

        std::cout << "Enter the collection that the document is stored in: ";
        std::cin >> collectionName;

        std::cout << "Here are a list of files under that collection:\n";
        getFileList(filesInCollection, collectionName);

        std::cout << "\nSelect a file to view/update: ";
        std::cin >> fileName;

        pathToFileName = "./db/" + collectionName + "/" + fileName + ".json";
        std::ifstream file(pathToFileName);
        std::ifstream file2(pathToFileName);
        if (!file || !file2)
        {
            std::cout   << "Error opening file\n"
                       ;
            return;
        }

        while (getline(file2, line))
        {
            std::cout << line << "\n\n";
        }
        file2.close();
        std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        rapidjson::Document document;
        document.Parse(fileContents.c_str());

        std::string key, updatedValue;
        std::cout << "Enter the key to update: ";
        std::cin >> key;
        std::cout << "Enter the updated value: ";
        std::cin >> updatedValue;

        // Split the key into its component parts
        std::vector<std::string> keys = convertToParamList(key);

        rapidjson::Value *jsonValue = &document;
        // CHATGPT referenced
        //  Traverse the object to find the nested value
        for (const std::string &subKey : keys)
        {
            if (jsonValue->IsArray()) // check if it's an array
            {
                size_t index = std::stoi(subKey);
                if (index < jsonValue->Size()) // check if the index is valid
                {
                    jsonValue = &((*jsonValue)[index]);
                }
                else
                {
                    std::cout   << "Index out of bounds: " << key   << std::endl;
                    return;
                }
            }
            else if (jsonValue->IsObject() && jsonValue->HasMember(subKey.c_str()))
            {
                jsonValue = &((*jsonValue)[subKey.c_str()]);
            }
            else
            {
                std::cout   << "Key not found: " << key   << std::endl;
                return;
            }
        }

        if (jsonValue->IsString())
        {
            jsonValue->SetString(updatedValue.c_str(), updatedValue.size(), document.GetAllocator());
        }
        else if (jsonValue->IsInt())
        {
            jsonValue->SetInt(std::stoi(updatedValue));
        }

        // Write the updated JSON to the file
        std::ofstream outputFile(pathToFileName);
        if (!outputFile)
        {
            std::cout   << "Error opening file for writing\n"
                       ;
            return;
        }
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        outputFile << buffer.GetString();
        outputFile.close();

        std::cout << "JSON file updated successfully.\n";
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

    std::cout << "First, we must locate the document to search.\n";
    getCollectionList(collectionList);
    if (collectionList.size() == 0)
    {
        std::cout   << "No collections found. Please create a collection and document first.\n\n"
                   ;
        return;
    }

    std::cout << "Here are all the available collections: \n";
    printCollections(collectionList);

    std::cout << "Enter the collection that the document is stored in: ";
    std::cin >> collectionName;

    std::cout << "Here are a list of files under that collection:\n";
    getFileList(filesInCollection, collectionName);

    std::cout << "Select a file to search: ";
    std::cin >> fileName;
    pathToFileName = "./db/" + collectionName + "/" + fileName + ".json";
    std::ifstream file(pathToFileName);
    if (!file)
    {
        std::cout   << "Error opening file\n"
                   ;
        return;
    }

    std::cout << "\n\n";

    std::cout << "Enter parameter you would like to search for: (ex. employee.name)" << std::endl;
    std::cin >> parameter;
    std::vector<std::string> paramList = convertToParamList(parameter);

    std::ifstream ifs(pathToFileName);

    json j = json::parse(ifs);
    handleSearchRequest(parameter, paramList, j);
}

void handleSearchRequest(const std::string &param, const std::vector<std::string> &paramList, json &j)
{
    for (int i = 0; i < paramList.size(); ++i)
    {
        if (j.is_object())
        {
            if (j.contains(paramList.at(i)))
            {
                j = j[paramList.at(i)];
            }
            else
            {
                std::cout   << "Could not find paramter within this JSON"   << std::endl;
                return;
            }
        }
        else if (j.is_array())
        {
            char c = paramList.at(i)[0];
            if (!isdigit(c))
            {
                return;
            }
            int index = std::stoi(paramList.at(i));
            if (index >= 0 && index < j.size())
            {
                j = j[index];
            }
            else
            {
                std::cout   << "Could not find this this parameter within this JSON"   << std::endl;
                return;
            }
        }
        else
        {
            std::cout   << "Could not find this parameter within this JSON"   << std::endl;
            return;
        }
    }
    // prints json instance of where the search parameter is located.
    std::cout << j << std::endl;
    std::cout << "\n\n";
    return;
}

void printCollections(const std::vector<std::string> &colList)
{
    for (int i = 0; i < colList.size(); ++i)
    {
        std::cout   << colList.at(i) << " ";
    }
    // std::cout   << "\n\n";
}

std::vector<std::string> convertToParamList(std::string param)
{
    std::vector<std::string> paramList;
    std::istringstream iss(param);
    std::string substring;

    while (std::getline(iss, substring, '.'))
    {
        paramList.push_back(substring);
    }
    return paramList;
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

            std::cout << "Collection Name: "   << collectionList.at(i)<< std::endl;

            std::cout << "Files in " << collectionList.at(i) << ": ";
            getFileList(filesInCurrCollection, collectionList.at(i));

            std::cout << "\n\n";
        }
    }
    else // executes when there's no collections or files
    {
        std::cout   << "There are currently no existing collections or files." << std::endl;
        std::cout   << "Please create some collections and files before trying this option again!"   << std::endl;
    }
}

void printFilteredValues(const json &jsonData, const std::string &keyPath)
{
    try
    {
        json filteredData = jsonData;
        std::stringstream ss(keyPath);
        std::string key;
        while (std::getline(ss, key, '.'))
        {
            filteredData = filteredData.at(key);
        }
        std::cout << keyPath << ": " << filteredData << '\n';
    }
    catch (const json::exception &)
    {
        std::cout << "Key \"" << keyPath << "\" not found." << std::endl;
    }
}

void filter()
{
    std::string collectionName;
    std::string fileName;
    std::string pathToFileName;
    std::vector<std::string> collectionList;
    std::vector<std::string> filesInCollection;

    std::cout << "First, we must locate the document to update.\n";
    getCollectionList(collectionList);

    if (collectionList.empty())
    {
        std::cout   << "No collections found. Please create a collection and document first.\n\n"
                   ;
        return;
    }

    std::cout << "Here are all the available collections:\n";
    for (const std::string &collection : collectionList)
    {
        std::cout   << collection << " ";
    }
    // std::cout   << "\n\n";

    std::cout << "Enter the collection that the document is stored in: ";
    std::cin >> collectionName;

    std::cout << "Here is a list of files under that collection:\n";
    getFileList(filesInCollection, collectionName);

    std::cout << "\nSelect a file to filter (do not need to add filetype at end): ";
    std::cin >> fileName;
    std::cin.ignore();

    pathToFileName = "./db/" + collectionName + "/" + fileName + ".json";
    std::ifstream jsonFile(pathToFileName);
    json jsonData;
    jsonFile >> jsonData;

    std::cout << "Enter the desired key paths to filter separated by a space (e.g., address.street): ";
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::vector<std::string> keyPaths;

    while (ss >> input)
    {
        keyPaths.push_back(input);
    }

    for (const auto &keyPath : keyPaths)
    {
        printFilteredValues(jsonData, keyPath);
    }
}
