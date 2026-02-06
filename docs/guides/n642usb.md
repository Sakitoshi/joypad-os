# N642USB Build Guide

> Use your N64 controller as a USB gamepad on PC, MiSTer, or any USB host.

## Overview

N642USB reads a native N64 controller and outputs a standard USB HID gamepad. Play N64 games on emulators, MiSTer FPGA, or any PC with the original controller feel. Features include:

- **Full analog stick support** — N64 stick scaled to full USB range
- **C-buttons as right stick** — C-pad maps to right analog for dual-stick games
- **Rumble Pak support** — Vibration feedback from games
- **2 button profiles** (Default, Dual Stick)
- **Low latency** — Direct joybus polling at 60Hz via PIO
- **Plug and play** — Standard USB HID gamepad, no drivers needed

## Parts List

| Part | Quantity | Link | ~Price |
|------|----------|------|--------|
| Adafruit KB2040 | 1 | [Adafruit](https://www.adafruit.com/product/5302) | $9 |
| N64 controller extension cable | 1 | [Amazon](https://www.amazon.com/s?k=n64+extension+cable) | $8 |
| USB-C cable | 1 | (for connecting to PC) | — |

**Total: ~$17** (+ tools if needed)

### Tools Required

- Soldering iron + solder
- Wire strippers
- Multimeter (recommended)
- Heat shrink tubing (optional)

## Wiring

Cut the N64 extension cable and strip the wires. You'll use the **male end** (the plug) that connects to the controller.

### N64 Controller Connector Pinout

```
     ┌──────────┐
     │          │
     │ 1  2  3 │
     │          │
     └──────────┘
      (front view)
```

| Pin | Color (typical) | Function |
|-----|-----------------|----------|
| 1 | White | Ground |
| 2 | Red | Data |
| 3 | Black | 3.3V Power |

> ⚠️ **Wire colors vary by cable!** Always verify with a multimeter. The N64 connector is simpler than GameCube — only 3 pins.

### KB2040 Wiring

| KB2040 Pin | Connects To |
|------------|-------------|
| **A3** (GPIO29) | N64 Data (Pin 2) |
| **3V3** | N64 3.3V (Pin 3) |
| **GND** | N64 Ground (Pin 1) |

> 💡 **Power note:** The KB2040 provides 3.3V to the controller. The N64 controller runs entirely on 3.3V — no 5V connection needed.

### Wiring Diagram

```
N64 Controller                  KB2040
       ┌─────┐                ┌─────────┐
 GND ──┤ 1   │────────────────┤ GND     │
       │     │                │         │
Data ──┤ 2   │────────────────┤ A3      │
       │     │                │ (GPIO29)│
3.3V ──┤ 3   │────────────────┤ 3V3     │
       └─────┘                └─────────┘

 Only 3 wires needed: Data, 3V3, GND
```

## Assembly

### Step 1: Prepare the Cable

1. Cut the N64 extension cable, keeping the **male end** (the plug the controller connects to)
2. Strip 2–3 inches of the outer sheath
3. Strip ~5mm from each inner wire
4. Identify wires with multimeter (continuity to pins)

### Step 2: Solder to KB2040

1. Tin the KB2040 pads (A3, 3V3, GND)
2. Solder N64 Data wire to **A3** (GPIO29)
3. Solder N64 3.3V wire to **3V3**
4. Solder N64 Ground wire to **GND**
5. Double-check connections with multimeter

### Step 3: Secure and Insulate

1. Apply heat shrink to individual solder joints
2. Use larger heat shrink or electrical tape for the wire bundle
3. Add strain relief where the cable meets the board
4. Optional: 3D print a case

## Firmware

1. Download the latest firmware:
   **[joypad_X.X.X_n642usb_kb2040.uf2](https://github.com/joypad-ai/joypad-os/releases/latest)**

2. Connect USB-C cable to KB2040 and your computer

3. Enter bootloader mode:
   - Hold **BOOT** button
   - Press **RESET** button
   - Release both
   - `RPI-RP2` drive appears

4. Drag & drop the `.uf2` file to the `RPI-RP2` drive

5. Drive auto-ejects when complete — KB2040 RGB LED should light up green

## Testing

1. Plug an N64 controller into the extension cable plug
2. Connect the KB2040 USB-C port to your PC
3. Open a gamepad tester (e.g., [Gamepad Tester](https://gamepad-tester.com))
4. Verify all buttons and the analog stick register correctly

### What to Check

- **Analog stick** — Full range on left analog X/Y (N64 stick is scaled from ±80 to full USB range)
- **C-buttons** — Register as both face buttons AND right stick directions
- **All buttons** — A, B, Z, L, R, Start, D-pad
- **Rumble** — Insert a Rumble Pak in the controller and test in a game with vibration

### Profile Switching

Hold **Start** for 2 seconds, then press **D-Pad Up/Down** to cycle profiles.

**Profiles:**
- **Default** — DC-style face buttons: A→B1, C-Down→B2, B→B3, C-Left→B4, C-Up/C-Right→L3/R3. C-buttons also map to right stick.
- **Dual Stick** — A→B1, B→B2, C-buttons map to right stick only (no button output). Best for dual-analog games.

## Troubleshooting

**No response from controller?**
- Verify wiring with multimeter — especially Data on A3 (GPIO29)
- Check solder joints aren't bridged
- Make sure you're using the correct end of the extension cable (male/plug end)
- Try a different N64 controller

**Analog stick range seems limited?**
- N64 sticks typically only reach ±80 out of ±128 — the firmware scales this to full USB range automatically
- A worn N64 stick may have reduced range — this is a physical controller issue

**Wrong button mappings?**
- Try the Dual Stick profile for a simpler layout
- Use [config.joypad.ai](https://config.joypad.ai) for custom mapping

**No rumble?**
- Rumble Pak must be inserted in the controller
- The firmware auto-detects and initializes the Rumble Pak ~170ms after connection
- Some games or platforms don't send rumble to HID gamepads
- Check USB power — rumble draws extra current

**Intermittent disconnects?**
- Check for cold solder joints
- Brief disconnects during Rumble Pak commands are normal and debounced internally
- Try a shorter USB-C cable

## Supported Controllers

✅ **Full Support:**
- Official Nintendo N64 controllers (all colors/revisions)
- N64 controllers with Rumble Pak
- N64 controllers with Controller Pak (pak type is detected)

⚠️ **Partial Support:**
- Third-party N64 controllers (may have non-standard analog range)
- Hori Mini Pad (different stick mechanism, range may vary)

❌ **Not Supported:**
- N64 mouse (Transfer Pak)
- Randnet keyboard

## Button Mapping Reference

### Default Profile (DC-style)

| N64 Button | USB Output |
|------------|------------|
| A | B1 (Cross/A) |
| B | B3 (Square/X) |
| C-Down | B2 (Circle/B) |
| C-Left | B4 (Triangle/Y) |
| C-Up | L3 (Left Stick Click) |
| C-Right | R3 (Right Stick Click) |
| Z | R1 (RB) |
| L | L2 (LT) |
| R | R2 (RT) |
| Start | Start |
| D-pad | D-pad |
| Analog Stick | Left stick |
| C-buttons | Right stick (digital) |

### Dual Stick Profile

| N64 Button | USB Output |
|------------|------------|
| A | B1 (Cross/A) |
| B | B2 (Circle/B) |
| Z | R1 (RB) |
| L | L2 (LT) |
| R | R2 (RT) |
| Start | Start |
| D-pad | D-pad |
| Analog Stick | Left stick |
| C-buttons | Right stick only (no button output) |

## Resources

- [Hardware Compatibility List](../HARDWARE.md)
- [Joypad OS GitHub](https://github.com/joypad-ai/joypad-os)
- [Discord Community](https://discord.gg/joypad)
- [Config Tool](https://config.joypad.ai)

---

*Questions? Join the [Joypad Discord](https://discord.gg/joypad) for help!*
