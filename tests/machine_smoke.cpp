#include "../src/core/machine.h"

#include <cassert>
#include <cstdint>

int main() {
    satari360::Machine machine(1024 * 1024);
    assert(!machine.reset()); // no TOS ROM loaded yet

    // Test ROM contains reset SP and PC vectors followed by a NOP.
    std::uint8_t rom[16] = {
        0x00, 0x00, 0x03, 0xF0, // initial SP = 0x3F0
        0x00, 0xE0, 0x00, 0x08, // initial PC = ROM base + 8
        0x4E, 0x71, 0x4E, 0x71, // NOP, NOP
        0x00, 0x00, 0x00, 0x00
    };
    assert(machine.load_tos_rom(rom, sizeof(rom)));
    assert(machine.reset());
    assert(machine.cpu().pc() == satari360::MemoryBus::kRomBase + 8);
    assert(machine.run_instructions(2));
    assert(machine.cpu().instructions_executed() == 2);
    return 0;
}
