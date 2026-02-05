# USB2GC Build Guide

> Use any USB controller on your GameCube or Wii.

![USB2GC Adapter](../images/Joypad_NGC.png)

## Overview

USB2GC lets you play GameCube and Wii games with modern USB controllers — Xbox, PlayStation, Switch Pro, 8BitDo, and more. Features include:

- **5 button profiles** (Default, SNES, Melee, MKWii, Fighting)
- **Rumble support** for compatible controllers
- **Keyboard mode** for PSO and other games
- **Copilot mode** for accessibility

## Parts List

| Part | Quantity | Link | ~Price |
|------|----------|------|--------|
| Adafruit KB2040 | 1 | [Adafruit](https://www.adafruit.com/product/5302) | $9 |
| GameCube controller extension cable | 1 | [Amazon](https://www.amazon.com/s?k=gamecube+extension+cable) | $8 |
| USB-C cable | 1 | (for flashing firmware) | — |

**Total: ~$17** (+ tools if needed)

### Tools Required

- Soldering iron + solder
- Wire strippers
- Multimeter (recommended)
- Heat shrink tubing (optional)

## Wiring

Cut the GameCube extension cable and strip the wires. You'll use the **female end** (the socket) that plugs into the console.

### GameCube Connector Pinout

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
| 6 | Blue | 3.3V (from console) |
| 7 | — | Shield/Ground |

> ⚠️ **Wire colors vary by cable!** Always verify with a multimeter.

### KB2040 Wiring

| KB2040 Pin | Connects To |
|------------|-------------|
| **D7** | GC Data (Pin 2) |
| **3V3** | GC 3.3V (Pin 6) |
| **GND** | GC Ground (Pin 3 or 4) |

**Do NOT connect 5V** — the KB2040 is powered via USB, not the console.

### Wiring Diagram

```
GameCube Console Port          KB2040
       ┌─────┐                ┌─────┐
  5V ──┤ 1   │                │     │
       │     │                │     │
Data ──┤ 2   │────────────────┤ D7  │
       │     │                │     │
 GND ──┤ 3   │────────────────┤ GND │
       │     │                │     │
 GND ──┤ 4   │                │     │
       │     │                │     │
3.3V ──┤ 6   │────────────────┤ 3V3 │
       └─────┘                └─────┘
```

## Assembly

### Step 1: Prepare the Cable

1. Cut the GameCube extension cable, keeping the **female end** (console side)
2. Strip 2-3 inches of the outer sheath
3. Strip ~5mm from each inner wire
4. Identify wires with multimeter (continuity to pins)

### Step 2: Solder to KB2040

1. Tin the KB2040 pads (D7, 3V3, GND)
2. Solder GC Data wire to **D7**
3. Solder GC 3.3V wire to **3V3**
4. Solder GC Ground wire to **GND**
5. Double-check connections with multimeter

### Step 3: Secure and Insulate

1. Apply heat shrink to individual wires
2. Use larger heat shrink or electrical tape for the bundle
3. Optional: 3D print a case ([STL files](https://github.com/joypad-ai/joypad-os/tree/main/cases/usb2gc))

## Firmware

1. Download the latest firmware:
   **[joypad_X.X.X_usb2gc_kb2040.uf2](https://github.com/joypad-ai/joypad-os/releases/latest)**

2. Connect USB-C cable to KB2040 and your computer

3. Enter bootloader mode:
   - Hold **BOOT** button
   - Press **RESET** button
   - Release both
   - `RPI-RP2` drive appears

4. Drag & drop the `.uf2` file to the `RPI-RP2` drive

5. Drive auto-ejects when complete — KB2040 LED should light up

## Testing

1. Plug a USB controller into the KB2040's USB-C port (with OTG adapter)
2. Connect the GameCube plug to your console's controller port
3. Turn on the console
4. Verify buttons work in a game or the GameCube menu

### Profile Switching

1. Hold **Select** for 2 seconds
2. Press **D-Pad Up** to cycle forward through profiles
3. Controller rumbles to confirm
4. Profile saves automatically

**Profiles:**
- Default — Standard mapping
- SNES — SNES-style (L/R as full press)
- SSBM — Super Smash Bros. Melee
- MKWii — Mario Kart Wii
- Fighting — Fight stick layout

## Troubleshooting

**No response from controller?**
- Verify wiring with multimeter
- Check solder joints aren't bridged
- Try a different USB controller
- Make sure USB cable supports data (not charge-only)

**Wrong button mappings?**
- Try different profiles (hold Select, tap D-Pad)
- Use [config.joypad.ai](https://config.joypad.ai) for custom mapping

**Intermittent disconnects?**
- Check for cold solder joints
- Secure cable strain relief
- Try shorter USB cable

**No rumble?**
- Controller must support rumble (Xbox, DualShock, etc.)
- Rumble is enabled by default in all profiles

## Supported Controllers

✅ **Full Support:**
- Xbox 360, One, Series X|S
- PlayStation DualShock 3/4, DualSense
- Switch Pro Controller
- 8BitDo controllers
- Most USB HID gamepads

⚠️ **Partial Support:**
- Generic USB controllers (may need config)
- USB keyboards (toggle with Scroll Lock)

## Resources

- [GameCube Protocol Reference](../consoles/GAMECUBE.md)
- [Hardware Compatibility List](../HARDWARE.md)
- [Joypad OS GitHub](https://github.com/joypad-ai/joypad-os)
- [Discord Community](https://discord.gg/joypad)
- [Config Tool](https://config.joypad.ai)

---

*Questions? Join the [Joypad Discord](https://discord.gg/joypad) for help!*
