#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>
#include <WiFi.h>

// WiFi network info.
char ssid[] = "Enter your Wifi SSID";
char wifiPassword[] = "Enter your Wifi password";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "Enter Cayenne username here";
char password[] = "Enter Cayenne password here";
char clientID[] = "Enter Cayenne client ID here";
unsigned long lastMillis = 0;
int touch = 15;
int led = 5;
int sense;
int state;
String button_state;

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(led, OUTPUT);
}

void loop() {
  Cayenne.loop();
  long rssi = WiFi.RSSI();
  Serial.println("RSSI:");
  Serial.println(rssi);
  sense = touchRead(touch);
  
  if(millis() - lastMillis > 1500) {
      lastMillis = millis();
      if(sense < 10)
      {
      state = 1;
      Serial.println(state);
      Cayenne.virtualWrite(0, state, "digital_sensor", "d");
      }
      else
     {
       state = 0;
       Serial.println(0);
       Cayenne.virtualWrite(0, state, "digital_sensor", "d");
     }

     Cayenne.virtualWrite(2, rssi, "rssi", "dbm");
   }
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  //Cayenne.virtualWrite(0, millis());
  // Some examples of other functions you can use to send data.
  //Cayenne.celsiusWrite(1, 22.0);
  //Cayenne.luxWrite(2, 700);
  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
 //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}

CAYENNE_IN(1)
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  button_state = getValue.asString();
  if (button_state == "1"){
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
    }
 //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
