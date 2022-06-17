# Psychopompus
Geiger-mueller Counter based on Arduino/ESP8266

**Components:**

  MICROCONTROLLER: Prefered Arduino or ESP8266.

  GEIGER-MUELLER MODULE w/ 400V power supply: Only included parameters for SI3BG. 

  SCREEN: 1602 LCD display w/ I2C module, 0802 & 2004 also works.

*Caveat: In the case you are not using a module designed for arduino, connect the input signal from geiger tube to a voltage-divider before feeding it to your chips.
Ignore this warning if you know what you are doing.*

**Connection schematics:**
This is the minimal circuit setup if you are using available modules.
![psyp](https://user-images.githubusercontent.com/56753892/174328762-9a3f501c-7d19-4d1e-8f35-57b50257870b.jpg)

**Screen layout description:**
If you didn't tweak my code, this is what would appear on screen.
![psyp2d](https://user-images.githubusercontent.com/56753892/174340073-daeaf4d0-1874-43e3-a61e-d637d7b00c09.jpg)
