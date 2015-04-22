/* 
 * File:   OpTable.h
 * Author: brandonrogers
 *
 * Created on March 26, 2015, 4:19 PM
 */

#ifndef OPTABLE_H
#define	OPTABLE_H

#include <string>
#include <map>

class OpTable {

public:
    OpTable();
    OpTable(const OpTable& orig);
    virtual ~OpTable();
    // get op code from table
    std::string getOpCode(int key);

private:
    // container for Op Codes
    std::map<int, std::string> table;
    
};

#endif	/* OPTABLE_H */

