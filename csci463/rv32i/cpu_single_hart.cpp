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

#include "cpu_single_hart.h"
#include "rv32i_hart.h"
#include "registerfile.h"
#include "hex.h"
#include <iostream>

/**
 * Runs the cpu simulator and executes the instructions.
 * 
 * Checks the execution limit given by the user and executes as many
 * instructions as requested. Also sets register 2 to the size of the
 * memory. If the machine is halted for any reason, it displays the
 * reason for halting and prints how many instructions were executed. 
 * 
 * @param exec_limit The maximum number of instructions to execute.
 *                   If the value is 0, run until there are none left.
 */
void cpu_single_hart::run(uint64_t exec_limit) {
    regs.set(2, mem.get_size());

    if (exec_limit == 0) {
        while (!is_halted())
            tick();
    }

    if (exec_limit != 0) {
        while (!is_halted() && get_insn_counter() < exec_limit)
            tick();
    }

    if (is_halted())
        std::cout << "Execution terminated. Reason: " << get_halt_reason() << std::endl;

    std::cout << get_insn_counter() << " instructions executed" << std::endl;
}
