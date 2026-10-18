#include "../src/core/disk_image.h"

#include <cassert>
#include <cstdint>
#include <vector>

int main() {
    satari360::DiskImage disk;
    assert(!disk.loaded());
    assert(!disk.load_st(nullptr, 512));

    std::vector<std::uint8_t> raw(1024, 0);
    raw[0] = 0x12;
    raw[1] = 0x34;
    raw[512] = 0xAB;
    assert(disk.load_st_file_bytes(raw));
    assert(disk.loaded());
    assert(disk.sector_count() == 2);

    std::uint8_t sector[512] = {};
    assert(disk.read_sector(0, sector, sizeof(sector)));
    assert(sector[0] == 0x12 && sector[1] == 0x34);
    assert(disk.read_sector(1, sector, sizeof(sector)));
    assert(sector[0] == 0xAB);
    assert(!disk.read_sector(2, sector, sizeof(sector)));
    assert(!disk.read_sector(0, sector, 10));

    std::vector<std::uint8_t> malformed(513, 0);
    assert(!disk.load_st_file_bytes(malformed));
    assert(disk.loaded()); // rejected load leaves the current image intact
    disk.eject();
    assert(!disk.loaded());
    return 0;
}
