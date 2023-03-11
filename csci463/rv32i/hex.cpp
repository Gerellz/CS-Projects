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

#include "hex.h"

/**
 * Returns the hex representation of a value.
 * 
 * Takes in a value 'i' and converts it, with 0 as the
 * fill character, to an 8 bit hexadecimal value and 
 * returns it as a string.
 * 
 * @param i Value to be converted to hexadecimal
 * 
 * @return String with exactly 2 hex digits representing
 *         the 8 bits of the i parameter.
 ******************************************************/
std::string hex::to_hex8(uint8_t i) {
    std::ostringstream os;
    os << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint16_t>(i);
    return os.str();
}

/**
 * Returns the 32 bit hex representation of a value.
 * 
 * Takes in a value 'i' and converts it, with 0 as the
 * fill character, to a 32 bit hexadecimal value and
 * returns it as a string.
 * 
 * @param i Value to be converted to hexadecimal
 * 
 * @return String with 8 hex digits representing the
 *         32 bits of the i parameter. 
 ****************************************************/
std::string hex::to_hex32(uint32_t i) {
    std::ostringstream os;
    os << std::hex << std::setfill('0') << std::setw(8) << i;
    return os.str();
}

/**
 * Returns the 32 bit hex representation of a value with
 * '0x' preceding it.
 * 
 * Takes in a value 'i' and calls the to_hex function to
 * convert it to the 32 bit hexadecimal value and returns
 * it as a string.
 * 
 * @param i Value to be converted to hexadecimal
 * 
 * @return String with 8 hex digits representing the
 *         32 bits of the i parameter with 0x preceding it.
 *********************************************************/
std::string hex::to_hex0x32(uint32_t i) {
    return std::string("0x")+to_hex32(i);
}

/**
 * Returns the 20 bit hex representation of a value with
 * '0x' preceding it.
 * 
 * Takes in a value 'i' then 'ands' it against 0xfffff to
 * get the LSBs and converts it to hex.
 * 
 * @param i Value to be converted to hexadecimal.
 * @return String with 5 hex digits representing the
 *         32 bits of the 'i' parameter with 0x
 *         preceding it. 
 *******************************************************/
std::string hex::to_hex0x20(uint32_t i) {
    std::ostringstream os;
    os << std::hex << std::setfill('0') << std::setw(5) << (i & 0xfffff);
    return std::string("0x")+os.str();
}

/**
 * Returns the 12 bit hex representation of a value with
 * '0x' preceding it.
 * 
 * Takes in a value 'i' then 'ands' it against 0xfff to
 * get the LSBs and converts it to hex. 
 * 
 * @param i Value to be converted to hexadecimal.
 * @return String with 3 hex digits representing the
 *         32 bits of the 'i' parameter with 0x
 *         preceding it.
 ******************************************************/
std::string hex::to_hex0x12(uint32_t i) {
    std::ostringstream os;
    os << std::hex << std::setfill('0') << std::setw(3) << (i & 0xfff);
    return std::string("0x")+os.str();
}
