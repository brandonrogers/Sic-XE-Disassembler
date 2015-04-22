/* 
 * File:   AsmLine.h
 * Author: brandonrogers
 *
 * Created on April 20, 2015, 11:30 PM
 */

#ifndef ASMLINE_H
#define	ASMLINE_H

#include <string>

// This is a wrapper class for the map collection. Each instance saves a single 
// line of the assembly code.    
class AsmLine {

public:

    AsmLine();

    std::string asmDirective; // assembler directives (RESB, START, etc)
    bool isExtended;	// character ‘+’ if it is format 4
    std::string opCode;		// opCode string from opCode container
    bool isImmediate;   // # or @ depending on immediate or indirect
    bool isIndirect;
    bool isLiteral;     // = sign if string literal
    std::string operand1;  // first operand (poss from littab or symtab)
    std::string operand2; // some opCodes might have 2 operands?
    bool isIndexed;  // ‘,x’ after operand for indexed mode
};

#endif	/* ASMLINE_H */

