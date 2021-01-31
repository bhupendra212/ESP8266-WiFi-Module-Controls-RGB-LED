#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Setting firebase configuration.
// Copy firebase host database url & password and paste it here
#define FIREBASE_HOST "ENTER_YOUR_FIREBASE_DATABASE_URL"
#define FIREBASE_AUTH "ENTER_YOUR_DATABASE_SECRET"
// Enter your WiFi connection details
#define WIFI_SSID "ENTER_YOUR_WIFI_SSID"
#define WIFI_PASSWORD "ENTER_YOUR_WIFI_PASSWORD"
// Setting RGB pin output
#define LED D0
#define LED D1
#define LED D2
// Declaring LED_STATUS = 0 means LED is OFF 
int LED_STATUS = 0;
int RED;
int GREEN;
int BLUE;

void setup() {
  // pinMode function is used to configure a specific pin to behave as an input or an output
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  Serial.begin(9600);
  // Connecting to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  // It connect your Arduino code to Firebase Realtime Database
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  // At launch, LED will be OFF
  Firebase.set("LED_STATUS",0);
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value) {
  // analogWrite function is used to pass values to specific pin
  // In our example it will pass RGB value to D0, D1 & D2 pins respectively
  analogWrite(D0, red_light_value);
  analogWrite(D1, green_light_value);
  analogWrite(D2, blue_light_value);
}

// Here we listening to our Firebase Realtime Database for any change in value
// If LED_STATUS = 0, LED will OFF
// IF LED_STATUS = 1, it will switch ON the LED with some RGB value
void loop() {
  LED_STATUS = Firebase.getInt("LED_STATUS");
  if(LED_STATUS == 0) {
    Serial.print("LED IS OFF");
  } else {
    Serial.println("LED IS ON");
    RED = Firebase.getInt("RED");
    GREEN = Firebase.getInt("GREEN");
    BLUE = Firebase.getInt("BLUE");
    RGB_color(RED, GREEN, BLUE);
  }
}