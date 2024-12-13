
#include "libporta.h"

void setup() {
  irsend.begin();  //Início do IR
  delay(1000);
  irsend.sendRaw(Power, 67, khz);
  delay(3000);
  irsend.sendRaw(PRO, 67, khz);
  delay(500);
  for (int i = 0; i <= 40; i++) {
    irsend.sendRaw(Mais, 67, khz);
    delay(150);
  }
  irsend.sendRaw(Power, 67, khz);
  delay(200);
  Serial.begin(115200);  //Início da comunicacao Serial
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.println("passou setup");
}

void loop() {
  if (!client.connected()) {
    reconnect();
    Serial.println("passou reconnect");
  }
  client.loop();
}
