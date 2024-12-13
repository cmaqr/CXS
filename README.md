# ESP8266 MQTT Infrared Control for Home Theater 🚀

This repository contains a project for controlling a home theater system using an ESP8266 microcontroller. The ESP8266 connects to a Wi-Fi network, communicates via MQTT, and sends infrared (IR) commands to the home theater. 🎶

## Features 🌟
- **MQTT Integration:** The ESP8266 communicates with an MQTT broker to receive commands.
- **IR Command Sending:** Sends IR commands to control the home theater.
- **Customizable IR Commands:** Easily configure commands for specific home theater functionalities or other IR devices like air conditioners and TVs. ❄️📺
- **Wi-Fi Connectivity:** Seamless integration with your home Wi-Fi network. 📡
- **Predefined Startup Sequence:** On power-up, the ESP automatically:
  1. Turns on the home theater. 🔊
  2. Sets the volume to maximum. 📈
  3. Configures the home theater to 5.1 surround sound. 🎛️
  4. Turns off the home theater. ❌

## Hardware Requirements 🛠️
- ESP8266 (e.g., NodeMCU)
- IR LED 💡
- Resistors (as required for the IR LED circuit)
- Power supply for the ESP8266 🔋
- Home theater system supporting IR commands (tested on SP177 from Multilaser) 🎥

## Software Requirements 💻
- Arduino IDE
- ESP8266 Board Manager for Arduino
- Libraries:
  - ESP8266WiFi 📶
  - PubSubClient
  - IRremoteESP8266

## Setup 🛠️

### Wiring 🔌
Connect the IR LED to the ESP8266 as follows:
- **IR LED Signal Pin:** Connect to GPIO D2 (defined as `EiR` in the code).
- Use a resistor if necessary to protect the IR LED.
- The ESP8266 is powered by a 5V internal track from the SP177 home theater.
- Ensure the IR LED is directly pointed at the home theater’s IR receiver. 🎯

### Code Configuration ✏️
1. Open the `variaveis.h` file and configure the following parameters:
    ```cpp
    const char* ssid = "YourWiFiSSID";           // Your Wi-Fi SSID
    const char* password = "YourWiFiPassword";   // Your Wi-Fi Password
    const char* mqtt_user = "YourMQTTUser";     // MQTT Username
    const char* mqtt_password = "YourMQTTPassword"; // MQTT Password
    const char* mqtt_server = "YourMQTTServerIP";   // MQTT Broker IP
    ```

2. Upload the code to the ESP8266 using the Arduino IDE. 🚀

### MQTT Configuration 🔗
- **MQTT Topics:**
  - **Command Topic:** `CXS/Comando`
  - **Response Topic:** `CXS/Resposta`
  - **Status Topic:** `CXS/Conexao`

- **Home Assistant YAML Configuration:**
  Ensure you have an MQTT server installed and running. Below is the configuration for Home Assistant:
  ```yaml
  - name: "PW Som"
    availability_topic: "CXS/Conexao"
    payload_available: "Online"
    payload_not_available: "Offline"
    command_topic: "CXS/Comando"
    payload_press: "Power"
    unique_id: "power"
    device:
      identifiers: "home_theater"
      name: "Home Theater"
      manufacturer: "Carlos"
      model: "ESP8266"

  - name: "VMais Som"
    availability_topic: "CXS/Conexao"
    payload_available: "Online"
    payload_not_available: "Offline"
    command_topic: "CXS/Comando"
    payload_press: "Mais"
    unique_id: "aumentar_volume"
    device:
      identifiers: "home_theater"
      name: "Home Theater"
      manufacturer: "Carlos"
      model: "ESP8266"

  - name: "VMenos Som"
    availability_topic: "CXS/Conexao"
    payload_available: "Online"
    payload_not_available: "Offline"
    command_topic: "CXS/Comando"
    payload_press: "Menos"
    unique_id: "diminuir_volume"
    device:
      identifiers: "home_theater"
      name: "Home Theater"
      manufacturer: "Carlos"
      model: "ESP8266"

  - name: "PRO Som"
    availability_topic: "CXS/Conexao"
    payload_available: "Online"
    payload_not_available: "Offline"
    command_topic: "CXS/Comando"
    payload_press: "PRO"
    unique_id: "botao_surround"
    device:
      identifiers: "home_theater"
      name: "Home Theater"
      manufacturer: "Carlos"
      model: "ESP8266"

  - name: "AUX Som"
    availability_topic: "CXS/Conexao"
    payload_available: "Online"
    payload_not_available: "Offline"
    command_topic: "CXS/Comando"
    payload_press: "AUX"
    unique_id: "botao_auxiliar"
    device:
      identifiers: "home_theater"
      name: "Home Theater"
      manufacturer: "Carlos"
      model: "ESP8266"

  - name: "DVD Som"
    availability_topic: "CXS/Conexao"
    payload_available: "Online"
    payload_not_available: "Offline"
    command_topic: "CXS/Comando"
    payload_press: "DVD"
    unique_id: "botao_dvd"
    device:
      identifiers: "home_theater"
      name: "Home Theater"
      manufacturer: "Carlos"
      model: "ESP8266"
  ```

### Supported Commands 💡
The following commands can be sent to the `CXS/Comando` topic to control the home theater:
- `Mais`: Increase volume 🔊
- `Menos`: Decrease volume 🔉
- `Power`: Toggle power 🔌
- `PRO`: Switch to PRO input 🎛️
- `AUX`: Switch to AUX input 🎵
- `DVD`: Switch to DVD input 🎬

### Functionality ⚙️
- The ESP8266 subscribes to the `CXS/Comando` topic and processes incoming commands.
- For each command, the corresponding IR signal is sent to the home theater system.
- The ESP8266 publishes responses to the `CXS/Resposta` topic and its status to the `CXS/Conexao` topic.
- IR commands can be modified to control other devices such as air conditioners or TVs. 🌬️📺

## Extras 🛠️
- **Power Supply:** The ESP8266 is powered by a 5V internal track from the SP177 home theater.
- **IR LED Positioning:** The IR LED is directly pointed at the home theater’s IR receiver for reliable signal transmission. 🔦
- **Tested Model:** This project has been tested with the SP177 home theater from Multilaser. ✅

## Troubleshooting 🛡️
- **Wi-Fi Connection Issues:** Ensure the correct SSID and password are configured. 📶
- **MQTT Connection Issues:** Verify the MQTT broker IP and credentials. 🔗
- **IR Signal Not Working:** Check the IR LED wiring and test the IR signal with an IR receiver or smartphone camera. 📸

## Acknowledgments 🙌
- Libraries used in the project: [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266), [PubSubClient](https://github.com/knolleary/pubsubclient).

---
Feel free to open issues or contribute to this project if you have suggestions or improvements! 🚀

