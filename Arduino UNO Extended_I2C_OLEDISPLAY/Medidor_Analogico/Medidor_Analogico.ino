// -----------------------------------------------------------------------------------------------------------------------------------
// Medidor_Analogico.ino sketch que simula un medidor analogico en una pantalla OLED I2C 0.96" de 128x64 con Arduino UNO Extended Rev3
// Se mide la entrada (A0) analogica cero a la cual se conecta un potenciometro de 100k.
// Visualiza una escala de cero a 1024, equivalente a cero a 5 voltios.
// Se debe instalar la libreria "OLED_I2C.zip" para que funcione este sketch
// Visita https://jorgechac.blogspot.com Venta de accesorios Arduino/Raspberry Pi Pico
// -----------------------------------------------------------------------------------------------------------------------------------

#include <OLED_I2C.h>              //libreria necesaria para el control de la pantala OLED
int pos=0;                         //posicion en X del medidor, cambiando este valor lo corremos a la derecha o la izquierda siendo 0 lo mas a la izquierda posible

//Ahora viene el medio circulo del medidor

float radio=50;                   // radio del circulo...cambiandolo el medidor quedara mas grande o mas chico
float xcentro=radio;              //  X del centro del circulo que sera el medidor
const float ycentro=60;           // Y del centro del circulo ... como es un medio circulo la coordenada Y se quedara lo mas abajo posible ya que solo se vera el medio circulo de arriba
float radiochico=2;               //radio del circulito chico donde se apoya la aguja del medidor

// Ahora la aguja del medidor...es un segmento de recta donde un vertice es fijo (el centro del circulo del medidor) y el otro varia

float xrecta;                    // X del otro extremo del segmento de recta el cual se calculara
float yrecta;                    // Y del otro extremo del segmento de recta el cual se calculara
float theta;                     // angulo que se movera la aguja del medidor segun el valor de la entrada analogica
const float pi=3.1415927;        // el numero pi para pasar angulos de grados a radianes
OLED  myOLED(SDA, SCL, 8);       // inicializamos la pantalla OLED
extern uint8_t SmallFont[];      // Selecciono el tamaño de fuente para los textos
extern uint8_t MediumNumbers[];  // Selecciono el tamaño de fuente para los numeros

void setup()
{
  myOLED.begin();                //inicializa el display OLED
  
  // Ahora damos un mensaje de inicio del programa
  
  myOLED.setFont(SmallFont);                    //seteo el tamaño de la fuente
  myOLED.print("MEDIDOR ANALOGICO", CENTER, 0); //imprime la frase entre comillas
  myOLED.update();                              // actualiza la pantalla
  delay(1000);
  myOLED.clrScr();                              // borra la pantalla
}

void loop () {
  float a=analogRead(0);                           // lee la entrada analogica 0
  theta=(a/2.84722-360)*pi/360;                    // el 2,84722 es para pasar valores de 0 a 1025 (lo que mide una entrada analogica) a grados y el resto de la ecuación convierte en radianes
  myOLED.drawCircle(xcentro+pos,ycentro,radio);    //Dibuja un circulo cuyo centro esta en las coordenadas x e y y su radio es r (x,y,r), este es el medidor
  myOLED.drawCircle(xcentro+pos,ycentro,46);
  myOLED.drawCircle(xcentro+pos,ycentro,42);
  myOLED.drawCircle(xcentro+pos,ycentro,38);
  myOLED.drawCircle(xcentro+pos,ycentro,radiochico); //Dibuja el circulito donde se apoya la aguja del medidor
  
  // ahora viene el segmento de recta que seria la aguja del medidor, un extremo es fijo (el centro del circulo) el otro varia segun:
  
  xrecta=radio*cos(theta)+xcentro;
  yrecta=radio*sin(theta)+ycentro;
  myOLED.drawLine(xcentro+pos,ycentro,xrecta+pos,yrecta); // dibuja una recta entre (X0,Y0) y (X1,Y1) seteando (X0,Y0,X1,Y1)
  
  // ahora las marcas de graduacion del medidor
  
  // graduacion 1
  myOLED.drawLine(xcentro+4*radio/5+pos,ycentro,xcentro+radio+pos,ycentro);
  // graduacion 2
  myOLED.drawLine(xcentro-4*radio/5+pos,ycentro,xcentro-radio+pos,ycentro);
  // graduacion 3
  myOLED.drawLine(xcentro+pos,ycentro-4*radio/5,xcentro+pos,ycentro-radio);  
  // graduacion 4
  myOLED.drawLine(radio*cos(pi/4)+(xcentro-63+pos),radio*sin(pi/4)+(ycentro-63),radio*cos(pi/4)+(xcentro-70+pos),radio*sin(pi/4)+(ycentro-70));  
  // graduacion 5
  myOLED.drawLine(radio*cos(pi/4)+(xcentro-7+pos),radio*sin(pi/4)+(ycentro-61),radio*cos(pi/4)+xcentro+pos,radio*sin(pi/4)+(ycentro-68));
  myOLED.setFont(SmallFont);     //seteo el tamaño de la fuente para el siguiente texto 
  myOLED.print("A0",115,20);     // imprime la frase que esta entre comillas (texto,x ,y)
  myOLED.print("512",41,2);      // imprime la frase que esta entre comillas 
  myOLED.print("1024",101 ,57);  // imprime la frase que esta entre comillas 
  myOLED.print("256",0,20);      // imprime la frase que esta entre comillas 
  myOLED.print("768",85,20);     // imprime la frase que esta entre comillas 
  myOLED.setFont(MediumNumbers); //seteo el tamaño de la fuente para los numeros
  myOLED.printNumI(a,RIGHT,0);   // imprime el valor de la entrada analogica
  myOLED.update();               //actualiza la pantalla
  delay(100);                    // mide datos cada 100 milisegundos
  myOLED.clrScr();               //borra la pantalla para reiniciar el loop
}
