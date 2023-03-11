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

#ifndef CPU_SINGLE_HART_H
#define CPU_SINGLE_HART_H

#include "rv32i_hart.h"

class cpu_single_hart : public rv32i_hart
{
public:
    /**
     * Construct a new cpu single hart object
     * 
     * @param mem A memory object
     */
    cpu_single_hart(memory &mem) : rv32i_hart(mem) {}
    void run(uint64_t exec_limit);
};

#endif /* CPU_SINGLE_HART_H */
