#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;


#include <string>

    void searchKeywordInCollections(const std::string& keyword); 
    
    void searchGetFileList(std::vector<std::string>& fileList, const std::string& collectionName); 
    // void getFileList(std::vector<std::string>& fileList, const std::string& collectionName); 
#endif  // DOCUMENT_MANAGER_H