#define BLYNK_TEMPLATE_ID "TMPL33hIiJB4s"
#define BLYNK_TEMPLATE_NAME "Smart Home"
#define BLYNK_AUTH_TOKEN "jsQlsHqIom7N0fqKEmb-pAJqEzBeQlEb"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Bonezegei_DHT11.h>

char ssid[] = "WIFI NAME";
char pass[] = "PASSWORD";

#define DHTPIN 25
Bonezegei_DHT11 dht(DHTPIN);

#define LED_PIN 26


#define IN1 4
#define IN2 5


BlynkTimer timer;



// Light Control
BLYNK_WRITE(V1)
{
  int value = param.asInt();
  digitalWrite(LED_PIN, value);
}

// Fan Control
BLYNK_WRITE(V2)
{
  int value = param.asInt();

  if (value == 1)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
}

// Send Sensor Data
void sendSensor()
{
  if (dht.getData())
  {
    float t = dht.getTemperature();
    float h = dht.getHumidity();

    Blynk.virtualWrite(V4, t);
    Blynk.virtualWrite(V5, h);

    Serial.print("Temperature: ");
    Serial.println(t);

    Serial.print("Humidity: ");
    Serial.println(h);
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}