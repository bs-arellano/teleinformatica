#include <WiFi.h>
#include <Arduino_MQTT_Client.h>
#include <ThingsBoard.h>

#define WIFI_AP "Jhon"
#define WIFI_PSWD "idyc5760"

#define TB_SERVER "demo.thingsboard.io"
#define TOKEN "80e8b0so6joockm08js0"

#define led_pin 13
#define button_pin 14

WiFiClient wifiClient;
Arduino_MQTT_Client mqttClient(wifiClient);
ThingsBoardSized<32> tb(mqttClient, 128);
int led_state = 0;
bool buttonState = false;

RPC_Response setLedSwitchState(RPC_Data &data)
{
  Serial.println("Cambio de led recibido");
  led_state = data;
  Serial.println("Nuevo estado: ");
  Serial.print(led_state);
  if (led_state)
  {
    digitalWrite(led_pin, HIGH);
  }
  else
  {
    digitalWrite(led_pin, LOW);
  }
  return RPC_Response("setLedSwitchValue", led_state);
}
bool subscribed = false;

const std::array<RPC_Callback, 1U> cb = {
  RPC_Callback("setLedSwitchValue", std::bind(&setLedSwitchState, std::placeholders::_1))
};


void setup()
{
  Serial.begin(9600);
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  WiFi.begin(WIFI_AP, WIFI_PSWD, 6);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    digitalWrite(led_pin, HIGH);
    delay(250);
    digitalWrite(led_pin, LOW);
    delay(250);
  }
  Serial.println("Wifi connected!");
}

void loop()
{
  //Ensure Wifi connection
  if (WiFi.status() != WL_CONNECTED)
  {
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      digitalWrite(led_pin, HIGH);
      delay(250);
      digitalWrite(led_pin, LOW);
      delay(250);
    }
    Serial.println("Wifi connected!");
  }

  //Connects to TB server
  while (!tb.connected())
  {
    if (tb.connect(TB_SERVER, TOKEN))
    {
      Serial.println("Connected to TB server");
    }
  }

  //Subscribe to RPC
  while (!subscribed) {
    if (!tb.RPC_Subscribe(cb.begin(), cb.cend()))
    {
      Serial.println("Failed to subscribe RPC");
      return;
    }
    else {
      Serial.println("Subscribed to RPC");
      subscribed = true;
    }
  }

  if (tb.connected() && subscribed) {
    if (digitalRead(button_pin) == HIGH && !buttonState) {
      tb.sendTelemetryData("buttonState", true);
      buttonState=true;
    }
    else if (digitalRead(button_pin) == LOW && buttonState){
      tb.sendTelemetryData("buttonState", false);
      buttonState=false;
    }
  }
  
  tb.loop();
}