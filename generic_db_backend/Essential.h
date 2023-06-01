#ifndef DOCUMENT_ESSENTIAL_H
#define DOCUMENT_ESSENTIAL_H

#include <vector>
#include <string>

void getCollectionList(std::vector<std::string> &collectionList);
std::string get_file_name(const std::string &file_path);
void getFileList(std::vector<std::string> &fileList, const std::string &collectionName);
void printCollections(const std::vector<std::string> &colList);
std::vector<std::string> convertToParamList(std::string param); 
void viewCurrCollectAndFiles(); 

#endif  // DOCUMENT_MANAGER_H