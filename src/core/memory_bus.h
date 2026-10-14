#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace satari360 {

class MemoryBus {
public:
    static constexpr std::uint32_t kRomBase = 0x00E00000;
    static constexpr std::size_t kMaxTosRomSize = 512 * 1024;

    explicit MemoryBus(std::size_t ram_size = 1024 * 1024);

    bool load_rom(const std::uint8_t* data, std::size_t size);
    void clear_rom();

    std::uint8_t read8(std::uint32_t address) const;
    std::uint16_t read16(std::uint32_t address) const;
    std::uint32_t read32(std::uint32_t address) const;

    void write8(std::uint32_t address, std::uint8_t value);
    void write16(std::uint32_t address, std::uint16_t value);
    void write32(std::uint32_t address, std::uint32_t value);

    std::size_t ram_size() const { return ram_.size(); }
    bool rom_loaded() const { return !rom_.empty(); }

private:
    bool is_ram(std::uint32_t address) const;
    bool is_rom(std::uint32_t address) const;

    std::vector<std::uint8_t> ram_;
    std::vector<std::uint8_t> rom_;
};

} // namespace satari360
