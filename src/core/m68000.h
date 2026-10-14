#pragma once

#include "memory_bus.h"

#include <cstdint>

namespace satari360 {

// Small 68000 execution scaffold. Only explicitly listed opcodes are implemented.
class M68000 {
public:
    explicit M68000(MemoryBus& bus);

    void reset();
    bool step();
    void set_pc(std::uint32_t value) { pc_ = value; }
    std::uint32_t pc() const { return pc_; }
    std::uint32_t data_register(unsigned index) const;
    std::uint16_t sr() const { return sr_; }
    bool halted() const { return halted_; }
    std::uint64_t instructions_executed() const { return instructions_executed_; }

private:
    void set_nz32(std::uint32_t value);
    MemoryBus& bus_;
    std::uint32_t d_[8];
    std::uint32_t a_[8];
    std::uint32_t pc_;
    std::uint16_t sr_;
    bool halted_;
    std::uint64_t instructions_executed_;
};

} // namespace satari360
