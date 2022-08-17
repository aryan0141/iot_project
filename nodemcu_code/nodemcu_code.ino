#include <ESP8266WiFi.h>

char ssid[]     = "<your_wifi_name>";
char password[] = "<your_wifi_password";
const char* HOST_IP = "<your_ip_address>";     // Localhost Server IP
const int HOST_PORT = 80;
// URI for the request
String url = "/liveSensorData";


const int trig = 12; // D6
const int echo = 14; // D5

int distance;  // This variable will store the distance of the object from the sensor.

void setup() {
  // Ultrasonic
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // Defining the Baud Rate
  Serial.begin(115200);
  delay(10);

  // Establishing Connection with WIFI:
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Checking the connection status of Wi-Fi:
  if(WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("Not connected to WIFI");
    return;
  } else {
    // Connecting To the Server:
    Serial.print("connecting to ");
    Serial.println(HOST_IP);
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    if (!client.connect(HOST_IP, HOST_PORT)) {
      // If NodeMCU is not able to connect to the server.
      Serial.println("connection failed");
    } else {
        // Input the data of Ultrasonic Sensor
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        // Calculating the distance by multiplying the speed of sound by the time of echo
        distance = pulseIn(echo, HIGH) * 0.034 / 2;
        String data = "{'data':" + String(distance) + "'}";
        Serial.println(data);
        // Send request to the server:
        client.println("POST " + url + " HTTP/1.1");
        client.println("Host: server_name");
        client.println("Accept: *" + url + "*");
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.print("Content-Length: ");
        client.println(data.length());
        client.println();
        client.print(data);
        unsigned long timeout = millis();
        while (client.available() == 0) {
          if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
          }
        }
        // Read all the lines of the reply from server and print them to Serial
        while (client.available()) {
          String line = client.readStringUntil('\r');
          Serial.print(line);
        }
        Serial.println();
        Serial.println("closing connection"); 
    }
  }
  // We will send the requests in every 5 seconds, that's why we are adding a delay of 5000 miliseconds => 5 sec.
  delay(5000);
}
