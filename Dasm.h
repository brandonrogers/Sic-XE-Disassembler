/* 
 * File:   Dasm.h
 * Author: brandonrogers
 *
 * Created on March 10, 2015, 5:01 PM
 */

#ifndef DASM_H
#define	DASM_H

#include <map>

#include "EndRecord.h"
#include "HeaderRecord.h"
#include "OpTable.h"
#include "SymbolLiteral.h"
#include "TextRecord.h"
#include "Record.h"


class Dasm {
    
public:
    
/******   End inner class AsmLine  *******/

    Dasm(int argc, char** argv);
    virtual ~Dasm();
    void setNIXBPE(int, int, AsmLine & line);
    int handleAddress(int opCode, AsmLine & line);
    int handleFormat1or2(int opCode, AsmLine & line);
    void disassemble();
    void printToFile(char *);
    void loadSymTab();
    
protected:
    // container to store Assembly record objects
    std::map<int, AsmLine> storage;
    // iterator object used to access all elements (for example, printing)
    std::map<int, AsmLine>::iterator iter;
    
    // file open values
    std::fstream file;
    std::string fileName;
    
    // symTab object
    SymbolLiteral symTab;
    
    // OpTable object
    OpTable opTab;
    
    // file output
    std::fstream outFile;
private:
    
    // used as a unique key for the asmLine map (like the code line numbers)
    int lineNum;
    // the program counter
    int progCounter;
    // base
    int base;
};


#endif	/* DASM_H */

