#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int numMeasure = 128;

int soundPin = A0;

int ledRedPin = 9;
int ledYellowPin = 10;
int ledGreenPin = 11;

long sum = 0;
long level = 0;

int soundLow = 125;
int soundmedium = 350;

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(soundPin, INPUT);

  pinMode(ledRedPin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
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

    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledYellowPin, LOW);
    digitalWrite(ledGreenPin, HIGH);
  }
  else if (level > soundLow && level < soundmedium)
  {
    lcd.print("Level=Medium");

    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledYellowPin, HIGH);
    digitalWrite(ledGreenPin, LOW);
  }
  else if (level > soundmedium)
  {
    lcd.print("Level=High");

    digitalWrite(ledRedPin, HIGH);
    digitalWrite(ledYellowPin, LOW);
    digitalWrite(ledGreenPin, LOW);
  }

  delay(100);

  sum = 0;
  lcd.clear();
}