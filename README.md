# Testing equipment for RaFrBio software

## Display 
3.2” TFT LCD with SD and Touch for Arduino Mega with adjustable TFT shield
(we don’t use touch screen function of the display)
Link:	[Datasheet display](https://drive.google.com/open?id=0B3NM4_m6O6VkZUs2ZkctZUhVSmM)

Arduino library used:
* **UTFT** - The UTFT library by Henning Karlsen provides an easy way to interface with many popular TFT modules.
* **UTFT_SDRaw** is an alternative to Henning Karlsen’s UTFT_TinyFAT and allows the loading of raw bitmap images to the LCD from the SD card. It uses the standard SdFat Arduino library for card access.


## Keypad
Normally high buttons (HIGH if no pressed, LOW if pressed)
(Need to implement anti-bounching filter to avoid double detection of key pressed)

KEY 1 -> Arduino PIN 11
KEY 2 -> Arduino PIN 10
KEY 3 -> Arduino PIN 13
KEY 4 -> Arduino PIN 12


## Beeper
If HIGH it makes “beep”, if LOW it doesn’t make noise

BEEPER -> Arduino PIN 9


## Encoder
Button   -> Arduino PIN 8
A switch -> Arduino PIN 2
B switch -> Arduino PIN 3

The two switches are closed or open at every step of the encoder with a time delay between the two switches, the first that switch determines the direction of the rotation (CW -> A-B or CCW -> B-A). 


'''
      ___5V__
      |    |__________ PIN 2   
      |_______________ PIN 3
      |    |
   A \    \  B
      |____|
        |
       \\\
'''

## Schematic
See the link for schematics: [Schematics](https://drive.google.com/open?id=0B7P0y6jUr96xZUoweGF4eUUxajA)
