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

void getFileList(std::vector<std::string> &fileList, const std::string &collectionName)
{
    //  generic_db_backend\db\searchFile
    std::string pathToCollection = "./db/" + collectionName;
    for (auto &i : fs::directory_iterator(pathToCollection))
    {
        std::cout << i.path().filename() << " ";
    }
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
