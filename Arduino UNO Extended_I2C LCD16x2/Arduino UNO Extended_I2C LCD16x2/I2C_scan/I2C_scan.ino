/*
 ---------------------------------------------------------------------------------------------------------------------------------------------------------
 I2C_Scan sketch para escanear buscando dispositivos I2C conectados, localizandolos y mandando las direcciones que encuentra al Monitor serie.
 El objeto contiene como variables el rango de direcciones para el escaneo Low_Address y High_Address. El objeto se inicializa a traves del método Init().
 Descarga gratis este sketch en https://create.arduino.cc/editor/jorgechac/eaad38ae-3d58-4617-b151-8ce6decc2924/preview
 Visita  https://jorgechac.blogspot.com venta de accesorios Arduino y Raspberry Pi Pico.
 ---------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#include <Wire.h>
 
void setup()
{
  Wire.begin(); 
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
}
 
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    
    // I2c_scanner utiliza el valor de retorno de la Write.endTransmisstion para ver si un dispositivo reconoció la dirección.
    
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("Dispositivo I2C encontrado en la direccion hexadecimal 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknow error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);                                // wait 5 seconds for next scan
}
