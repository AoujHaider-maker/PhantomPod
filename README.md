# PhantomPod!
Concept illustration:

<img width="363" height="479" alt="image" src="https://github.com/user-attachments/assets/e3178f4f-8b4d-403e-b12b-a08705990edb" />

PhantomPod is a pocket digital cassette player built around an ESP32-S3. You slot in a vertical cassette-shaped cartridge that holds a microSD card and an NFC tag. Spring-loaded pogo pins read its six gold contacts, and the player recognizes it automatically. It has a 2.23" 128×32 OLED, 12 underglow RGB LEDs, a side rotary encoder and buttons, two headphone jacks driven by a PCM5102A DAC and TPA6132A2 amp, and USB-C LiPo charging. I designed the whole 80×125 mm 2-layer PCB in KiCad (schematic, layout, DRC/ERC clean), exported the Gerbers and BOM, and wrote a PlatformIO bring-up firmware starter. It hasn’t been built yet, so the firmware is untested on hardware.

## Features:

- Swapable digital cassette: vertical cassette-shaped cartridge that houses a microSD card and NFC tag internally. Slot it in, and the player will recognize it automatically.
- Pogo pin spring-loaded contact reads 6 gold contacts of the cassette analogously to how the contact mechanism would work in a standard cassette deck.
- ESP32-S3-WROOM-1 module as an “brain” placed onto 2-layer KiCad custom-made PCB (80×125 mm).
- 2.23" 128x32 OLED (I2C) for track info and animations, framed by an angled bezel so it fits the cassette-player look.
- 12 SK6812MINI RGB LED lights for the circuit under the board through the transparent shell.
- Rotary encoder on the side of the device to control volume (Bourns PEC09).
- Buttons to the side of the device for play/pause and FF/RW functions, plus one button for setup and power slider, so the front of the housing remains pristine.
- 2× 3.5 mm audio jacks, so the experience can be shared with someone else powered by PCM5102A DAC and TPA6132A2 headphone amplifier.
- Rechargeable LiPo battery charged through USB-C port, with appropriate charging circuitry and protection.
- Translucent shell inspired by Sony TPS-L2.
  
## CAD Model:

Design target: a clear shell roughly 88 × 133.5 mm and about 20 mm thick, so the board and underglow LEDs are visible. The cassette slides in vertically from the top and the pogo pins touch its six gold pads. The OLED sits behind an angled window; the display is rectangular, and the bezel plus the firmware (which keeps the corners black) give it the angled shape. The casing isn’t modelled yet. The board’s 3D model is in CAD/ for anyone designing one.

## PCB
Here's the PCB I made in  KiCad.
<img width="946" height="616" alt="image" src="https://github.com/user-attachments/assets/bd4c1319-b21f-4a1a-9bf5-bd641cfeca20" />

<img width="977" height="674" alt="image" src="https://github.com/user-attachments/assets/736c56b5-f92a-4428-8a99-5190ab44b667" />

## Firmware Overview

Starter bring-up firmware (PlatformIO, ESP32-S3). It checks the OLED, LEDs, RC522, cassette microSD, audio and controls. Pins are in Firmware/include/pins.h. It has not been tested on hardware yet, because the board hasn’t been built. Music playback and the menu are still to do. Anyone building this is welcome to write their own firmware.

## BOM:

Here should be everything you need to make the PhantomPod. The full KiCad parts list is in Production/DCD.csv.

**Main parts**
- 1x ESP32-S3-WROOM-1-N16 module
- 1x 2.23" 128x32 I2C OLED display (4-pin: GND, VCC, SCL, SDA)
- 1x RC522 RFID reader module (8-pin)
- 1x PCM5102A DAC breakout (6-pin)
- 1x TPA6132A2 headphone amplifier
- 12x SK6812MINI RGB LEDs (underglow)
- 1x Bourns PEC09 rotary encoder (side volume dial)
- 2x CUI SJ1-3523N 3.5 mm headphone jacks
- 1x USB-C receptacle (GCT USB4105)
- 1x 3.7 V LiPo battery with protection circuit, JST-PH 2-pin plug
- 1x JST-PH S2B-PH-K 2-pin battery connector

**Cassette**
- 6x spring-loaded pogo pins (2.54 mm pitch)
- 1x NFC tag (NTAG213/215) and 1x microSD card
- 1x 3D-printed cassette and clear shell

**Power and protection**
- 1x MCP73831 LiPo charger
- 1x AP2112K-3.3 LDO regulator
- 1x USBLC6-2SC6 USB protection
- 3x AO3401A P-MOSFETs, 2x 2N7002 N-MOSFETs

**Buttons**
- 6x Omron B3U-3000P side buttons (play, forward, back, setup, reset, boot)
- 1x SPDT slide switch (power)

**Passives (0603 unless noted)**
- Capacitors: 12x 100 nF, 6x 1 uF, 1x 10 uF, 1x 0.1 uF, 3x 2.2 uF (0805), 2x 4.7 uF (0805), 1x 10 uF (0805), 1x 100 uF (1210)
- Resistors: 4x 100 kOhm, 2x 10 kOhm, 2x 5.1 kOhm, 1x 2 kOhm, 1x 1 kOhm, 1x 330 Ohm
- 1x red or green LED (charge indicator)
- Female pin sockets for the modules (1x4, 1x8, 1x6, 1x3) and a 1x6 pin header
## IMPORTANT
This is a design that hasn’t been built yet.
