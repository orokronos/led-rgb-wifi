#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <WiFi.h>
#include <analogWrite.h>
WiFiClient wiFiClient;
Adafruit_MQTT_Client mqttClient(&wiFiClient, "192.168.1.103", 1883);
Adafruit_MQTT_Subscribe redSubscriber(&mqttClient, "/red");
Adafruit_MQTT_Subscribe blueSubscriber(&mqttClient, "/blue");
Adafruit_MQTT_Subscribe greenSubscriber(&mqttClient, "/green");

void redCallback(double x) {
analogWrite(12,x);
}
void blueCallback(double x) {
analogWrite(27,x);
}
void greenCallback(double x) {
analogWrite(14,x);


}
void setup() {
 // put your setup code here, to run once:
 Serial.begin(115200);
 WiFi.begin("createch", "createch");
 delay(5000);  
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());  redSubscriber.setCallback(redCallback);
 mqttClient.subscribe(&redSubscriber);
 blueSubscriber.setCallback(blueCallback);
 mqttClient.subscribe(&blueSubscriber);
 greenSubscriber.setCallback(greenCallback);
 mqttClient.subscribe(&greenSubscriber);
 }
 
 void loop() {
 if (mqttClient.connected()) {
   mqttClient.processPackets(10000);
   mqttClient.ping();
 } else {
   mqttClient.disconnect();
   mqttClient.connect();
 }
 }
