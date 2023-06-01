#include "Search.h"
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

std::vector<std::pair<std::string, std::string>> keywordResult;

void searchKeywordInCollections(const std::string& keyword)
{
    std::vector<std::string> collectionList;
    std::vector<std::string> fileList;

    fs::path path_to_dir("./db");

    // collection list 
    for (const auto& entry : fs::directory_iterator(path_to_dir))
    {
        if (entry.is_directory())
        {
            collectionList.push_back(entry.path().filename().string());
        }
    }

    // Search for keyword in each collection
    for (const auto& collection : collectionList)
    {
        fileList.clear();

        // Get the list of files in the collection
        searchGetFileList(fileList, collection);

        for (const auto& file : fileList)
        {
            std::ifstream input(file);
            std::string line;
            bool keywordFound = false;

            // read in file contents
            while (std::getline(input, line))
            { 
                if (line.find(keyword) != std::string::npos)
                {
                    keywordFound = true;
                    break;
                }
            }

            if (keywordFound)
            {
                keywordResult.push_back(std::make_pair(file, collection));
            }

            
        }
        // display where file found 
        
    }
    if (!keywordResult.empty())
    {
        std::cout << "\nKeyword found!" << std::endl;
        for (const auto& foundFile : keywordResult)
        {
            std::cout << "Collection: " << foundFile.second << std::endl << std::endl << "File: " << foundFile.first << std::endl;
        }
    }
    else if (keywordResult.empty())
    {
        std::cout << "Keyword was not found in any file." << std::endl;
    }
}

void searchGetFileList(std::vector<std::string>& fileList, const std::string& collectionName)
{
    fs::path path_to_collection("./db/" + collectionName);
    for (const auto& entry : fs::directory_iterator(path_to_collection))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".json")
        {
            fileList.push_back(entry.path().string());
        }
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

    std::cout << "\nFirst, we must locate the document to search.\n";
    getCollectionList(collectionList);
    if (collectionList.size() == 0)
    {
        std::cout << "No collections found. Please create a collection and document first.\n\n";
        return;
    }

    std::cout << "\nHere are all the available collections: \n";
    printCollections(collectionList);

    std::cout << "\nEnter the collection that the document is stored in: ";
    std::cin >> collectionName;

    std::cout << "Here are a list of files under that collection:\n";
    getFileList(filesInCollection, collectionName);

    std::cout << "Select a file to search (without the quotation marks): ";
    std::cin >> fileName;
    pathToFileName = "./db/" + collectionName + "/" + fileName + ".json";
    std::ifstream file(pathToFileName);
    if (!file)
    {
        std::cout << "Error opening file\n";
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
                std::cout << "Could not find paramter within this JSON" << std::endl;
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
                std::cout << "Could not find this this parameter within this JSON" << std::endl;
                return;
            }
        }
        else
        {
            std::cout << "Could not find this parameter within this JSON" << std::endl;
            return;
        }
    }
    // prints json instance of where the search parameter is located.
    std::cout << j << std::endl;
    std::cout << "\n\n";
    return;
}
