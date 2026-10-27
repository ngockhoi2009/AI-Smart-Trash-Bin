
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>

const char* wifi = "Nha11wifi";
const char* password = "1411wifi";

const char* serverURL = "http://192.168.1.6:3000/capture";
const char* resultURL = "http://192.168.1.6:3000/result";

const int Trig = 5;
const int Echo = 19;

const float detect = 20;
const float reset = 22;

Servo servo1;
Servo servo2;
const int s1gpio = 13;
const int s2gpio = 27;

const int angle0 = 90;
const int s1Recycle = 160;
const int s2Recycle = 20;
const int s1NonRecycle = 20;
const int s2NonRecycle = 160;

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

  bool k = true;
  while (k) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Chờ tí!");
      delay(700);
    }
    else k = false;
  }
  Serial.println();
  Serial.println("Đã kết nối wifi");
}

float Distance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  long time = pulseIn(Echo, HIGH, 10000);
  if (time == 0) {
    return -1;
  }
  return time*0.0343 /2;
}

bool guitinhieu() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Không kết nối WiFi");
    return false;
  }
  HTTPClient http;
  http.setTimeout(5000);
  http.begin(serverURL);

  int code = http.GET();
  bool s = false;

  if (code == 200) {
    Serial.println("Đã gửi tín hiệu");
    String ans = http.getString();
    Serial.println(ans);
    s = true;
  } 
  else Serial.println(code);
  http.end();
  return s;
}

int kq() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Mat Wi-Fi!");
    return 0;
  }

  HTTPClient http;
  http.setTimeout(5000);
  http.begin(resultURL);
  int code = http.GET();
  int type = 0;
  if (code == 200) {
    String res = http.getString();
    Serial.print("Ket qua tu AI: ");
    Serial.println(res);
    if (res.indexOf("\"type\":1") >= 0 ||
      res.indexOf("\"type\": 1") >= 0) {
      type = 1;
    } 
    else if (res.indexOf("\"type\":2") >= 0 ||
      res.indexOf("\"type\": 2") >= 0) {
      type = 2;
    }
  } 
  else Serial.println(code);
  http.end();
  return type;
}

void QuayServo(int type) {
  if (type == 1) {
    Serial.println("Recycle");
    servo1.write(s1Recycle);
    servo2.write(s2Recycle);
    delay(800);
    servo1.write(angle0);
    servo2.write(angle0);
    delay(800);
    Serial.println("Done");
  } 
  else if (type == 2) {
    Serial.println("Non-recycle");
    servo1.write(s1NonRecycle);
    servo2.write(s2NonRecycle);
    delay(800);
    servo1.write(angle0);
    servo2.write(angle0);
    delay(800);
    Serial.println("Done");
  } 
  else Serial.println("Khong co ket qua AI, khong quay servo");
}

bool object = false;
unsigned long long last = 0;
const int cd = 3000;

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Đang kết nối lại");
    WiFi.reconnect();
    delay(500);
    return;
  }
  float dis = Distance();
  Serial.print("Khoang cach: ");
  Serial.print(dis);
  Serial.println(" cm");
  if (!object && dis <= detect) {
    object = true;
    if (last == 0 || millis() - last >= cd) {
      last = millis();
      Serial.println("Phát hiện vật");
      if (guitinhieu()) {
        Serial.println("AI đang phân loại");
        int type = kq();
        QuayServo(type);
      }
    } 
    else Serial.println("Bềnh tễnh");
  }
  if (object && dis >= reset) {
     object = false;
    Serial.println("Đã phân loại thành công");
  }
  delay(200);
}
