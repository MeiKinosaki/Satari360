#include "floppy_controller.h"

namespace satari360 {

FloppyController::FloppyController() { reset(); }

void FloppyController::reset() {
    command_ = 0;
    track_ = 0;
    sector_ = 1;
    status_ = 0;
    buffer_.fill(0);
    data_index_ = 0;
}

bool FloppyController::mount_st(const std::uint8_t* data, std::size_t size) {
    const bool ok = disk_.load_st(data, size);
    status_ = ok ? kStatusReady : kStatusError;
    return ok;
}

bool FloppyController::mount_msa(const std::uint8_t* data, std::size_t size) {
    const bool ok = disk_.load_msa(data, size);
    status_ = ok ? kStatusReady : kStatusError;
    return ok;
}

void FloppyController::eject() {
    disk_.eject();
    status_ = 0;
    data_index_ = 0;
}

bool FloppyController::handles(std::uint32_t address) const {
    return address >= kBaseAddress && address <= kLastAddress;
}

std::uint8_t FloppyController::read8(std::uint32_t address) const {
    if (address == kBaseAddress) return status_;
    if (address == kBaseAddress + 1u) return track_;
    if (address == kBaseAddress + 2u) return sector_;
    if (address == kBaseAddress + 3u) {
        if (data_index_ >= buffer_.size()) return 0xFF;
        return buffer_[data_index_++];
    }
    return 0xFF;
}

void FloppyController::write8(std::uint32_t address, std::uint8_t value) {
    if (address == kBaseAddress) {
        command_ = value;
        execute_command(value);
    } else if (address == kBaseAddress + 1u) {
        track_ = value;
    } else if (address == kBaseAddress + 2u) {
        sector_ = value;
    } else if (address == kBaseAddress + 3u) {
        // Writes are deliberately unsupported until write-protect semantics exist.
        status_ = static_cast<std::uint8_t>(status_ | kStatusError);
    }
}

void FloppyController::execute_command(std::uint8_t command) {
    if (command == kCommandReadSector) {
        if (!disk_.loaded() || sector_ == 0) {
            status_ = kStatusError;
            data_index_ = 0;
            return;
        }
        // Initial geometry assumption: 9 sectors per track, one side.
        const std::size_t lba = static_cast<std::size_t>(track_) * 9u +
                                static_cast<std::size_t>(sector_ - 1u);
        if (!disk_.read_sector(lba, buffer_.data(), buffer_.size())) {
            status_ = kStatusError;
            data_index_ = 0;
            return;
        }
        data_index_ = 0;
        status_ = kStatusReady;
    } else {
        status_ = static_cast<std::uint8_t>(status_ | kStatusError);
    }
}

} // namespace satari360
