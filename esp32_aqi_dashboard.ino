#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "wifi_name";
const char* password = "wifi_password";

// Pins
#define MQ2_PIN 34   // MQ2 connected to GPIO34
#define MQ135_PIN 35 // MQ135 connected to GPIO35 (not used for now)

// Web server
WebServer server(80);

// Calibration factor (from your test: 946 raw = AQI 112)
const float MQ2_FACTOR = 0.118;  

// AQI level function
String getAQIIndex(float aqi) {
  if (aqi <= 50) return "Good";
  else if (aqi <= 100) return "Moderate";
  else if (aqi <= 150) return "Unhealthy (Sensitive)";
  else if (aqi <= 200) return "Unhealthy";
  else if (aqi <= 300) return "Very Unhealthy";
  else return "Hazardous";
}

// Handle webpage
void handleRoot() {
  int mq2 = analogRead(MQ2_PIN);
  // Ignore MQ135 for now since it's stuck at 4095

  float aqi = mq2 * MQ2_FACTOR;

  if (aqi < 0) aqi = 0;
  if (aqi > 500) aqi = 500;  

  String aqiStatus = getAQIIndex(aqi);

  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>ESP32 AQI Dashboard</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { 
        background-color: #0d1117; 
        color: #e6edf3; 
        font-family: Arial, sans-serif; 
        text-align: center; 
        margin: 0; padding: 0; 
      }
      h1 { color: #39ff14; margin-top: 20px; }
      .card {
        background: #161b22; 
        padding: 30px; 
        border-radius: 20px; 
        box-shadow: 0 0 20px #0ef; 
        display: inline-block; 
        margin-top: 40px;
      }
      .aqi-value {
        font-size: 60px; 
        font-weight: bold; 
        margin: 10px 0; 
        color: #58a6ff;
      }
      .status {
        font-size: 24px; 
        font-weight: bold; 
        margin-top: 10px;
        color: #ff7b72;
      }
    </style>
  </head>
  <body>
    <h1>ESP32 Air Quality Monitor</h1>
    <div class="card">
      <div class="aqi-value">)rawliteral" + String((int)aqi) + R"rawliteral(</div>
      <div class="status">)rawliteral" + aqiStatus + R"rawliteral(</div>
    </div>
    <script>
      setTimeout(() => { location.reload(); }, 5000); // Refresh every 5s
    </script>
  </body>
  </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.println("ESP32 IP Address: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
