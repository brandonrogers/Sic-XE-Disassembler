/* 
 * File:   OpTable.cpp
 * Author: brandonrogers
 * 
 * Created on March 26, 2015, 4:19 PM
 */

#include "OpTable.h"
#include <iostream>

OpTable::OpTable() {
    std::cout << "Assembling Op Table... ";
    table.insert( std::pair<int, std::string>(0x18, "ADD"));
    table.insert( std::pair<int, std::string>(0x58, "ADDF"));
    table.insert( std::pair<int, std::string>(0x90, "ADDR"));
    table.insert( std::pair<int, std::string>(0x40, "AND"));
    table.insert( std::pair<int, std::string>(0xB4, "CLEAR"));
    table.insert( std::pair<int, std::string>(0x28, "COMP"));
    table.insert( std::pair<int, std::string>(0x88, "COMPF"));
    table.insert( std::pair<int, std::string>(0xA0, "COMPR"));
    table.insert( std::pair<int, std::string>(0x24, "DIV"));
    table.insert( std::pair<int, std::string>(0x64, "DIVF"));
    table.insert( std::pair<int, std::string>(0x9C, "DIVR"));
    table.insert( std::pair<int, std::string>(0xC4, "FIX"));
    table.insert( std::pair<int, std::string>(0xC0, "FLOAT"));
    table.insert( std::pair<int, std::string>(0xF4, "HIO"));
    table.insert( std::pair<int, std::string>(0x3C, "J"));
    table.insert( std::pair<int, std::string>(0x30, "JEQ"));
    table.insert( std::pair<int, std::string>(0x34, "JGT"));
    table.insert( std::pair<int, std::string>(0x38, "JLT"));
    table.insert( std::pair<int, std::string>(0x48, "JSUB"));
    table.insert( std::pair<int, std::string>(0x00, "LDA"));
    table.insert( std::pair<int, std::string>(0x68, "LDB"));
    table.insert( std::pair<int, std::string>(0x50, "LDCH"));
    table.insert( std::pair<int, std::string>(0x70, "LDF"));
    table.insert( std::pair<int, std::string>(0x08, "LDL"));
    table.insert( std::pair<int, std::string>(0x6C, "LDS"));
    table.insert( std::pair<int, std::string>(0x74, "LDT"));
    table.insert( std::pair<int, std::string>(0x04, "LDX"));
    table.insert( std::pair<int, std::string>(0xD0, "LPS"));
    table.insert( std::pair<int, std::string>(0x20, "MUL"));
    table.insert( std::pair<int, std::string>(0x60, "MULF"));
    table.insert( std::pair<int, std::string>(0x98, "MULR"));
    table.insert( std::pair<int, std::string>(0xC8, "NORM"));
    table.insert( std::pair<int, std::string>(0x44, "OR"));
    table.insert( std::pair<int, std::string>(0xD8, "RD"));
    table.insert( std::pair<int, std::string>(0xAC, "RMO"));
    table.insert( std::pair<int, std::string>(0x4C, "RSUB"));
    table.insert( std::pair<int, std::string>(0xA4, "SHIFTL"));
    table.insert( std::pair<int, std::string>(0xA8, "SHIFTR"));
    table.insert( std::pair<int, std::string>(0xF0, "SIO"));
    table.insert( std::pair<int, std::string>(0xEC, "SSK"));
    table.insert( std::pair<int, std::string>(0x0C, "STA"));
    table.insert( std::pair<int, std::string>(0x78, "STB"));
    table.insert( std::pair<int, std::string>(0x54, "STCH"));
    table.insert( std::pair<int, std::string>(0x80, "STF"));
    table.insert( std::pair<int, std::string>(0xD4, "STI"));
    table.insert( std::pair<int, std::string>(0x14, "STL"));
    table.insert( std::pair<int, std::string>(0x7C, "STS"));
    table.insert( std::pair<int, std::string>(0xE8, "STSW"));
    table.insert( std::pair<int, std::string>(0x84, "STT"));
    table.insert( std::pair<int, std::string>(0x10, "STX"));
    table.insert( std::pair<int, std::string>(0x1C, "SUB"));
    table.insert( std::pair<int, std::string>(0x5C, "SUBF"));
    table.insert( std::pair<int, std::string>(0x94, "SUBR"));
    table.insert( std::pair<int, std::string>(0xB0, "SVC"));
    table.insert( std::pair<int, std::string>(0xE0, "TD"));
    table.insert( std::pair<int, std::string>(0xF8, "TIO"));
    table.insert( std::pair<int, std::string>(0x2C, "TIX"));
    table.insert( std::pair<int, std::string>(0xB8, "TIXR"));
    table.insert( std::pair<int, std::string>(0xDC, "WD"));
    std::cout << " Done, loaded " << table.size() << " Op Codes." << std::endl;
}

OpTable::OpTable(const OpTable& orig) {
}

OpTable::~OpTable() {
}


std::string OpTable::getOpCode(int key) {
    
    // search table for value given key
    std::string temp = table.find(key)->second;
    // tests if the string is empty and the search was unsuccessful 
    if (temp.empty()) {
        std::cerr << "Warning, could not find " << std::hex << key << std::endl;
        return "ERROR";
    }
    // tests if the table is empty
    else if (table.empty()) {
        std::cerr<< "Critical Error, OpTable is empty" << std::endl;
        exit(1);
    }
    return temp;
}
