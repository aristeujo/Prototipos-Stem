#include "Wifi.h"
#include "webSocketClient.h"
#include "utils.h"
#include "serial_comm.h"

WifiManager wifi;

const String ip = "10.0.0.159"; //ip do Esp servidor

Serial_comm serial;

//const String ip = "ws://stem.local";
const int port = 81; //porta do websocket no Esp servidor

void setup() {
  Serial.begin(9600);
  Serial.println("\n\nStarting Esp");
  
  wifi.startWiFi();
  serial.sendJson("ESP_IP", wifi.ip , 1);

  startWebSocketClient(ip, port);
  serial.sendJson("ws_client", "started", 1);
  updateWebsocketClient();
  Serial.println("End of Setup");
};

void loop() {
  updateWebsocketClient();
  
  char * messageFromSerial = getMessageFromSerial();
  
  if (messageFromSerial != "0"){
    Serial.println(messageFromSerial);
    sendMessageWsClient(messageFromSerial);
  };
};
