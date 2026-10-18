#include "memory_bus.h"

#include <algorithm>

namespace satari360 {

MemoryBus::MemoryBus(std::size_t ram_size) : ram_(ram_size, 0) {}

bool MemoryBus::attach_device(BusDevice* device) {
    if (device == nullptr) return false;
    if (std::find(devices_.begin(), devices_.end(), device) != devices_.end()) return true;
    devices_.push_back(device);
    return true;
}

bool MemoryBus::load_rom(const std::uint8_t* data, std::size_t size) {
    if (data == nullptr || size == 0 || size > kMaxTosRomSize ||
        size > 0x01000000u - kRomBase) return false;
    rom_.assign(data, data + size);
    return true;
}

void MemoryBus::clear_rom() { rom_.clear(); }

bool MemoryBus::is_ram(std::uint32_t address) const {
    return static_cast<std::uint64_t>(address) < ram_.size();
}

bool MemoryBus::is_rom(std::uint32_t address) const {
    return !rom_.empty() && address >= kRomBase &&
           static_cast<std::uint64_t>(address - kRomBase) < rom_.size();
}

std::uint8_t MemoryBus::read8(std::uint32_t address) const {
    for (std::vector<BusDevice*>::const_iterator it = devices_.begin(); it != devices_.end(); ++it)
        if ((*it)->handles(address)) return (*it)->read8(address);
    if (is_ram(address)) return ram_[address];
    if (is_rom(address)) return rom_[address - kRomBase];
    return 0xFF;
}

std::uint16_t MemoryBus::read16(std::uint32_t address) const {
    return static_cast<std::uint16_t>((static_cast<std::uint16_t>(read8(address)) << 8) |
                                      static_cast<std::uint16_t>(read8(address + 1u)));
}

std::uint32_t MemoryBus::read32(std::uint32_t address) const {
    return (static_cast<std::uint32_t>(read8(address)) << 24) |
           (static_cast<std::uint32_t>(read8(address + 1u)) << 16) |
           (static_cast<std::uint32_t>(read8(address + 2u)) << 8) |
           static_cast<std::uint32_t>(read8(address + 3u));
}

void MemoryBus::write8(std::uint32_t address, std::uint8_t value) {
    for (std::vector<BusDevice*>::const_iterator it = devices_.begin(); it != devices_.end(); ++it) {
        if ((*it)->handles(address)) { (*it)->write8(address, value); return; }
    }
    if (is_ram(address)) ram_[address] = value;
}

void MemoryBus::write16(std::uint32_t address, std::uint16_t value) {
    write8(address, static_cast<std::uint8_t>(value >> 8));
    write8(address + 1u, static_cast<std::uint8_t>(value));
}

void MemoryBus::write32(std::uint32_t address, std::uint32_t value) {
    write8(address, static_cast<std::uint8_t>(value >> 24));
    write8(address + 1u, static_cast<std::uint8_t>(value >> 16));
    write8(address + 2u, static_cast<std::uint8_t>(value >> 8));
    write8(address + 3u, static_cast<std::uint8_t>(value));
}

} // namespace satari360
