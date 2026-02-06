# GC2USB Build Guide

> Use your GameCube controller as a USB gamepad on PC, MiSTer, or any USB host.

## Overview

GC2USB reads a native GameCube controller and outputs a standard USB HID gamepad. Plug your favorite GC controller into your PC, Steam Deck, MiSTer FPGA, or any device with a USB port. Features include:

- **Full analog support** — Control stick, C-stick, and analog L/R triggers
- **3 button profiles** (Default, Xbox, Nintendo)
- **Rumble passthrough** — Rumble Pak feedback from games
- **Low latency** — Direct joybus polling at 125Hz via PIO
- **Plug and play** — Shows up as a standard USB HID gamepad, no drivers needed

## Parts List

| Part | Quantity | Link | ~Price |
|------|----------|------|--------|
| Adafruit KB2040 | 1 | [Adafruit](https://www.adafruit.com/product/5302) | $9 |
| GameCube controller extension cable | 1 | [Amazon](https://www.amazon.com/s?k=gamecube+extension+cable) | $8 |
| USB-C cable | 1 | (for connecting to PC) | — |

**Total: ~$17** (+ tools if needed)

### Tools Required

- Soldering iron + solder
- Wire strippers
- Multimeter (recommended)
- Heat shrink tubing (optional)

## Wiring

Cut the GameCube extension cable and strip the wires. You'll use the **male end** (the plug) that connects to the controller.

### GameCube Controller Connector Pinout

```
    ┌───────────┐
    │ 1   2   3 │
    │           │
    │ 4   5   6 │
    │     7     │
    └───────────┘
```

| Pin | Color (typical) | Function |
|-----|-----------------|----------|
| 1 | White | 5V Power |
| 2 | Red | Data |
| 3 | Black | Ground |
| 4 | Green | Ground |
| 5 | — | Not used |
| 6 | Blue | 3.3V |
| 7 | — | Shield/Ground |

> ⚠️ **Wire colors vary by cable!** Always verify with a multimeter.

### KB2040 Wiring

| KB2040 Pin | Connects To |
|------------|-------------|
| **A3** (GPIO29) | GC Data (Pin 2) |
| **3V3** | GC 3.3V (Pin 6) |
| **GND** | GC Ground (Pin 3 or 4) |

> 💡 **Power note:** The KB2040 provides 3.3V to the controller via its onboard regulator. Do NOT connect Pin 1 (5V) — the controller only needs 3.3V for signaling, and the KB2040 is powered via USB.

### Wiring Diagram

```
GameCube Controller             KB2040
       ┌─────┐                ┌─────────┐
  5V ──┤ 1   │                │         │
       │     │                │         │
Data ──┤ 2   │────────────────┤ A3      │
       │     │                │ (GPIO29)│
 GND ──┤ 3   │────────────────┤ GND     │
       │     │                │         │
 GND ──┤ 4   │                │         │
       │     │                │         │
3.3V ──┤ 6   │────────────────┤ 3V3     │
       └─────┘                └─────────┘

 Only 3 wires needed: Data, 3V3, GND
```

## Assembly

### Step 1: Prepare the Cable

1. Cut the GameCube extension cable, keeping the **male end** (the plug the controller connects to)
2. Strip 2–3 inches of the outer sheath
3. Strip ~5mm from each inner wire
4. Identify wires with multimeter (continuity to pins)

### Step 2: Solder to KB2040

1. Tin the KB2040 pads (A3, 3V3, GND)
2. Solder GC Data wire to **A3** (GPIO29)
3. Solder GC 3.3V wire to **3V3**
4. Solder GC Ground wire to **GND**
5. Double-check connections with multimeter

### Step 3: Secure and Insulate

1. Apply heat shrink to individual solder joints
2. Use larger heat shrink or electrical tape for the wire bundle
3. Add strain relief where the cable meets the board
4. Optional: 3D print a case

## Firmware

1. Download the latest firmware:
   **[joypad_X.X.X_gc2usb_kb2040.uf2](https://github.com/joypad-ai/joypad-os/releases/latest)**

2. Connect USB-C cable to KB2040 and your computer

3. Enter bootloader mode:
   - Hold **BOOT** button
   - Press **RESET** button
   - Release both
   - `RPI-RP2` drive appears

4. Drag & drop the `.uf2` file to the `RPI-RP2` drive

5. Drive auto-ejects when complete — KB2040 RGB LED should light up purple

## Testing

1. Plug a GameCube controller into the extension cable plug
2. Connect the KB2040 USB-C port to your PC
3. Open a gamepad tester (e.g., [Gamepad Tester](https://gamepad-tester.com))
4. Verify all buttons, both sticks, and analog triggers register correctly

### What to Check

- **Control stick** — Full range on left analog X/Y
- **C-stick** — Full range on right analog X/Y
- **L/R triggers** — Analog range 0–255 with digital click
- **All buttons** — A, B, X, Y, Z, Start, D-pad
- **Rumble** — Test in a game that supports gamepad vibration

### Profile Switching

Hold **Start** for 2 seconds, then press **D-Pad Up/Down** to cycle profiles. The controller rumbles to confirm.

**Profiles:**
- **Default** — Standard GC layout: A/B/X/Y mapped as-is
- **Xbox** — A/B swapped (matches Xbox controller layout)
- **Nintendo** — X/Y swapped (matches modern Nintendo layout)

## Troubleshooting

**No response from controller?**
- Verify wiring with multimeter — especially Data on A3 (GPIO29)
- Check solder joints aren't bridged
- Make sure you're using the correct end of the extension cable (male/plug end)
- Try a different GameCube controller

**Wrong button mappings?**
- Try different profiles (hold Start, tap D-Pad)
- Use [config.joypad.ai](https://config.joypad.ai) for custom mapping

**Analog sticks drifting?**
- GC sticks are calibrated on power-up — make sure sticks are centered when plugging in
- Check for a worn controller (physical stick drift)

**Intermittent disconnects?**
- Check for cold solder joints
- Secure cable strain relief
- Try a shorter USB-C cable

**No rumble?**
- Rumble requires the controller to have a working rumble motor
- Some games or platforms don't send rumble to HID gamepads
- Check USB power — rumble draws extra current

## Supported Controllers

✅ **Full Support:**
- Official Nintendo GameCube controllers (all colors/revisions)
- WaveBird Wireless (receiver plugs in like a wired controller)
- Nintendo Switch GameCube controller (Smash Bros. edition)

⚠️ **Partial Support:**
- Third-party GameCube controllers (may have non-standard analog ranges)
- GameCube keyboard (detected but keyboard mode not applicable in USB output)

❌ **Not Supported:**
- DK Bongos (non-standard protocol)
- GameCube microphone

## Button Mapping Reference

### Default Profile

| GC Button | USB Output |
|-----------|------------|
| A | B2 (Circle/B) |
| B | B1 (Cross/A) |
| X | B4 (Triangle/Y) |
| Y | B3 (Square/X) |
| Z | R1 (RB) |
| L (digital) | L2 (LT) |
| R (digital) | R2 (RT) |
| L (analog) | Left trigger axis |
| R (analog) | Right trigger axis |
| Start | Start |
| D-pad | D-pad |
| Control Stick | Left stick |
| C-Stick | Right stick |

## Resources

- [GameCube Protocol Reference](../consoles/GAMECUBE.md)
- [Hardware Compatibility List](../HARDWARE.md)
- [Joypad OS GitHub](https://github.com/joypad-ai/joypad-os)
- [Discord Community](https://discord.gg/joypad)
- [Config Tool](https://config.joypad.ai)

---

*Questions? Join the [Joypad Discord](https://discord.gg/joypad) for help!*
