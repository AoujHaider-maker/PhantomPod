# PhantomPod!
<img width="363" height="479" alt="image" src="https://github.com/user-attachments/assets/e3178f4f-8b4d-403e-b12b-a08705990edb" />



PhantomPod is a Device that can store your music and/or your audio files in a physical format.

I built this for [Stardance](https://stardance.space/r-33jyd), a Hack Club program where teens get to learn how to design their own custom hardware + software from scratch with all the physical components granted for free!

## Features:

- Swapable digital cassette: vertical cassette-shaped cartridge that houses a microSD card and NFC tag internally. Slot it in, and the player will recognize it automatically.
- Pogo pin spring-loaded contact reads 6 gold contacts of the cassette analogously to how the contact mechanism would work in a standard cassette deck.
- ESP32-S3-WROOM-1 module as an “brain” placed onto 2-layer KiCad custom-made PCB (80×125 mm).
- Display OLED for album art and animations where the screen size would be selected once a specific component was picked.
- 12 SK6812MINI RGB LED lights for the circuit under the board through the transparent shell.
- Rotary encoder on the side of the device to control volume (Bourns PEC09).
- Buttons to the side of the device for play/pause and FF/RW functions, plus one button for setup and power slider, so the front of the housing remains pristine.
- 2× 3.5 mm audio jacks, so the experience can be shared with someone else powered by PCM5102A DAC and TPA6132A2 headphone amplifier.
- Rechargeable LiPo battery charged through USB-C port, with appropriate charging circuitry and protection.
- Translucent shell inspired by Sony TPS-L2.
  
## CAD Model:

The PhantomPod is a clear shell, roughly 88 × 133.5 mm and about 20 mm thick, so the circuit board and underglow LEDs are visible. The cassette slides in vertically from the top, and the pogo pins touch its six gold pads.

![3D render](images/render.png)

The PCB's 3D model was exported from KiCad (see hardware/).

## PCB
Here's the PCB I made in  KiCad.
<img width="946" height="616" alt="image" src="https://github.com/user-attachments/assets/bd4c1319-b21f-4a1a-9bf5-bd641cfeca20" />

<img width="977" height="674" alt="image" src="https://github.com/user-attachments/assets/736c56b5-f92a-4428-8a99-5190ab44b667" />

## Firmware Overview

The firmware for the ESP32-S3 is planned in Arduino/PlatformIO. It is not written yet, because I'm waiting for the hardware to test it. Planned design:

1. Boot, then initialise the OLED, buttons, encoder and the RGB LEDs.
2. Poll the RC522 RFID reader for a cassette tag. When one is detected, power the cassette contacts (CASS_EN) and mount its microSD card over SPI.
3. Play audio from the card through the PCM5102A DAC over I2S, with volume from the rotary encoder.
4. Buttons: play/pause, next/previous, setup. The OLED shows the track name and animations.
5. LED effects follow the music (planned).

## BOM:
