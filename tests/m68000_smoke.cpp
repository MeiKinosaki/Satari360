#include "../src/core/m68000.h"

#include <cassert>
#include <cstdint>

int main() {
    satari360::MemoryBus bus(1024);
    bus.write32(0, 0x000003F0); // initial stack pointer
    bus.write32(4, 0x00000100); // initial PC

    // MOVEQ #5,D0; MOVEQ #-1,D1; NOP; BPL.s +2 (not taken);
    // BRA.s +2 (skips 0x10A); BSR.s +4 -> RTS; return to BRA.w +2.
    bus.write16(0x100, 0x7005);
    bus.write16(0x102, 0x72FF);
    bus.write16(0x104, 0x4E71);
    bus.write16(0x106, 0x6A02); // BPL: N=1, so not taken
    bus.write16(0x108, 0x6002); // BRA.s to 0x10C
    bus.write16(0x10A, 0xFFFF); // skipped
    bus.write16(0x10C, 0x6104); // BSR.s target 0x112
    bus.write16(0x10E, 0x6000); // BRA.w
    bus.write16(0x110, 0x0002); // extension, target 0x112
    bus.write16(0x112, 0x4E75); // RTS
    bus.write16(0x114, 0xFFFF); // unsupported opcode to test explicit halt
    bus.write16(0x116, 0x4E71);

    satari360::M68000 cpu(bus);
    cpu.reset();
    assert(cpu.pc() == 0x100);
    assert(cpu.step() && cpu.data_register(0) == 5);
    assert(cpu.step() && cpu.data_register(1) == 0xFFFFFFFFu);
    assert((cpu.sr() & 0x0008u) != 0); // Negative flag
    assert(cpu.step());                 // NOP
    assert(cpu.step() && cpu.pc() == 0x10A); // BPL not taken
    assert(cpu.step() && cpu.pc() == 0x10C); // BRA.s skips 0x10A
    assert(cpu.step() && cpu.pc() == 0x112); // BSR.s
    assert(bus.read32(0x3EC) == 0x10E);       // return PC pushed
    assert(cpu.step() && cpu.pc() == 0x10E); // RTS returns
    assert(cpu.step() && cpu.pc() == 0x114); // BRA.w +2
    assert(!cpu.step());
    assert(cpu.halted());
    assert(cpu.pc() == 0x116);
    return 0;
}
