//***********************************************************************
//
//  Gerald Ellsworth
//  Z1885378
//  CSCI 463-1
// 
//  I certify that this is my own work and where appropriate an extension
//  of the starter code provided for the assignment.
//
//***********************************************************************

#include <string>
#include <sstream>
#include <iomanip>

#ifndef HEX_H
#define HEX_H

class hex {
    public:
        static std::string to_hex8(uint8_t i);
        static std::string to_hex32(uint32_t i);
        static std::string to_hex0x32(uint32_t i);
        static std::string to_hex0x20(uint32_t i);
        static std::string to_hex0x12(uint32_t i);
};

#endif /* HEX_H */
