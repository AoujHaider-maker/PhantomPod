# PhantomPod firmware (starter, untested on hardware)

A bring-up sketch that checks each part of the board in turn: OLED, 12 LEDs, RC522, cassette microSD, audio beep, encoder and buttons.
Pin numbers come from the KiCad PCB (`include/pins.h`).

Build: install VS Code + the PlatformIO extension, open this folder, click Upload.

Known notes
- Board has not been built yet, so none of this has run on real hardware.
- Buttons and encoder are read with internal pull-ups (assumes they connect to GND when pressed).
- OLED driver may need changing to SSD1306 depending on the module.
- GPIO10 (SD_CS) goes nowhere; the music card is the cassette microSD on CASS_CS (GPIO3).
- Music playback, menu and cassette-insert detection are not written yet.
