#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//OBD related
#include "BluetoothSerial.h"
#include "ELMduino.h"

BluetoothSerial SerialBT;
#define ELM_PORT   SerialBT
#define DEBUG_PORT Serial

ELM327 myELM327;

uint32_t oiltemp = 0;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000
};

void setup() {
  Serial.begin(115200);
  SerialBT.setPin("1234");
  ELM_PORT.begin("ArduHUD", true);

  if (!ELM_PORT.connect("OBDII"))
  {
    DEBUG_PORT.println("Couldn't connect to OBD scanner - Phase 1");
    while (1);
  }

  if (!myELM327.begin(ELM_PORT, true, 2000))
  {
    //Serial.println("Couldn't connect to OBD scanner - Phase 2");
    while (1);
  }

  //Serial.println("Connected to ELM327");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  delay(2000);

}

void loop() {

  float tempOilTemp = myELM327.oilTemp();

  if (myELM327.status == ELM_SUCCESS)
  {
    oiltemp = (uint32_t)tempOilTemp;
    //Serial.print("Oiltemp: "); Serial.println(oiltemp);
  }
  else
    myELM327.printError();

  showEngOilTemp(oiltemp);
}


void showEngOilTemp(uint32_t oiltemp) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("Engine Oil Temp:"));
  display.println(F(" "));

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(oiltemp);
  display.print((char)247); display.print("C");

  display.display();
  delay(5000);
}
