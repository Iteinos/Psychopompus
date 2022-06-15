#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define GEIGER 12
LiquidCrystal_I2C lcd(0x3F, 8, 2); //try 0x27 if it doesnt work
long refreshTimer = 0;
long cpmTimer = 0;
int dernr = -1;
int gammaTrigger = 0;
bool updateReading = 0;
int count = 0; // total
int cps = 0;
int cpm[61]; // buffer
int countpermin = -1;
int trigger_elapsed = -1;
long timer_triggered = 0;
byte radiationSymbol[] = {
  0x08,
  0x05,
  0x03,
  0x07,
  0x10,
  0x0A,
  0x06,
  0x0E
};

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
const int esp = 0;
#endif
#if defined(ESP8266)
const int esp = 1;
#include <ESP8266WiFi.h>
#endif
const float conversion_index = 0.00468; //0.00468 for SI3BG, 0.0065 for M4011

/* Reference:
   For the conversion from Counts per Minute to microSieverts per Hour,
   Confer https://www.gqelectronicsllc.com/forum/topic.asp?TOPIC_ID=5357#:~:text=The%20estimated%20sensitivity%20of%20the%20SI-3BG%20tube%20is,sensitivity%20in%20the%20GMC-500%2B%20firmware%20%281%2F0.194%3D5.1546%20CPM%2F%20%28uSv%2Fh%29%29.
*/
void setup()
{
  //WiFi.forceSleepBegin(); //powersaving
  for (int i = 0; i < 61; i++)
  {
    cpm[i] = 0;
  }
  pinMode(GEIGER, INPUT);
  lcd.init();
  lcd.createChar(0, radiationSymbol);
  lcd.home();
  lcd.write(0);
  delay(1000);
  lcd.clear();
  Serial.begin(115200);
  Serial.println("Debug console");
}

void alertDisplay()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GM_OBSRV");
  lcd.setCursor(2, 0);
  lcd.write(0);
  lcd.setCursor(0, 1);
  lcd.print("CONFIRMD");
}

float uSvConvert(int rawcpm)
{
  if (rawcpm >= 0) {
    float result = conversion_index * rawcpm;
    return result;
  } else {
    //Calibrating measurements... Wait untill 1 minute runtime
    return (0);
  }
}

void gammaDetect()
{
  gammaTrigger = digitalRead(GEIGER);
  if (!gammaTrigger)
  {
    updateReading = 0;
  }
  if (gammaTrigger && !updateReading)
  {
    Serial.println("Detection");
    updateReading = 1;
    count++;
    cps++;
    timer_triggered = millis();
    alertDisplay();
  }
  countpermin = 0;
  for (int i = 0; i < 61; i++)
  {
    countpermin += cpm[i];
  }

  if (millis() - cpmTimer >= 1000)
  {
    dernr = cps;
    cps = 0;
    cpmTimer = millis();
  }
  int sec_d_min = (millis() / 1000) % 60;
  cpm[sec_d_min] = dernr;
  trigger_elapsed = ((millis() - timer_triggered) / 1000);
}

void loop()
{
  gammaDetect();
  if (millis() - refreshTimer > 1000)
  {
    refreshTimer = millis();
    if (trigger_elapsed >= 1)
    {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("TTL ");
      lcd.print(count);
      lcd.setCursor(0, 0);
      lcd.print("CPM ");
      lcd.print(countpermin);
      Serial.print("TOTAL ");
      Serial.print(count);
      Serial.print(",     ELAPSED(s) ");
      Serial.print(trigger_elapsed);
      Serial.print(",     CPM ");
      Serial.print(countpermin);
      Serial.print(",     USV/H ");
      Serial.println(uSvConvert(countpermin));
    }
    else
    {
      alertDisplay();
    }
  }
}
