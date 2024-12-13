#include "variaveis.h"



void setup_wifi() {
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  randomSeed(micros());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String messageTemp;
  for (int i = 0; i < length; i++) {
    // Serial.print((char)payload[i]);
    messageTemp += (char)payload[i];
  }
  if (strcmp(topic, "CXS/Comando") == 0) {

    if (messageTemp == "Mais") {
      irsend.sendRaw(Mais, 67, khz);
      delay(300);
      client.publish("CXS/Resposta", "Mais");
    }

    else if (messageTemp == "Menos") {
      irsend.sendRaw(Menos, 67, khz);
      delay(300);
      client.publish("CXS/Resposta", "Menos");
    }

    else if (messageTemp == "Power") {
      irsend.sendRaw(Power, 67, khz);
      delay(300);
      client.publish("CXS/Resposta", "Power");
    }

    else if (messageTemp == "PRO") {
      irsend.sendRaw(PRO, 67, khz);
      delay(300);
      client.publish("CXS/Resposta", "PRO");
    }

    else if (messageTemp == "AUX") {
      irsend.sendRaw(AUX, 67, khz);
      delay(300);
      client.publish("CXS/Resposta", "AUX");
    }

    else if (messageTemp == "DVD") {
      irsend.sendRaw(DVD, 67, khz);
      delay(200);
      client.publish("CXS/Resposta", "DVD");
    }
  }
}

void reconnect() {
  int attemptCount = 0;

  while (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
  }

  while (!client.connected()) {
    Serial.print("Tentando Conectar ao MQTT...");
    if (client.connect("CXS", mqtt_user, mqtt_password, "CXS/Conexao", 1, true, "Offline", true)) {
      client.publish("CXS/Conexao", "Online", true);
      Serial.println("conectado");
      client.subscribe("CXS/Comando");
      attemptCount = 0;  // Reset attempt count on successful connection
    } else {
      Serial.print("Falha na conexão, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
      attemptCount++;
      if (attemptCount >= 10) {
        Serial.println("Falha na conexão após 10 tentativas, reconectando ao WiFi...");
        WiFi.disconnect();
        delay(1000);
        WiFi.begin(ssid, password);
        attemptCount = 0;  // Reset attempt count after reconnecting to WiFi
      }
    }
  }
}
