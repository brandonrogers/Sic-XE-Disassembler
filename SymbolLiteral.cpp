/* 
 * File:   SymbolLiteral.cpp
 * Author: brandonrogers
 * 
 * Created on March 26, 2015, 4:20 PM
 */

#include "SymbolLiteral.h"
#include <iostream>

// constructor reads in the symFile line by line into a symTab container
SymbolLiteral::SymbolLiteral(std::string fileName) {
    std::cout << "Constructing symbol literal table... ";
    
    std::string address;
    std::string symbol;
    std::string temp;
    
    // open symbol file using argv[1] passed from main, appends .sym to filename
    symFile.open(fileName.append(".sym"), std::ios::in);
    // error, symbol file wasn't found
    if (!symFile.is_open()) {
        std::cerr << "Could not open symbol file " << fileName << ", "
                "exiting" << std::endl;
        exit(1);
    }
    // get two lines of the symFile, these are discarded
    std::getline(symFile, temp, '\n');
    std::getline(symFile, temp, '\n');
    
    std::cout << " Done. Found " << table.size() << " symbols / literals" 
            << std::endl;
}

// close fstream on symFile
SymbolLiteral::~SymbolLiteral() {
    symFile.close();
}

//query the symTab container for a symbol given the address. 
std::string SymbolLiteral::getSymbol(int address) {
    // search table for value given key
    // WARNING this might be a null pointer exception if map.end() doesn't have
    // a 'second' value
    std::string temp = table.find(address)->second;
    // tests if the string is empty and the search was unsuccessful 
    if (temp.empty()) {
        std::cerr << "Warning, could not find symbol at " << address << 
                std::endl;
    }
    // tests if the table is empty
    if (table.empty()) {
        std::cerr<< "Warning, SymbolLiteral table is empty" << std::endl;
    }
    return temp;
}

