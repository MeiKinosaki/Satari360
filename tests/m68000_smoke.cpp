#include "../src/core/m68000.h"

#include <cassert>
#include <cstdint>

int main() {
    satari360::MemoryBus bus(1024);
    bus.write32(0, 0x000003F0); // initial stack pointer
    bus.write32(4, 0x00000100); // initial PC

    // MOVEQ #5,D0; MOVEQ #-1,D1; NOP; BRA.s +2; skipped word;
    // BSR.s +2; skipped word; subroutine RTS; BRA.w +2; skipped word.
    bus.write16(0x100, 0x7005);
    bus.write16(0x102, 0x72FF);
    bus.write16(0x104, 0x4E71);
    bus.write16(0x106, 0x6002);
    bus.write16(0x108, 0xFFFF);
    bus.write16(0x10A, 0x6102);
    bus.write16(0x10C, 0xFFFF);
    bus.write16(0x10E, 0x4E75);
    bus.write16(0x110, 0x6000);
    bus.write16(0x112, 0x0002);
    bus.write16(0x114, 0xFFFF);
    bus.write16(0x116, 0x4E71);

    satari360::M68000 cpu(bus);
    cpu.reset();
    assert(cpu.pc() == 0x100);
    assert(cpu.step() && cpu.data_register(0) == 5);
    assert(cpu.step() && cpu.data_register(1) == 0xFFFFFFFFu);
    assert((cpu.sr() & 0x0008u) != 0); // Negative flag
    assert(cpu.step());                 // NOP
    assert(cpu.step() && cpu.pc() == 0x10A); // BRA.s skips 0x108
    assert(cpu.step() && cpu.pc() == 0x10E); // BSR.s jumps to 0x10E
    assert(bus.read32(0x3EC) == 0x10C);       // return PC pushed
    assert(cpu.step() && cpu.pc() == 0x10C); // RTS returns
    // At 0x10C is deliberately unsupported, so execution stops there.
    assert(!cpu.step());
    assert(cpu.halted());
    return 0;
}
