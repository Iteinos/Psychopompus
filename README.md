# Psychopompus
Geiger-mueller Counter based on Arduino/ESP8266

**Components:**

  MICROCONTROLLER: Prefered Arduino or ESP8266.

  GEIGER-MUELLER MODULE w/ 400V power supply: Only included parameters for SI3BG. 

  SCREEN: 1602 LCD display w/ I2C module, 0802 & 2004 also works.

*Caveat: In the case you are not using a module designed for arduino, connect the input signal from geiger tube to a voltage-divider before feeding it to your chips.
Ignore this warning if you know what you are doing.*

**Connection schematics & Screen layout description:**
1. This is the minimal circuit setup if you are using available modules.

2. If you didn't tweak my code, this is what would appear on screen.

![psypinstr](https://user-images.githubusercontent.com/56753892/174457381-e9d3a523-cb67-4b9f-93d2-a46712cf4147.jpg)
