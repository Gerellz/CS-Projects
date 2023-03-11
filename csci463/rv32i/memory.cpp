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

#include "memory.h"

/**
 * Construct a new memory object and defaults all
 * bytes to 0xa5.
 * 
 * Takes a value for the size of the vector and
 * rounds it to the nearest 16. Finally resizes
 * the vector and fills all bytes with the value
 * 0xa5.
 * 
 * @param siz A value that will be used to set
 *            the size of the memory vector.
 ***********************************************/
memory::memory(uint32_t siz) {
    siz = (siz+15)&0xfffffff0;
    mem.resize(siz, 0xa5);
}

/**
 * Destroy the memory::memory object
 * 
 * Destructor for the memory object.
 * Since we are using a vector, nothing
 * is necessary here apart from its existence.
 ********************************************/
memory::~memory() {
}

/**
 * Checks if a value is in the vector or not.
 * 
 * Checks the value 'i' against the size of
 * the memory vector and sees if that value is
 * an address in it.
 * 
 * @param i A value that potentially represents
 *          an address in the memory vector.
 * 
 * @return True if 'i' is greater than the size
 *         of the vector and therefore illegal.
 *         Returns false otherwise.
 *********************************************/
bool memory::check_illegal(uint32_t i) const {
    if (i >= mem.size()) { 
        std::cout << "WARNING: Address out of range: " << hex::to_hex0x32(i) << std::endl;
        return true;
    }
    else
        return false;
}

/**
 * Returns the number of bytes in the
 * memory vector.
 * 
 * Checks the size of the vector and returns
 * the value.
 * 
 * @return uint32_t that is the size of the
 *         memory vector. 
 ******************************************/
uint32_t memory::get_size() const {
    return mem.size();
}

/**
 * Returns the value in the given memory address.
 * 
 * Checks if the address is in the vector, if it
 * is, return the value in that address. If not,
 * we return 0.
 * 
 * @param addr A memory address that we want to check
 *             the element of.
 * 
 * @return A uint8_t element in the given memory address 
 ******************************************************/
uint8_t memory::get8(uint32_t addr) const {
    if (!check_illegal(addr))
        return mem[addr];
    else
        return 0;
}

/**
 * Returns the values in the given memory addresses.
 * 
 * Calls the get8 function twice to get two
 * consecutive memory addresses and places them
 * in a uint16_t in little endian order by shifting 
 * the first value 8 bits and then or'ing it against 
 * the second value to flip all of those bits 'on' 
 * creating one 16 bit value from two 8 bit values.
 * 
 * @param addr A memory address that we want to get
 *             the element of.
 * 
 * @return A uint16_t value created by combining two
 *         memory address values.
 **************************************************/
uint16_t memory::get16(uint32_t addr) const {
    uint8_t addrA = get8(addr);
    uint8_t addrB = get8(addr + 1);
    uint16_t fullAddr = addrB << 8 | addrA;
    return fullAddr;
}

/**
 * Returns the values in the given memory addresses.
 * 
 * Calls the get16 function twice to get four
 * consecutive memory addresses and places them
 * in a uint32_t in little endian order by shifting
 * the first value 16 bits and then or'ing it
 * against the second value to flip all of those bits
 * on creating one 32 bit value from two 16 bit ones.
 * 
 * @param addr A memory address that we want to get
 *             the element of.
 * 
 * @return A uint32_t value created by combining
 *         two 16 bit addresses (or 4 8 bit ones).
 ***************************************************/
uint32_t memory::get32(uint32_t addr) const {
    uint16_t addrA = get16(addr);
    uint16_t addrB = get16(addr + 2);
    uint32_t fullAddr = addrB << 16 | addrA;
    return fullAddr;
}

/**
 * Returns the sign extended value in the given memory address.
 * 
 * Calls the get8 function and places the value into 32 bit
 * signed integer, then returns that signed integer.
 * 
 * @param addr A memory address that we want the element of.
 * 
 * @return A int32_t value created by placing the 8 bit value
 *         into it. 
 *************************************************************/
int32_t memory::get8_sx(uint32_t addr) const {
    return (int8_t) get8(addr);
}

/**
 * Returns the sign extended value of a 16 bit memory address.
 * 
 * Calls the get16 function and places the value into a 32 bit
 * signed integer, then returns that signed integer.
 * 
 * @param addr A memory address that we want the element of.
 * 
 * @return A int32_t value created by placing the 16 bit value
 *         into it.
 ************************************************************/
int32_t memory::get16_sx(uint32_t addr) const {
    return (int16_t) get16(addr);
}

/**
 * Returns the sign extended value of a 32 bit memory address.
 * 
 * Calls the get32 function and places the value into a 32 bit
 * signed integer, then returns that signed integer.
 * 
 * @param addr A memory address that we want the element of.
 * 
 * @return A int32_t value created by placing the 32 bit value
 *         into it. 
 ************************************************************/
int32_t memory::get32_sx(uint32_t addr) const {
    return (int32_t) get32(addr);
}

/**
 * Sets the memory address to the given value.
 * 
 * If a memory address location is valid, take the
 * given value and place it in said memory address.
 * If it is not valid, early return.
 * 
 * @param addr A memory address that we want to place
 *             an element into.
 * 
 * @param val An 8 bit value that we are placing into
 *            a memory storage location.
 ***************************************************/
void memory::set8(uint32_t addr, uint8_t val) {
    if (!check_illegal(addr)) {
        mem[addr] = val;
    }
    else
        return;
}

/**
 * Sets the memory addresses to the given values.
 * 
 * Calls the set8 function twice to place a given
 * 16 bit value into two memory locations.
 * 
 * @param addr A memory address that we want to
 *             place an element into.
 * 
 * @param val A 16 bit value that we are placing
 *            into two memory storage locations.
 ***********************************************/
void memory::set16(uint32_t addr, uint16_t val) {
    uint8_t val1 = (uint8_t) (val >> 8);            // Split the 16 bit value into two 8 bit values
    uint8_t val2 = (uint8_t) val;                   // so they can be set consecutively.
    set8(addr, val2);
    set8(addr + 1, val1);
}

/**
 * Sets the memory addresses to the given values.
 * 
 * Calls the set16 function twice to place a given
 * 32 bit value into 4 memory locations.
 * 
 * @param addr A memory address that we want to
 *             place an element into.
 * 
 * @param val A 32 bit value that we are placing
 *            into four memory storage locations.
 ************************************************/
void memory::set32(uint32_t addr, uint32_t val) {
    uint16_t val1 = (uint16_t) (val >> 16);         // As above, split the 32 bit value into two
    uint16_t val2 = (uint16_t) val;                 // 16 bit values to be set consecutively.
    set16(addr, val2);
    set16(addr + 2, val1);
}

/**
 * Prints the contents of memory to standard output.
 * 
 * Dumps the entire contents of simulated memory in hex
 * with the corresponding ASCII characters on the right.
 */
void memory::dump() const {
    std::string str;                                // Created a string to hold the ascii characters.

    for (uint32_t i = 0; i < get_size(); i++) {     // Loop to print each line.

        // Grab the byte and place it into the variable 'ch'.
        // Check if the byte is a printable ascii character or not.
        // If it is, it goes into ch as that character, if not, it goes as a '.'.
        // Append the character to the string 'str'.
        uint8_t ch = get8(i);
        ch = isprint(ch) ? ch : '.';
        str.insert(str.length(), 1, ch);

        if (i % 16 == 0)
            std::cout << std::setw(8) << std::setfill('0') << hex::to_hex32(i) << ": ";

        std::cout << hex::to_hex8(get8(i)) << " ";  // Converts to hex the value of a memory address 'i' and prints it. 

        if (i % 16 == 7)                            // After 8 loops through 'i' we print a space.
            std::cout << " ";

        if (i % 16 == 15) {                         // After 16 loops through 'i' we print the ASCII section.
            std::cout << "*" << str << "*" << std::endl;
            str.clear();
        }
    }
}

/**
 * Attempts to load file into memory.
 * 
 * Opens a file in binary mode and reads its
 * contents into memory. If a file cannot be opened,
 * an error message is printed and we exit.
 * 
 * @param fname a file to be read.
 * 
 * @return false if the file is read as being too big
 *         for our memory or if the file cannot be
 *         opened at all. Returns true if the file is
 *         accessed with no problems.
 ****************************************************/
bool memory::load_file(const std::string &fname) {
    std::ifstream infile(fname, std::ios::in|std::ios::binary);
    
    if (!infile.is_open()) {
        std::cerr << "Error: File " << fname << " failed to open. Ending program." << std::endl;
        return false;
    }
    else {
        uint8_t i;
        infile >> std::noskipws;
        for (uint32_t addr = 0; infile >> i; ++addr) {
            if (check_illegal(addr)) {
                std::cerr << "Program too big." << std::endl;
                infile.close();
                return false;
            }
            set8(addr, i);
        }
        return true;
    }
}
