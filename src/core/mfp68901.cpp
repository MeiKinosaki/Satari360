#include "mfp68901.h"

namespace satari360 {

void MFP68901::reset() { registers_.fill(0); }

bool MFP68901::handles(std::uint32_t address) const {
    return address >= kBaseAddress && address <= kLastAddress && (address & 1u) != 0;
}

std::uint8_t MFP68901::read8(std::uint32_t address) const {
    if (!handles(address)) return 0xFF;
    return registers_[(address - kBaseAddress) / 2u];
}

void MFP68901::write8(std::uint32_t address, std::uint8_t value) {
    if (!handles(address)) return;
    registers_[(address - kBaseAddress) / 2u] = value;
}

} // namespace satari360
