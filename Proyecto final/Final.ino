#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Definir el pin del sensor MQ-7
#define MQ7_PIN 34

// Credenciales Wi-Fi
char ssid[] = "";
char pass[] = "";

// Auth Token de Blynk
char auth[] = BLYNK_AUTH_TOKEN;

// Variable para almacenar el valor del sensor
int sensorValue = 0;

void setup() {
  // Inicializar el serial
  Serial.begin(9600);

  // Inicializar Blynk
  Blynk.begin(auth, ssid, pass);
  while(!Blynk.connected()){
    Serial.println("Connecting to Blynk...");
    delay(500);
  }
  Serial.println("Connected to Blynk");

  // Configurar el pin del sensor como entrada
  pinMode(MQ7_PIN, INPUT);
}

void loop() {
  // Leer el valor del sensor
  sensorValue = analogRead(MQ7_PIN);
  
  // Imprimir el valor en el Serial Monitor
  Serial.print("MQ-7 Sensor Value: ");
  Serial.println(sensorValue);

  // Enviar el valor del sensor a Blynk (asumiendo que usas el Virtual Pin V5)
  Blynk.virtualWrite(V5, sensorValue);

  // Comprobar si el valor del sensor supera 1000
  if (sensorValue > 1000) {
    // Registrar un evento en Blynk y enviar una notificación
    Blynk.logEvent("gas_leak", "¡Se detectó un nivel alto de gas!");
  }

  // Ejecutar Blynk.run() para mantener la conexión
  Blynk.run();

  // Esperar un segundo antes de la siguiente lectura
  delay(1000);
}
