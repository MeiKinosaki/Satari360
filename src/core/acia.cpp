#include "acia.h"

namespace satari360 {

void ACIA::reset() { registers_.fill(0); }

bool ACIA::handles(std::uint32_t address) const {
    return address == kKeyboardBase || address == kKeyboardBase + 2u ||
           address == kMidiBase || address == kMidiBase + 2u;
}

std::uint8_t ACIA::read8(std::uint32_t address) const {
    if (!handles(address)) return 0xFF;
    if (address == kKeyboardBase) return registers_[0];
    if (address == kKeyboardBase + 2u) return registers_[1];
    if (address == kMidiBase) return registers_[2];
    return registers_[3];
}

void ACIA::write8(std::uint32_t address, std::uint8_t value) {
    if (!handles(address)) return;
    if (address == kKeyboardBase) registers_[0] = value;
    else if (address == kKeyboardBase + 2u) registers_[1] = value;
    else if (address == kMidiBase) registers_[2] = value;
    else registers_[3] = value;
}

} // namespace satari360
