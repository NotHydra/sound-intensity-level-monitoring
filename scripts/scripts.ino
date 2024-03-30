#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int numMeasure = 128;

int soundPin = A0;

long sum = 0;
long level = 0;

int soundLow = 40;
int soundmedium = 400;

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(soundPin, INPUT);
}

void loop()
{
  for (int i = 0; i < numMeasure; i++)
  {
    sum = sum + analogRead(soundPin);
  }

  level = (sum / numMeasure) - 13;

  lcd.setCursor(0, 1);
  lcd.print("Decibel=");
  lcd.print(level);
  lcd.print("db");

  lcd.setCursor(0, 0);
  if (level < soundLow)
  {
    lcd.print("Level=Low");
  }
  else if (level > soundLow && level < soundmedium)
  {
    lcd.print("Level=Medium");
  }
  else if (level > soundmedium)
  {
    lcd.print("Level=High");
  }

  delay(500);

  sum = 0;
  lcd.clear();
}