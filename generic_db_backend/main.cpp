#include "Add.h"
#include "Essential.h"
#include "Search.h"
#include "View.h"
#include "Delete.h"
#include "Update.h"
#include "Create.h"
#include "Filter.h"

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

// void createDocument();

// void getCollectionList(std::vector<std::string> &collectionList);
// std::string get_file_name(const std::string &file_path);



std::vector<std::string> convertToParamList(std::string param);
std::string keyword;
// Color::Modifier green(Color::FG_GREEN);
// Color::Modifier magenta(Color::FG_MAGENTA);
// Color::Modifier yellow(Color::FG_YELLOW);
// Color::Modifier def(Color::FG_DEFAULT);

int main()
{
    int option;

    bool displayMenu = true;
    bool welcome = true;
    std::string subChoice;
    bool isEnterPressed = false;

    std::cout << "Welcome to GenericDB" << std::endl;
    std::cout << "Our database offered a number of features to try!" << std::endl;
    std::cout << "To try, press your 'enter' key to prompt the menu." << std::endl;
    std::cout << "From the menu, enter a number to access a feature." << std::endl;
    welcome = false;

    std::string line;
    std::getline(std::cin, line);

    if (line.empty())
    {
        isEnterPressed = true;
    }

    while (isEnterPressed && displayMenu)
    {
        std::cout << "\n** GenericDB **" << std::endl;
        std::cout << "................................................." << std::endl;
        std::cout << "Choose from the following operations:" << std::endl;
        std::cout << "1. Add a document or collection to the database" << std::endl;
        std::cout << "2. Delete a document from the database" << std::endl;
        std::cout << "3. Search the database or collection" << std::endl;
        std::cout << "4. Update a document or value" << std::endl;
        std::cout << "5. Create a document" << std::endl;
        std::cout << "6. View current collections and files" << std::endl;
        std::cout << "7. Filter a document" << std::endl;
        std::cout << "8. View file in database" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "................................................" << std::endl;
        std::cout << "Enter option: ";
        std::cin >> option;
        std::cout << "\n\n";

        switch (option)
        {
        case (1):
            std::cout << "What would you like to add to the database?" << std::endl;
            std::cout << "......................................................." << std::endl;
            std::cout << "Press your 'a' key: to add a document to the database" << std::endl;
            std::cout << "Press your 'b' key: to add a collection to the database" << std::endl;
            std::cout << "......................................................." << std::endl;
            std::cout << "Your Choice: ";
            std::cin >> subChoice;

            // adds a document to the database
            if (subChoice == "a")
            {
                addDocument();
            }
            else if (subChoice == "b") // adds a collection to the database
            {
                addCollection();
            }
            else 
            {
                std::cout << "\nPlease only enter the options indicated. Try again!" << std::endl;
            }
            break;
        case (2):
            deleteDocument();
            break;
        case (3):
            std::cout << "............................................................." << std::endl;
            std::cout << "Press your 'a' key: to search for a keyword in the database" << std::endl; // make this view database file
            std::cout << "Press your 'b' key: to search for a parameter in the database" << std::endl;
            std::cout << "............................................................." << std::endl;
            std::cout << "Your Choice: ";
            std::cin >> subChoice;

            // searches the database
            if (subChoice == "a")
            {
                std::cout << "Enter keyword you would like to search for: ";
                std::cin >> keyword;
                searchKeywordInCollections(keyword);
            }
            else if (subChoice == "b") // searches for a specific thing in the database
            {
                searchParameter();
            }
            else 
            {
                std::cout << "\nPlease only enter the options indicated. Try again!" << std::endl;
            }

            break;
        case (4):
            std::cout << ".................................................." << std::endl;
            std::cout << "Press your 'a' key: to update a document" << std::endl;
            std::cout << "Press your 'b' key: to update a document value" << std::endl;
            std::cout << ".................................................." << std::endl;
            std::cout << "Your Choice: "; 
            std::cin >> subChoice;

            // updates entire document
            if (subChoice == "a")
            {
                updateDocument();
            }
            else if (subChoice == "b") // updates a document val
            {
                updateDocumentValue();
            }
            else 
            {
                std::cout << "\nPlease only enter the options indicated. Try again!" << std::endl;
            }

            break;
        case (5):
            createDocument();
            break;
        case (6):
            viewCurrCollectAndFiles();
            break;
        case (7):
            filter();
            break;
        case (8):
            viewDatabase();
        case (9):
            displayMenu = false;
            break;
        default:
            std::cout << "Unrecognized choice. Try again and input another number." << std::endl << std::endl;
            break;
        }
    }
}

