#include <ESP8266WiFi.h>

const char *ssid = "";
const char *password = "";

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    delay(10);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.println();

    Serial.print("Conectando em: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    Serial.print("Conectando...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("Conectado ao WiFi.");

    server.begin();
    Serial.println("Servidor inicializado");

    Serial.print("IP local:");
    Serial.println(WiFi.localIP());
}

void loop() {

    WiFiClient client = server.available();
    if (!client) {
        return;
    }

    Serial.println("Cliente acessando");

    while (!client.available()) {
        delay(1);
    }

    String req = client.readStringUntil('\r');
    Serial.println(req);
    client.flush();

    if (req.indexOf("builtLed_on") != -1) {
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("LED Ligado");
    } else if (req.indexOf("builtLed_off") != -1) {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("LED Desligado");
    }
    
    Serial.println("Cliente desconectado");
}
