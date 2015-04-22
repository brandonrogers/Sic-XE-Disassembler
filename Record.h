/* 
 * File:   Record.h
 * Author: brandonrogers
 *
 * Created on March 26, 2015, 4:18 PM
 */

#ifndef RECORD_H
#define	RECORD_H

#include <string>
#include <iostream>
#include <fstream>

class Record {
public:
    Record();
    virtual ~Record();
    void unexpectedEOF(std::fstream & file);
    void errorReadingStream(std::fstream & file);
    int ASCIItoHEX(const char aASCII);
protected:

    int start;
    int first;

private:
    
};

#endif	/* RECORD_H */

