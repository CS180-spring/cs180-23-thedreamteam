#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>
#include "document.h"

class Collection {
    public:
        //Creates collection object
        Collection(std::string collectionName);
        
        //Adds a Document Object to a collection
        void addDoc(Document doc);

        //Prints all Document Object data files in given collection
        void printDocs();


    private:
        std::string collectionName;
        std::vector<Document> collectionDocs;
};


#endif