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

#include "rv32i_decode.h"

/**
 * Disassembles any instruction.
 * 
 * Decodes the given 32 bit instruction and returns a string
 * with the instruction name and correct form of rendering to output.
 * Has a switch statement that determines, based on the opcode,
 * which instruction to render. If the opcode is shared by many instructions,
 * another switch statement is made to differentiate them based on factors
 * such as the funct3 or funct7 bits of the 32 bit instruction.
 * 
 * @param addr The address from which the instruction is grabbed.
 * @param insn The instruction being decoded.
 * @return Returns a string that formats the output correctly
 *         showing the instruction name and its arguments.
 ***************************************************************************/
std::string rv32i_decode::decode(uint32_t addr, uint32_t insn) {
    switch(get_opcode(insn)) {
        default:             return render_illegal_insn();
        case opcode_lui:     return render_lui(insn);
        case opcode_auipc:   return render_auipc(insn);
        case opcode_jal:     return render_jal(addr, insn);
        case opcode_jalr:    return render_jalr(insn);
        case opcode_btype:
            switch(get_funct3(insn)) {
                default:            return render_illegal_insn();
                case funct3_beq:    return render_btype(addr, insn, "beq");
                case funct3_bne:    return render_btype(addr, insn, "bne");
                case funct3_blt:    return render_btype(addr, insn, "blt");
                case funct3_bge:    return render_btype(addr, insn, "bge");
                case funct3_bltu:   return render_btype(addr, insn, "bltu");
                case funct3_bgeu:   return render_btype(addr, insn, "bgeu");
            }
            assert(0 && "unrecognized funct3"); // impossible

        case opcode_load_imm:
            switch(get_funct3(insn)) {
                default:            return render_illegal_insn();
                case funct3_lb:     return render_itype_load(insn, "lb");
                case funct3_lh:     return render_itype_load(insn, "lh");
                case funct3_lw:     return render_itype_load(insn, "lw");
                case funct3_lbu:    return render_itype_load(insn, "lbu");
                case funct3_lhu:    return render_itype_load(insn, "lhu");
            }
            assert(0 && "unrecognized funct3"); // impossible

        case opcode_stype:
            switch(get_funct3(insn)) {
                default:            return render_illegal_insn();
                case funct3_sb:     return render_stype(insn, "sb");
                case funct3_sh:     return render_stype(insn, "sh");
                case funct3_sw:     return render_stype(insn, "sw");
            }
            assert(0 && "unrecognized funct3"); // impossible

        case opcode_alu_imm:
            switch(get_funct3(insn)) {
                default:            return render_illegal_insn();
                case funct3_add:    return render_itype_alu(insn, "addi", get_imm_i(insn));
                case funct3_slt:    return render_itype_alu(insn, "slti", get_imm_i(insn));
                case funct3_sltu:   return render_itype_alu(insn, "sltiu", get_imm_i(insn));
                case funct3_xor:    return render_itype_alu(insn, "xori", get_imm_i(insn));
                case funct3_or:     return render_itype_alu(insn, "ori", get_imm_i(insn));
                case funct3_and:    return render_itype_alu(insn, "andi", get_imm_i(insn));
                case funct3_sll:    return render_itype_alu(insn, "slli", get_imm_i(insn)%XLEN);
                case funct3_srx:
                    switch(get_funct7(insn)) {
                        default:            return render_illegal_insn();
                        case funct7_sra:    return render_itype_alu(insn, "srai", get_imm_i(insn)%XLEN);
                        case funct7_srl:    return render_itype_alu(insn, "srli", get_imm_i(insn)%XLEN);
                    }
                    assert(0 && "unrecognized funct7"); // impossible
            }
            assert(0 && "unrecognized funct3"); // impossible

        case opcode_rtype:
            switch(get_funct3(insn)) {
                default:            return render_illegal_insn();
                case funct3_add:
                    switch(get_funct7(insn)) {
                        default:            return render_illegal_insn();
                        case funct7_add:    return render_rtype(insn, "add");
                        case funct7_sub:    return render_rtype(insn, "sub");
                    }
                    assert(0 && "unrecognized funct7"); // impossible
                case funct3_sll:    return render_rtype(insn, "sll");
                case funct3_slt:    return render_rtype(insn, "slt");
                case funct3_sltu:   return render_rtype(insn, "sltu");
                case funct3_xor:    return render_rtype(insn, "xor");
                case funct3_srx:    
                    switch(get_funct7(insn)) {
                        default:            return render_illegal_insn();
                        case funct7_srl:    return render_rtype(insn, "srl");
                        case funct7_sra:    return render_rtype(insn, "sra");
                    }
                    assert(0 && "unrecognized funct7"); // impossible
                case funct3_or:     return render_rtype(insn, "or");
                case funct3_and:    return render_rtype(insn, "and");
            }
            assert(0 && "unrecognized funct3"); // impossible
        case opcode_system:
            switch(get_funct3(insn)) {
                default:            return render_illegal_insn();
                case funct3_add:
                    switch(insn) {
                        default:            return render_illegal_insn();
                        case insn_ecall:    return render_ecall(insn);
                        case insn_ebreak:   return render_ebreak(insn);
                    }
                    assert(0 && "unrecognized funct3"); // impossible
                case funct3_csrrw:  return render_csrrx(insn, "csrrw");
                case funct3_csrrs:  return render_csrrx(insn, "csrrs");
                case funct3_csrrc:  return render_csrrx(insn, "csrrc");
                case funct3_csrrwi: return render_csrrxi(insn, "csrrwi");
                case funct3_csrrsi: return render_csrrxi(insn, "csrrsi");
                case funct3_csrrci: return render_csrrxi(insn, "csrrci");
            }
            assert(0 && "unrecognized funct3"); // impossible
    }
    assert(0 && "unrecognized opcode"); // It should be impossible to ever get here!
}

/**
 * Gets the opcode from the 32 bit value of an instruction.
 * 
 * Checks an instruction against a hex value so that only
 * the first 7 bits are shown, then returns that value.
 * 
 * @param insn The instruction that we want the opcode of
 * @return Returns the unsigned integer value of the opcode.
 **********************************************************/
uint32_t rv32i_decode::get_opcode(uint32_t insn) {
    return (insn & 0x0000007f);
}

/**
 * Get the rd value from the 32 bit instruction.
 * 
 * Checks an instruction against a hex value so that only
 * the rd bits are shown, then shifts and returns that value.
 * 
 * @param insn The instruction that we want the opcode of
 * @return Returns the unsigned integer of the rd value.
 ************************************************************/
uint32_t rv32i_decode::get_rd(uint32_t insn) {
    return ((insn >> 7) & 0x0000001f);
}

/**
 * Get the funct3 value from the 32 bit instruction.
 * 
 * Checks an instruction against a hex value so that only
 * the funct3 bits are shown, then shifts and returns that value.
 * 
 * @param insn The instruction that we want the opcode of
 * @return Returns the unsigned integer of the funct3 value.
 ****************************************************************/
uint32_t rv32i_decode::get_funct3(uint32_t insn) {
    return ((insn >> 12) & 0x00000007);
}

/**
 * Get the rs1 value from the 32 bit instruction.
 * 
 * Checks an instruction against a hex value so that only
 * the rs1 bits are shown, then shifts and returns that value.
 * 
 * @param insn The instruction that we want the rs1 value of
 * @return Returns the unsigned integer of the rs1 value
 ************************************************************/
uint32_t rv32i_decode::get_rs1(uint32_t insn) {
    return ((insn >> 15) & 0x0000001f);
}

/**
 * Get the rs2 value from the 32 bit instruction
 * 
 * Checks an instruction against a hex value so that only
 * the rs2 bits are shown, then shifts and returns that value.
 * 
 * @param insn The instruction that we want the rs1 value of.
 * @return Returns the unsigned integer of the rs2 value.
 *************************************************************/
uint32_t rv32i_decode::get_rs2(uint32_t insn) {
    return ((insn >> 20) & 0x0000001f);
}

/**
 * Get the funct7 value from the 32 bit instruction
 * 
 * Checks an instruction against a hex value so that only
 * the funct7 bits are shown, then shifts and returns that value.
 * 
 * @param insn The instruction that we want the funct7 value of.
 * @return Returns the unsigned integer of the funct7 value.
 ***************************************************************/
uint32_t rv32i_decode::get_funct7(uint32_t insn) {
    return ((insn >> 25) & 0x0000007f);
}

/**
 * Get the imm i value from the 32 bit instruction
 * 
 * Checks an instruction against a hex value so that only the
 * first 12 bits are returned, then shifts it over 20 places.
 * If the very first bit of the instruction is a 1, set all bits
 * in the leftmost 20 bit spaces as 1. If not, they all remain 0.
 * 
 * @param insn The instruction that we want the imm i value of.
 * @return Returns a signed integer representing the imm i value of
 *         an instruction.
 *****************************************************************/
int32_t rv32i_decode::get_imm_i(uint32_t insn) {
    int32_t imm_i = (insn & 0xfff00000) >> 20;

    if (insn & 0x80000000)
        imm_i |= 0xfffff000;
    return imm_i;
}

/**
 * Get the imm u value from the 32 bit instruction.
 * 
 * Checks the instruction against a hex value so that only the
 * first 20 bits are returned the same and the 12 least significant
 * bits are turned to 0. 
 * 
 * @param insn The instruction that we want the imm u value of.
 * @return Returns a signed integer representing the imm u value of
 *         an instruction.
 *****************************************************************/
int32_t rv32i_decode::get_imm_u(uint32_t insn) {
    int32_t imm_u = (insn & 0xfffff000);
    return imm_u;
}

/**
 * Get the imm b value from a 32 bit instruction.
 * 
 * Sets a value so that the first 6 bits except the MSB
 * are turned on and shifted over 20 places. Then we 'or'
 * that against a hex value representing the shifted bits 9-12.
 * Finally we shift the 8th bit 4 places and 'or' that value
 * against the imm_b value. After this, if the MSB
 * was a 1, we set the first MSB bits to 1.
 * 
 * @param insn The instruction we want the imm b value from.
 * @return A signed integer representing the imm b value of
 *         an instruction.
 *************************************************************/
int32_t rv32i_decode::get_imm_b(uint32_t insn) {
    int32_t imm_b = (insn & 0x7e000000) >> (25-5);  // get a-g bits into proper place.
    imm_b |= (insn & 0x00000f00) >> (7-0);          // get the u-x bits into the proper place.
    imm_b |= (insn & 0x00000080) << 4;              // get the y bit into its proper place.

    if (insn & 0x80000000)
        imm_b |= 0xfffff000; // sign-extend the left if 'a' is 1.
    
    return imm_b;
}

/**
 * Get the imm s value from a 32 bit instruction.
 * 
 * Sets a value that represents bits 26-32 and
 * shift it over 20 places to the right. Then we 'or'
 * that value against bits 8-12 shifted over 7
 * places. If the MSB is a 1, the first 20 bits will
 * also become 1.
 * 
 * @param insn The instruction we want the imm s value from.
 * @return A signed integer representing the imm s value of
 *         an instruction.
 **********************************************************/
int32_t rv32i_decode::get_imm_s(uint32_t insn) {
    int32_t imm_s = (insn & 0xfe000000) >> (25-5);
    imm_s |= (insn & 0x00000f80) >> (7-0);

    if (insn & 0x80000000)
        imm_s |= 0xfffff000;

    return imm_s;
}

/**
 * Get the imm j value from a 32 bit instruction.
 * 
 * Sets a value imm_j to 10 of the 11 MSBs excluding the first
 * then shifts them over 20 places to the right. Then, we take
 * bits 13-20 and 'or' them against the imm_j value. Finally, we
 * take bit 12 and shift it over 9 places to the right before 'or'ing
 * it against imm_j. This gives us the final position for the
 * elements of imm_j. If the MSB is a 1, the first 12 bits of imm_j
 * will also be 1. 
 * 
 * @param insn The instruction we wish to get the imm_j value of.
 * @return A signed integer representing the imm j value of
 *         an instruction.
 *******************************************************************/
int32_t rv32i_decode::get_imm_j(uint32_t insn) {
    int32_t imm_j = (insn & 0x7fe00000) >> 20; //get a-k bits move them into proper place
    imm_j |= (insn & 0x00100000) >> 9; // get l bit into proper place
    imm_j |= (insn & 0x000ff000); // get m-t bits

    if (insn & 0x80000000)
        imm_j |= 0xfff00000;

    return imm_j;
}

/**
 * Function that writes an error message if an
 * invalid instruction is called.
 * 
 * @return Returns a string informing the user that
 *         the instruction does not exist.
 *************************************************/
std::string rv32i_decode::render_illegal_insn() {
    return "ERROR: UNIMPLEMENTED INSTRUCTION";
}

/**
 * Renders the lui instruction.
 * 
 * Creates a string showing the mnemonic of the instruction,
 * the register destination, and the imm_u value in hex.
 * 
 * @param insn The lui instruction we want to render.
 * @return A string containing the information for the lui instruction.
 *********************************************************************/
std::string rv32i_decode::render_lui(uint32_t insn) {
    uint32_t rd = get_rd(insn);
    int32_t imm_u = get_imm_u(insn);

    std::ostringstream os;
    os << render_mnemonic("lui") << render_reg(rd) << "," << to_hex0x20((imm_u >> 12)&0x0fffff);
    return os.str();
}

/**
 * Renders the auipc instruction.
 * 
 * Creates a string showing the mnemonic, the register destination,
 * and the the 20 bit hex value of the imm_u.
 * 
 * @param insn The auipc instruction we want to render
 * @return A string containing the information for the auipc instruction.
 ***********************************************************************/
std::string rv32i_decode::render_auipc(uint32_t insn) {
    uint32_t rd = get_rd(insn);
    int32_t imm_u = get_imm_u(insn);

    std::ostringstream os;
    os << render_mnemonic("auipc") << render_reg(rd) << "," << to_hex0x20((imm_u >> 12) & 0x0fffff);
    return os.str();
}

/**
 * Renders the jal instruction.
 * 
 * Creates a string showing the mnemonic, the register destination,
 * and a 32 bit hex value of the next address to be accessed based on
 * the imm_j value.
 * 
 * @param addr The address location of the instruction
 * @param insn The jal instruction we want to render.
 * @return A string containing the information for the jal instruction.
 *********************************************************************/
std::string rv32i_decode::render_jal(uint32_t addr, uint32_t insn) {
    uint32_t rd = get_rd(insn);
    int32_t jump = addr + get_imm_j(insn);

    std::ostringstream os;
    os << render_mnemonic("jal") << render_reg(rd) << "," <<to_hex0x32(jump);
    return os.str();
}

/**
 * Renders the jalr instruction.
 * 
 * Creates a string showing the mnemonic, the imm_i value
 * shown as a register, and the base displacement of the rs1 and
 * rd values.
 * 
 * @param insn The jalr instruction we want to render
 * @return A string containing the information for the jalr instruction.
 **********************************************************************/
std::string rv32i_decode::render_jalr(uint32_t insn) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t imm = get_imm_i(insn);

    std::ostringstream os;
    os << render_mnemonic("jalr") << render_reg(rd) << "," << render_base_disp(rs1, imm);
    return os.str();
}

/**
 * Renders all btype instructions.
 * 
 * Creates a string showing the necessary information for any
 * of the btype instructions. Renders the mnemonic first, followed by
 * the rs1 and rs2 values rendered with an x preceding them, and finally
 * the target address rendered as a hex value.
 * 
 * @param addr The address of the instruction.
 * @param insn The btype instruction we want to render
 * @param mnemonic The mnemonic of any of the btype instructions
 * @return A string containing the information for any of the btype instructions.
 *******************************************************************************/
std::string rv32i_decode::render_btype(uint32_t addr, uint32_t insn, const char *mnemonic) {
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t pcrel_13 = get_imm_b(insn) + addr;
    
    std::ostringstream os;
    os << render_mnemonic(mnemonic) << render_reg(rs1) << "," << render_reg(rs2) << "," << to_hex0x32(pcrel_13);
    return os.str();
}

/**
 * Renders all itype loading instructions.
 * 
 * Creates a string containing the mnemonic, the rd value shown as a register,
 * and the rs1 and imm_i value of the instruction shown as a base displacement.
 * 
 * @param insn The itype instruction we want to render.
 * @param mnemonic A mnemonic of any of the itype instructions.
 * @return A string containing the information for any of the itype load instructions.
 ************************************************************************************/
std::string rv32i_decode::render_itype_load(uint32_t insn, const char *mnemonic) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);

    std::ostringstream os;
    os << render_mnemonic(mnemonic) << render_reg(rd) << "," << render_base_disp(rs1, get_imm_i(insn));
    return os.str();
}

/**
 * Renders all stype instructions.
 * 
 * Creates a string containing the mnemonic, the rs2 value as a register,
 * and the rs1 and imm_s values of the instruction shown as a base displacement.
 * 
 * @param insn The stype instruction we want to render.
 * @param mnemonic A mnemonic of any of the stype instructions.
 * @return A string containing the information for any of the stype instructions.
 *******************************************************************************/
std::string rv32i_decode::render_stype(uint32_t insn, const char *mnemonic) {
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    std::ostringstream os;
    os << render_mnemonic(mnemonic) << render_reg(rs2) << "," << render_base_disp(rs1, get_imm_s(insn));
    return os.str();
}

/**
 * Renders all itype instructions that have to do with arithmetic.
 * 
 * Creates a string containing the mnemonic, the rd value as a register,
 * the rs1 value as a register, and the imm_i value.
 * 
 * @param insn The arithmatic itype instruction we want to render.
 * @param mnemonic The mnemonic of any of the itype instruction we want to render.
 * @param imm_i The imm_i value from any of the itype instructions.
 * @return A string containing the information for any of the arithmatic itype instructions.
 ******************************************************************************************/
std::string rv32i_decode::render_itype_alu(uint32_t insn, const char *mnemonic, int32_t imm_i) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    
    std::ostringstream os;
    os << render_mnemonic(mnemonic) << render_reg(rd) << "," << render_reg(rs1) << "," << imm_i;
    return os.str();
}

/**
 * Renders all rtype instructions.
 * 
 * Creates a string containing the mnemonic, rd value as a register,
 * rs1 value as a register, and rs2 value as a register.
 * 
 * @param insn The rtype instruction we want to render.
 * @param mnemonic The mnemonic of any of the rtype instructions
 * @return A string containing the information for any of the rtype instructions.
 *******************************************************************************/
std::string rv32i_decode::render_rtype(uint32_t insn, const char *mnemonic) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    std::ostringstream os;
    os << render_mnemonic(mnemonic) << render_reg(rd) << "," << render_reg(rs1) << "," << render_reg(rs2);
    return os.str();
}

/**
 * Renders the ecall instruction.
 * 
 * @param insn The instruction for ecall
 * @return Returns "ecall".
 **************************************/
std::string rv32i_decode::render_ecall(uint32_t insn) {
    std::ostringstream os;
    os << "ecall";
    return os.str();
}

/**
 * Renders the ebreak instruction.
 * 
 * @param insn The instruction for ebreak
 * @return Returns "ebreak"
 ***************************************/
std::string rv32i_decode::render_ebreak(uint32_t insn) {
    std::ostringstream os;
    os << "ebreak";
    return os.str();
}

/**
 * Renders any csrr instruction.
 * 
 * Creates a string containing the mnemonic, the rd value as a register,
 * a 12 bit hex value representing the imm_i value of the instruction, and the
 * rs1 value as a register.
 * 
 * @param insn The csrr instruction we want to render.
 * @param mnemonic The specific mnemonic of a csrr instruction
 * @return A string containing the information for any csrr instruction.
 ****************************************************************************/
std::string rv32i_decode::render_csrrx(uint32_t insn, const char *mnemonic) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);

    std::ostringstream os;
    os << render_mnemonic(mnemonic) << render_reg(rd) << "," << to_hex0x12(get_imm_i(insn)) << "," << render_reg(rs1);
    return os.str();
}

/**
 * Renders any csrr_i instruction
 * 
 * Creates a string containing the mnemonic, the rd value as a register,
 * a 12 bit hex value representing the imm_i value of the instruction,
 * and the rs1 value.
 *  
 * @param insn The csrr_i instruction we want to render.
 * @param mnemonic The specific mnemonic of a csrr_i instruction.
 * @return A string containing the information for any csrr_i instruction.
 ************************************************************************/
std::string rv32i_decode::render_csrrxi(uint32_t insn, const char *mnemonic) {
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);

    std::ostringstream os;
    os << render_mnemonic(mnemonic) << render_reg(rd) << "," << to_hex0x12(get_imm_i(insn)) << "," << rs1;
    return os.str();
}

/**
 * Renders any input integer to a register form.
 * 
 * Helper function that creates a string to add an x infront 
 * of any integer to denote that it is a register.
 * 
 * @param r An integer that we want to display as a register.
 * @return A string plus the letter 'x' infront of it.
 ***********************************************************/
std::string rv32i_decode::render_reg(int r) {
    std::string str = std::to_string(r);
    return "x"+str;
}

/**
 * Renders two inputs to a form denoting a base displacement.
 * 
 * Helper function that creates a string to show a register and its
 * base displacement in proper form.
 * 
 * @param base The base register
 * @param disp The displacement from the base register.
 * @return Returns a string rendering the form of a base displacement.
 ***********************************************************************/
std::string rv32i_decode::render_base_disp(uint32_t base, int32_t disp) {
    std::ostringstream os;
    os << disp << "(" << render_reg(base) << ")";
    return os.str();
}

/**
 * Renders the mnemonic of an instruction with proper formatting.
 * 
 * Creates a string with a fixed with and shifted to the left so that
 * an instructions mnemonic is properly spaced out and formatted.
 * 
 * @param m A string that represents an instructions mnemonic form.
 * @return A string of the mnemonic of an instruction with proper formatting. 
 ***************************************************************************/
std::string rv32i_decode::render_mnemonic(const std::string &m) {
    std::ostringstream os;
    os << std::setw(mnemonic_width) << std::left << m;
    return os.str();
}
