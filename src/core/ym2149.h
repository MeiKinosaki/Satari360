#pragma once

#include <array>
#include <cstdint>
#include "memory_bus.h"

namespace satari360 {

// Register latch for the Atari ST PSG. This is not an audio synthesizer yet.
class YM2149 : public BusDevice {
public:
    static constexpr std::uint32_t kBaseAddress = 0x00FF8800;
    void reset();
    bool handles(std::uint32_t address) const override;
    std::uint8_t read8(std::uint32_t address) const override;
    void write8(std::uint32_t address, std::uint8_t value) override;
    void select_register(std::uint8_t index);
    void write_data(std::uint8_t value);
    std::uint8_t read_data() const;
    std::uint8_t selected_register() const { return selected_; }

private:
    std::array<std::uint8_t, 16> registers_{};
    std::uint8_t selected_ = 0;
};

} // namespace satari360
