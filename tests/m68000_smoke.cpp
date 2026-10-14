#include "../src/core/m68000.h"

#include <cassert>
#include <cstdint>

int main() {
    satari360::MemoryBus bus(1024);
    // Reset vectors: initial stack pointer and initial PC.
    bus.write32(0, 0x000003F0);
    bus.write32(4, 0x00000100);
    // MOVEQ #5,D0; MOVEQ #-1,D1; NOP; unknown opcode.
    bus.write16(0x100, 0x7005);
    bus.write16(0x102, 0x72FF);
    bus.write16(0x104, 0x4E71);
    bus.write16(0x106, 0xFFFF);

    satari360::M68000 cpu(bus);
    cpu.reset();
    assert(cpu.pc() == 0x100);
    assert(cpu.step());
    assert(cpu.data_register(0) == 5);
    assert(cpu.step());
    assert(cpu.data_register(1) == 0xFFFFFFFFu);
    assert((cpu.sr() & 0x0008u) != 0); // Negative flag
    assert(cpu.step());
    assert(cpu.instructions_executed() == 3);
    assert(!cpu.step());
    assert(cpu.halted());
    assert(cpu.pc() == 0x108);
    return 0;
}
