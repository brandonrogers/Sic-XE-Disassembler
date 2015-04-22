/* 
 * File:   AsmLine.cpp
 * Author: brandonrogers
 * 
 * Created on April 20, 2015, 11:30 PM
 */

#include "AsmLine.h"

AsmLine::AsmLine() {
    asmDirective = ""; // assembler directives (RESB, START, etc)
    isExtended = false;	// character ‘+’ if it is format 4
    opCode = "";		// opCode string from opCode container
    isImmediate = false;   // # or @ depending on immediate or indirect
    isIndirect = false;
    isLiteral = false;     // = sign if string literal
    operand1 = "";  // first operand (poss from littab or symtab)
    operand2 = ""; // some opCodes might have 2 operands?
    isIndexed = false;  // ‘,x’ after operand for indexed mode
}


