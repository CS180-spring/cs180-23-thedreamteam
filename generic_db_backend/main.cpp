
#include <iostream>
#include "document.h"
#include "collection.h"
int main() {

    std::string dataInput1 = "This is a data input for CS180!";
    Document doc1(dataInput1);

    std::string dataInput2 = "What do you call a bagel that can fly? A plain bagel.";
    Document doc2(dataInput1);

    std::string dataInput3 = "This is tedious";
    Document doc3(dataInput1);

    std::string collectionName = "files";
    Collection documentCollection(collectionName);

    documentCollection.addDoc(dataInput1);
    documentCollection.addDoc(dataInput2);
    documentCollection.addDoc(dataInput3);

    documentCollection.printDocs();




}