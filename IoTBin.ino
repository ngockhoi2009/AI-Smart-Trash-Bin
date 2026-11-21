
  #include <WiFi.h>
  #include <HTTPClient.h>
  #include <ESP32Servo.h>


  const char* wifi = "your wifi";
  const char* password = "your wifipassword";

  const char* serverURL = "http://YourIPAdress:3000/capture"; //
  const char* resultURL = "http://YourIPAdress:3000/result";

  const int Trig = 5;
  const int Echo = 19;
  const float detect = 20;
  const float reset = 22;

  Servo servo1;
  Servo servo2;
  const int s1gpio = 13;
  const int s2gpio = 27;
  const int angle0 = 90;
  const int s1recycle = 160;
  const int s2recycle = 20;
  const int s1nonrecycle = 20;
  const int s2nonrecycle = 160;

  bool object = false;
  unsigned long last = 0;
  const unsigned long cd = 3000;

  const unsigned long timeout = 120000;
  const unsigned long interval = 1000;

  void setup() {
    Serial.begin(115200);
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);
    digitalWrite(Trig, LOW);
    servo1.setPeriodHertz(50);
    servo2.setPeriodHertz(50);
    servo1.attach(s1gpio);
    servo1.write(angle0);
    servo2.attach(s2gpio);
    servo2.write(angle0);
    delay(1000);

    WiFi.begin(wifi, password);
    Serial.print("Dang ket noi Wi-Fi");

    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(700);
    }
    Serial.println();
    Serial.println("Da ket noi Wi-Fi");
  }

  float Distance() {
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    long time = pulseIn(Echo, HIGH, 10000);
    if (time == 0) return -1;
    return time * 0.0343 / 2;
  }

  bool guitinhieu() {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Khong ket noi Wi-Fi");
      return false;
    }
    HTTPClient http;
    http.setTimeout(5000);
    http.begin(serverURL);

    int code = http.GET();
    bool s = false;
    if (code == 200) {
      String ans = http.getString();
      Serial.println("Phan hoi tu Node.js:");
      Serial.println(ans);

      if (ans.indexOf("\"success\":true") >= 0 || ans.indexOf("\"success\": true") >= 0) {
        s = true;
        Serial.println("Da gui tin hieu thanh cong");
      }
      else {
        Serial.println("Node.js khong chap nhan yeu cau capture");
      }
    }
    else {
      Serial.print("Capture HTTP Error: ");
      Serial.println(code);
    }
    http.end();
    return s;
  }

  int kq() {
    unsigned long start = millis();
    while (millis() - start < timeout) {
      if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Mat Wi-Fi, dang ket noi lai...");
        WiFi.reconnect();
        delay(interval);
        continue;
      }
      HTTPClient http;
      http.setTimeout(5000);
      http.begin(resultURL);
      int code = http.GET();
      if (code == 200) {
        String res = http.getString();
        Serial.print("Ket qua tu AI: ");
        Serial.println(res);
        if (res.indexOf("\"status\":\"done\"") >= 0 || res.indexOf("\"status\": \"done\"") >= 0) {
          int type = 0;
          if (res.indexOf("\"type\":1") >= 0 || res.indexOf("\"type\": 1") >= 0) type = 1;
          else if (res.indexOf("\"type\":2") >= 0 || res.indexOf("\"type\": 2") >= 0) type = 2;
          http.end();
          if (type == 1 || type == 2) {
            Serial.println("Finish Classify");
            return type;
          }
          Serial.println("Loi: AI done nhung type khong hop le");
          return 0;
        }
        else if (res.indexOf("\"status\":\"error\"") >= 0 || res.indexOf("\"status\": \"error\"") >= 0) {
          Serial.println("AI classify ERROR");
          http.end();
          return 0;
        }
        else Serial.println("Dang cho AI xu ly...");
      }
      else {
        Serial.print("HTTP Error: ");
        Serial.println(code);
      }
      http.end();
      delay(interval);
    }
    Serial.println("AI timeout - khong nhan duoc ket qua");
    return 0;
  }

  void QuayServo(int type) {
    if (type == 1) {
      Serial.println("Recycle");
      servo1.write(s1recycle);
      servo2.write(s2recycle);
      delay(800);
      servo1.write(angle0);
      servo2.write(angle0);
      delay(800);
      Serial.println("Done");
    }

    else if (type == 2) {
      Serial.println("Non-recycle");
      servo1.write(s1nonrecycle);
      servo2.write(s2nonrecycle);
      delay(800);
      servo1.write(angle0);
      servo2.write(angle0);
      delay(800);
      Serial.println("Done");
    }
    else Serial.println("No AI Result");
  }

  void loop() {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Reconnecting");
      WiFi.reconnect();
      delay(500);
      return;
    }
    float dis = Distance();
    Serial.print("Khoang cach: ");
    Serial.print(dis);
    Serial.println(" cm");
    if (!object && dis > 0 && dis <= detect) {
      object = true;
      if (last == 0 || millis() - last >= cd) {
        last = millis();
        Serial.println("Phat hien vat");
        if (guitinhieu()) {
          Serial.println("AI dang phan loai");
          int type = kq();
          QuayServo(type);
        }
        else Serial.println("Cannot send capture request");
      }
      else Serial.println("Waitinggg");
    }
    if (object && dis >= reset) {
      object = false;
      Serial.println("Done - Ready for next object");
    }
    delay(200);
  }
