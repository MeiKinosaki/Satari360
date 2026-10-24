#include "../src/core/floppy_controller.h"

#include <cassert>
#include <cstdint>
#include <vector>

int main() {
    satari360::FloppyController fdc;
    assert(fdc.handles(0x00FF8604));
    assert(!fdc.handles(0x00FF8608));
    assert((fdc.read8(0x00FF8604) & satari360::FloppyController::kStatusReady) == 0);

    std::vector<std::uint8_t> disk(18u * 512u, 0);
    disk[0] = 0x4A;
    disk[1] = 0x2B;
    assert(fdc.mount_st(disk.data(), disk.size()));
    fdc.write8(0x00FF8605, 0); // track 0
    fdc.write8(0x00FF8606, 1); // sector 1
    fdc.write8(0x00FF8604, satari360::FloppyController::kCommandReadSector);
    assert(fdc.read8(0x00FF8607) == 0x4A);
    assert(fdc.read8(0x00FF8607) == 0x2B);

    fdc.write8(0x00FF8606, 0);
    fdc.write8(0x00FF8604, satari360::FloppyController::kCommandReadSector);
    assert((fdc.read8(0x00FF8604) & satari360::FloppyController::kStatusError) != 0);
    fdc.eject();
    assert(!fdc.disk_loaded());
    return 0;
}
