#include "ym2149.h"

namespace satari360 {

bool YM2149::handles(std::uint32_t address) const {
    return address == kBaseAddress || address == kBaseAddress + 2u;
}

std::uint8_t YM2149::read8(std::uint32_t address) const {
    return address == kBaseAddress ? selected_ : read_data();
}

void YM2149::write8(std::uint32_t address, std::uint8_t value) {
    if (address == kBaseAddress) select_register(value);
    else if (address == kBaseAddress + 2u) write_data(value);
}

void YM2149::reset() {
    registers_.fill(0);
    selected_ = 0;
}

void YM2149::select_register(std::uint8_t index) {
    selected_ = static_cast<std::uint8_t>(index & 0x0Fu);
}

void YM2149::write_data(std::uint8_t value) {
    registers_[selected_] = value;
}

std::uint8_t YM2149::read_data() const {
    return registers_[selected_];
}

} // namespace satari360
