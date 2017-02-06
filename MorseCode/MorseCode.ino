
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
//#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
  #include <SoftwareSerial.h>
#endif

#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

    #define FACTORYRESET_ENABLE         1
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
    #define MODE_LED_BEHAVIOUR          "MODE"
    #define BLUEFRUIT_HWSERIAL_NAME          Serial1
    #define BLUEFRUIT_UART_MODE_PIN         -1   // Not used with FLORA
    #define BLUEFRUIT_UART_CTS_PIN          -1   // Not used with FLORA
    #define BLUEFRUIT_UART_RTS_PIN          -1   // Not used with FLORA
/*=========================================================================*/

// Create the bluefruit object, either software serial...uncomment these lines

Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

String message = "";

void setup(void)
{
  //while (!Serial);  // required for Flora & Micro
  //delay(500);

  Serial.begin(115200);
  pixels.begin(); // This initializes the NeoPixel library.
  
  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }

  if( FACTORYRESET_ENABLE )
  {
  
    if(!ble.factoryReset()){
      //error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  //Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while(! ble.isConnected()) {
      delay(500);
  }

  // LED Activity command is only supported from 0.6.6
  if( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }
}

void loop(void)
{
  // Check for incoming characters from Bluefruit
  ble.println("AT+BLEUARTRX");
  ble.readline();
  ble.waitForOK();
  if(strcmp(ble.buffer, "OK") == 0) {
    // no data
    return;
  }
  
  int i = 0;
  
  while(NULL != ble.buffer[i] && i < 10)
  {
    message = message + ble.buffer[i];
    i++;
  }
  
  Serial.println(message);
  Serial.println("hello");
  
  int k = 0;
  message.toLowerCase();
  
  Serial.println(message);
  
  while(k < message.length())
  {
    sendLetter(message.charAt(k));
    delay(500);
    k++;
  }

  message = "";
 
}

void sendLetter(char letter)
{
   if(letter == 'a')  morseA();
   else if (letter == 'b') morseB();
   else if (letter == 'c') morseC();
   else if (letter == 'd') morseD();
   else if (letter == 'e') morseE();
   else if (letter == 'f') morseF();
   else if (letter == 'g') morseG();
   else if (letter == 'h') morseH();
   else if (letter == 'i') morseI();
   else if (letter == 'j') morseJ();
   else if (letter == 'k') morseK();
   else if (letter == 'l') morseL();
   else if (letter == 'm') morseM();
   else if (letter == 'n') morseN();
   else if (letter == 'o') morseO();
   else if (letter == 'p') morseP();
   else if (letter == 'q') morseQ();
   else if (letter == 'r') morseR();
   else if (letter == 's') morseS();
   else if (letter == 't') morseT();
   else if (letter == 'u') morseU();
   else if (letter == 'v') morseV();
   else if (letter == 'w') morseW();
   else if (letter == 'x') morseX();
   else if (letter == 'y') morseY();
   else if (letter == 'z') morseZ();
}

void setPixelOnShort()
{
    setPixelOn();
    delay(200);
    setPixelOff();
    delay(500);
}

void setPixelOnLong()
{
    setPixelOn();
    delay(1000);
    setPixelOff();
    delay(500);
}

void setPixelOn()
{
    pixels.setPixelColor(0, pixels.Color(200,200,200));
    pixels.show(); // This sends the updated pixel color to the hardware.
    
}

void setPixelOff()
{
    pixels.setPixelColor(0, pixels.Color(0,0,0)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
 
}

void morseA()
{
  setPixelOnShort();
  setPixelOnLong();
}

void morseB()
{
  setPixelOnLong();
  setPixelOnShort();
  setPixelOnShort();
  setPixelOnShort();
}

void morseC()
{
  setPixelOnLong();
  setPixelOnShort();
  setPixelOnLong();
  setPixelOnShort();
}

void morseD()
{
  setPixelOnLong();
  setPixelOnShort();
  setPixelOnShort();
}

void morseE()
{
  setPixelOnShort();
}

void morseF()
{
  setPixelOnShort();
  setPixelOnShort();
  setPixelOnLong();
  setPixelOnShort();
}

void morseG()
{
  setPixelOnLong();
  setPixelOnLong();
  setPixelOnShort();
}

void morseH()
{
  setPixelOnShort();
  setPixelOnShort();
  setPixelOnShort();
  setPixelOnShort();
}

void morseI()
{
  setPixelOnShort();
  setPixelOnShort();
}

void morseJ()
{
  setPixelOnLong();
  setPixelOnShort();
  setPixelOnShort();
  setPixelOnShort();
}

void morseK()
{
  
  setPixelOnShort();
  setPixelOnLong();
  setPixelOnLong();
  setPixelOnLong();
}

void morseL()
{
  setPixelOnLong();
  setPixelOnShort();
  setPixelOnLong();
}

void morseM()
{
  setPixelOnLong();
  setPixelOnLong();
}

void morseN()
{
  setPixelOnLong();
  setPixelOnShort();
}

void morseO()
{
  setPixelOnLong();
  setPixelOnLong();
  setPixelOnLong();
}

void morseP()
{
  setPixelOnShort();
  setPixelOnLong();
  setPixelOnLong();
  setPixelOnShort();
}

void morseQ()
{
  setPixelOnLong();
  setPixelOnLong();
  setPixelOnShort();
  setPixelOnLong();
}
void morseR()
{
  setPixelOnLong();
  setPixelOnShort();
  setPixelOnShort();
  setPixelOnShort();
}
void morseS()
{
  setPixelOnShort();
  setPixelOnLong();
  setPixelOnShort();
}

void morseT()
{
  setPixelOnLong();
}

void morseU()
{
  setPixelOnShort();
  setPixelOnShort();
  setPixelOnLong();
}

void morseV()
{
  setPixelOnShort();
  setPixelOnShort();
  setPixelOnShort();
  setPixelOnLong();
}

void morseW()
{
  setPixelOnShort();
  setPixelOnLong();
  setPixelOnLong();
}

void morseX()
{
  setPixelOnLong();
  setPixelOnShort();
  setPixelOnShort();
  setPixelOnLong();
}

void morseY()
{
  setPixelOnLong();
  setPixelOnShort();
  setPixelOnLong();
  setPixelOnLong();
}

void morseZ()
{
  setPixelOnLong();
  setPixelOnLong();
  setPixelOnShort();
  setPixelOnShort();
}




