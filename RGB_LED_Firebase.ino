#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Setting firebase configuration.
#define FIREBASE_HOST "arduino-19b69.firebaseio.com"
#define FIREBASE_AUTH "EEzjM9REddlieBAS5E5FlG1em3pM1dxZX1Wg37Hv"
// WiFi connection details
#define WIFI_SSID "A 501"
#define WIFI_PASSWORD "Saurabh@12may"
// Setting RGB pin output
#define LED D0
#define LED D1
#define LED D2
void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("LED_STATUS",0);
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(D0, red_light_value);
  analogWrite(D1, green_light_value);
  analogWrite(D2, blue_light_value);
}

int LED_STATUS = 0;
int RED;
int GREEN;
int BLUE;
void loop() {
  LED_STATUS = Firebase.getInt("LED_STATUS");
  if(LED_STATUS == 0){
    Serial.print("LED IS OFF");
  } else {
    Serial.println("LED IS ON");
    RED = Firebase.getInt("RED");
    GREEN = Firebase.getInt("GREEN");
    BLUE = Firebase.getInt("BLUE");
    RGB_color(RED, GREEN, BLUE);
  }
}
