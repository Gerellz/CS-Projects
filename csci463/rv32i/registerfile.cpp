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

#include "registerfile.h"

/**
 * Construct a new registerfile::registerfile object
 * 
 * Calls the reset function to construct a vector with
 * 32 simulated registers and fills them with the hex
 * value 0xf0f0f0f0 except for the 0th element which is 0.
 *********************************************************/
registerfile::registerfile() {
    reset();
}

/**
 * Destroy the registerfile::registerfile object
 */
registerfile::~registerfile() {
}

/**
 * Resets the registerfile object.
 * 
 * Resizes the register vector to have 32 elements and fills them
 * all with 0xf0f0f0f0 except for register 0 which is always 0.
 */
void registerfile::reset() {
    regs.resize(32, 0xf0f0f0f0);
    regs[0] = 0;
}

/**
 * Sets an element of a registerfile vector to a given value.
 * 
 * @param r The register to be changed.
 * @param val The value being placed into the register.
 */
void registerfile::set(uint32_t r, int32_t val) {
    if (r != 0)
        regs[r] = val;
}

/**
 * Gets a value from the register 
 * 
 * @param r The register being checked.
 * @return The value of a register.
 */
int32_t registerfile::get(uint32_t r) const {
    if (r != 0)
        return regs[r];
    else
        return 0;
}

/**
 * Dumps the 32 registers and displays them in proper form.
 * 
 * Prints all 32 registers at 8 register values per line.  
 * 
 * @param hdr A value to be placed before the registers. Defaults to "".
 */
void registerfile::dump(const std::string &hdr) const {
    for (uint32_t i = 0; i < regs.size(); i++) {
        if (i % 8 == 0)
            std::cout << hdr << std::setw(3) << std::right << render_regs(i);
        
        std::cout << " " << hex::to_hex32(get(i));
        
        if (i % 8 == 3)
            std::cout << " ";
        
        if (i % 8 == 7)
            std::cout << std::endl;
    }
}

/**
 * Helper function to display the registers properly.
 * 
 * Displays every 8th register with an x in front of it
 * aligned to the right.
 * 
 * @param r The register we want to display with an x in front of it.
 * @return Returns the register in "xr" form.
 */
std::string registerfile::render_regs(uint32_t r) {
    std::ostringstream os;
    os << "x" << r;
    return os.str();
}
