// ----------------------------------------------------------------------------
// LCD Custom Character Generator
// Support character lcd and create code for Arduino
// Interfacing  I2C
// Data Type Hex
// Fuente: https://maxpromer.github.io/LCD-Character-Creator/
// Visita https://jorgechac.blogspot.com Venta de accesorios Arduino/Raspberry
// ----------------------------------------------------------------------------

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti

LiquidCrystal_I2C lcd(0x3F, 16, 2);

byte customChar[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

void setup() {
  lcd.begin();
  lcd.createChar(0, customChar);
  lcd.home();
  lcd.write(0);
}

void loop() { }
