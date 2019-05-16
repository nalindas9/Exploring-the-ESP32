#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>

// WiFi network info.
char ssid[] = "Enter WiFi SSID here";
char wifiPassword[] = "Enter WiFi password here";
int pin1 = 25;
int pin2 = 22;

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "Enter Cayenne username here";
char password[] = "Enter Cayenne password here";
char clientID[] = "Enter Cayenne client ID here";
unsigned long lastMillis = 0;


void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
   pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
}

void loop() {
  Cayenne.loop();
  bool motion1 = digitalRead(pin1);
  bool motion2= digitalRead(pin2);
  
  if(millis() - lastMillis > 1500) {
      lastMillis = millis();
    Serial.println(motion1);
    Cayenne.virtualWrite(0, motion1, "motion", "d");
    Serial.println(motion2);
    Cayenne.virtualWrite(1, motion2, "motion", "d");
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
//ss message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
