/* 
 * File:   Dasm.cpp
 * Author: brandonrogers
 * 
 * Created on March 10, 2015, 5:01 PM
 */

#include "AsmLine.h"
#include "Dasm.h"
#include <iostream>
#include <sstream>

// constructor handles file open operations, explicitly calls SymbolLiteral
// constructor with argv[1] as file name
// Throws error: fileName for .obj not found (from cmd line)
Dasm::Dasm(int argc, char* argv[]) : symTab(argv[1]) {
    
    // correct number of arguments, open object file using argv[1]
    Dasm::fileName = argv[1];
    Dasm::file.open(fileName.append(".obj"), std::ios::in);
    // error, fileName is invalid or file open failed
    if (!file.is_open()) {
        std::cerr<< "Could not open object file " << fileName << ", exiting" 
                << std::endl;
        exit(1);
    }
    // set ProgCtr, lineNum, and base to default values
    progCounter = 0; lineNum = 0; base = -1;
}

// close files in destructor
Dasm::~Dasm() {
    file.close();
}


void Dasm::disassemble() {
    // next character
    char next;
    // most significant nibble
    int msn;
    // get next character
    next = file.get();
    
    while (!file.eof()) {
        // process a header record
        if (next == 'H') {
            HeaderRecord newHeader;
            newHeader.setProgName(file);
            newHeader.setProgStart(file);
            newHeader.setProgLength(file);
            // add the header record to the table (at address 0)
            // 
            AsmLine header;
            header.asmDirective = newHeader.getProgName();
            header.opCode = "START";
            header.operand1 = newHeader.getProgStart();
            // add AsmLine to storage at first location (0)
            storage.insert(std::pair<int,AsmLine>(lineNum, header));
            // increment lineNum by 5
            lineNum += 5;
        }
        
        else if (next == 'T') {
            TextRecord newText;
            // set text start and text length 
            newText.setTextStartAddr(file);
            // used as a max value for iterating thru entire text record
            newText.setTextLength(file);
            int i;
            int width;
            for (i = 0; i < newText.getTextLength(); i += width) {
                width = 0;
                // create a new AsmLine object
                AsmLine textRec;
                // get most significant and least sig nibble (total 1 byte)
                // convert this to HEX FIRST
                msn = file.get() * 0x10;
                // ditto
                int byte = file.get() + msn;
                // get the modulus 
                // mod = 0 - format 1 or 2 instruction
                // mod = 1 - immediate
                // mod = 2 - indirect
                // mod = 3 - neither immediate or indirect
                int mod = byte % 0x04;
                // calculate the actual numeric op code value
                int numOpCode = byte - mod;
                // get the op code string
                textRec.opCode = opTab.getOpCode(numOpCode);
                /* Handles a format 1 or format 2 instruction. 
                 These include instructions that do not have an operand
                 or where the operand is a register or two registers.
                 Increment progCounter by 1 or 2 */
                if (mod == 0) {
                    width = handleFormat1or2(numOpCode, textRec);
                    progCounter += width;
                }
                else {
                    // get the third nibble
                    // convert to a HEX FIRST
                    char flags = file.get();
                    flags = newText.ASCIItoHEX(flags);
                    // set indirect, immediate, indexed, and extended flags
                    setNIXBPE(mod, flags, textRec);
                    // Increment progCounter by 3 or 4
                    width = handleAddress(numOpCode, textRec);
                    progCounter += width;
                }
                
                // finally insert the instruction into table
                storage.insert(std::pair<int,AsmLine>(lineNum, textRec));
                lineNum += 5;
                // create a BASE directive if LDB opCode is found
                if (numOpCode == 0x68) {
                    AsmLine baseLine;
                    baseLine.opCode = "BASE";
                    baseLine.operand1 = textRec.operand1;
                    storage.insert(std::pair<int,AsmLine>(lineNum, baseLine));
                    lineNum += 5;
                }
            }
            
        }
        else if (next == 'M') {
            // do nothing?
            std::string modLine;
            std::getline(file, modLine);
            // do something with modLine?
        }
        else if (next == 'E') {
            EndRecord newEnd;
            AsmLine endRec;
            int i;
            int hexValEnd;
            for (i = 0x100000; i > 0x00; i = i / 0x10) {
                char tempChar = file.get();
                int hexValEnd = newEnd.ASCIItoHEX(tempChar);
                hexValEnd *= i;
            }
                newEnd.setFirst(hexValEnd);
                std::string addrString = symTab.getSymbol(newEnd.getFirst());
                if (addrString.empty()) {
                    int intStr = newEnd.getFirst();
                    std::stringstream ss;
                    ss << intStr;
                    endRec.operand1 = ss.str();
                }       
                else {
                    endRec.operand1 = addrString;
                }
                endRec.opCode = "END";
                storage.insert(std::pair<int, AsmLine>(progCounter, endRec));
                progCounter += 3;
        }
        // get first character on the next line
        next = file.get();    
    }
        
}
    //opTab.getOpCode(progCounter);

void Dasm::printToFile(char * fileName) {
    //iter = storage.begin();
    std::cout << "Writing to file ... " << fileName << ".sic" << std::endl;
}

void Dasm::setNIXBPE(int mod, int flags, AsmLine & textRec) {
    // sets immediate or indirect flag
    if (mod == 1)
        textRec.isImmediate = true;
    if (mod == 2)
        textRec.isIndirect = true;
    
    // sets flags
    if (flags == 1 || flags == 9) {
        textRec.isExtended = true;
    }
    if (flags == 8 || flags == 9 || (flags == 0xA && flags <= 0xC)) {
        textRec.isIndexed = true;
    } 
}

// handles the address portion of the instruction. These can range from 3 to 5
// nibbles. checks isExtended flag to determine length of address. Returns 
int Dasm::handleAddress(int opCode, AsmLine & line) {
    int i = 0;
    int address = 0;
    Record temp;
    // format 4
    if (line.isExtended) {
        // get 5 characters, convert them to ints, and multiply to get their
        // significant places
        for (i = 0x10000; i > 0x00; i = i / 0x10) {
            int hexVal;
            char tempChar;
            tempChar = file.get();
            // check for error, unexpected eof          
            temp.unexpectedEOF(file);
            hexVal = temp.ASCIItoHEX(tempChar);
            hexVal *= i;
            // adds values starting at MSB position and moving right each
            // iteration
            address += hexVal;
        } 
        return 5;
    }
    
    // format 3
    else {
        // get 3 characters and do conversion
        for (i = 0x100; i > 0x00; i = i / 0x10) {
            int hexVal;
            char tempChar;
            tempChar = file.get();
            // check for error, unexpected eof
            temp.unexpectedEOF(file);
            hexVal = temp.ASCIItoHEX(tempChar);
            hexVal *= i;
            // adds values starting at MSB position and moving right each
            // iteration
            address += hexVal;
        }
    }
    return 3;
}

int Dasm::handleFormat1or2(int opCode, AsmLine & line) {
    // format 1: C4, C0, F4, C8, F0, F8
    if (opCode == 0xC4 || opCode == 0xC0 || opCode == 0xF4 || opCode == 0xC8 ||
            opCode == 0xF0 || opCode == 0xF8) {
        // increment progCounter by 1
        progCounter++;
        return 1;
    }
    
    // format 2: 90, B4, A0, 9C, 98, AC, A8, 94, B0, B8
    else {
        return 2;
    }
}
/****       main()          ****/

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr<< "Incorrect number of command line arguments, exiting" << 
                std::endl;
        exit(1);
    }
    Dasm driver(argc, argv);
    driver.disassemble();
    driver.printToFile(argv[1]);
    return 0;
}

