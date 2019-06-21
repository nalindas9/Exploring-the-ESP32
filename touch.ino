int touch=15;
void setup()
{
Serial.begin(115200);
Serial.println("Touch sensor tutorial ESP32");
}

void loop()
{
Serial.println( touchRead(touch));
delay(1000);
}
