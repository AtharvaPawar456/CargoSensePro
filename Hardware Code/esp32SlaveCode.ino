#include <HardwareSerial.h>

#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "MAHAKAL";
const char *password = "sateri456";

const char *serverUrl = "https://api.thingspeak.com/update?";
const char *apiKey = "K8CH7XH11OFPA1WG";

int currentCardID = 0;
int average = 0;
int distanceCm = 0;

HardwareSerial SerialPort(2); // use UART2

int LED = 15;

void makeGetRequest() {
  HTTPClient http;

  String url = String(serverUrl) +
               "api_key=" + apiKey +
               "&field1=" + currentCardID +  // id
               "&field2=" + average +        // weight Avg
               "&field3=" + distanceCm ;     // height

  Serial.println("Sending GET request to: " + url);

  http.begin(url);

  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("HTTP response code: %d\n", httpCode);
    String payload = http.getString();
    Serial.println("Server response: " + payload);
  } else {
    Serial.printf("HTTP request failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}


void setup()
{
  SerialPort.begin(9600, SERIAL_8N1, 16, 17);
  pinMode(LED, OUTPUT);
  Serial.begin(115200); // Starts the serial communication

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println("Connected to WiFi");
   

  Serial.println("Uart started");

}

void loop()
{
  if (SerialPort.available())
  {
    String message = SerialPort.readStringUntil('\n');
    int commaIndex1 = message.indexOf(',');
    int commaIndex2 = message.lastIndexOf(',');
    
    if (commaIndex1 != -1 && commaIndex2 != -1) {
      int val1 = message.substring(0, commaIndex1).toInt();
      int val2 = message.substring(commaIndex1 + 1, commaIndex2).toInt();
      int val3 = message.substring(commaIndex2 + 1).toInt();
      
      // Serial.print(" val1: ");Serial.print(val1);
      // Serial.print(" val2: ");Serial.print(val2);
      // Serial.print(" val3: ");Serial.println(val3);
      
      currentCardID = val1;
      average = val2;
      distanceCm = val3;

      Serial.print("currentCardID: ");Serial.print(currentCardID);
      Serial.print(" average: ");Serial.print(average);
      Serial.print(" distanceCm: ");Serial.println(distanceCm);
      Serial.println("------------");

      makeGetRequest();


    }
  }
}
