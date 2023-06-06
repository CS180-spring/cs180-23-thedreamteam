#ifndef FILTER_H
#define FILTER_H

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


    void filter(); 
    void printFilteredValues(const json &jsonData, const std::string &keyPath); 



#endif 