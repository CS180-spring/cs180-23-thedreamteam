#include "Update.h"
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

Color::Modifier green(Color::FG_GREEN);
Color::Modifier magenta(Color::FG_MAGENTA);
Color::Modifier yellow(Color::FG_YELLOW);
Color::Modifier def(Color::FG_DEFAULT);

void updateDocument()
{
    std::string collectionName;
    std::string fileName;
    std::string pathToFileName;
    std::string line;
    std::vector<std::string> collectionList;
    std::vector<std::string> filesInCollection;

    std::cout << "First, we must locate the document to update.\n";
    getCollectionList(collectionList);
    if (collectionList.size() == 0)
    {
        std::cout << "No collections found. Please create a collection and document first.\n\n";
        return;
    }
    else
    {
        std::cout << "Here are all the available collections: \n";
        for (unsigned int i = 0; i < collectionList.size(); i++)
        {
            std::cout << collectionList.at(i) << " ";
        }
        std::cout << std::endl;
        std::cout << "\n\n";

        std::cout << "Enter the collection that the document is stored in: ";
        std::cin >> collectionName;

        std::cout << "Here are a list of files under that collection:\n";
        getFileList(filesInCollection, collectionName);

        std::cout << "\nSelect a file to view/update: ";
        std::cin >> fileName;

        pathToFileName = "./db/" + collectionName + "/" + fileName + ".json";
        std::ifstream file(pathToFileName);
        if (!file)
        {
            std::cout << "Error opening file\n";
        }

        while (getline(file, line))
        {
            std::cout << line << std::endl;
        }
        std::cout << "Enter the new text for the document (type END on a new line to finish): \n";
        std::string json;
        std::string input_line;
        while (std::getline(std::cin, input_line))
        {
            if (input_line == "END")
            {
                break;
            }
            if (!json.empty())
            {
                json += '\n';
            }
            json += input_line;
        }
        std::cout << "\n\n";
        std::ofstream fout(pathToFileName);
        fout << json;
        fout.close();
    }
}

void updateDocumentValue()
{
    std::string collectionName;
    std::string fileName;
    std::string line;
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
    else
    {
        std::cout << "Here are all the available collections: \n";
        for (const std::string &collection : collectionList)
        {
            std::cout << collection << " ";
        }
        // std::cout   << "\n\n";

        std::cout << "Enter the collection that the document is stored in: ";
        std::cin >> collectionName;

        std::cout << "Here are a list of files under that collection:\n";
        getFileList(filesInCollection, collectionName);

        std::cout << "\nSelect a file to view/update: ";
        std::cin >> fileName;

        pathToFileName = "./db/" + collectionName + "/" + fileName + ".json";
        std::ifstream file(pathToFileName);
        std::ifstream file2(pathToFileName);
        if (!file || !file2)
        {
            std::cout << "Error opening file\n";
            return;
        }

        while (getline(file2, line))
        {
            std::cout << line << "\n\n";
        }
        file2.close();
        std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        rapidjson::Document document;
        document.Parse(fileContents.c_str());

        std::string key, updatedValue;
        std::cout << "Enter the key to update: ";
        std::cin >> key;
        std::cout << "Enter the updated value: ";
        std::cin >> updatedValue;

        // Split the key into its component parts
        std::vector<std::string> keys = convertToParamList(key);

        rapidjson::Value *jsonValue = &document;
        // CHATGPT referenced
        //  Traverse the object to find the nested value
        for (const std::string &subKey : keys)
        {
            if (jsonValue->IsArray()) // check if it's an array
            {
                size_t index = std::stoi(subKey);
                if (index < jsonValue->Size()) // check if the index is valid
                {
                    jsonValue = &((*jsonValue)[index]);
                }
                else
                {
                    std::cout << "Index out of bounds: " << key << std::endl;
                    return;
                }
            }
            else if (jsonValue->IsObject() && jsonValue->HasMember(subKey.c_str()))
            {
                jsonValue = &((*jsonValue)[subKey.c_str()]);
            }
            else
            {
                std::cout << "Key not found: " << key << std::endl;
                return;
            }
        }

        if (jsonValue->IsString())
        {
            jsonValue->SetString(updatedValue.c_str(), updatedValue.size(), document.GetAllocator());
        }
        else if (jsonValue->IsInt())
        {
            jsonValue->SetInt(std::stoi(updatedValue));
        }

        // Write the updated JSON to the file
        std::ofstream outputFile(pathToFileName);
        if (!outputFile)
        {
            std::cout << "Error opening file for writing\n";
            return;
        }
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        outputFile << buffer.GetString();
        outputFile.close();

        std::cout << "JSON file updated successfully.\n";
    }
}