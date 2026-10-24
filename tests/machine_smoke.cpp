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
    machine.bus().write8(0x00FF820C, 0x01);
    assert(machine.video().resolution() == 1);
    machine.bus().write8(0x00FF8800, 0x08); // PSG register select
    machine.bus().write8(0x00FF8802, 0x0F); // PSG data port
    assert(machine.psg().selected_register() == 8);
    assert(machine.psg().read_data() == 0x0F);
    machine.bus().write8(0x00FFFA01, 0x5A); // MFP register latch
    assert(machine.bus().read8(0x00FFFA01) == 0x5A);
    machine.bus().write8(0x00FFFC00, 0x12); // keyboard ACIA control latch
    assert(machine.bus().read8(0x00FFFC00) == 0x12);

    std::uint8_t disk_bytes[512] = {};
    disk_bytes[0] = 0xD1;
    assert(machine.floppy().mount_st(disk_bytes, sizeof(disk_bytes)));
    machine.bus().write8(0x00FF8605, 0); // track
    machine.bus().write8(0x00FF8606, 1); // sector
    machine.bus().write8(0x00FF8604, satari360::FloppyController::kCommandReadSector);
    assert(machine.bus().read8(0x00FF8607) == 0xD1);
    assert(machine.run_instructions(2));
    assert(machine.cpu().instructions_executed() == 2);
    return 0;
}
