// -----------------------------------------------------------------------------------------------------------------------
// I2C_LCD_16x2.ino sketch para manejo basico de un modulo I2C LCD 2x16 con Arduino UNO Extended
// Se debe instalar la libreria "LiquidCrystal_I2C.zip" para que funcione este sketch
// Descarga gratis este sketch en https://create.arduino.cc/editor/jorgechac/1dc82806-7b66-4105-bdda-47176a28fb6c/preview
// Visita https://jorgechac.blogspot.com Venta de accesorios Arduino/Raspberry Pi Pico
// -----------------------------------------------------------------------------------------------------------------------

#include <LiquidCrystal_I2C.h>    // Libreria que controla el I2C
#include <Wire.h>                 // La libreria Wire viene incluida en el IDE de arduino

LiquidCrystal_I2C lcd(0x27,16,2); // dependiendo del fabricante del LCD, la direccion 0x27 puede cambiar, utilice el I2C_Scan primero por favor!

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" PROTOCOLO  I2C ");  // Mensaje a desplegar
  lcd.setCursor(0,1);
  lcd.print("Prueba LCD 16x2 "); // Mensaje 2 a desplegar
  delay(3000);                  // espera 3 segundos con el mensaje estatico 
}

void loop() { 
  for(int c=0;c<12;c++){
  lcd.scrollDisplayLeft();     // Movimiento a la Izquierda
  delay(400);
  }
  for(int c=0; c<12;c++){
  lcd.scrollDisplayRight();    // Movimiento a la Derecha 
  delay(400); 
  }
}
