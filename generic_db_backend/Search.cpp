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
#include "colormod.h"

namespace fs = std::filesystem;

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
        getFileList(fileList, collection);

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

            // display where file found 
            if (keywordFound)
            {
                std::cout << "Keyword found in file: " << file << std::endl;
            }
        }
    }
}

