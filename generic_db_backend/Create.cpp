
#include "Create.h"
#include "Essential.h"
#include "Add.h"

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

void createDocument()
{
    std::string filename;
    std::string collectionChoice;

    std::cout << "Enter the contents of the JSON document (type END on a new line to finish):" << std::endl;
    std::string json;
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == "END")
        {
            break;
        }
        if (!json.empty())
        {
            json += '\n';
        }
        json += line;
    }

    std::cout << "\nEnter a filename for the JSON file: ";
    std::cin >> filename;
    filename = filename + ".json";

    std::vector<std::string> collectionList;
    getCollectionList(collectionList);

    if (collectionList.size() == 0)
    {
        std::cout << "No collections found. Please create a collection first.\n";
        addCollection();
        getCollectionList(collectionList);
    }
    std::cout << "\n\nSelect one of the following collections to insert document into.\n";
    std::cout << "Here are the current collections in our database:\n\n";

    for (unsigned int i = 0; i < collectionList.size(); ++i)
    {
        std::cout << collectionList.at(i) << " ";
    }
    while (1)
    {
        std::cin >> collectionChoice;
        if (std::find(collectionList.begin(), collectionList.end(), collectionChoice) != collectionList.end())
        {
            break;
        }
    }
    std::ofstream fout("./db/" + collectionChoice + "/" + filename);
    fout << json;
    fout.close();

    std::cout << "JSON file created successfully and stored in collection: " << collectionChoice << std::endl;
}





