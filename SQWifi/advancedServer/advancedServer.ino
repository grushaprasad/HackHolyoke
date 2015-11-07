#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define PIN_LED 2
#define PIN_BUZZER 15
#define PIN_BUTTON 0
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

void handleJSON() {
  // json string in the form of:
  // {"adc":xxx,"but":xxx}
  String json = "{\"adc\":";
  json += analogRead(A0);
  json += ",\"but\":";
  json += digitalRead(PIN_BUTTON);
  json += "}";
  server.send(200, "text/plain", json);
}

void setup(void){
  pixel.begin();
  pixel.show();

  Serial.begin(115200);
  
  pinMode(PIN_LIGHTSENSOR_ENABLE, OUTPUT);
  digitalWrite(PIN_LIGHTSENSOR_ENABLE, HIGH);

  pinMode(PIN_BUTTON, INPUT_PULLUP);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/ja", handleJSON);
  server.on("/cc", handleColorChange);
  
  server.begin();
}

void handleColorChange() {
  int r, g, b;  
  for(int i=0; i<server.args(); i++) {
    if (server.argName(i) == "r") {
      r = server.arg(i).toInt();
    } else if (server.argName(i) == "g") {
      g = server.arg(i).toInt();
    } else if (server.argName(i) == "b") {
      b = server.arg(i).toInt();
    }
  }
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();  
  server.send(200, "text/plain", "");
}

void loop(void){
  server.handleClient();
} 
