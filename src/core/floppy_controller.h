#pragma once

#include "disk_image.h"
#include "memory_bus.h"

#include <array>
#include <cstddef>
#include <cstdint>

namespace satari360 {

// Experimental sector-command controller scaffold, not cycle-accurate WD1772.
class FloppyController : public BusDevice {
public:
    static constexpr std::uint32_t kBaseAddress = 0x00FF8604;
    static constexpr std::uint32_t kLastAddress = 0x00FF8607;
    static constexpr std::uint8_t kCommandReadSector = 0x80;
    static constexpr std::uint8_t kStatusReady = 0x01;
    static constexpr std::uint8_t kStatusError = 0x10;

    FloppyController();
    void reset();
    bool mount_st(const std::uint8_t* data, std::size_t size);
    bool mount_msa(const std::uint8_t* data, std::size_t size);
    void eject();
    bool disk_loaded() const { return disk_.loaded(); }

    bool handles(std::uint32_t address) const override;
    std::uint8_t read8(std::uint32_t address) const override;
    void write8(std::uint32_t address, std::uint8_t value) override;

private:
    void execute_command(std::uint8_t command);
    DiskImage disk_;
    std::uint8_t command_;
    std::uint8_t track_;
    std::uint8_t sector_;
    std::uint8_t status_;
    std::array<std::uint8_t, DiskImage::kSectorSize> buffer_;
    mutable std::size_t data_index_;
};

} // namespace satari360
