#include "../src/core/memory_bus.h"

#include <cassert>
#include <cstdint>

int main() {
    satari360::MemoryBus bus(1024 * 1024);

    bus.write8(0x100, 0x12);
    assert(bus.read8(0x100) == 0x12);

    bus.write16(0x200, 0xABCD);
    assert(bus.read8(0x200) == 0xAB);
    assert(bus.read8(0x201) == 0xCD);
    assert(bus.read16(0x200) == 0xABCD);

    bus.write32(0x300, 0x12345678);
    assert(bus.read32(0x300) == 0x12345678);

    const std::uint8_t rom[] = {0x60, 0x00, 0x4E, 0x71};
    assert(bus.load_rom(rom, sizeof(rom)));
    assert(bus.read32(satari360::MemoryBus::kRomBase) == 0x60004E71);
    bus.write8(satari360::MemoryBus::kRomBase, 0x00);
    assert(bus.read8(satari360::MemoryBus::kRomBase) == 0x60);

    assert(bus.read8(0x00F00000) == 0xFF);
    assert(!bus.load_rom(nullptr, 4));
    return 0;
}
