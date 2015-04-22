/* 
 * File:   EndRecord.h
 * Author: brandonrogers
 *
 * Created on March 26, 2015, 4:18 PM
 */

#ifndef ENDRECORD_H
#define	ENDRECORD_H

#include "Record.h"

class EndRecord : public Record  {
public:
    // Constructor uses the E value from object code to set the 
    // first variable in Record
    EndRecord();
    virtual ~EndRecord();
    void setFirst(int addr);
    int getFirst();
protected:
    int firstAddr;
private:
    
};

#endif	/* ENDRECORD_H */

