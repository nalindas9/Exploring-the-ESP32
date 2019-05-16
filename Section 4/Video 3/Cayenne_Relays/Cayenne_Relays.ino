#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>

// WiFi network info.
char ssid[] = "Enter WiFI SSID here";
char wifiPassword[] = "Enter WiFI password here";
int relayPin1 = 23;
int relayPin2 = 19;
String state1;
String state2;

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "Enter your Cayenne username here";
char password[] = "Enter your Cayenne password here";
char clientID[] = "Enter your Cayenne Client ID here";
unsigned long lastMillis = 0;


void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
}

void loop() {
  Cayenne.loop();
  
  if(millis() - lastMillis > 1500) {
      lastMillis = millis();
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

CAYENNE_IN(2)
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
//ss message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
state1 =  getValue.asString();

if(state1 == "1")
{
  digitalWrite(relayPin1, LOW);
  }
else
{
  digitalWrite(relayPin1, HIGH);
  }
}

CAYENNE_IN(3)
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
//ss message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");

state2 =  getValue.asString();

if(state2 == "1")
{
  digitalWrite(relayPin2, LOW);
  }
else
{
  digitalWrite(relayPin2, HIGH);
  }
}
