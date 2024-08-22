#include <ESP8266WiFi.h>

// Preencher com o nome e a senha da rede WiFi
const char *ssid = "";
const char *password = "";

WiFiServer server(80);

void setup() {
    //Define a velocidade do monitor serial 115200bps
    Serial.begin(115200);
    delay(10);

    // Define o led embutido no próprio módulo ESP8266 como um pino de saída
    pinMode(LED_BUILTIN, OUTPUT);
    //Envia um sinal digital HIGH que faz o led embutido, que é ativo em LOW, ficar apagado
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.println();

    Serial.print("Conectando em: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    Serial.print("Conectando...");

    //Repete o loop enquanto o WiFi não estiver conectado
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

//Com base na requisição, determina um valor numérico relativo a ação a ser tomada
int getAction(String request){
    if(request.indexOf("builtLed_on") != -1) return 1;
    if(request.indexOf("builtLed_off") != -1) return 2;
    return 0;
}

void loop() {

    //Cria um WiFiClient se houver
    WiFiClient client = server.available();

    //Se não houver cliente, o 'return' faz o programa voltar ao início do loop
    if (!client) {
        return;
    }

    //Retorna no monitor serial que há um cliente conectado
    Serial.println("Cliente acessando");

    //Aguarda alguma solicitação do cliente
    while (!client.available()) {
        delay(1); //atraso para evitar sobrecarga do CPU da placa
    }

    //Cria uma requisição como String que é lida até um caractére '\r'
    String req = client.readStringUntil('\r');

    //Imprime a requisição no monitor serial
    Serial.println(req);

    //Limpa os dados do cliente
    client.flush();

    switch (getAction(req)) {
        case 1:
            digitalWrite(LED_BUILTIN, LOW);  // Liga o LED embutido
            Serial.println("LED Ligado.");
            break;
        case 2:
            digitalWrite(LED_BUILTIN, HIGH);  // Desliga o LED embutido
            Serial.println("LED Desligado.");
            break;
        default:
            Serial.println("Tentativa de requisição inválida.");
            break;
    }
    
    //Imprime no monitor serial que o cliente foi desconectado
    Serial.println("Cliente desconectado.");
}
