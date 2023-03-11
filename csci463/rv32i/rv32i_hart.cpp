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
#include "rv32i_hart.h"
#include <iostream>
#include <iomanip>

/**
 * Resets the rv32i_hart and calls regs.reset().
 * 
 * Sets the pc to 0, resets the registers, sets the instruction
 * counter to 0 and turns the halt off so the rv32i can run.
 *************************************************************/
void rv32i_hart::reset() {
    pc = 0;
    regs.reset();
    insn_counter = 0;
    halt = false;
    halt_reason = "none";
}

/**
 * Dumps the registers and then prints the pc register.
 * 
 * Calls the register dump function and then prints
 * the pc register value underneath it.
 * 
 * @param hdr A string placed before the registers.
 *****************************************************/
void rv32i_hart::dump(const std::string &hdr) const {
    regs.dump(hdr);
    std::cout << hdr << " pc " << hex::to_hex32(pc) << std::endl;
}

/**
 * Tells the sim to execute instructions.
 * 
 * Checks for halts to stop the simulator, if there is none
 * it executes instructions. If show_instructions is on, it
 * prints the instructions. If show_registers is on, it prints
 * the registers.
 * 
 * @param hdr A string printed on the left of all output.
 ************************************************************/
void rv32i_hart::tick(const std::string &hdr) {
    if (halt)
        return;

    if (show_registers)
        dump(hdr);

    if (pc % 4 != 0) {
        halt = true;
        halt_reason = "PC alignment error";
        return;
    }

    insn_counter++;
    uint32_t insn = mem.get32(pc);

    if (show_instructions) {
        std::cout << hdr << to_hex32(pc) << ": " << to_hex32(insn) << "  ";
        exec(insn, &std::cout);
    }
    else
        exec(insn, nullptr);
}

/**
 * Executes instructions based on opcode.
 * 
 * Switch statement that determines which instruction to
 * execute. If an opcode is not registered to an instruction,
 * it calls the illegal instruction.
 * 
 * @param insn An instruction to be read and executed.
 * @param pos An ostream object that contains the printed executed instruction.
 *****************************************************************************/
void rv32i_hart::exec(uint32_t insn, std::ostream* pos) {
    switch(get_opcode(insn)) {
        default:                exec_illegal_insn(insn, pos); return;
        case opcode_lui:        exec_lui(insn, pos); return;
        case opcode_auipc:      exec_auipc(insn, pos); return;
        case opcode_jal:        exec_jal(insn, pos); return;
        case opcode_jalr:       exec_jalr(insn, pos); return;     
        case opcode_btype:
            switch(get_funct3(insn)) {
                default:            exec_illegal_insn(insn, pos); return; 
                case funct3_beq:    exec_beq(insn, pos); return;
                case funct3_bne:    exec_bne(insn, pos); return;    
                case funct3_blt:    exec_blt(insn, pos); return;
                case funct3_bge:    exec_bge(insn, pos); return;
                case funct3_bltu:   exec_bltu(insn, pos); return;
                case funct3_bgeu:   exec_bgeu(insn, pos); return;
            }
        case opcode_load_imm:
            switch(get_funct3(insn)) {
                default:            exec_illegal_insn(insn, pos); return;
                case funct3_lb:     exec_lb(insn, pos); return;
                case funct3_lh:     exec_lh(insn, pos); return;
                case funct3_lw:     exec_lw(insn, pos); return;
                case funct3_lbu:    exec_lbu(insn, pos); return;
                case funct3_lhu:    exec_lhu(insn, pos); return;
            }
        case opcode_stype:
            switch(get_funct3(insn)) {
                default:            exec_illegal_insn(insn, pos); return;
                case funct3_sb:     exec_sb(insn, pos); return;
                case funct3_sh:     exec_sh(insn, pos); return;
                case funct3_sw:     exec_sw(insn, pos); return;
            }
        case opcode_alu_imm:
            switch(get_funct3(insn)) {
                case funct3_add:    exec_addi(insn, pos); return;
                case funct3_slt:    exec_slti(insn, pos); return;
                case funct3_sltu:   exec_sltiu(insn, pos); return;
                case funct3_xor:    exec_xori(insn, pos); return;
                case funct3_or:     exec_ori(insn, pos); return;
                case funct3_and:    exec_andi(insn, pos); return;
                case funct3_sll:    exec_slli(insn, pos); return;
                case funct3_srx:
                    switch(get_funct7(insn)) {
                        default:            exec_illegal_insn(insn, pos); return;
                        case funct7_sra:    exec_srai(insn, pos); return;
                        case funct7_srl:    exec_srli(insn, pos); return;
                    }
            }
        case opcode_rtype:
            switch(get_funct3(insn)) {
                default:        exec_illegal_insn(insn, pos); return;
                case funct3_add:
                    switch(get_funct7(insn)) {
                        default:            exec_illegal_insn(insn, pos); return;
                        case funct7_add:    exec_add(insn, pos); return;
                        case funct7_sub:    exec_sub(insn, pos); return;
                    }
                case funct3_sll:        exec_sll(insn, pos); return;
                case funct3_slt:        exec_slt(insn, pos); return;
                case funct3_sltu:       exec_sltu(insn, pos); return;
                case funct3_xor:        exec_xor(insn, pos); return;
                case funct3_srx:
                    switch(get_funct7(insn)) {
                        default:            exec_illegal_insn(insn, pos); return;
                        case funct7_srl:    exec_srl(insn, pos); return;
                        case funct7_sra:    exec_sra(insn, pos); return;
                    }
                case funct3_or:         exec_or(insn, pos); return;
                case funct3_and:        exec_and(insn, pos); return;
            }
        case opcode_system:
            switch(get_funct3(insn)) {
                default:        exec_illegal_insn(insn, pos); return;
                case funct3_add:
                    switch(insn) {
                        case insn_ecall:        exec_ecall(insn, pos); return;
                        case insn_ebreak:       exec_ebreak(insn, pos); return;
                    }
                case funct3_csrrs:      exec_csrrs(insn, pos); return;
            }
    }
}

/**
 * Halts the program and calls render_illegal_insn().
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 ******************************************************************************/
void rv32i_hart::exec_illegal_insn(uint32_t insn, std::ostream* pos) {
    (void)insn;
    if (pos)
        *pos << render_illegal_insn();
    halt = true;
    halt_reason = "Illegal instruction";
}

/**
 * Executes and prints the lui instruction.
 * 
 * Sets the rd's register to the imm_u value and increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_lui(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    int32_t imm_u = get_imm_u(insn);

    if (pos) {
        std::string s = render_lui(insn);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(imm_u) << std::endl;
    }
    regs.set(rd, imm_u);
    pc += 4;
}

/**
 * Executes and prints the auipc instruction.
 * 
 * Sets the rd's register to pc + imm_u and increments the pc by 4.
 *   
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_auipc(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    int32_t imm_u = get_imm_u(insn);

    int32_t val = pc + imm_u;

    if (pos) {
        std::string s = render_auipc(insn);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(pc) << " + " << hex::to_hex0x32(imm_u) << 
            " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the jal instruction.
 * 
 * Sets the rd's register to the pc + 4 and then increments the pc by imm_j.
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_jal(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    int32_t imm_j = get_imm_j(insn);

    int32_t val = pc + imm_j;
    int32_t next_val = pc + 4;

    if (pos) {
        std::string s = render_jal(pc, insn);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(next_val) << ",  pc = " << hex::
            to_hex0x32(pc) << " + " << hex::to_hex0x32(imm_j) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, next_val);
    pc = val;
}

/**
 * Executes and prints the jalr instruction.
 * 
 * Sets the rd's register to the pc + 4 and then increments the pc by the value in rs1
 * + the imm_i value &'ed with 0xfffffffe.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_jalr(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    int32_t val = (regs.get(rs1) + imm_i) & 0xfffffffe;
    int32_t next_val = pc + 4;

    if (pos) {
        std::string s = render_jalr(insn);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(next_val) << ",  pc = (" << hex::
            to_hex0x32(imm_i) << " + " << hex::to_hex0x32(regs.get(rs1)) << ") & 0xfffffffe = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, next_val);
    pc = val;
}

/**
 * Executes and prints the beq instruction.
 * 
 * If the rs1 and rs2 values are the same, increment the pc by imm_b, if
 * they are not equal, increment the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_beq(uint32_t insn, std::ostream* pos) {
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t val;

    if (regs.get(rs1) == regs.get(rs2))
        val = pc + imm_b;
    else
        val = pc + 4;

    if (pos) {
        std::string s = render_btype(pc, insn, "beq    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " == " << hex::to_hex0x32(regs.get(rs2)) <<
            " ? " << hex::to_hex0x32(imm_b) << " : " << 4 << ") = " << hex::to_hex0x32(val) << std::endl;
    }
    pc = val;
}

/**
 * Executes and prints the bne instruction.
 * 
 * If the rs1 and rs2 values are not the same, increment the pc by imm_b,
 * if they are the same, increment the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_bne(uint32_t insn, std::ostream* pos) {
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t val;

    if (regs.get(rs1) != regs.get(rs2))
        val = pc + imm_b;
    else
        val = pc + 4;

    if (pos) {
        std::string s = render_btype(pc, insn, "bne    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " != " << hex::to_hex0x32(regs.get(rs2)) <<
            " ? " << hex::to_hex0x32(imm_b) << " : " << 4 << ") = " << hex::to_hex0x32(val) << std::endl;
    }
    pc = val;
}

/**
 * Executes and prints the blt instruction.
 * 
 * If the rs1 value is less than the rs2 value, increment the pc by imm_b,
 * otherwise increment the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_blt(uint32_t insn, std::ostream* pos) {
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t val;

    if (regs.get(rs1) < regs.get(rs2))
        val = pc + imm_b;
    else
        val = pc + 4;

    if (pos) {
        std::string s = render_btype(pc, insn, "blt    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " < " << hex::to_hex0x32(regs.get(rs2)) <<
            " ? " << hex::to_hex0x32(imm_b) << " : " << 4 << ") = " << hex::to_hex0x32(val) << std::endl;
    }
    pc = val;
}

/**
 * Executes and prints the bge instruction.
 * 
 * If the rs1 value is greater than or equal to the rs2 value, increment
 * the pc by imm_b. Otherwise increment the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_bge(uint32_t insn, std::ostream* pos) {
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t val;

    if (regs.get(rs1) >= regs.get(rs2))
        val = pc + imm_b;
    else
        val = pc + 4;

    if (pos) {
        std::string s = render_btype(pc, insn, "bge    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " >= " << hex::to_hex0x32(regs.get(rs2)) <<
            " ? " << hex::to_hex0x32(imm_b) << " : " << 4 << ") = " << hex::to_hex0x32(val) << std::endl; 
    }
    pc = val;
}

/**
 * Executes and prints the bltu instruction.
 * 
 * If the rs1 value is less than the rs2 value, increment the pc by imm_b.
 * Otherwise, increment the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_bltu(uint32_t insn, std::ostream* pos) {
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t val;

    if ((uint32_t)regs.get(rs1) < (uint32_t)regs.get(rs2))
        val = pc + imm_b;
    else
        val = pc + 4;

    if (pos) {
        std::string s = render_btype(pc, insn, "bltu   ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " <U " << hex::to_hex0x32(regs.get(rs2)) <<
            " ? " << hex::to_hex0x32(imm_b) << " : " << 4 << ") = " << hex::to_hex0x32(val) << std::endl;
    }
    pc = val;
}

/**
 * Executes and prints the bgeu instruction.
 * 
 * If the rs1 value is greater than or equal to the rs2 value, increment
 * the pc by imm_b. Otherwise, increment the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_bgeu(uint32_t insn, std::ostream* pos) {
    int32_t rs1 = get_rs1(insn);
    int32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t val;

    if ((uint32_t)regs.get(rs1) >= (uint32_t)regs.get(rs2))
        val = pc + imm_b;
    else
        val = pc + 4;

    if (pos) {
        std::string s = render_btype(pc, insn, "bgeu   ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " >=U " << hex::to_hex0x32(regs.get(rs2)) <<
            " ? " << hex::to_hex0x32(imm_b) << " : " << 4 << ") = " << hex::to_hex0x32(val) << std::endl;
    }
    pc = val;
}

/**
 * Executes and prints the addi instruction.
 * 
 * Sets the rd's register to the rs1 value + imm_i.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_addi(uint32_t insn, std::ostream* pos) {
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    int32_t val;

    val = regs.get(rs1) + imm_i;

    if (pos) {
        std::string s = render_itype_alu(insn, "addi   ", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " + " <<
            hex::to_hex0x32(imm_i) << " = " << hex::to_hex0x32(val) << std::endl; 
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the lbu instruction.
 * 
 * Sets the rd's register to the value of the zero-extended byte
 * fetched from the memory address given by rs1 + imm_i. Increments
 * the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_lbu(uint32_t insn, std::ostream* pos) {
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    uint32_t val = regs.get(rs1) + imm_i;
    uint32_t mval = mem.get8(val) & 0x000000ff;

    if (pos) {
        std::string s = render_itype_load(insn, "lbu    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = zx(m8(" << hex::to_hex0x32(regs.get(rs1)) << " + " <<
            hex::to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(mval) << std::endl;
    }
    regs.set(rd, mval);
    pc += 4;
}

/**
 * Executes and prints the lhu instruction.
 * 
 * Sets the rd's register to the value of the zero-extended 16 bit
 * value fetched from the memory address given by rs1 + imm_i. 
 * Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_lhu(uint32_t insn, std::ostream* pos) {
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    uint32_t val = regs.get(rs1) + imm_i;
    uint32_t mval = mem.get16(val) & 0x0000ffff;

    if (pos) {
        std::string s = render_itype_load(insn, "lhu    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = zx(m16(" << hex::to_hex0x32(regs.get(rs1)) << " + " <<
            hex::to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(mval) << std::endl;
    }
    regs.set(rd, mval);
    pc += 4;
}

/**
 * Executes and prints the lb instruction.
 * 
 * Sets the rd's register to the sign extended byte fetched
 * from the memory address of rs1 + imm_i. Increments the pc
 * by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_lb(uint32_t insn, std::ostream* pos) {
    int8_t rd = get_rd(insn);
    int8_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    uint32_t val = regs.get(rs1) + imm_i;
    uint32_t mval = mem.get8_sx(val);

    if (pos) {
        std::string s = render_itype_load(insn, "lb     ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = sx(m8(" << hex::to_hex0x32(regs.get(rs1)) << " + " << 
            hex::to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(mval) << std::endl; 
    }
    regs.set(rd, mval);
    pc += 4;
}

/**
 * Executes and prints the lh instruction.
 * 
 * Sets the rd's register to the sign extended 16 bits fetched from
 * the memory address of rs1 + imm_i. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_lh(uint32_t insn, std::ostream* pos) {
    int16_t rd = get_rd(insn);
    int16_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    uint32_t val = regs.get(rs1) + imm_i;
    uint32_t mval = mem.get16_sx(val);

    if (pos) {
        std::string s = render_itype_load(insn, "lh     ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = sx(m16(" << hex::to_hex0x32(regs.get(rs1)) << " + " <<
            hex::to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(mval) << std::endl;
    }
    regs.set(rd, mval);
    pc += 4;
}

/**
 * Executes and prints the lw instruction.
 * 
 * Sets the rd's register to the sign extended 32 bits fetched from
 * the memory address of rs1 + imm_i. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_lw(uint32_t insn, std::ostream* pos) {
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    uint32_t val = regs.get(rs1) + imm_i;
    uint32_t mval = mem.get32_sx(val);

    if (pos) {
        std::string s = render_itype_load(insn, "lw     ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = sx(m32(" << hex::to_hex0x32(regs.get(rs1)) << " + " <<
            hex::to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(mval) << std::endl;
    }
    regs.set(rd, mval);
    pc += 4;
}

/**
 * Executes and prints the sb instruction.
 * 
 * Sets the byte of memory at the address given by rs1 + imm_s to
 * the lowest 8 bits of the rs2 value. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_sb(uint32_t insn, std::ostream* pos) {
    int8_t rs1 = get_rs1(insn);
    int8_t rs2 = get_rs2(insn);
    int32_t imm_s = get_imm_s(insn);

    uint32_t val = regs.get(rs1) + imm_s;
    uint32_t mval = regs.get(rs2) & 0x000000ff;

    if (pos) {
        std::string s = render_stype(insn, "sb     ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// m8(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::to_hex0x32(imm_s) << ") = " <<
            hex::to_hex0x32(mval) << std::endl;
    }
    mem.set8(val, mval);
    pc += 4;
}

/**
 * Executes and prints the sh instruction.
 * 
 * Sets the 16 bits of memory at the address given by rs1 + imm_s to
 * the lowest 16 bits of the rs2 value. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_sh(uint32_t insn, std::ostream* pos) {
    int8_t rs1 = get_rs1(insn);
    int8_t rs2 = get_rs2(insn);
    int32_t imm_s = get_imm_s(insn);

    uint32_t val = regs.get(rs1) + imm_s;
    uint32_t mval = regs.get(rs2) & 0x0000ffff;

    if (pos) {
        std::string s = render_stype(insn, "sh     ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// m16(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::to_hex0x32(imm_s) << ") = " <<
            hex::to_hex0x32(mval) << std::endl;
    }
    mem.set16(val, mval);
    pc += 4;
}

/**
 * Executes and prints the sw instruction.
 * 
 * Sets the 32 bits of memory at the address given by the rs1 + imm_s
 * to the 32 bits of the rs2 value. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_sw(uint32_t insn, std::ostream* pos) {
    int8_t rs1 = get_rs1(insn);
    int8_t rs2 = get_rs2(insn);
    int32_t imm_s = get_imm_s(insn);

    uint32_t val = regs.get(rs1) + imm_s;
    uint32_t mval = regs.get(rs2);

    if (pos) {
        std::string s = render_stype(insn, "sw     ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// m32(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::to_hex0x32(imm_s) << ") = " <<
            hex::to_hex0x32(mval) << std::endl;
    }
    mem.set32(val, mval);
    pc += 4;
}

/**
 * Executes and prints the slti instruction.
 * 
 * If the signed value of rs1 is less than the imm_i value, sets the
 * rd's register to 1 otherwise set it to 0. Increment the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_slti(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn); 
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    int32_t val = ((int32_t)regs.get(rs1) < imm_i) ? 1 : 0;

    if (pos) {
        std::string s = render_itype_alu(insn, "slti   ", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = (" << hex::to_hex0x32(regs.get(rs1)) << " < " << imm_i <<
            ") ? 1 : 0 = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the sltiu instruction.
 * 
 * If the unsigned value of rs1 is less than the imm_i value, sets the
 * rd's register to 1 otherwise sets it to 0. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_sltiu(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn); 
    uint32_t rs1 = get_rs1(insn);
    uint32_t imm_i = get_imm_i(insn);

    uint32_t val = ((uint32_t)regs.get(rs1) < imm_i) ? 1 : 0;

    if (pos) {
        std::string s = render_itype_alu(insn, "sltiu  ", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = (" << hex::to_hex0x32(regs.get(rs1)) << " <U " << imm_i <<
            ") ? 1 : 0 = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the xori instruction.
 * 
 * Sets the rd's register value to the bitwise XOR of rs1 and imm_i.
 * Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_xori(uint32_t insn, std::ostream* pos) {
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    int32_t val = regs.get(rs1) ^ imm_i;

    if (pos) {
        std::string s = render_itype_alu(insn, "xori   ", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " ^ " <<
            hex::to_hex0x32(imm_i) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the ori instruction.
 * 
 * Sets the rd's register value to the bitwise or of rs1 and imm_i.
 * Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_ori(uint32_t insn, std::ostream* pos) {
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    int32_t val = regs.get(rs1) | imm_i;

    if (pos) {
        std::string s = render_itype_alu(insn, "ori    ", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " | " <<
            hex::to_hex0x32(imm_i) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the andi instruction.
 * 
 * Sets the rd's register value to the bitwise AND of rs1 and imm_i.
 * Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_andi(uint32_t insn, std::ostream* pos) {
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);

    int32_t val = regs.get(rs1) & imm_i;

    if (pos) {
        std::string s = render_itype_alu(insn, "andi   ", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " & " <<
            hex::to_hex0x32(imm_i) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;    
}

/**
 * Executes and prints the slli instruction.
 * 
 * Shifts rs1 left by the shamt_i value and sets that as the rd's register
 * value. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_slli(uint32_t insn, std::ostream* pos) {
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    int8_t shamt_i = imm_i & 0x1f;

    int32_t val = regs.get(rs1) << shamt_i;

    if (pos) {
        std::string s = render_itype_alu(insn, "slli   ", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " << " <<
            imm_i << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the srli instruction.
 * 
 * Logical shifts the rs1 value right by the shamt_i value and sets
 * that as the rd's register value. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_srli(uint32_t insn, std::ostream* pos) {
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    int8_t shamt_i = imm_i & 0x1f;

    imm_i = imm_i & 0xbff;

    int32_t val = (uint32_t)regs.get(rs1) >> shamt_i;

    if (pos) {
        std::string s = render_itype_alu(insn, "srli   ", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " <<
            imm_i << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the srai instruction.
 * 
 * Arithmetically shifts the rs1 value right by the shamt_i value and
 * sets that as the rd's register value. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_srai(uint32_t insn, std::ostream* pos) {
    int32_t rd = get_rd(insn);
    int32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    int8_t shamt_i = imm_i & 0x1f;

    imm_i = imm_i & 0xbff;

    int32_t val = regs.get(rs1) >> shamt_i;

    if (pos) {
        std::string s = render_itype_alu(insn, "srai   ", imm_i);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " <<
            imm_i << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the add instruction.
 * 
 * Sets the rd's register to rs1 + rs2. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_add(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    uint32_t val = regs.get(rs1) + regs.get(rs2);

    if (pos) {
        std::string s = render_rtype(insn, "add    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " + " <<
            hex::to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the sub instruction.
 * 
 * Sets the rd's register to rs1 - rs2. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_sub(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    uint32_t val = regs.get(rs1) - regs.get(rs2);

    if (pos) {
        std::string s = render_rtype(insn, "sub    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " - " <<
            hex::to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the sll instruction.
 * 
 * Shifts the rs1 value left by the 5 least significant bits of rs2
 * and sets rd's register to that value. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_sll(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    int32_t shamt = regs.get(rs2) & 0x1f;
    int32_t val = (regs.get(rs1) << (regs.get(rs2) & 0x1f));

    if (pos) {
        std::string s = render_rtype(insn, "sll    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " << " <<
            shamt << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the slt instruction.
 * 
 * If the rs1 value is less than the rs2 value, the rd's register is
 * set to 1. If it is greater, it is set to 0. Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_slt(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    int32_t val = (regs.get(rs1) < regs.get(rs2)) ? 1 : 0;

    if (pos) {
        std::string s = render_rtype(insn, "slt    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = (" << hex::to_hex0x32(regs.get(rs1)) << " < " << hex::
            to_hex0x32(regs.get(rs2)) << ") ? 1 : 0 = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the sltu instruction.
 * 
 * If the unsigned rs1 value is less than the unsigned rs2 value
 * sets the rd's register value to 1, otherwise sets it to 0. Increments
 * the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_sltu(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    int32_t val = (regs.get(rs1) < regs.get(rs2)) ? 1 : 0;

    if (pos) {
        std::string s = render_rtype(insn, "sltu  ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = (" << hex::to_hex0x32(regs.get(rs1)) << " <U " << hex::
            to_hex0x32(regs.get(rs2)) << ") ? 1 : 0 = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;    
}

/**
 * Executes and prints the xor instruction.
 * 
 * Sets the rd's register value to the XOR between rs1 and rs2.
 * Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_xor(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    int32_t val = regs.get(rs1) ^ regs.get(rs2);

    if (pos) {
        std::string s = render_rtype(insn, "xor    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " ^ " <<
            hex::to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the srl instruction.
 * 
 * Logically shifts the rs1 value by the 5 least significant bits
 * of the rs2 register and sets rd's register value to it. Increments
 * the pc by 4. 
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_srl(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    int32_t shamt = regs.get(rs2) & 0x1f;
    int32_t val = ((uint32_t)regs.get(rs1) >> shamt);

    if (pos) {
        std::string s = render_rtype(insn, "srl    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " <<
            shamt << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the sra instruction.
 * 
 * Arithmetically shifts the rs1 value by the 5 least significant bits
 * of the rs2 register and sets rd's register value to it. Increments
 * the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_sra(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    int32_t shamt = regs.get(rs2) & 0x1f;
    int32_t val = (regs.get(rs1) >> shamt);

    if (pos) {
        std::string s = render_rtype(insn, "sra    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " <<
            shamt << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the or instruction.
 * 
 * Sets the rd's register value to the OR between rs1 and rs2.
 * Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_or(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    int32_t val = regs.get(rs1) | regs.get(rs2);

    if (pos) {
        std::string s = render_rtype(insn, "or     ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " | " <<
            hex::to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the and instruction.
 * 
 * Sets the rd's register value to the AND between rs1 and rs2.
 * Increments the pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_and(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    int32_t val = regs.get(rs1) & regs.get(rs2);

    if (pos) {
        std::string s = render_rtype(insn, "and    ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " & " <<
            hex::to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
 * Executes and prints the csrrs instruction.
 * 
 * Sets the rd's register value to the mhartid value which is 0 by
 * default. If the csrrx instruction is anything but csrrs, it is
 * an illegal instruction and the program is halted. Increments the
 * pc by 4.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_csrrs(uint32_t insn, std::ostream* pos) {
    uint32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    int32_t csr = imm_i & 0x00000fff;

    if (csr != 0xf14) {
        halt = true;
        halt_reason = "Illegal CSR in CRRSS instruction";
    }

    if (pos) {
        std::string s = render_csrrx(insn, "csrrs  ");
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// " << render_reg(rd) << " = " << mhartid << std::endl;
    }
    regs.set(rd, mhartid);
    pc += 4;
}

/**
 * Executes and prints the ecall instruction.
 * 
 * Halts the program and states the reason as ECALL.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_ecall(uint32_t insn, std::ostream* pos) {
    if (pos) {
        std::string s = render_ecall(insn);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s << std::endl;
    }
    halt = true;
    halt_reason = "ECALL instruction";
}

/**
 * Executes and prints the ebreak instruction.
 * 
 * Halts the program and states the reason as EBREAK.
 * 
 * @param insn An instruction to be read.
 * @param pos An ostream object that contains the printed execution instruction.
 */
void rv32i_hart::exec_ebreak(uint32_t insn, std::ostream* pos) {
    if (pos) {
        std::string s = render_ebreak(insn);
        *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s;
        *pos << "// HALT" << std::endl;
    }
    halt = true;
    halt_reason = "EBREAK instruction";
}
