#include <SPI.h>
#include <MFRC522.h>
#include <HardwareSerial.h>
HardwareSerial SerialPort(2); // use UART2

// #include <WiFi.h>
// #include <HTTPClient.h>

// const char *ssid = "MAHAKAL";
// const char *password = "sateri456";

const char *serverUrl = "https://api.thingspeak.com/update?";
const char *apiKey = "K8CH7XH11OFPA1WG";


#include <Arduino.h>
#include "HX711.h"

// 1-HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 14;
const int LOADCELL_SCK_PIN = 4;

// 2-HX711 circuit wiring
const int _2LOADCELL_DOUT_PIN = 27;
const int _2LOADCELL_SCK_PIN = 13;

HX711 scale;    float reading;
// Calibration factor (replace with your calibration factor)
#define CALIBRATION_FACTOR 205.313

HX711 _2scale;  float _2reading;

// Calibration factor (replace with your calibration factor)
#define _2CALIBRATION_FACTOR 226.213



// Ultrasonic Sensor Pins
const int trigPin = 15;
const int echoPin = 2;

// RFID Pins
#define SS_PIN 5
#define RST_PIN 22

// Ultrasonic Sensor Constants
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

// Ultrasonic Sensor Variables
long duration;
float distanceInch;

float distanceCm;
String prevCardID = "";
String currentCardID = "";
float weight1;
float weight2;
float average;

String cardId1 = " 24 86 6c 04"; // white card
String cardId2 = " 9a 52 9d 80"; // blue tag

// RFID Object
MFRC522 rfid(SS_PIN, RST_PIN);

float readUltrasonicSensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
    
  duration = pulseIn(echoPin, HIGH);
  return duration * SOUND_SPEED / 2;
}

// void makeGetRequest() {
//   HTTPClient http;

//   String url = String(serverUrl) +
//                "api_key=" + apiKey +
//                "&field1=" + currentCardID +  // id
//                "&field2=" + average +        // weight Avg
//                "&field3=" + distanceCm ;     // height

//   Serial.println("Sending GET request to: " + url);

//   http.begin(url);

//   int httpCode = http.GET();
//   if (httpCode > 0) {
//     Serial.printf("HTTP response code: %d\n", httpCode);
//     String payload = http.getString();
//     Serial.println("Server response: " + payload);
//   } else {
//     Serial.printf("HTTP request failed, error: %s\n", http.errorToString(httpCode).c_str());
//   }

//   http.end();
// }

void uartsendData(String currentCardID, String average, String distanceCm)
{
  // Send the values over UART with commas as delimiters
  SerialPort.print(currentCardID);
  SerialPort.print(",");
  SerialPort.print(average);
  SerialPort.print(",");
  SerialPort.print(distanceCm);
  SerialPort.println();
}



void setup() {
  Serial.begin(115200); // Starts the serial communication
  SerialPort.begin(9600, SERIAL_8N1, 16, 17); 

  // // Connect to WiFi
  // WiFi.begin(ssid, password);
  // Serial.println("Connecting to WiFi...");
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println(".");
  // }
  // Serial.println("Connected to WiFi");
    
  // Ultrasonic Sensor Setup
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    
  randomSeed(analogRead(0)); // Initialize random number generator

  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(CALIBRATION_FACTOR); // Set the calibration factor
  scale.tare(); // Reset the scale to 0

  _2scale.begin(_2LOADCELL_DOUT_PIN, _2LOADCELL_SCK_PIN);
  _2scale.set_scale(_2CALIBRATION_FACTOR); // Set the calibration factor
  _2scale.tare(); // Reset the scale to 0


  // RFID Setup
  SPI.begin();rfid.PCD_Init();
  Serial.println("Cargo Sense - Project Started");
}

void loop() {
  // RFID Loop
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    currentCardID = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        currentCardID += String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        currentCardID += String(rfid.uid.uidByte[i], HEX);
    }

    // if (currentCardID != prevCardID) {
    if (currentCardID != "") {
      distanceCm = readUltrasonicSensor();
      Serial.print("RFID Card UID: ");Serial.println(currentCardID);

      if (cardId1 == currentCardID){Serial.print("-------------- cardId1:");currentCardID = 12; Serial.println(cardId1);}
      if (cardId2 == currentCardID){Serial.print("-------------- cardId2:");currentCardID = 23; Serial.println(cardId2);}

      Serial.print("Distance (cm): ");Serial.println(distanceCm);

      if (scale.wait_ready_timeout(200)) {
          reading = scale.get_units();
          Serial.print("1 - Weight: ");Serial.print(reading);Serial.println(" Gram");
      } 
      if (_2scale.wait_ready_timeout(200)) {
          _2reading = _2scale.get_units();
          Serial.print("2 - Weight: ");Serial.print(_2reading);Serial.println(" Gram");
      } 
      else {Serial.println("HX711 not found.");}

      weight1 = reading;
      weight2 = _2reading;
      
      // weight1 = 4.0 + random(0, 7001) / 1000.0;
      // weight2 = 4.0 + random(0, 7001) / 1000.0;
      Serial.println("weight1: " + String(weight1) + "weight2: " + String(weight2));

      average = (weight1 + weight2) / 2.0;
      Serial.println("average: " + String(average));


      // uartsendData(currentCardID, average, distanceCm);
      uartsendData(String(currentCardID), String(average), String(distanceCm));
      // Make GET request
      // makeGetRequest();

      prevCardID = currentCardID;
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();

    delay(1000); // Delay between readings
  }
}
