#include "../src/core/m68000.h"

#include <cassert>
#include <cstdint>

int main() {
    satari360::MemoryBus bus(1024);
    bus.write32(0, 0x000003F0);
    bus.write32(4, 0x00000100);

    // MOVE.L #$12345678,D0; MOVEQ #5,D0; MOVEQ #-1,D1; NOP;
    // BPL (not taken); BRA.s; BSR.s; BRA.w; RTS; unsupported opcode.
    bus.write16(0x100, 0x203C);
    bus.write32(0x102, 0x12345678);
    bus.write16(0x106, 0x7005);
    bus.write16(0x108, 0x72FF);
    bus.write16(0x10A, 0x5080); // ADDQ.L #8,D0 -> D0=13
    bus.write16(0x10C, 0x5181); // SUBQ.L #8,D1 -> D1=-9
    bus.write16(0x10E, 0x4E71);
    bus.write16(0x110, 0x6A02);
    bus.write16(0x112, 0x6002);
    bus.write16(0x114, 0xFFFF);
    bus.write16(0x116, 0x6104);
    bus.write16(0x118, 0x6000);
    bus.write16(0x11A, 0x0002);
    bus.write16(0x11C, 0x4E75);
    bus.write16(0x11E, 0xFFFF);

    satari360::M68000 cpu(bus);
    cpu.reset();
    assert(cpu.pc() == 0x100);
    assert(cpu.step() && cpu.data_register(0) == 0x12345678u);
    assert(cpu.step() && cpu.data_register(0) == 5);
    assert(cpu.step() && cpu.data_register(1) == 0xFFFFFFFFu);
    assert((cpu.sr() & 0x0008u) != 0);
    assert(cpu.step() && cpu.data_register(0) == 13); // ADDQ.L #8,D0
    assert(cpu.step() && cpu.data_register(1) == 0xFFFFFFF7u); // SUBQ.L #8,D1
    assert(cpu.step()); // NOP
    assert(cpu.step() && cpu.pc() == 0x114); // BPL not taken
    assert(cpu.step() && cpu.pc() == 0x116); // BRA.s
    assert(cpu.step() && cpu.pc() == 0x11C); // BSR.s
    assert(bus.read32(0x3EC) == 0x118);
    assert(cpu.step() && cpu.pc() == 0x118); // RTS
    assert(cpu.step() && cpu.pc() == 0x11E); // BRA.w
    assert(!cpu.step());
    assert(cpu.halted());
    assert(cpu.pc() == 0x120);
    return 0;
}
