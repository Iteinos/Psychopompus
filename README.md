# Psychopompus 渡靈
Geiger-mueller Counter based on Arduino/ESP8266
基於Arduino/樂鑫ESP8266的蓋格穆勒計數器

Components:

MICROCONTROLLER: Prefered Arduino or ESP8266.

GEIGER-MUELLER MODULE w/ 400V power supply: Only included parameters for SI3BG. 

SCREEN: 1602 LCD display w/ I2C module, 0802 & 2004 also works.

Caveat: In the case you are not using a module designed for arduino, connect the input signal from geiger tube to a voltage-divider before feeding it to your chips.
Ignore this warning if you know what you are doing.
