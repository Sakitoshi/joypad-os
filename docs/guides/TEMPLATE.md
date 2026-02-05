# [Adapter Name]

> One-line description of what this adapter does.

![Header image or wiring diagram](../images/guides/adapter-name-hero.png)

## Overview

Brief explanation of the use case. What controllers work? What console/system does it connect to?

## Parts List

| Part | Quantity | Link | ~Price |
|------|----------|------|--------|
| MCU Board (e.g., KB2040) | 1 | [Adafruit](https://adafruit.com/...) | $X.XX |
| USB Cable | 1 | [Amazon](https://...) | $X.XX |
| ... | ... | ... | ... |

**Total: ~$XX**

### Optional
- 3D printed case ([STL files](../cases/adapter-name/))
- Heat shrink tubing

## Wiring

![Wiring diagram](../images/guides/adapter-name-wiring.png)

| MCU Pin | Connects To |
|---------|-------------|
| GP0 | ... |
| GP1 | ... |
| GND | ... |

## Assembly

### Step 1: Prepare the MCU
Description and photo.

### Step 2: Wire the connections
Description and photo.

### Step 3: (Optional) Install in case
Description and photo.

## Firmware

1. Download the latest firmware: [joypad_X.X.X_adaptername_board.uf2](https://github.com/joypad-ai/joypad-os/releases/latest)
2. Hold **BOOT** button while connecting USB to your computer
3. Drag & drop the `.uf2` file to the `RPI-RP2` drive
4. Drive auto-ejects when complete

## Testing

1. Connect a USB controller to the adapter
2. Connect the adapter to your console
3. Verify button inputs work
4. (Optional) Test with [config.joypad.ai](https://config.joypad.ai)

## Troubleshooting

**Controller not recognized?**
- Check USB cable supports data (not charge-only)
- Try a different controller

**Buttons mapped wrong?**
- Use [config.joypad.ai](https://config.joypad.ai) to customize mappings

## Resources

- [Joypad OS GitHub](https://github.com/joypad-ai/joypad-os)
- [Discord Community](https://discord.gg/joypad)
