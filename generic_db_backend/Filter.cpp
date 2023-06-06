#include "Filter.h"
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


using json = nlohmann::json;
namespace fs = std::filesystem;

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
        std::cout << "No collections found. Please create a collection and document first.\n\n";
        return;
    }

    std::cout << "Here are all the available collections:\n";
    for (const std::string &collection : collectionList)
    {
        std::cout << collection << " ";
    }

    std::cout << "\nEnter the collection that the document is stored in: ";
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