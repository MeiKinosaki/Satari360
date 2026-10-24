#pragma once

#include "m68000.h"
#include "atari_video.h"
#include "ym2149.h"
#include "memory_bus.h"
#include "mfp68901.h"
#include "acia.h"
#include "floppy_controller.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace satari360 {

// Minimal machine shell: memory bus + CPU. Video/audio/I/O are not yet emulated.
class Machine {
public:
    explicit Machine(std::size_t ram_size = 1024 * 1024);

    MemoryBus& bus() { return bus_; }
    const MemoryBus& bus() const { return bus_; }
    AtariVideo& video() { return video_; }
    YM2149& psg() { return psg_; }
    MFP68901& mfp() { return mfp_; }
    ACIA& acia() { return acia_; }
    FloppyController& floppy() { return floppy_; }
    M68000& cpu() { return cpu_; }
    const M68000& cpu() const { return cpu_; }

    bool load_tos_rom(const std::uint8_t* data, std::size_t size);
    bool reset();
    bool run_instructions(std::size_t budget);

private:
    MemoryBus bus_;
    AtariVideo video_;
    YM2149 psg_;
    MFP68901 mfp_;
    ACIA acia_;
    FloppyController floppy_;
    M68000 cpu_;
};

} // namespace satari360
