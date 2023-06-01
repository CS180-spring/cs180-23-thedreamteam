#include "Document.h"

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

Color::Modifier green(Color::FG_GREEN);
Color::Modifier magenta(Color::FG_MAGENTA);
Color::Modifier yellow(Color::FG_YELLOW);
Color::Modifier def(Color::FG_DEFAULT);


void addDocument()
{
    std::vector<std::string> collectionList;
    getCollectionList(collectionList);

    // checks if any collections exist
    if (collectionList.size() == 0) // when no collection exists
    {
        std::cout << yellow << "\nNo collections found. Please add a collection to the databasefirst before adding any documents" << def << "\n\n";
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
                std::cout << yellow << "This collection does not exist. Please try again." << def << std::endl;
            }
        }
        else
        {
            std::cout << yellow << "\nThat was not a JSON file! Please upload JSON files only with the .json extension included." << def << std::endl;
        }
    }
}