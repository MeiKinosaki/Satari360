#pragma once

#include "memory_bus.h"
#include <array>
#include <cstdint>

namespace satari360 {

// MFP 68901 register latch scaffold; timer/interrupt behavior is not implemented.
class MFP68901 : public BusDevice {
public:
    static constexpr std::uint32_t kBaseAddress = 0x00FFFA01;
    static constexpr std::uint32_t kLastAddress = 0x00FFFA3F;
    void reset();
    bool handles(std::uint32_t address) const override;
    std::uint8_t read8(std::uint32_t address) const override;
    void write8(std::uint32_t address, std::uint8_t value) override;
private:
    std::array<std::uint8_t, 32> registers_{};
};

} // namespace satari360
