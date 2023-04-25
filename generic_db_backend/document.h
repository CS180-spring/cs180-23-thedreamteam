#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <iostream>
#include <string>


class Document {
    public:
        //Creates Document object with inputted data field
        Document(std::string data);

        //Returns data input from specified Document object
        std::string getData();
    private:
        std::string data;
};

#endif
