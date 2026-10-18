#include "disk_image.h"

#include <limits>

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


bool DiskImage::load_msa(const std::uint8_t* data, std::size_t size) {
    if (data == nullptr || size < 10 || data[0] != 0x0E || data[1] != 0x0F) return false;
    const std::size_t sectors_per_track = (static_cast<std::size_t>(data[2]) << 8) | data[3];
    const std::size_t sides = static_cast<std::size_t>(((data[4] << 8) | data[5])) + 1u;
    const std::size_t start_track = (static_cast<std::size_t>(data[6]) << 8) | data[7];
    const std::size_t end_track = (static_cast<std::size_t>(data[8]) << 8) | data[9];
    if (sectors_per_track == 0 || sectors_per_track > 11 || sides == 0 || sides > 2 ||
        start_track > end_track || end_track > 79) return false;
    const std::size_t track_count = (end_track - start_track + 1u) * sides;
    const std::size_t track_bytes = sectors_per_track * kSectorSize;
    const std::size_t total_bytes = track_count * track_bytes;
    if (total_bytes == 0 || total_bytes > 2u * 1024u * 1024u) return false;

    std::vector<std::uint8_t> decoded;
    decoded.reserve(total_bytes);
    std::size_t pos = 10;
    for (std::size_t track = 0; track < track_count; ++track) {
        if (pos + 2 > size) return false;
        const std::size_t packed_size = (static_cast<std::size_t>(data[pos]) << 8) | data[pos + 1];
        pos += 2;
        if (packed_size == 0 || packed_size > size - pos) return false;
        const std::size_t end = pos + packed_size;
        const std::size_t out_start = decoded.size();
        if (packed_size == track_bytes) {
            decoded.insert(decoded.end(), data + pos, data + end);
        } else {
            while (pos < end && decoded.size() - out_start < track_bytes) {
                if (pos + 1 < end && data[pos] == 0xE5 && data[pos + 1] == 0xE5) {
                    if (pos + 4 > end) return false;
                    const std::uint8_t value = data[pos + 2];
                    const std::size_t count = data[pos + 3];
                    if (count == 0 || count > track_bytes - (decoded.size() - out_start)) return false;
                    decoded.insert(decoded.end(), count, value);
                    pos += 4;
                } else {
                    decoded.push_back(data[pos++]);
                }
            }
            if (decoded.size() - out_start != track_bytes) return false;
        }
        pos = end;
        if (decoded.size() - out_start != track_bytes) return false;
    }
    if (pos != size || decoded.size() != total_bytes) return false;
    image_.swap(decoded);
    return true;
}

bool DiskImage::load_msa_file_bytes(const std::vector<std::uint8_t>& bytes) {
    return load_msa(bytes.empty() ? nullptr : &bytes[0], bytes.size());
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
