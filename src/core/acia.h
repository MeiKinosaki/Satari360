#pragma once

#include "memory_bus.h"
#include <array>
#include <cstdint>

namespace satari360 {

// ACIA register scaffold for keyboard/MIDI ports; serial protocol is not emulated.
class ACIA : public BusDevice {
public:
    static constexpr std::uint32_t kKeyboardBase = 0x00FFFC00;
    static constexpr std::uint32_t kMidiBase = 0x00FFFC04;
    void reset();
    bool handles(std::uint32_t address) const override;
    std::uint8_t read8(std::uint32_t address) const override;
    void write8(std::uint32_t address, std::uint8_t value) override;
private:
    std::array<std::uint8_t, 4> registers_{};
};

} // namespace satari360
