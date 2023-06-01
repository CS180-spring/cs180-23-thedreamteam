#include "Add.h"
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

void addDocument()
{
    std::vector<std::string> collectionList;
    getCollectionList(collectionList);

    // checks if any collections exist
    if (collectionList.size() == 0) // when no collection exists
    {
        std::cout   << "\nNo collections found. Please add a collection to the databasefirst before adding any documents"   << "\n\n";
    }
    else // when collection exists
    {
        /**
         * 2 ways to add: (if already in program --> can just upload name of file),
         * or add actual pathway to file on computer
         */
        std::cout << "\nEnter a file path to add to database: ";
        std::string filepath;
        std::cin >> filepath;

        // checking for correct file extension (.json)
        if (filepath.find(".json") != std::string::npos)
        {
            std::ifstream inputfile(filepath);

            std::string collectionChoice;

            std::cout << "......................................." << std::endl;
            std::cout << "Select one of the following collections to insert document into."
                      << "\n\n";
            for (unsigned int i = 0; i < collectionList.size(); ++i)
            {
                std::cout << collectionList.at(i) << std::endl;
            }
            std::cout << "......................................." << std::endl;
            std::cout << "\nThe collection name that you've entered: ";
            std::cin >> collectionChoice;
            std::cout << "\n\n";

            // checks if user inputted collection name exists
            bool collectionExists = false;
            for (unsigned int i = 0; i < collectionList.size(); ++i)
            {
                if (collectionChoice == collectionList.at(i))
                {
                    collectionExists = true;
                }
            }

            if (collectionExists)
            {
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
                std::cout   << "This collection does not exist. Please try again."   << std::endl;
            }
        }
        else
        {
            std::cout   << "\nThat was not a JSON file! Please upload JSON files only with the .json extension included."   << std::endl;
        }
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
        std::cout   << "Could not create directory\n";
        std::cerr << "Error creating directory!\n";
        std::cout  ;
        exit(1);
    }

    std::cout << "Collection created successfully!" << std::endl
              << std::endl;
}