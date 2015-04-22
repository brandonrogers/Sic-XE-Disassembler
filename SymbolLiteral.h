/* 
 * File:   SymbolLiteral.h
 * Author: brandonrogers
 *
 * Created on March 26, 2015, 4:20 PM
 */

#ifndef SYMBOLLITERAL_H
#define	SYMBOLLITERAL_H

#include <string>
#include <fstream>
#include <map>

class SymbolLiteral {

public:
    // constructor takes a string argument as the .sym filename
    SymbolLiteral(std::string file);
    virtual ~SymbolLiteral();
    std::string getSymbol(int addr);

protected:
    
private:
    // container for symTab
    std::map<int, std::string> table;
    // fstream for .sym file
    std::fstream symFile;
};

#endif	/* SYMBOLLITERAL_H */

