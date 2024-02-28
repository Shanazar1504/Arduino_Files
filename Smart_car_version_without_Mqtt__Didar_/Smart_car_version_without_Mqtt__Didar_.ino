#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <ESP8266TimeAlarms.h>

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(80);

const char* ntpServer    = "pool.ntp.org";

int starterSleep = 1500;

#define GPIO_RELAY 0
#define GPIO2_RELAY 2
#define GPIO3_RELAY 3
#define GPIO4_RELAY 1
#define PUB_GPIO_STATUS "car/gpio/status"
#define SUB_GPIO_ACTION "car/gpio/action"

String getMin, getHrs, getMoment, getCommand, getOnce, getRepeat, localCarDoor = "0", localCarIgnition = "0", received_payload, ipAddress, current_time, getStarterSleep;
int setMin, setHrs, setMoment, setCommand, setOnce, setRepeat, relay_state;
AlarmId idstart, idopen, idclose;
unsigned long previousMillis = 0;
unsigned long interval = 30000;

void setup() {
  Serial.begin(115200);

  configTime(0, 0, ntpServer);
  setenv("TZ", "<+05>-5", 1);
  tzset();
  Serial.print("Clock before sync: ");

  pinMode(GPIO_RELAY, OUTPUT);
  pinMode(GPIO2_RELAY, OUTPUT);
  pinMode(GPIO3_RELAY, OUTPUT);
  pinMode(GPIO4_RELAY, OUTPUT);

  digitalWrite(GPIO_RELAY, HIGH);
  digitalWrite(GPIO2_RELAY, HIGH);
  digitalWrite(GPIO3_RELAY, HIGH);
  digitalWrite(GPIO4_RELAY, HIGH);


  initWifiStation();

  server.on("/config/smart/car/version/", catchVersion);
  server.on("/config/smart/car/ipaddress/", catchIP);
  server.on("/config/smart/car/listen/time/", listenTime);
  server.on("/config/smart/car/door/open/", DoorOpen);
  server.on("/config/smart/car/door/close/", DoorClose);
  server.on("/config/smart/car/ignition/on/", IgnitionOn);
  server.on("/config/smart/car/ignition/off/", IgnitionOff);
  server.on("/config/smart/car/engine/start/", EngineStart);
  server.on("/config/smart/car/listen/", listenEvent);
  server.on("/config/smart/car/listen/token/", listenToken);
  server.on("/config/smart/car/listen/runtime/", listenRuntime);

  server.on("/config/smart/car/door/open/timer/", doorOpenTimer);
  server.on("/config/smart/car/door/close/timer/", doorCloseTimer);
  server.on("/config/smart/car/engine/start/timer/", engineStartTimer);
  server.on("/config/smart/car/default/timer/", defaultTimer);
  server.on("/config/smart/car/genericArgs", handleGenericArgs);
  server.on("/config/smart/car/runtime", handleRuntime);
}

void loop() {
  server.handleClient();

  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    initWifiStation();
    previousMillis = currentMillis;
  }
  digitalClockDisplay();
}

//############### CONTROL WITH GIVEN TIMER #####################//

void doorOpenTimer() {
  if (setOnce == 1) {
    idopen = Alarm.alarmOnce(setHrs, setMin, 0, DoorOpen);
    Serial.println("#################################################################################################### SETTING DOOR OPEN TIMER ENABLE ################################################################################################################");
    delay(1000);
    server.send(200, "text/html", "setTimer");
  } else {
    Alarm.free(idopen); idopen = dtINVALID_ALARM_ID;
    Serial.println("#################################################################################################### SETTING DOOR OPEN TIMER DISABLE ################################################################################################################");
    delay(1000);
    server.send(200, "text/html", "setTimerDisable");
  }
}

void doorCloseTimer() {
  if (setOnce == 1) {
    idclose = Alarm.alarmOnce(setHrs, setMin, 0, DoorClose);
    Serial.println("#################################################################################################### SETTING DOOR CLOSE TIMER ENABLE ################################################################################################################");
    delay(1000);
    server.send(200, "text/html", "setTimer");
  } else {
    Alarm.free(idclose); idclose = dtINVALID_ALARM_ID;
    Serial.println("#################################################################################################### SETTING DOOR CLOSE TIMER DISABLE ################################################################################################################");
    delay(1000);
    server.send(200, "text/html", "setTimerDisable");
  }
}

void engineStartTimer() {
  if (setOnce == 1) {
    idstart = Alarm.alarmOnce(setHrs, setMin, 0, IgnitionEngine);
    Serial.println("#################################################################################################### SETTING START TIMER ENABLE ################################################################################################################");
    delay(1000);
    server.send(200, "text/html", "setTimer");
  } else {
    Alarm.free(idstart); idstart = dtINVALID_ALARM_ID;
    Serial.println("#################################################################################################### SETTING START TIMER DISABLE ################################################################################################################");
    delay(1000);
    server.send(200, "text/html", "setTimerDisable");
  }
}

void defaultTimer() {
  server.send(200, "text/html", "default");
}

//############### GETTING DATA FROM DEVICE WITH LOCALHOST #####################//
void catchVersion() {
  server.send(200, "text/html", "Model:101");
}
void catchIP() {
  server.send(200, "text/html", "1");
}
void listenEvent() {
  server.send(200, "text/html", localCarDoor + localCarIgnition);
}
void listenTime() {
  server.send(200, "text/html", current_time);
}

void listenToken() {
  //  server.send(200, "text/html", mqttUser);
}

void listenRuntime() {
  String myString = String(starterSleep);
  server.send(200, "text/html", myString);
}
//############### CONTROL CAR WITH LOCALHOST #####################//
void DoorOpen() {
  digitalWrite(GPIO_RELAY, LOW);
  delay(100);
  digitalWrite(GPIO_RELAY, HIGH);
  Serial.println("#################################################################################################### DOOR OPENED (VIA LOCALHOST) ################################################################################################################");
  localCarDoor = "1";
  server.send(200, "text/html", "1");
}

void DoorClose() {
  digitalWrite(GPIO2_RELAY, LOW);
  delay(100);
  digitalWrite(GPIO2_RELAY, HIGH);
  Serial.println("#################################################################################################### DOOR CLOSED (VIA LOCALHOST) ################################################################################################################");
  localCarDoor = "0";
  server.send(200, "text/html", "1");
}

void IgnitionOn() {
  digitalWrite(GPIO3_RELAY, LOW);
  Serial.println("#################################################################################################### IGNITION ON (VIA LOCALHOST) ################################################################################################################");
  localCarIgnition = "1";
  server.send(200, "text/html", "1");
}

void IgnitionOff() {
  digitalWrite(GPIO3_RELAY, HIGH);
  Serial.println("#################################################################################################### IGNITION OFF (VIA LOCALHOST) ################################################################################################################");
  localCarIgnition = "0";
  server.send(200, "text/html", "0");
}

void EngineStart() {
  digitalWrite(GPIO4_RELAY, LOW);
  delay(starterSleep);
  digitalWrite(GPIO4_RELAY, HIGH);
  Serial.println("#################################################################################################### ENGINE START (VIA LOCALHOST) ################################################################################################################");
  localCarIgnition = "2";
  server.send(200, "text/html", "1");
}

void IgnitionEngine() {
  digitalWrite(GPIO3_RELAY, LOW);
  Serial.println("IGNITION ON");
  localCarIgnition = "1";
  delay(3000);
  digitalWrite(GPIO4_RELAY, LOW);
  Serial.println("ENGINE RELAY HIGH");
  delay(starterSleep);
  digitalWrite(GPIO4_RELAY, HIGH);
  Serial.println("ENGINE RELAY LOW");
  Serial.println("############################################################################################# IGNITION ON + ENGINE START (USING TIMER) ############################################################################################################");
  localCarIgnition = "2";
  Alarm.timerOnce(setMoment, OnceIgnitionOff);
  server.send(200, "text/html", "1");
}

void OnceIgnitionOff() {
  digitalWrite(GPIO3_RELAY, HIGH);
  Serial.println("###################################################################################################### ENGINE STOP (USING TIMER) ##################################################################################################################");
  localCarIgnition = "0";
  //  mqttClient.publish(PUB_GPIO_STATUS, "4");
  server.send(200, "text/html", "0");
}

//############### GET TIMER AND SET WITH LOCALHOST #####################//
void handleGenericArgs() { //Handler
  String message = "Number of args received:";
  message += server.args();            //Get number of parameters
  message += "\n";                            //Add a new line
  for (int i = 0; i < server.args(); i++) {
    getHrs = server.arg(0);
    getMin = server.arg(1);
    getMoment = server.arg(2);
    getOnce = server.arg(3);
    getCommand = server.arg(4);
    getStarterSleep = server.arg(5);

    setHrs = getHrs.toInt();
    setMin = getMin.toInt();
    setMoment = getMoment.toInt();
    setOnce = getOnce.toInt();
    setCommand = getCommand.toInt();
    starterSleep = getStarterSleep.toInt();
  }
  if (setCommand == 2) {
    doorOpenTimer();
  }
  if (setCommand == 3) {
    doorCloseTimer();
  }
  if (setCommand == 1) {
    engineStartTimer();
  }
  if (setCommand == 0) {
    defaultTimer();
  }
  server.send(200, "text/html", "1");
}

//############### ADD RUNTIME (ENGINE) WITH LOCALHOST #####################//

void handleRuntime() {
  String str = "";
  if (server.arg("runtime") == "") {    //Parameter not found
    str = "0"; //token not found
  } else {    //Parameter found
    str += server.arg("runtime");     //Gets the value of the query parameter
    starterSleep = str.toInt();
  }
  server.send(200, "text/html", "1");          //Returns the HTTP response
}

//############### GET DATE AND TIME FROM INTERNET #####################//
void digitalClockDisplay() {
  time_t tnow = time(nullptr);
  Serial.println(ctime(&tnow));
  current_time = ctime(&tnow);
  Alarm.delay(0);
}

//############### INIT WIFI STATION #####################//
void initWifiStation() {
  delay(10);
  Serial.println('\n');
  wifiMulti.addAP("gray", "87654321");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("LDR", "12345678");
  wifiMulti.addAP("car", "123456789");
  wifiMulti.addAP("phantom", "phantom123");
  wifiMulti.addAP("white", "11111111");
  wifiMulti.addAP("Test", "test1234");
  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  WiFi.hostname("AUTO");
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
  ipAddress = WiFi.localIP().toString();
  server.begin();
  Serial.println("HTTP server started");
  Serial.print("Clock after Wifi: ");
}
