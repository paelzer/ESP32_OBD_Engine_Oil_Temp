# ESP32_OBD_Engine_Oil_Temp
Reads engine oil temperature and battery voltage via ELM327 mini bluetooth scanner from car OBD and prints on OLED display

It has been tested sucessfully with following setup:

* Windows 10 x64

* Arduino IDE 1.8.18

* ESP32 D1 mini (other uC boards work as well with some modifications depending on the model)

* OLED TFT ILI9341 display 2.8" 320x240px (red colored board version)

## Requires following extensions installed to the Arduino IDE:
* Bodmer's "TFT_eSPI" library (I used v2.3.70)
* Powerbroker2's "ELMDuino" (I used 2.6.4)

## Required hardware components:
    ESP32 D1 mini
    OLED TFT Display 2.8" 320x240px (ILI9341)
    ELM327 mini bluetooth scanner
