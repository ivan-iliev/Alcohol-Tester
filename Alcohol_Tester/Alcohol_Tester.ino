
/******************************
        MADE BY IVAN ILIEV
         FOR National IT Comp
              2020
   email:mr.i.iliev@gmail.com
        GitHub:ivan-iliev
 ******************************/

//Including the Firebase header so we can send data from the MQ3 sensor
#include "FirebaseESP8266.h"
//Includding the Wi-Fi header for the node-mcu board ,so that we can conect to Wi-Fi
#include <ESP8266WiFi.h>
//Including the header LCD display header ,so we can display the values from the sensor
#include <LiquidCrystal.h>
//Defining the firebase db and the wi-fi network
#define FIREBASE_HOST "nodemcu-915c6.firebaseio.com"
#define FIREBASE_AUTH "6Q0Y2gTSJswpeuBoJUQK0yOLsPu2Lj3UzcWSl0Dn"
#define WIFI_SSID "Wi-Fi_IoT"                                          //Wi-Fi Name
#define WIFI_PASSWORD "qwertyui"                                        //Wi-Fi Pass

//setting the analog pin for the sensor , the path for the db and the variable that will hold the value of the sensor
const int AOUTpin = 13;
String path = "/Values";
int value;

//declaring a variable for the data that we are sending and making a func that will print our data
FirebaseData firebaseData;
void printResult(FirebaseData & data);
//Setting the contrast and the pins for our LCD display
int Contrast = 10;
LiquidCrystal lcd(5, 4, 0, 2, 14, 12);

void setup() {
  //Setting the bauds that our serial monitor will print on
  Serial.begin(19200);

  //Setting the contrast and the number of collumns and rows on  the display
  analogWrite(16, Contrast);
  lcd.begin(16, 2);

  //Conecting to the Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //Setting up the FireBase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

//function for printing the data that we get from the server

void printResult(FirebaseData &data)
{


  Serial.println(data.intData());

}

void loop()
{
  //Getting the value from the sensor
  value = analogRead(AOUTpin);

  //Checking if the value of the sensor is in the borders
  if (value < 200)
  {
    //showing the message and the value on the display
    lcd.setCursor(0, 0);
    lcd.print(value);

    lcd.setCursor(0, 1);
    lcd.print("You are sober:) ");

    //delay so we can send only one value to the server
    delay(9000);

    //Pushing the data to the db and printing passed if we have send the date and failed if we havent
    if (Firebase.pushInt(firebaseData, path + "/Sober/Value", value))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }



  }
  if (value >= 200 && value < 280)
  {


    lcd.setCursor(0, 0);
    lcd.print(value);

    lcd.setCursor(0, 1);
    lcd.print("Alcohol detected!           ");


    delay(9000);
    if (Firebase.pushInt(firebaseData, path + "/Low/Value", value))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }


  }
  if (value >= 280 && value < 350)
  {

    lcd.setCursor(0, 0);
    lcd.print(value);

    lcd.setCursor(0, 1);
    lcd.print("Medium level                      ");

    delay(9000);
    if (Firebase.pushInt(firebaseData, path + "/Medium/Value", value))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }

  }
  if (value >= 350 && value < 450)
  {
    lcd.setCursor(0, 0);
    lcd.print(value);

    lcd.setCursor(0, 1);
    lcd.print("Serious Booze!    ");


    delay(9000);
    if (Firebase.pushInt(firebaseData, path + "/High/Value", value))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }

  }
  if (value > 450)
  {

    lcd.setCursor(0, 0);
    lcd.print(value);

    lcd.setCursor(0, 1);
    lcd.print("You are drunk!       ");

    delay(9000);
    if (Firebase.pushInt(firebaseData, path + "/Drunk/Value", value))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }

    lcd.setCursor(0, 0);
    lcd.print(value);

    lcd.setCursor(0, 1);
    lcd.print("You are drunk!");


    Serial.println("You are drunk!");
  }

  //putting delay of 500 miliseconds so that there is a space between each data that we send to the db
  delay (500);
}
