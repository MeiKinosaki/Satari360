#include "machine.h"

namespace satari360 {

Machine::Machine(std::size_t ram_size) : bus_(ram_size), video_(), psg_(), cpu_(bus_) {
    bus_.attach_device(&video_);
    bus_.attach_device(&psg_);
}

bool Machine::load_tos_rom(const std::uint8_t* data, std::size_t size) {
    return bus_.load_rom(data, size);
}

bool Machine::reset() {
    if (!bus_.rom_loaded()) return false;
    cpu_.reset();
    return !cpu_.halted();
}

bool Machine::run_instructions(std::size_t budget) {
    for (std::size_t i = 0; i < budget; ++i) {
        if (!cpu_.step()) return false;
    }
    return true;
}

} // namespace satari360
