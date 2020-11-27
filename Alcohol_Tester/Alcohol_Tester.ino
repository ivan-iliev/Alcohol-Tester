/******************************
        MADE BY IVAN ILIEV
         FOR National IT Comp
              2020
   email:mr.i.iliev@gmail.com
        GitHub:ivan-iliev
 ******************************/


#include <LiquidCrystal.h>

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "FirebaseESP8266.h"


#define FIREBASE_HOST "nodemcu-915c6.firebaseio.com"
#define FIREBASE_AUTH "6Q0Y2gTSJswpeuBoJUQK0yOLsPu2Lj3UzcWSl0Dn"
#define WIFI_SSID "Wi-Fi_IoT"                                          
#define WIFI_PASSWORD "qwertyui"                                        



IPAddress ip;
const int AOUTpin = 0;
int value;
int Contrast = 100;
LiquidCrystal lcd(04, 00, 02, 14, 12, 13);
float sensor_volt;
float RS_gas;
float R0;
float ratio;
float BAC;
int R2 = 2000;
const int buttonPin = 16;
int ledState = 0;
int btn_State = 0;
float maxPromil = 0;
FirebaseData firebaseData;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

String toString(const IPAddress& address) {
  return String() + address[0] + "." + address[1] + "." + address[2] + "." + address[3];
}



void updateDatabase()
{



  String ipString = toString(ip);
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  firebaseData.setBSSLBufferSize(1024, 1024);

  
  firebaseData.setResponseSize(1024);

  String wifiMacString = WiFi.macAddress();
  String path = "/" + wifiMacString;
  timeClient.update();
  timeClient.setTimeOffset(0);

  String jsonStr = "";

  FirebaseJson json1;

  FirebaseJsonData jsonObj;
  long timeStamp = timeClient.getEpochTime();
  json1.set("/Promiles", BAC * 0.0001);
  json1.set("/IP", ipString);
  json1.set("/Timestamp", (String)timeStamp);

  Serial.println("------------------------------------");
  Serial.println("JSON Data");
  json1.toString(jsonStr, true);
  Serial.println(jsonStr);
  Serial.println("------------------------------------");

  Serial.println("------------------------------------");
  Serial.println("Set JSON test...");

  if (Firebase.push(firebaseData, path, json1))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.print("VALUE: ");

    Serial.println("------------------------------------");
    Serial.println();

    maxPromil = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Uploaded");
    lcd.setCursor(0, 1);
    lcd.print("Result.");

  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();

    maxPromil = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connecton");
    lcd.setCursor(0, 1);
    lcd.print("Error.");


  }

}







void setup() {
  timeClient.begin();
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  ip = WiFi.localIP();


  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println();

  pinMode(buttonPin, INPUT);
  analogWrite(5, Contrast);
  lcd.begin(16, 2);
}

void loop() {

  timeClient.update();

  value = analogRead(AOUTpin);
  sensor_volt = (float)value / 1024 * 5.0;
  RS_gas = ((5.0 * R2) / sensor_volt) - R2;
  
  R0 = 45000;
  ratio = RS_gas / R0; 
  double x = 0.4 * ratio;
  BAC = pow(x, -1.431);f
  float finalValue = BAC * 0.001;
  ledState = digitalRead(LED_BUILTIN);
  btn_State = digitalRead(buttonPin);


  if (btn_State == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reading Data.");
    if (finalValue > maxPromil) {
      maxPromil = finalValue;
    }

  } else if (btn_State == LOW && maxPromil != 0) {
    Serial.println(maxPromil);
    if (maxPromil <= 0.1 && maxPromil >= 0.01 )
    {

      
      lcd.setCursor(0, 0);
      lcd.print(maxPromil);
      lcd.print(" g/DL");

      lcd.setCursor(0, 1);
      lcd.print("Low Level of promiles.");
    }
    if (maxPromil >= 0.1 && maxPromil <= 0.3)
    {


      lcd.setCursor(0, 0);
      lcd.print(maxPromil);
      lcd.print(" g/DL");

      lcd.setCursor(0, 1);
      lcd.print("Medium Level of promiles.");
    }
    if (maxPromil > 0.3) {

      lcd.setCursor(0, 0);
      lcd.print(maxPromil);
      lcd.print(" g/DL");

      lcd.setCursor(0, 1);
      lcd.print("High Level of promiles.");
    }

    updateDatabase();
  }


}
