#include "collection.h"

Collection::Collection(std::string collectionName) {
    try{
        if(collectionName == ""){
            throw(collectionName);
        }  
        else{
            this->collectionName = collectionName;
            std::cout << "Created collection named: " << collectionName << std::endl;
        }
    }
    catch(std::string error) {
        std::cout << "Entered an invalid name for collection! Collection name cannot be an empty string." << std::endl;
    }
}

void Collection::addDoc(Document doc) {
    this->collectionDocs.push_back(doc);
}

void Collection::printDocs() {
    for(unsigned int i = 0; i < this->collectionDocs.size(); ++i ){ 
        std::cout << "********************" << std::endl;
        std::cout << i << ": " << this->collectionDocs.at(i).getData() << std::endl;
    }
}