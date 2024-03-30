

//////////////////////
//Aqui comienza la config, setear SSID y Clave

#ifndef STASSID
#define STASSID "Ltec"
#define STAPSK  "elgato123"
#endif


/////////////pinIO/////////// ESTABLECER LOS PROPIOS
//
int _ext = 5;        //  Extractor
int _SDA = 22;
int _SCL = 21;
int _luz = 18;            //  Luz           
int _hig = 26;            //  Higrometro    

int _ven = 19;             //  Ventilador    

//Control del Faso v0.98 ESP32

//Wire Para i2C, EEPROM y RTC
#include <Wire.h>
#include <AT24CX.h>   //EEPROM

//RTC esta libreria es para el DS3231, usar la propia
#include <DS3231.h>

// Arduino On The AIR para subir proyectos directamente por WiFii
#include <ArduinoOTA.h>

#include <stdio.h>


//Librerias del sensor DHT
#include "DHT.h"
#include <Adafruit_Sensor.h>

#include <Arduino.h>

//Librerias para Wifii y Webserver

#include <WebServer.h>


//#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
////Libreria DIMMER (opcional) POR RBDDimmer
//#include <RBDdimmer.h>//

//#include <ThingSpeak.h>






#define USE_SERIAL  Serial
// Inicializamos Dimmer y Libreria DHT, modificar con DHT11, DHT22 o el modelo que sea

//dimmerLamp dimmer(outputPin, zerocross); //initialase port for dimmer for ESP8266, ESP32, Arduino due boards

//LIBRERIA DHT, cambiar segun modelo
DHT dht(_hig, DHT22);
WiFiClient cliente;
////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Declaracion de variables////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

bool luzprendida, ventiladorprendido, ISFAN, isExt, modetemp;

unsigned long milsto = 0;
unsigned long milsto2 = 0;

unsigned long milismenu = 0;

int timeout = 5000;

int Ciclo = 12;             //Ciclo de luz en horas
int hora;
int fan = 20;
int offset = 0;     // Offset de horario
bool invert = true;            //para detectar +12hrs ciclo
String Icono =  "asd";

int ramp1 = 50;             // % de dimerizacion de extractor de entrada
float ramp2 = 26;           // Temperatura de disparo de extractor
int ramp3 = 100;            // % de dimerizacion de extractor maximo, no se guarda en la memoria
float ramp4 = 27;           // Temperatura de extractor a maxima potencia
bool engagestorememory = false;
bool dostore = false;
bool started = true;
bool extON;
int minimoextractor = 100;
int pwr = 0;                // Variable de dimmerLamp



float extPWM = 0;
String pwrtmp = "";           // Conversor ajustador de dimmerlamp (aveces el 0 es 30)
//String pwrtmp;
int Humedadmaxima = 75;
int pwroffset = 0;          // Valor del 0 del dimmer
int dimstate = 0;               // estado del extractor


// Variables de control de EEPROM
int CO, Mmodetemp, MDtemp, MHumedadmaxima, MemoriFAN;
float _offset = 0;
byte _invert, _ISFAN, _modetemp, _Ciclo, _Humedadmaxima;
//////////////RTC///////////////////

DS3231 RTC;
AT24C32 EepromRTC;
bool h12Flag;
bool pmFlag = true;
byte segundo, minuto, horaSis, minuti, hori;

//byte alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits, alarmHour2,alarmMinute2;
float systemp = 0;


/////////////////webserverDHT///////////////////
int MTEMP1 = 9;
int MTEMP2 = 0;
int leeMemoria = 0;
int wifitimeout = 0;        //
unsigned long previousMillisdht = 0;    // will store last time DHT was updated
unsigned long currentMillisdht = 0;
const long interval = 5000;
unsigned long ext_timer = 0;
float t = 0.0;
int h = 0;
//float s = 0.0;
///////////////////////////////////////////////

const int output = 2;


//////////DATALOGER//////////

float DLAval[] = {25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25};
float DLBval[] = {28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28};
float DLCval[] = {25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25};

const int DLTA = 10000;
const int DLTB = 3600000;
unsigned long DLA = 0;
int DLB = 0;
float DLMax = 0;
float DLMin = 0;
/////////////////
String myStatus;
