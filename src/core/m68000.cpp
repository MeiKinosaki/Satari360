#include "m68000.h"

namespace satari360 {
namespace {
const std::uint16_t kFlagC = 0x0001;
const std::uint16_t kFlagV = 0x0002;
const std::uint16_t kFlagZ = 0x0004;
const std::uint16_t kFlagN = 0x0008;

bool condition_true(unsigned condition, std::uint16_t sr) {
    const bool c = (sr & kFlagC) != 0;
    const bool v = (sr & kFlagV) != 0;
    const bool z = (sr & kFlagZ) != 0;
    const bool n = (sr & kFlagN) != 0;
    switch (condition) {
        case 0: return true;             // T
        case 2: return !c && !z;         // HI
        case 3: return c || z;           // LS
        case 4: return !c;               // CC
        case 5: return c;                // CS
        case 6: return !z;               // NE
        case 7: return z;                // EQ
        case 8: return !v;               // VC
        case 9: return v;                // VS
        case 10: return !n;              // PL
        case 11: return n;               // MI
        case 12: return n == v;          // GE
        case 13: return n != v;          // LT
        case 14: return !z && (n == v);  // GT
        case 15: return z || (n != v);   // LE
        default: return false;           // condition 1 is BSR, handled separately
    }
}
}

M68000::M68000(MemoryBus& bus)
    : bus_(bus), pc_(0), sr_(0x2700), halted_(false), instructions_executed_(0) {
    for (unsigned i = 0; i < 8; ++i) { d_[i] = 0; a_[i] = 0; }
}

void M68000::reset() {
    for (unsigned i = 0; i < 8; ++i) { d_[i] = 0; a_[i] = 0; }
    a_[7] = bus_.read32(0);
    pc_ = bus_.read32(4);
    sr_ = 0x2700;
    halted_ = false;
    instructions_executed_ = 0;
}

std::uint32_t M68000::data_register(unsigned index) const {
    return index < 8 ? d_[index] : 0;
}

void M68000::set_nz32(std::uint32_t value) {
    sr_ &= static_cast<std::uint16_t>(~(kFlagN | kFlagZ | kFlagV | kFlagC));
    if (value == 0) sr_ |= kFlagZ;
    if ((value & 0x80000000u) != 0) sr_ |= kFlagN;
}

bool M68000::step() {
    if (halted_) return false;
    const std::uint16_t opcode = bus_.read16(pc_);
    pc_ += 2;

    if (opcode == 0x4E71) { // NOP
        ++instructions_executed_;
        return true;
    }
    if (opcode == 0x4E75) { // RTS
        pc_ = bus_.read32(a_[7]);
        a_[7] += 4;
        ++instructions_executed_;
        return true;
    }
    if ((opcode & 0xF1FFu) == 0x203Cu) { // MOVE.L #imm32,Dn
        const unsigned reg = (opcode >> 9) & 7u;
        d_[reg] = bus_.read32(pc_);
        pc_ += 4;
        set_nz32(d_[reg]);
        ++instructions_executed_;
        return true;
    }
    if ((opcode & 0xF100u) == 0x7000u) { // MOVEQ #imm8,Dn
        const unsigned reg = (opcode >> 9) & 7u;
        const std::int32_t imm = static_cast<std::int8_t>(opcode & 0xFFu);
        d_[reg] = static_cast<std::uint32_t>(imm);
        set_nz32(d_[reg]);
        ++instructions_executed_;
        return true;
    }
    if ((opcode & 0xF000u) == 0x6000u) { // Bcc, BRA and BSR
        const unsigned condition = (opcode >> 8) & 0x0Fu;
        const std::uint8_t short_disp = static_cast<std::uint8_t>(opcode & 0xFFu);
        std::int32_t displacement;
        if (short_disp == 0) {
            displacement = static_cast<std::int16_t>(bus_.read16(pc_));
            pc_ += 2;
        } else {
            displacement = static_cast<std::int8_t>(short_disp);
        }

        if (condition == 1) { // BSR: push return PC and branch
            a_[7] -= 4;
            bus_.write32(a_[7], pc_);
            pc_ = static_cast<std::uint32_t>(pc_ + displacement);
        } else if (condition_true(condition, sr_)) {
            pc_ = static_cast<std::uint32_t>(pc_ + displacement);
        }
        ++instructions_executed_;
        return true;
    }

    // Unknown opcodes stop execution instead of silently pretending to emulate them.
    halted_ = true;
    return false;
}

} // namespace satari360
