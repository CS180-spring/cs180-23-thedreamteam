#include "View.h"
#include "Essential.h"

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

namespace fs = std::filesystem;
std::vector<std::pair<std::string, std::string>> foundFiles;

/**
 * Search database for contents given file and collection name
 * 1. Display all existing collections to chose from
 * 2. Display all files in collection to chose from
 * 3. Search for content in file
 */
void viewDatabase()
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