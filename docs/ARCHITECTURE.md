# Satari360 architecture (development scaffold)

## Current executable core
- `MemoryBus`: configurable low-memory RAM plus a read-only ROM window beginning at `0x00E00000`.
- `M68000`: experimental instruction-stepper; only explicitly implemented opcodes execute.
- `Machine`: owns the bus and CPU, loads a caller-supplied TOS image, resets from vectors, and runs a bounded instruction budget.

## Current limitations
This is not yet a complete Atari ST machine. There is no Shifter video, YM2149 audio, MFP/ACIA, WD1772 floppy controller, keyboard/mouse/joystick integration, TOS compatibility validation, or Xbox 360 executable. The ROM window and RAM mapping are scaffolding and do not yet model the full Atari ST address map or memory configuration.

## Development rule
Do not mark a subsystem complete until its tests are built and run, and record target-console validation separately from host validation.
