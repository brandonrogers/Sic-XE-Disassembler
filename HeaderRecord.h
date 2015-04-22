/* 
 * File:   HeaderRecord.h
 * Author: brandonrogers
 *
 * Created on March 26, 2015, 4:19 PM
 */

#ifndef HEADERRECORD_H
#define	HEADERRECORD_H

#include "Record.h"

class HeaderRecord : public Record {
public:
    HeaderRecord();
    virtual ~HeaderRecord();
    std::string getProgName();
    int getProgLength();
    int getProgStart();
    void setProgName(std::fstream & file);
    void setProgLength(std::fstream & file);
    void setProgStart(std::fstream & file);
private:
    std::string progName;
    int progLength;
    int progStart;
};

#endif	/* HEADERRECORD_H */

