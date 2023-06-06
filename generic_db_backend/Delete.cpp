#include "Delete.h"
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

void deleteDocument()
{
    std::cout << "Enter the file to delete from database (ex: ["
              << "collectionname"
              << "]/["
              << "filename"
              << "])" << std::endl;
    std::string filepath;
    std::cin >> filepath;

    std::string filepathFormat = "./db/" + filepath;

    const char *file = filepathFormat.c_str();

    if (std::remove(file) != 0)
    {
        // If the file deletion fails, print an error message
        std::cout << "File could not be deleted!\n";
        std::perror("Error deleting file");
    }
    else
    {
        std::printf("File deleted successfully\n");
    }
}


