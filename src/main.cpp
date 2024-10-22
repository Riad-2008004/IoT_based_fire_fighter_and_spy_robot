#include <WiFi.h>
#include <WebServer.h>

// Motor control pins
const int motor1Pin1 = 5;   // IN1
const int motor1Pin2 = 18;  // IN2
const int motor2Pin1 = 19;  // IN3
const int motor2Pin2 = 21;  // IN4
const int enablePin = 23;   // ENA (PWM control for motor speed)

// WiFi credentials
const char* ssid = "your-ssid";
const char* password = "your-password";

WebServer server(80); // Create a web server object

// Forward movement
void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Backward movement
void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// Turn left (stop right motor)
void turnLeft() {
  digitalWrite(motor1Pin1, LOW);  // Stop left motor
  digitalWrite(motor1Pin2, LOW);  // Stop left motor
  digitalWrite(motor2Pin1, HIGH); // Right motor moves forward
  digitalWrite(motor2Pin2, LOW);  // Right motor moves forward
}

// Turn right (stop left motor)
void turnRight() {
  digitalWrite(motor1Pin1, HIGH); // Left motor moves forward
  digitalWrite(motor1Pin2, LOW);  // Left motor moves forward
  digitalWrite(motor2Pin1, LOW);  // Stop right motor
  digitalWrite(motor2Pin2, LOW);  // Stop right motor
}

// Stop movement
void stopMovement() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

// Setup function
void setup() {
  Serial.begin(115200);

  // Initialize motor pins
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start server and define movement routes
  server.on("/forward", moveForward);
  server.on("/backward", moveBackward);
  server.on("/left", turnLeft);
  server.on("/right", turnRight);
  server.on("/stop", stopMovement);
  
  // Start web server
  server.begin();
}

void loop() {
  server.handleClient(); // Handle client requests
}
