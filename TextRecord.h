/* 
 * File:   TextRecord.h
 * Author: brandonrogers
 *
 * Created on March 26, 2015, 4:19 PM
 */

#ifndef TEXTRECORD_H
#define	TEXTRECORD_H

#include "Record.h"

class TextRecord : public Record {
public:
    TextRecord();
    virtual ~TextRecord();
    // columns 2-7, length of text record
    int getTextLength();
    int getInstruction();
    int getTextStartAddr();
    
    void setTextStartAddr(std::fstream & file);
    void setTextLength(std::fstream & file);
    void setInstruction(std::fstream & file);
private:
    int textLength;
    int textStartAddr;
    int textInstruction;
};

#endif	/* TEXTRECORD_H */

