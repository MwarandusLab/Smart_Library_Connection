#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "TRUSTKISIA-TECH";
const char* password = "30010231";
const char* server_ip = "192.168.137.1";
const int server_port = 80;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // Print ESP8266 IP address when connected
  Serial.println("Connected to WiFi");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());
}

String urlEncode(const String& str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;

  for (unsigned int i = 0; i < str.length(); i++) {
    c = str.charAt(i);

    if (c == ' ') {
      encodedString += '+';
    } else if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '-' || c == '_' || c == '.' || c == '~')) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
    }
  }

  return encodedString;
}

void loop() {
  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n');

    if (receivedData == "A") {
      sendToServer_2("2302989343");  //derrick
      delay(500);
    } else if (receivedData == "B") {
      sendToServer_1("24394053903");  //linah
      delay(500);
    } else if (receivedData == "C") {
      sendToServer("236843783929");  //kheri
      delay(500);
    }

    delay(500);
  }
}

void sendToServer(String data) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://" + String(server_ip) + ":" + String(server_port) + "/server_1.php";

    // Use WiFiClient instead of HTTPClient for ESP8266
    WiFiClient client;
    http.begin(client, url);

    // Set content type to application/x-www-form-urlencoded
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = http.POST("data=" + urlEncode(data));
    delay(1000);
    Serial.println(url);
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.print("Payload: ");
        Serial.println(payload);

      } else {
        Serial.println("Failed to connect to server. HTTP error: " + String(httpCode));
      }
    } else {
      Serial.println("Failed to connect to server");
    }
    http.end();
  }
}

void sendToServer_1(String datas) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://" + String(server_ip) + ":" + String(server_port) + "/server_2.php";

    // Use WiFiClient instead of HTTPClient for ESP8266
    WiFiClient client;
    http.begin(client, url);

    // Set content type to application/x-www-form-urlencoded
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = http.POST("data=" + urlEncode(datas));
    Serial.println(url);
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.println("Failed to connect to server");
    }
    http.end();
  }
}

void sendToServer_2(String data) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://" + String(server_ip) + ":" + String(server_port) + "/server_3.php";

    // Use WiFiClient instead of HTTPClient for ESP8266
    WiFiClient client;
    http.begin(client, url);

    // Set content type to application/x-www-form-urlencoded
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = http.POST("data=" + urlEncode(data));
    Serial.println(url);
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.println("Failed to connect to server");
    }
    http.end();
  }
}

