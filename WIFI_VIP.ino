#include <ESP8266WiFi.h>
WiFiServer server(80);
int out = 0;
int timer = 0;
int car = 0;
int mil;
int mil2;
int complete;
const char* ssid = "Abs";
const char* password = "12345678";
void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(D1, INPUT_PULLUP);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  server.begin();
  Serial.println(WiFi.localIP());
}

void loop() {
  CheckClient();
  car = digitalRead(D1);
  if (car == 0) {
    if (timer == -1 and complete == 1) {
      timer = 20;
    }
    if (timer > 0 and millis() - mil2 > 1000) {
      timer--;
      mil2 = millis();
      complete = 0;
    }
  }
  if (car == 1) {
    timer = -1;
    complete = 1;
  }
  out = timer;
  
  
  if (out == -1) {
   out = 700;
  }
}
void CheckClient() {
  WiFiClient client = server.available();  // Проверка подключения клиента
  if (!client.available()) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<!DOCTYPE html>");
    client.println("<html lang=\"ru\">");
    client.println("<head>");
    client.println("<meta charset=\"UTF-8\">");
    client.println("<title>");
    client.println(out);
    client.println("</title>");
    client.println("</head>");
    client.println("<body>");
    client.println(out);
    client.println("</body>");
    client.println("</html>");
    delay(1);
  }
}
