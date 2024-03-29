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

#ifndef RV32I_HART_H
#define RV32I_HART_H

#include "registerfile.h"
#include "memory.h"
#include "rv32i_decode.h"

class rv32i_hart : public rv32i_decode
{
public:
    /**
     * Construct a new rv32i hart object
     * 
     * @param m A memory object.
     */
    rv32i_hart(memory &m) : mem(m) { }
    /**
     * Set the show instructions to true or false.
     * 
     * @param b Boolean, defaults to false.
     */
    void set_show_instructions(bool b) { show_instructions = b; }
    /**
     * Set the show registers to true or false.
     * 
     * @param b Boolean, defaults to false.
     */
    void set_show_registers(bool b) { show_registers = b; }
    /**
     * Determines if the program is halted.
     * 
     * @return If program is halted, returns true.
     * @return If program is not halted, returns false.
     */
    bool is_halted() const { return halt; }
    /**
     * Get the halt reason
     * 
     * @return A string containing the reason for halting.
     */
    const std::string &get_halt_reason() const { return halt_reason; }
    /**
     * Gets the insn counter 
     * 
     * @return The value of the instruction counter.
     */
    uint64_t get_insn_counter() const { return insn_counter; }
    /**
     * Sets the mhartid to a value.
     * 
     * @param i A value to set the mhartid. Defaults to 0.
     */
    void set_mhartid(int i) { mhartid = i; }

    void tick(const std::string &hdr="");
    void dump(const std::string &hdr="") const;
    void reset();

private:
    static constexpr int instruction_width          = 35;
    void exec(uint32_t insn, std::ostream*);
    void exec_illegal_insn(uint32_t insn, std::ostream*);
    void exec_lui(uint32_t insn, std::ostream*);
    void exec_auipc(uint32_t insn, std::ostream*);
    void exec_jal(uint32_t insn, std::ostream*);
    void exec_jalr(uint32_t insn, std::ostream*);
    void exec_beq(uint32_t insn, std::ostream*);
    void exec_bne(uint32_t insn, std::ostream*);
    void exec_blt(uint32_t insn, std::ostream*);
    void exec_bge(uint32_t insn, std::ostream*);
    void exec_bltu(uint32_t insn, std::ostream*);
    void exec_bgeu(uint32_t insn, std::ostream*);
    void exec_lb(uint32_t insn, std::ostream*);
    void exec_lh(uint32_t insn, std::ostream*);
    void exec_lw(uint32_t insn, std::ostream*);
    void exec_lbu(uint32_t insn, std::ostream*);
    void exec_lhu(uint32_t insn, std::ostream*);
    void exec_sb(uint32_t insn, std::ostream*);
    void exec_sh(uint32_t insn, std::ostream*);
    void exec_sw(uint32_t insn, std::ostream*);
    void exec_addi(uint32_t insn, std::ostream*);
    void exec_slti(uint32_t insn, std::ostream*);
    void exec_sltiu(uint32_t insn, std::ostream*);
    void exec_xori(uint32_t insn, std::ostream*);
    void exec_ori(uint32_t insn, std::ostream*);
    void exec_andi(uint32_t insn, std::ostream*);
    void exec_slli(uint32_t insn, std::ostream*);
    void exec_srai(uint32_t insn, std::ostream*);
    void exec_srli(uint32_t insn, std::ostream*);
    void exec_add(uint32_t insn, std::ostream*);
    void exec_sub(uint32_t insn, std::ostream*);
    void exec_sll(uint32_t insn, std::ostream*);
    void exec_slt(uint32_t insn, std::ostream*);
    void exec_sltu(uint32_t insn, std::ostream*);
    void exec_xor(uint32_t insn, std::ostream*);
    void exec_srl(uint32_t insn, std::ostream*);
    void exec_sra(uint32_t insn, std::ostream*);
    void exec_or(uint32_t insn, std::ostream*);
    void exec_and(uint32_t insn, std::ostream*);
    void exec_ecall(uint32_t insn, std::ostream*);
    void exec_ebreak(uint32_t insn, std::ostream*);
    void exec_csrrs(uint32_t insn, std::ostream*);

    bool halt = { false };
    std::string halt_reason = { "none" };
    uint32_t mhartid = { 0 };
    bool show_instructions = { false };
    bool show_registers = { false };

    uint64_t insn_counter = { 0 };
    uint32_t pc = { 0 };

protected:
    registerfile regs;
    memory &mem;
};

#endif /* RV32I_HART_H */
