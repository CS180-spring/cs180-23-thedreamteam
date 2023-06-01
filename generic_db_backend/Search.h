#ifndef SEARCH_H
#define SEARCH_H


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



    void searchKeywordInCollections(const std::string& keyword); 
    void searchParameter();
    void handleSearchRequest(const std::string &param, const std::vector<std::string> &paramList, json &j); 
    void searchGetFileList(std::vector<std::string>& fileList, const std::string& collectionName); 
    // void getFileList(std::vector<std::string>& fileList, const std::string& collectionName); 
#endif  // DOCUMENT_MANAGER_H