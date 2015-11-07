#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define PIN_LED 2
#define PIN_LIGHTSENSOR_ENABLE 16

// ====== PLEASE CHANGE THE SSID TO A UNIQUE NAME ======
const char ssid[] = "SQWiFi-xx"; // this is the custom ssid

const char password[] = "";     // this is the WiFi password (optional)
ESP8266WebServer server(80);

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void handleRoot() {
  server.send(200, "text/html", "<h1>Hello from SquareWear Wifi!</h1>");
}

void handleRead() {
  String message = "<h1>light sensor value: ";
  message += analogRead(A0);
  message += "</h1>";
  server.send(200, "text/html", message);
}

void handleLED() {
  int r = random(0, 64);
  int g = random(0, 64);
  int b = random(0, 64);
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
  
  server.send(200, "text/html", "<h1>random LED color</h1>");
}

void setup(void){
  pixel.begin();
  pixel.show();
  
  pinMode(PIN_LIGHTSENSOR_ENABLE, OUTPUT);
  digitalWrite(PIN_LIGHTSENSOR_ENABLE, HIGH);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/read", handleRead);
  server.on("/led", handleLED);
  
  server.begin();
}
 
void loop(void){
  server.handleClient();
} 
