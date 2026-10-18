#include "../src/core/atari_video.h"
#include "../src/core/ym2149.h"

#include <cassert>
#include <cstdint>

int main() {
    satari360::AtariVideo video;
    video.reset();
    assert(video.handles(0x00FF8200));
    assert(!video.handles(0x00FF8210));
    video.write8(0x00FF820C, 0x02);
    assert(video.resolution() == 2);
    video.write8(0x00FF820A, 0x01);
    video.write8(0x00FF820B, 0x23);
    assert(video.sync_mode() == 0x0123);

    satari360::YM2149 psg;
    psg.reset();
    psg.select_register(8);
    psg.write_data(0x0F);
    assert(psg.read_data() == 0x0F);
    psg.select_register(24); // index is masked to 4 bits
    assert(psg.selected_register() == 8);
    return 0;
}
