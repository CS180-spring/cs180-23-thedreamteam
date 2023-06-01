#ifndef FILTER_H
#define FILTER_h

#include "Add.h"
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

void filter(); 
void printFilteredValues(const json &jsonData, const std::string &keyPath); 

#endif 


