# BT2USB Build Guide

> Use Bluetooth controllers as wired USB gamepads.

## Overview

BT2USB turns Bluetooth controllers into USB gamepads. Pair once, then use as a standard wired controller — no drivers needed.

**Why BT2USB?**
- Lower latency than native Bluetooth on many systems
- Use PS/Xbox controllers on devices without Bluetooth
- Consolidate wireless controllers to single USB port
- Works with retro PCs, MiSTer, emulation boxes

## Parts List

| Part | Quantity | Link | ~Price |
|------|----------|------|--------|
| Raspberry Pi Pico W | 1 | [Raspberry Pi](https://www.raspberrypi.com/products/raspberry-pi-pico/) | $6 |
| USB Micro-B cable | 1 | (for connecting to PC) | — |

**Total: ~$6**

### Alternative: Pico 2 W

For better performance, use the newer Pico 2 W:

| Part | Quantity | Link | ~Price |
|------|----------|------|--------|
| Raspberry Pi Pico 2 W | 1 | [Raspberry Pi](https://www.raspberrypi.com/products/raspberry-pi-pico-2/) | $7 |

## Assembly

**No soldering required!** Just flash the firmware.

## Firmware

1. Download the latest firmware:
   - **Pico W:** [joypad_X.X.X_bt2usb_pico_w.uf2](https://github.com/joypad-ai/joypad-os/releases/latest)
   - **Pico 2 W:** [joypad_X.X.X_bt2usb_pico2_w.uf2](https://github.com/joypad-ai/joypad-os/releases/latest)

2. Connect USB cable to Pico and your computer

3. Enter bootloader mode:
   - Hold **BOOTSEL** button while plugging in USB
   - `RPI-RP2` drive appears

4. Drag & drop the `.uf2` file to the `RPI-RP2` drive

5. Drive auto-ejects when complete — onboard LED blinks

## Pairing Controllers

### First-Time Pairing

1. Put your controller in **pairing mode**:

   | Controller | How to Pair |
   |------------|-------------|
   | DualShock 4 | Hold **Share + PS** until light double-flashes |
   | DualSense | Hold **Create + PS** until light double-flashes |
   | Switch Pro | Hold **Sync** button (top of controller) |
   | Xbox (BT) | Hold **Pair** button (top near USB port) |
   | 8BitDo | Hold **Pair** button (varies by model) |

2. Pico LED will flash rapidly during discovery
3. LED goes solid when paired
4. Controller works immediately!

### Reconnecting

Once paired, controllers reconnect automatically:
1. Turn on controller normally
2. Wait 2-3 seconds
3. Connected!

### Pairing a Different Controller

To pair a new controller, you need to clear the existing pairing:
1. Unplug the Pico
2. Hold **BOOTSEL** button
3. Plug in USB (but DON'T enter bootloader — release quickly)
4. LED flashes — pairing memory cleared
5. Put new controller in pairing mode

## Usage

Once paired, the controller appears as a standard USB HID gamepad:

- **Windows:** Shows as "Joypad SInput" in Game Controllers
- **Linux:** Shows in `/dev/input/js*`
- **macOS:** Works in supported games
- **MiSTer/Retro:** Just works!

### LED Indicators

| LED Pattern | Meaning |
|-------------|---------|
| Slow blink | Searching for controller |
| Fast blink | Pairing in progress |
| Solid | Connected |
| Off | No power / error |

## Supported Bluetooth Controllers

✅ **Full Support:**
- PlayStation DualShock 4 (all revisions)
- PlayStation DualSense (PS5)
- Nintendo Switch Pro Controller
- Nintendo Joy-Cons (grip mode)
- 8BitDo Bluetooth controllers

⚠️ **Partial Support:**
- Xbox Wireless (Bluetooth mode only, not Xbox Wireless protocol)
- Generic Bluetooth gamepads (may vary)

❌ **Not Supported:**
- Wii Remote (different protocol)
- Xbox 360 Wireless (requires proprietary dongle)

## Troubleshooting

**Controller won't pair?**
- Make sure controller is in pairing mode (light flashing)
- Clear existing pairing (see above)
- Try moving closer to the Pico
- Some controllers take 5-10 seconds to pair

**Paired but won't reconnect?**
- Turn controller off and on again
- Make sure Pico has power before turning on controller
- Clear pairing and re-pair if persistent

**Input lag?**
- BT2USB is typically lower latency than native Bluetooth
- If lag persists, check USB cable quality
- Avoid USB hubs if possible

**Buttons mapped wrong?**
- Use [config.joypad.ai](https://config.joypad.ai) for custom mapping
- Default mapping follows SInput standard

## Multiple Controllers

The current firmware supports **one controller at a time**. For multiple controllers:

- Use multiple Pico W boards (one per controller)
- Or wait for multi-controller firmware update

## Resources

- [Bluetooth Protocol Details](../HARDWARE.md#bluetooth-input-via-dongle)
- [Hardware Compatibility List](../HARDWARE.md)
- [Joypad OS GitHub](https://github.com/joypad-ai/joypad-os)
- [Config Tool](https://config.joypad.ai)

---

*Questions? Join the [Joypad Discord](https://discord.gg/joypad) for help!*
