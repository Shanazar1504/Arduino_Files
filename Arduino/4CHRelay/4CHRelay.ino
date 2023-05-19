#include "ESP8266WiFi.h"
#define RELAY 0
#define LED 2

byte relON[] = {0xA0, 0x01, 0x01, 0xA2};
byte relOFF[] = {0xA0, 0x01, 0x00, 0xA1};

const char* ssid = "LDR";
const char* password = "12345678";

unsigned char status_RELAY = 0;
WiFiServer server(80);
String header;
String RELAYState = "vyp";

void setup() {

  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  digitalWrite(LED, HIGH);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  digitalWrite(LED, LOW);
}

void loop() {
  WiFiClient client = server.available();

  if(client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if(client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if(c == '\n') {

          if(currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            //turns the GPIOs on and off
            if(header.indexOf("GET /on") >= 0) {
              Serial.println("GPIO /on");
              RELAYState = "zap";
              Serial.begin(9600);
              Serial.write(relON, sizeof(relON));
            } else if(header.indexOf("GET /off") >= 0) {
              Serial.println("GPIO /off");
              RELAYState = "vyp";
              Serial.begin(9600);
              Serial.write(relOFF, sizeof(relOFF));
            }

            // html page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");

            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button {background-color: #7ad226; border: none; color: white; padding: 16px 40px; border-radius: 10px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #ff3333;}</style></head>");
            client.println("<p>Stav rele -" + RELAYState + "</p>");

            if(RELAYState == "vyp") {
              client.println("<p><a href=\"/on\"><button class=\"button\">ZAP</button></a></p>");
            } else {
              client.println("<p><a href=\"/off\"><button class=\"button button2\">VYP</button></a></p>");
            }

            client.println("</body></html>");
            client.println();

            break;
          } else {
            currentLine = "";
          }

      } else if(c != '\r') {
           currentLine + c;
        }
      }
    }
            //clear the header variable
        header = "";
        //close the connection
        client.stop();
        Serial.println("Client disconnected");
        Serial.println("");
  }
}
