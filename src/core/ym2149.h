#pragma once

#include <array>
#include <cstdint>

namespace satari360 {

// Register latch for the Atari ST PSG. This is not an audio synthesizer yet.
class YM2149 {
public:
    void reset();
    void select_register(std::uint8_t index);
    void write_data(std::uint8_t value);
    std::uint8_t read_data() const;
    std::uint8_t selected_register() const { return selected_; }

private:
    std::array<std::uint8_t, 16> registers_{};
    std::uint8_t selected_ = 0;
};

} // namespace satari360
