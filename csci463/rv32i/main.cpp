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

#include <iostream>
#include <unistd.h>
#include <sstream>
#include "hex.h"
#include "memory.h"
#include "registerfile.h"
#include "rv32i_decode.h"
#include "rv32i_hart.h"
#include "cpu_single_hart.h"

using std::cerr;
using std::endl;
using std::cout;

/**
 * Prints an error message and exits the program
 * 
 * Function is called if there is an error opening
 * the file or if there is a problem with the command
 * line calling the program. Prints an error message
 * and exits the program.
 ***************************************************/
static void usage() {
    cerr << "Usage: rv32i [-d] [-i] [-r] [-z] [-l exec-limit] [-m hex-mem-size] infile" << endl;
    cerr << "    -d show disassembly before program execution" << endl;
    cerr << "    -i show instruction printing during execution" << endl;
    cerr << "    -l maximum number of instructions to exec" << endl;
    cerr << "    -m specify memory size (default = 0x100)" << endl;
    cerr << "    -r show register printing during execution" << endl;
    cerr << "    -z show a dump of the regs & memory after simulation" << endl;
    exit(1);
}

/**
 * Decodes and prints each instruction
 * 
 * Calls the decode function and returns a string.
 * Then prints the memory address, instruction hex value
 * and the instruction mnemonic. 
 * 
 * @param mem The memory object we look to decode.
 ******************************************************/
static void disassemble(const memory &mem) {
    for (uint32_t i = 0; i < mem.get_size(); i+=4) {
        rv32i_decode::decode(i, mem.get32(i));
        std::cout << hex::to_hex32(i) << ": " << hex::to_hex32(mem.get32(i)) << "  " << rv32i_decode::decode(i, mem.get32(i)) << std::endl;
    }
}

/**
 * Loads in a file then calls disassemble and dump.
 * 
 * Attempts to load in a file with a certain memory limit.
 * If the file is allowed, the disassemble function is called
 * followed by a dump of the memory object's memory. If the file
 * is not allowed, an error message is displayed. Optional arguments
 * allow for a memory dump, register dump, instruction showing, and
 * ability to limit number of instructions executed.
 * 
 * @param argc The number of arguments written by a user for the program.
 * @param argv The argument vector.
 * @return Returns 0 on a successful run.
 ***********************************************************************/
int main(int argc, char **argv)
{
    bool d_flags = false;
    bool i_flags = false;
    bool r_flags = false;
    bool z_flags = false;
    uint64_t exec_limit = 0; // default execution limit = no limit.
    uint32_t memory_limit = 0x100; // default memory size = 256 bytes
    int opt;
    while ((opt = getopt(argc, argv, "dil:m:rz")) != -1)
    {
        switch (opt)
        {
        case 'd':
            {
                d_flags = true;
            }
            break;
        case 'i':
            {
                i_flags = true;
            }
            break;
        case 'l':                                           
            {
                std::istringstream lss(optarg);
                lss >> std::hex >> exec_limit;
            }
            break;
        case 'm':                                           
            {
                std::istringstream iss(optarg);
                iss >> std::hex >> memory_limit;
            }
            break;
        case 'r':
            {
                r_flags = true;
            }
            break;
        case 'z':
            {
                z_flags = true;
            }
            break;
        default: /* ’?’ */
            usage();
        }
    }

    if (optind >= argc)
        usage(); // missing filename

    memory mem(memory_limit);

    if (!mem.load_file(argv[optind]))
        usage();

    cpu_single_hart cpu(mem);

    if (d_flags)
        disassemble(mem);

    if (i_flags)
        cpu.set_show_instructions(1);
    
    if (r_flags)
        cpu.set_show_registers(1);

    cpu.reset();
    cpu.run(exec_limit);

    if (z_flags) {
        cpu.dump();
        mem.dump();
    }

    return 0;
}
