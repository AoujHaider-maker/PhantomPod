#pragma once
// PhantomPod GPIO map. Taken from DCD.kicad_pcb (U1 = ESP32-S3-WROOM-1).
// Module pin -> GPIO is from the ESP32-S3-WROOM-1 datasheet.

// I2S -> PCM5102A (J5)
#define PIN_I2S_BCLK   4   // module pin 4
#define PIN_I2S_WS     5   // module pin 5  (LCK)
#define PIN_I2S_DOUT   6   // module pin 6  (DIN)

// Encoder + buttons (assumed wired to GND when pressed: use INPUT_PULLUP)
#define PIN_ENC_SW     7
#define PIN_ENC_A     18
#define PIN_ENC_B      8
#define PIN_BTN_FF    15
#define PIN_BTN_BACK  16
#define PIN_BTN_PLAY  17
#define PIN_BTN_SETUP  1

// USB (native, handled by the chip)
#define PIN_USB_DM    19
#define PIN_USB_DP    20

// Shared SPI bus (RC522 on J4 + cassette microSD on J10)
#define PIN_SPI_MOSI  11
#define PIN_SPI_SCK   12
#define PIN_SPI_MISO  13
#define PIN_RFID_CS    9
#define PIN_RFID_RST  14
#define PIN_CASS_CS    3   // cassette microSD chip select (J10 pin 3)
// SD_CS (GPIO10) is routed to nothing on this board revision.

// I2C OLED (J3)
#define PIN_I2C_SDA    2
#define PIN_I2C_SCL   21

// Power switches (active HIGH)
#define PIN_CASS_EN   38   // HIGH = power the cassette pads (CASS_3V3)
#define PIN_LED_EN    39   // HIGH = power the LED strip (LED_PWR)
#define PIN_LED_DATA  40   // SK6812MINI data
#define NUM_LEDS      12
