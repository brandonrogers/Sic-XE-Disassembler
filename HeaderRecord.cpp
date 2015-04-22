/* 
 * File:   HeaderRecord.cpp
 * Author: brandonrogers
 * 
 * Created on March 26, 2015, 4:19 PM
 */

#include <iostream>
#include <fstream>

#include "HeaderRecord.h"
#include "Record.h"

HeaderRecord::HeaderRecord() {
    progName = "";
    progLength = 0;
    progStart = 0;
    std::cout<< "Processing Header Record" << std::endl;
}


HeaderRecord::~HeaderRecord() {
}

std::string HeaderRecord::getProgName() {
    return progName;
}

int HeaderRecord::getProgLength() {
    return progLength;
}

int HeaderRecord::getProgStart() {
    return progStart;
}

// sets the prog name. Requires a file pointer. Extracts exactly six characters
// from fstream
void HeaderRecord::setProgName(std::fstream & file) {
    int i;
    // get 6 characters and append them to the progName string
    for (i = 0; i < 6; i++) {
        // needs a string argument for append()
        char tempChar = file.get();
        
        // error handler, check for eof bit
        Record::unexpectedEOF(file);
        // append to string
        progName += tempChar;
    }
    std::cout << "Program name: " + progName;
}

// sets prog length. extracts exactly six characters at columns 14-19
void HeaderRecord::setProgLength(std::fstream & file) {
    int i = 0;
    // get 6 characters, convert them to ints, and multiply to get their
    // significant places
    for (i = 0x100000; i > 0x00; i = i / 0x10) {
        int hexVal;
        char tempChar;
        tempChar = file.get();
        // check for error, unexpected eof
        Record::unexpectedEOF(file);
        hexVal = ASCIItoHEX(tempChar);
        hexVal *= i;
        // adds values starting at MSB position and moving right each
        // iteration
        progLength += hexVal;
    }
    std::cout << "  Program length: " << std::hex << progLength << std::endl;
}

// gets column 8-13 in header record setting the prog start address
void HeaderRecord::setProgStart(std::fstream & file) {
    int i = 0;
    // get 6 characters, convert them to ints, and multiply to get their
    // significant places
    for (i = 0x100000; i > 0x00; i = i / 0x10) {
        int hexVal;
        char tempChar;
        tempChar = file.get();
        // check for error, unexpected eof
        Record::unexpectedEOF(file);
        hexVal = ASCIItoHEX(tempChar);
        hexVal *= i;
        // adds values starting at MSB position and moving right each
        // iteration
        progStart += hexVal;
    }
    std::cout << "  Program start address: " << progStart;
}