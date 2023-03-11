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

#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "hex.h"

class registerfile : public hex
{
public:
    registerfile();
    ~registerfile();

    void reset();
    void set(uint32_t r, int32_t val);
    int32_t get(uint32_t r) const;
    void dump(const std::string &hdr) const;

protected:
    static std::string render_regs(uint32_t r);

private:
    std::vector<uint32_t> regs;
};

#endif /* REGISTERFILE_H */
