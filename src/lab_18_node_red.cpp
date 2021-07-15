/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/Labs/lab_18_node_red/src/lab_18_node_red.ino"
void callback(char *topic, byte *payload, unsigned int length);
void setup();
void loop();
#line 1 "d:/Labs/lab_18_node_red/src/lab_18_node_red.ino"
SYSTEM_THREAD(ENABLED);
#include "MQTT.h"
#include "oled-wing-adafruit.h"
#include "blynk.h"


OledWingAdafruit display;
WidgetMap myMap(V1);

String topic1 = "node1";
String topic2 = "node2";
String topic3 = "node3";
bool valid = false;


double longitude = 0.0;
double latitude = 0.0;
MQTT client("lab.thewcl.com", 1883, callback);

void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String s = p;
  double value = s.toFloat();
  Serial.printf("%s",p);
  Serial.println();
  Serial.println(value);

  if ((String) topic == "node2")
  {
    longitude = value;
  }
  if ((String) topic == "node3")
  {
    latitude = value;
  }

}


void setup()
{ 
  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.display();
  Serial.begin(9600);

  client.connect(System.deviceID());
  if (client.isConnected())
  {
    client.subscribe("node2");
    client.publish("node1","hello world");
  }

  Blynk.begin("DISy_9aRsQHnyt8mtvZXh09rT-tdy72R", IPAddress(167, 172, 234, 162), 9090);
  
}

void loop()
{
  Blynk.run();
  display.loop();
  client.connect(System.deviceID());
  
  if (client.isConnected())
  {
    client.subscribe("node2");
    client.subscribe("node3");
    client.publish("node1","where is the ISS?");
    client.loop();

  }
  else
  {
    client.connect(System.deviceID());
  }

  //update OLED
  String output = "Long: " + (String) longitude;
  output += "\nLatitude: " + (String) latitude;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(output);
  display.display();

  //sending the map data to our phone. 
  myMap.location(1, latitude, longitude, "value");

  delay(10000);
}