//D0 is D0 on the hardware, but also tied to red LED
//D1 is D1 on the hardware
//D2 is D2 on the hardware
//D4 is D3 on the hardware, but also tied to blue LED
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;
ESP8266WebServer server(80);

String webpage = "";
String css = "";

const char * ssid = "pearly-gateway";
const char * password = "this could be heaven or this could be hell";

const char * host = "mlwymore.public.iastate.edu";

int stepPin = D1;
int dirPin = D2; //D3 on the hardware

int flag = 0;

enum direction_t {LEFT, RIGHT};

void turn(direction_t dir) {
  switch(dir) {
    case LEFT:
      digitalWrite(dirPin, HIGH);
      break;
    case RIGHT:
      digitalWrite(dirPin, LOW);
      break;
  }
  for (int i = 0; i < 100; i++) {
    digitalWrite(stepPin, HIGH);
    delay(10);
    digitalWrite(stepPin, LOW);
    delay(10);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, HIGH); //LOW for clockwise, HIGH for CCW

  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  webpage = "<!DOCTYPE html><html lang=en><meta charset=UTF-8><meta content=\"width=device-width,initial-scale=1\"name=viewport><meta content=\"ie=edge\"http-equiv=X-UA-Compatible><link href=main.css rel=stylesheet><title>Control Your Robot Body!</title><main><ul><li><a href=left><button type=button>Left</button><li><a href=right><button type=button>Right</button></ul></main>";
  css = "* {box-sizing: border-box;}";

  
  Serial.println("Web page:");
  Serial.println(webpage);

  if (mdns.begin("remotebot", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", []() {
    server.send(200, "text/html", webpage);
  });
  server.on("/main.css", []() {
    server.send(200, "text/css", css);
  });
  server.on("/right", []() {
    server.send(200, "text/html", webpage);
    turn(RIGHT);
  });
  server.on("/left", []() {
    server.send(200, "text/html", webpage);
    turn(LEFT);
  });
  server.begin();
  Serial.println("HTTP server started");
}

int value = 0;

void loop(void) {
  // put your main code here, to run repeatedly:
  server.handleClient();
  /*if (flag) {
    digitalWrite(stepPin, HIGH);
    flag = 0;
    }
    else {
    digitalWrite(stepPin, LOW);
    flag = 1;
    }
    delay(1000);*/
  /* digitalWrite(stepPin, HIGH);
    delay(10);
    digitalWrite(stepPin, LOW);
    delay(10);
  */
  /*delay(5000);
    ++value;

    Serial.print("connecting to ");
    Serial.println(host);

    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
    }

    String url = "/index.html";
    Serial.print("Requesting URL: ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");
    delay(500);

    while(client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");*/
}
