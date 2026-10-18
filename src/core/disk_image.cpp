#include "disk_image.h"

namespace satari360 {

bool DiskImage::load_st(const std::uint8_t* data, std::size_t size) {
    // Atari ST raw sector images must be a non-empty multiple of 512 bytes.
    // Bound image size to 2 MiB for this initial read-only implementation.
    if (data == nullptr || size == 0 || size > 2u * 1024u * 1024u ||
        (size % kSectorSize) != 0) return false;
    image_.assign(data, data + size);
    return true;
}

bool DiskImage::load_st_file_bytes(const std::vector<std::uint8_t>& bytes) {
    return load_st(bytes.empty() ? nullptr : &bytes[0], bytes.size());
}

void DiskImage::eject() { image_.clear(); }

bool DiskImage::read_sector(std::size_t lba, std::uint8_t* output, std::size_t output_size) const {
    if (!loaded() || output == nullptr || output_size < kSectorSize || lba >= sector_count())
        return false;
    const std::size_t offset = lba * kSectorSize;
    for (std::size_t i = 0; i < kSectorSize; ++i) output[i] = image_[offset + i];
    return true;
}

} // namespace satari360
