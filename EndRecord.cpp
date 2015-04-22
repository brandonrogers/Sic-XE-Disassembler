/* 
 * File:   EndRecord.cpp
 * Author: brandonrogers
 * 
 * Created on March 26, 2015, 4:18 PM
 */

#include "EndRecord.h"

EndRecord::EndRecord() {
    std::cout << "Processing End Record...";
}

void EndRecord::setFirst(int addr) {
    firstAddr = addr;
}

int EndRecord::getFirst() {
    return firstAddr;
}

EndRecord::~EndRecord() {
}

