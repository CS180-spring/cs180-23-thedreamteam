#include "document.h"
#include <typeinfo>

Document::Document(std::string data) {
    try {
        if(data == "") {
            throw(data);
        }
        else {
            this->data = data;
            std::cout << "Created new document" << std::endl;
        }
    }
    catch(std::string error) {
        std::cout << "Entered an invalid data input for document! Document data input cannot be an empty string." << std::endl;
    }
    
}

std::string Document::getData() {
    return this->data;
}