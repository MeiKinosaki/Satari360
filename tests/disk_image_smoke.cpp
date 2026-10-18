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
    // Minimal valid MSA: one side, one track, one uncompressed 512-byte sector.
    std::vector<std::uint8_t> msa(10 + 2 + 512, 0);
    msa[0] = 0x0E; msa[1] = 0x0F;
    msa[2] = 0; msa[3] = 1; // sectors per track
    msa[4] = 0; msa[5] = 0; // one side
    msa[6] = 0; msa[7] = 0; // start track
    msa[8] = 0; msa[9] = 0; // end track
    msa[10] = 0x02; msa[11] = 0x00; // 512-byte track payload
    msa[12] = 0x5C;
    assert(disk.load_msa_file_bytes(msa));
    assert(disk.sector_count() == 1);
    assert(disk.read_sector(0, sector, sizeof(sector)));
    assert(sector[0] == 0x5C);

    // Reject a malformed MSA without replacing the already loaded disk.
    std::vector<std::uint8_t> bad_msa(10, 0);
    assert(!disk.load_msa_file_bytes(bad_msa));
    assert(disk.loaded() && disk.sector_count() == 1);
    disk.eject();
    assert(!disk.loaded());
    return 0;
}
