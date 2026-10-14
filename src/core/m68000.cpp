#include "m68000.h"

namespace satari360 {
namespace {
const std::uint16_t kFlagC = 0x0001;
const std::uint16_t kFlagV = 0x0002;
const std::uint16_t kFlagZ = 0x0004;
const std::uint16_t kFlagN = 0x0008;
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
    if ((opcode & 0xF100u) == 0x7000u) { // MOVEQ #imm8,Dn
        const unsigned reg = (opcode >> 9) & 7u;
        const std::int32_t imm = static_cast<std::int8_t>(opcode & 0xFFu);
        d_[reg] = static_cast<std::uint32_t>(imm);
        set_nz32(d_[reg]);
        ++instructions_executed_;
        return true;
    }
    if ((opcode & 0xFF00u) == 0x6000u) { // BRA with 8-bit displacement
        const std::int8_t displacement = static_cast<std::int8_t>(opcode & 0xFFu);
        if (displacement == 0) {
            // 16-bit extension form is intentionally not implemented yet.
            halted_ = true;
            return false;
        }
        pc_ = static_cast<std::uint32_t>(pc_ + static_cast<std::int32_t>(displacement));
        ++instructions_executed_;
        return true;
    }

    // Unknown opcodes stop execution instead of silently pretending to emulate them.
    halted_ = true;
    return false;
}

} // namespace satari360
