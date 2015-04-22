/* 
 * File:   TextRecord.cpp
 * Author: brandonrogers
 * 
 * Created on March 26, 2015, 4:19 PM
 */

#include "TextRecord.h"

TextRecord::TextRecord() {
    std::cout<< "Processing Text Record" << std::endl;
    textLength = 0;
    textStartAddr = 0;
}


TextRecord::~TextRecord() {
}

// returns length of text record
int TextRecord::getTextLength() {
    return textLength;
}

// returns the machine instruction as an int
int TextRecord::getInstruction() {
    return 0;
}

int TextRecord::getTextStartAddr() {
    return textStartAddr;
}

// gets column 8-9 and sets the text record length
void TextRecord::setTextLength(std::fstream & file) {
    int i = 0;
    // get 2 characters, convert them to ints, and multiply to get their
    // significant places
    for (i = 0x10; i > 0x00; i = i / 0x10) {
        int hexVal;
        char tempChar;
        tempChar = file.get();
        // check for error, unexpected eof
        Record::unexpectedEOF(file);
        hexVal = ASCIItoHEX(tempChar);
        hexVal *= i;
        // adds values starting at MSB position and moving right each
        // iteration
        textLength += hexVal;
    }
}

void TextRecord::setInstruction(std::fstream & file) {
    return;
}

void TextRecord::setTextStartAddr(std::fstream & file) {
    int i = 0;
    // get 2 characters, convert them to ints, and multiply to get their
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
        textStartAddr += hexVal;
    }
}