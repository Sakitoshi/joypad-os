# USB2USB Build Guide

> Convert any USB controller to a universal SInput gamepad.

## Overview

USB2USB converts any USB controller into a standardized SInput HID gamepad. Use it to:

- Add modern USB controllers to retro PC setups
- Standardize button mappings across different controllers
- Add profile switching and custom configs to any controller
- Pass through IMU data and RGB LED control

## Parts List

| Part | Quantity | Link | ~Price |
|------|----------|------|--------|
| Adafruit Feather RP2040 USB Host | 1 | [Adafruit](https://www.adafruit.com/product/5723) | $13 |
| USB-C cable | 1 | (for connecting to PC) | — |

**Total: ~$13**

That's it! The Feather USB Host has a built-in USB-A port for your controller.

## Assembly

**No soldering required!** The Feather RP2040 USB Host is ready to use out of the box.

1. Download firmware
2. Flash to board
3. Plug in controller
4. Done

## Firmware

1. Download the latest firmware:
   **[joypad_X.X.X_usb2usb_feather.uf2](https://github.com/joypad-ai/joypad-os/releases/latest)**

2. Connect USB-C cable to Feather and your computer

3. Enter bootloader mode:
   - Hold **BOOT** button
   - Press **RESET** button
   - Release both
   - `RPI-RP2` drive appears

4. Drag & drop the `.uf2` file to the `RPI-RP2` drive

5. Drive auto-ejects when complete

## Usage

1. Connect your USB controller to the Feather's **USB-A host port**
2. Connect the Feather's **USB-C port** to your PC/device
3. Controller appears as "Joypad SInput" gamepad
4. Use normally in any game or application

### SInput Features

The output is a standardized SInput HID gamepad with:

- **17 buttons** — All standard gamepad buttons
- **6 analog axes** — Two sticks + two triggers + optional gyro
- **IMU passthrough** — Motion data from DualSense/Switch Pro
- **Player LED** — Controller identification
- **RGB LED** — Status feedback

### Profile Switching

Same as other Joypad adapters:
1. Hold **Select** for 2 seconds
2. Press **D-Pad Up/Down** to cycle profiles
3. Controller rumbles to confirm

## Supported Controllers

✅ **Full Support:**
- Xbox 360, One, Series X|S (wired)
- PlayStation DualShock 3/4, DualSense
- Switch Pro Controller
- 8BitDo USB controllers
- Most USB HID gamepads

✅ **USB Keyboards/Mice:**
- Keyboards work as gamepad (WASD = stick, etc.)
- Mice supported for games with mouse input

## Troubleshooting

**Controller not recognized?**
- Try a different USB cable
- Check controller works on PC directly
- Some wireless receivers may not be compatible

**Buttons mapped wrong?**
- Use [config.joypad.ai](https://config.joypad.ai) to customize
- Try different profiles

**No rumble?**
- Rumble passthrough requires compatible controller
- Some games may not send rumble to HID gamepads

## Alternative Boards

If you don't have the Feather USB Host, you can use:

| Board | Notes |
|-------|-------|
| RP2040-Zero | Needs USB-A breakout board |
| KB2040 | Needs USB-A OTG adapter |
| Pico | Needs USB-A host wiring |

The Feather USB Host is recommended for simplicity.

## Resources

- [SInput Protocol Spec](https://github.com/joypad-ai/sinput-spec)
- [Hardware Compatibility List](../HARDWARE.md)
- [Joypad OS GitHub](https://github.com/joypad-ai/joypad-os)
- [Config Tool](https://config.joypad.ai)

---

*Questions? Join the [Joypad Discord](https://discord.gg/joypad) for help!*
