#include "atari_video.h"

namespace satari360 {

void AtariVideo::reset() {
    registers_.fill(0);
    sync_mode_ = 0;
    resolution_ = 0;
}

bool AtariVideo::handles(std::uint32_t address) const {
    return address >= kBaseAddress && address < kBaseAddress + registers_.size();
}

std::uint8_t AtariVideo::read8(std::uint32_t address) const {
    if (!handles(address)) return 0xFF;
    return registers_[address - kBaseAddress];
}

void AtariVideo::write8(std::uint32_t address, std::uint8_t value) {
    if (!handles(address)) return;
    const std::size_t offset = address - kBaseAddress;
    registers_[offset] = value;
    // These offsets are a scaffold only; precise ST register semantics remain TODO.
    if (offset == 0x0A) sync_mode_ = static_cast<std::uint16_t>((sync_mode_ & 0x00FFu) | (value << 8));
    if (offset == 0x0B) sync_mode_ = static_cast<std::uint16_t>((sync_mode_ & 0xFF00u) | value);
    if (offset == 0x0C) resolution_ = static_cast<std::uint8_t>(value & 0x03u);
}

} // namespace satari360
