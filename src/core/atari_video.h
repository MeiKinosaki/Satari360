#pragma once

#include <array>
#include <cstdint>

namespace satari360 {

// Initial Atari ST Shifter register model; timing and pixel fetch are not emulated yet.
class AtariVideo {
public:
    static constexpr std::uint16_t kBaseAddress = 0x00FF8200;

    void reset();
    bool handles(std::uint32_t address) const;
    std::uint8_t read8(std::uint32_t address) const;
    void write8(std::uint32_t address, std::uint8_t value);

    std::uint16_t sync_mode() const { return sync_mode_; }
    std::uint8_t resolution() const { return resolution_; }

private:
    std::array<std::uint8_t, 16> registers_{};
    std::uint16_t sync_mode_ = 0;
    std::uint8_t resolution_ = 0;
};

} // namespace satari360
