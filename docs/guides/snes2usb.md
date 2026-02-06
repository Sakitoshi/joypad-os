# SNES2USB Build Guide

> Use your SNES or NES controller as a USB gamepad on PC, MiSTer, or any USB host.

## Overview

SNES2USB reads native SNES and NES controllers and outputs a standard USB HID gamepad. Play retro games on emulators, MiSTer FPGA, or any PC with the original controller. Features include:

- **SNES and NES support** — Auto-detects controller type
- **SNES mouse support** — Use the original SNES mouse as a USB input
- **Select+Start = Home** — Combo maps to the Guide/Home button
- **No analog sticks to worry about** — Pure digital, zero drift
- **Low latency** — Direct shift-register polling via GPIO
- **Plug and play** — Standard USB HID gamepad, no drivers needed

## Parts List

| Part | Quantity | Link | ~Price |
|------|----------|------|--------|
| Adafruit KB2040 | 1 | [Adafruit](https://www.adafruit.com/product/5302) | $9 |
| SNES controller extension cable | 1 | [Amazon](https://www.amazon.com/s?k=snes+extension+cable) | $7 |
| USB-C cable | 1 | (for connecting to PC) | — |

**Total: ~$16** (+ tools if needed)

> 💡 **NES option:** Use an NES extension cable instead if you only need NES support. The pinout is compatible — same signals, different connector shape.

### Tools Required

- Soldering iron + solder
- Wire strippers
- Multimeter (recommended)
- Heat shrink tubing (optional)

## Wiring

Cut the SNES extension cable and strip the wires. You'll use the **male end** (the plug) that connects to the controller.

### SNES Controller Connector Pinout

```
     ┌─────────────────┐
     │ 1 2 3 4 │ 5 6 7 │
     └─────────────────┘
       (front view)
```

| Pin | Color (typical) | Function |
|-----|-----------------|----------|
| 1 | White | 5V Power |
| 2 | Yellow | Clock |
| 3 | Orange | Latch |
| 4 | Red | Data (serial out) |
| 5 | — | Data1 (multitap/keyboard) |
| 6 | — | I/O Bit (mouse/keyboard) |
| 7 | Brown | Ground |

> ⚠️ **Wire colors vary by cable!** Always verify with a multimeter.

### KB2040 Wiring

| KB2040 Pin | GPIO | Connects To |
|------------|------|-------------|
| **D5** | GPIO5 | SNES Clock (Pin 2) |
| **D6** | GPIO6 | SNES Latch (Pin 3) |
| **D7** | GPIO7 | SNES Data (Pin 4) |
| **D8** | GPIO8 | SNES Data1 (Pin 5) — optional* |
| **D9** | GPIO9 | SNES I/O Bit (Pin 6) — optional* |
| **3V3** | — | SNES 5V (Pin 1)** |
| **GND** | — | SNES Ground (Pin 7) |

> \* **Data1** and **I/O Bit** are only needed for SNES mouse or future multitap support. For basic SNES/NES controller use, you only need Clock, Latch, Data, 3V3, and GND (5 wires).

> \*\* **Voltage note:** The SNES controller officially runs at 5V, but the shift registers work reliably at 3.3V. We connect 3V3 to the controller's power pin — this is safe and standard for RP2040 adapters.

### Wiring Diagram

```
SNES Controller                 KB2040
       ┌─────┐                ┌─────────┐
  5V ──┤ 1   │────────────────┤ 3V3     │
       │     │                │         │
 CLK ──┤ 2   │────────────────┤ D5      │
       │     │                │ (GPIO5) │
 LAT ──┤ 3   │────────────────┤ D6      │
       │     │                │ (GPIO6) │
DATA ──┤ 4   │────────────────┤ D7      │
       │     │                │ (GPIO7) │
 GND ──┤ 7   │────────────────┤ GND     │
       └─────┘                └─────────┘

 Minimum 5 wires: CLK, LAT, DATA, 3V3, GND

 Optional (for mouse/multitap):
  Pin 5 (Data1) ──────────── D8 (GPIO8)
  Pin 6 (IOBit) ──────────── D9 (GPIO9)
```

## Assembly

### Step 1: Prepare the Cable

1. Cut the SNES extension cable, keeping the **male end** (the plug the controller connects to)
2. Strip 2–3 inches of the outer sheath
3. Strip ~5mm from each inner wire
4. Identify wires with multimeter (continuity to pins)

### Step 2: Solder to KB2040

1. Tin the KB2040 pads (D5, D6, D7, 3V3, GND)
2. Solder SNES Clock wire to **D5** (GPIO5)
3. Solder SNES Latch wire to **D6** (GPIO6)
4. Solder SNES Data wire to **D7** (GPIO7)
5. Solder SNES 5V wire to **3V3** (safe at 3.3V)
6. Solder SNES Ground wire to **GND**
7. *(Optional)* Solder Data1 to **D8** and I/O Bit to **D9** for mouse support
8. Double-check all connections with multimeter

### Step 3: Secure and Insulate

1. Apply heat shrink to individual solder joints
2. Use larger heat shrink or electrical tape for the wire bundle
3. Add strain relief where the cable meets the board
4. Optional: 3D print a case

## Firmware

1. Download the latest firmware:
   **[joypad_X.X.X_snes2usb_kb2040.uf2](https://github.com/joypad-ai/joypad-os/releases/latest)**

2. Connect USB-C cable to KB2040 and your computer

3. Enter bootloader mode:
   - Hold **BOOT** button
   - Press **RESET** button
   - Release both
   - `RPI-RP2` drive appears

4. Drag & drop the `.uf2` file to the `RPI-RP2` drive

5. Drive auto-ejects when complete — KB2040 RGB LED should light up purple

## Testing

1. Plug a SNES (or NES) controller into the extension cable plug
2. Connect the KB2040 USB-C port to your PC
3. Open a gamepad tester (e.g., [Gamepad Tester](https://gamepad-tester.com))
4. Verify all buttons register correctly

### What to Check

**SNES controller:**
- **D-pad** — All 4 directions
- **Face buttons** — B, A, X, Y
- **Shoulder buttons** — L, R
- **Start, Select** — Both buttons
- **Home combo** — Press Select+Start together (should register as Home/Guide button)

**NES controller:**
- **D-pad** — All 4 directions
- **A, B** — Both face buttons
- **Start, Select** — Both buttons

**SNES mouse:**
- **Movement** — Registers on left analog stick
- **Buttons** — Left click (B1), Right click (B2)

## Troubleshooting

**No response from controller?**
- Verify wiring with multimeter — especially Clock (D5), Latch (D6), and Data (D7)
- Check that 3V3 and GND are connected
- Make sure you're using the correct end of the extension cable (male/plug end)
- Try a different SNES or NES controller

**Buttons seem stuck or scrambled?**
- Clock and Latch wires may be swapped — double-check pinout
- Check for bridged solder joints on adjacent pins

**Controller detected as wrong type?**
- The firmware auto-detects SNES vs NES vs mouse on each poll
- If detection is flaky, check Data line connection

**Select+Start not triggering Home?**
- The combo is exclusive — it only fires when Select and Start are the **only** buttons pressed
- If you're holding any other button, Select+Start pass through normally

**SNES mouse not working?**
- Make sure Data1 (D8) and I/O Bit (D9) are connected
- Mouse requires all 7 wires

**NES controller not detected?**
- NES controllers work with the same wiring (Clock, Latch, Data)
- Some third-party NES controllers may not follow standard protocol

## Supported Controllers

✅ **Full Support:**
- Official Super Nintendo (SNES) controllers
- Official Nintendo Entertainment System (NES) controllers
- Super Famicom controllers
- Famicom controllers (with adapter)
- SNES mouse

⚠️ **Partial Support:**
- Third-party SNES/NES controllers (most work, some may have timing issues)
- SNES Xband keyboard (detected, limited mapping)

❌ **Not Supported:**
- Super Scope (light gun — different protocol)
- SNES Multitap (future firmware update planned)

## Button Mapping Reference

### SNES Controller

| SNES Button | USB Output |
|-------------|------------|
| B | B1 (Cross/A) |
| A | B2 (Circle/B) |
| Y | B3 (Square/X) |
| X | B4 (Triangle/Y) |
| L | L1 (LB) |
| R | R1 (RB) |
| Select | Select (Minus) |
| Start | Start (Plus) |
| Select+Start | Home/Guide (exclusive combo) |
| D-pad | D-pad |

### NES Controller

| NES Button | USB Output |
|------------|------------|
| B | B1 (Cross/A) |
| A | B2 (Circle/B) |
| Select | Select (Minus) |
| Start | Start (Plus) |
| D-pad | D-pad |

### SNES Mouse

| Mouse Input | USB Output |
|-------------|------------|
| Movement X/Y | Left analog stick |
| Left click | B1 (Cross/A) |
| Right click | B2 (Circle/B) |

## Resources

- [Hardware Compatibility List](../HARDWARE.md)
- [Joypad OS GitHub](https://github.com/joypad-ai/joypad-os)
- [Discord Community](https://discord.gg/joypad)
- [Config Tool](https://config.joypad.ai)

---

*Questions? Join the [Joypad Discord](https://discord.gg/joypad) for help!*
