#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace satari360 {

// Read-only raw ST floppy image. MSA compression and FDC timing are not supported.
class DiskImage {
public:
    static constexpr std::size_t kSectorSize = 512;

    bool load_st(const std::uint8_t* data, std::size_t size);
    bool load_st_file_bytes(const std::vector<std::uint8_t>& bytes);
    void eject();

    bool loaded() const { return !image_.empty(); }
    std::size_t size_bytes() const { return image_.size(); }
    std::size_t sector_count() const { return image_.size() / kSectorSize; }
    bool read_sector(std::size_t lba, std::uint8_t* output, std::size_t output_size) const;

private:
    std::vector<std::uint8_t> image_;
};

} // namespace satari360
