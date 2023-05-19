/*
 * ESP8266 (NodeMCU) Handling Web form data basic example
 * https://circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<h2>Circuits4you<h2>
<h3> HTML Form ESP8266</h3>

<form action="/action_page">
  First name:<br>
  <input type="text" name="firstname" value="Mickey">
  <br>
  Last name:<br>
  <input type="text" name="lastname" value="Mouse">
  <br><br>
  <input type="submit" value="Submit">
</form> 

</body>
</html>
)=====";

//SSID and Password of your WiFi router
const char* ssid = "LDR"; 
const char* password = "12345678";

int day = 0, hour = 0, minute = 0, second = 0;
long countdown_time = (day*86400) + (hour*3600) + (minute * 60) + second;
long new_countdowntime_seconds;

ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleSet() {
String sv = String(new_countdowntime_seconds);
  server.send(200, "text/html", sv); //Send web page
}
//===============================================================
// This routine is executed when you press submit
//===============================================================
void handleForm() {
 String firstName = server.arg("firstname"); 
 String lastName = server.arg("lastname"); 

 Serial.print("First Name:");
 Serial.println(firstName);

 Serial.print("Last Name:");
 Serial.println(lastName);
  
 String s = "<a href='/'> Go Back </a>";
 second = lastName.toInt(); 
 server.send(200, "text/html", s); //Send web page

}

void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/action_page", handleForm); //form action is handled here
  server.on("/set", handleSet); 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void looper() {
  long countdowntime_seconds = countdown_time - (millis() / 1000);
  if (countdowntime_seconds >= 0) {
    long countdown_day = countdowntime_seconds / 86400;
    long countdown_hour = countdowntime_seconds / 3600;
    long countdown_minute = ((countdowntime_seconds / 60)%60);
    long countdown_sec = countdowntime_seconds % 60;
    if (countdown_day < 10) {
      Serial.print("0");
    }
    Serial.print(countdown_day);
    Serial.print(":");
    if (countdown_hour < 10) {
      Serial.print("0");
    }
    Serial.print(countdown_hour);
    Serial.print(":");
    if (countdown_minute < 10) {
      Serial.print("0");  
    }
    Serial.print(countdown_minute);
    Serial.print(":");
    if (countdown_sec < 10) {
      Serial.print("0");
    }
    Serial.println(countdown_sec);  

    //delay for get data each seconds
    delay(1000);
    
  } else if(countdowntime_seconds < 0) {
    countdowntime_seconds = 0;
    Serial.println("time detected");
    break;
  }
  new_countdowntime_seconds = countdowntime_seconds;
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
  looper();
}
