long day = 0, hour = 0, minute = 0, second = 15;
long countdown_time = (day*86400) + (hour*3600) + (minute * 60) + second;
void setup() {
  Serial.begin(115200);
  Serial.print("dd:HH:MM:SS");

  setTimer();
}

void loop() {
//setTimer();
}

void setTimer() {
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
    
  } else if(countdowntime_seconds == 0) {
    Serial.println("time detected");
  }
}
