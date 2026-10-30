// PhantomPod bring-up starter. Untested on hardware: expect to debug.
// Each stage prints to Serial and to the OLED so you can see what works.
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <U8g2lib.h>
#include <Adafruit_NeoPixel.h>
#include <MFRC522.h>
#include <driver/i2s.h>
#include "pins.h"

// 2.23" 128x32 modules are usually SSD1305. If the screen stays blank,
// swap to U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C.
U8G2_SSD1305_128X32_ADAFRUIT_F_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE, PIN_I2C_SCL, PIN_I2C_SDA);
Adafruit_NeoPixel leds(NUM_LEDS, PIN_LED_DATA, NEO_GRB + NEO_KHZ800);
MFRC522 rfid(PIN_RFID_CS, PIN_RFID_RST);

volatile int encPos = 0;
int lastA = HIGH;

void show(const char* l1, const char* l2 = "") {
  oled.clearBuffer();
  oled.setFont(u8g2_font_6x12_tr);
  oled.drawStr(0, 12, l1);
  oled.drawStr(0, 28, l2);
  oled.sendBuffer();
  Serial.printf("%s | %s\n", l1, l2);
}

void stageLeds() {
  digitalWrite(PIN_LED_EN, HIGH);
  leds.begin(); leds.setBrightness(40);
  for (int i = 0; i < NUM_LEDS; i++) { leds.setPixelColor(i, leds.Color(0, 80, 255)); leds.show(); delay(60); }
}

void stageAudioBeep() {
  i2s_config_t cfg = {};
  cfg.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
  cfg.sample_rate = 44100;
  cfg.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;
  cfg.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;
  cfg.communication_format = I2S_COMM_FORMAT_STAND_I2S;
  cfg.dma_buf_count = 8; cfg.dma_buf_len = 256;
  cfg.tx_desc_auto_clear = true;
  i2s_pin_config_t pins = {};
  pins.mck_io_num = I2S_PIN_NO_CHANGE;       // PCM5102A SCK is tied low on the module
  pins.bck_io_num = PIN_I2S_BCLK;
  pins.ws_io_num = PIN_I2S_WS;
  pins.data_out_num = PIN_I2S_DOUT;
  pins.data_in_num = I2S_PIN_NO_CHANGE;
  i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pins);
  int16_t buf[512];
  float ph = 0;
  for (int n = 0; n < 200; n++) {             // ~2 s of 440 Hz, kept quiet
    for (int i = 0; i < 512; i += 2) {
      int16_t s = (int16_t)(sinf(ph) * 3000); ph += 2 * PI * 440 / 44100;
      buf[i] = s; buf[i + 1] = s;
    }
    size_t w; i2s_write(I2S_NUM_0, buf, sizeof(buf), &w, portMAX_DELAY);
  }
}

bool stageCassetteSD() {
  digitalWrite(PIN_CASS_EN, HIGH); delay(50);
  return SD.begin(PIN_CASS_CS, SPI, 4000000);
}

void setup() {
  Serial.begin(115200); delay(1500);
  pinMode(PIN_CASS_EN, OUTPUT); digitalWrite(PIN_CASS_EN, LOW);
  pinMode(PIN_LED_EN, OUTPUT);  digitalWrite(PIN_LED_EN, LOW);
  const int ins[] = {PIN_ENC_SW, PIN_ENC_A, PIN_ENC_B, PIN_BTN_FF, PIN_BTN_BACK, PIN_BTN_PLAY, PIN_BTN_SETUP};
  for (int p : ins) pinMode(p, INPUT_PULLUP);
  pinMode(PIN_RFID_CS, OUTPUT); digitalWrite(PIN_RFID_CS, HIGH);
  pinMode(PIN_CASS_CS, OUTPUT); digitalWrite(PIN_CASS_CS, HIGH);

  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  oled.begin();
  show("PhantomPod", "bring-up v0");
  delay(1000);

  stageLeds();       show("LEDs on", "blue ring?");  delay(1000);

  SPI.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI);
  rfid.PCD_Init();
  byte v = rfid.PCD_ReadRegister(MFRC522::VersionReg);
  char b[24]; snprintf(b, sizeof b, "RC522 ver 0x%02X", v);
  show(b, (v == 0x91 || v == 0x92) ? "OK" : "check wiring"); delay(1500);

  bool sd = stageCassetteSD();
  show("Cassette SD", sd ? "mounted" : "not found"); delay(1500);

  show("Audio", "440Hz beep");
  stageAudioBeep();
  show("Turn knob/press", "buttons...");
}

void loop() {
  int a = digitalRead(PIN_ENC_A);
  if (a != lastA && a == LOW) encPos += (digitalRead(PIN_ENC_B) == HIGH) ? 1 : -1;
  lastA = a;

  char l1[24], l2[24];
  snprintf(l1, sizeof l1, "enc %d sw%d", encPos, !digitalRead(PIN_ENC_SW));
  snprintf(l2, sizeof l2, "F%d B%d P%d S%d", !digitalRead(PIN_BTN_FF), !digitalRead(PIN_BTN_BACK),
           !digitalRead(PIN_BTN_PLAY), !digitalRead(PIN_BTN_SETUP));
  static uint32_t t = 0;
  if (millis() - t > 80) { show(l1, l2); t = millis(); }

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    char u[24] = "tag:";
    for (byte i = 0; i < rfid.uid.size && i < 4; i++) sprintf(u + strlen(u), "%02X", rfid.uid.uidByte[i]);
    show("Cassette tag!", u); delay(1000);
    rfid.PICC_HaltA();
  }
}
