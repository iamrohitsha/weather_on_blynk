#define BLYNK_TEMPLATE_ID "TMPL3A5G0q7kO"
#define BLYNK_TEMPLATE_NAME "weather"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Blynk authentication token
char auth[] = "fqlTo3uJv0eAGHje7y5Mw4rMWPWdh16l"; // Replace with your Blynk auth token

// WiFi credentials
char ssid[] = "OPPO A77s";  // Replace with your WiFi SSID
char pass[] = "k6euqgyx";  // Replace with your WiFi password

// DHT sensor setup
#define DHTPIN D5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensorData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V0, t);
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");
}

void setup() {
  Serial.begin(9600);
  delay(100);
  
  Serial.println("Starting...");
  WiFi.begin(ssid, pass);
  Serial.println("Connecting to WiFi...");
  
//  int timeout = 30;
//  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
//    delay(1000);
//    Serial.print(".");
//    timeout--;
//  }
  
//  if (WiFi.status() == WL_CONNECTED) {
//    Serial.println("\nConnected to WiFi");
    Blynk.config(auth);
//    if (Blynk.connect()) {
//      Serial.println("Connected to Blynk server");
//    } else {
//      Serial.println("Failed to connect to Blynk server");
//    }
//  } else {
//    Serial.println("\nFailed to connect to WiFi");
//    return;
//  }

  dht.begin();
  Serial.println("DHT sensor initialized.");

  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
