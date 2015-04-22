/* 
 * File:   Record.cpp
 * Author: brandonrogers
 * 
 * Created on March 26, 2015, 4:18 PM
 */


#include "Record.h"

// record parent class. contains methods used across different record types
Record::Record() {
}


Record::~Record() {
}

void Record::unexpectedEOF(std::fstream & file) {
    if (file.eof()) {
        std::cout << "Error, reached unexpected end of file, exiting" 
                << std::endl;
        exit(1);
    }
}

void Record::errorReadingStream(std::fstream & file) {
    if (!file) {
        std::cout << "Error, could not read from file stream, exiting" 
                << std::endl;
        exit(1);
    }
}

int Record::ASCIItoHEX(const char ASCII) {
    // atoi converts char to int
    // int ASCII = std::atoi(aASCII);
    // value is 0 - 9
    if(ASCII >= 48 && ASCII <= 57) {
        return (ASCII - 48);
    }
    // value is A - F
    else if(ASCII >= 65 && ASCII <= 70) {
        return (ASCII - 55);
    }
    else if(ASCII >= 97 && ASCII <= 102)	//if char is a-f
	return (ASCII - 87);
    // error check to see if input is out of range
    else {
        std::cout << "ERROR: invalid input conversion ASCII to HEX, expected "
                "0 - F, found: ";
        std::cout << ASCII;
        return (-1); // return -1 if out of range 
    }
}