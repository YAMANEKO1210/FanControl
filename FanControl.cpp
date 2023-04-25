#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>

#define FAN1_1 12
#define FAN1_2 14
#define FAN2_1 26
#define FAN2_2 27
#define TPE_PWM 34

const char *ssid = "FANControl"; // ESP32C3のWi-Fiホットスポット名
const char *password = "password1"; // ESP32C3のWi-Fiパスワード

int fanTemp = 26; // ファンを稼働させる温度
int ondo;

WebServer server(80);

void handleRoot() // ルートページを返す
{

   String html =
  "<!DOCTYPE html><html lang='ja'><head><meta charset='UTF-8'>\
          <body><h1>ファンコントローラー</h1>";
  html += "<p>現在の温度: " + String(ondo) + " &#8451;</p>";
  html += "<form method='POST' action='/settemp'>";
  html += "<p>動作設定温度</p>";
  html += "<input type='number' id='temp' name='temp' value='" + String(fanTemp) + "'><br><br>";
  html += "<input type='submit' value='Set'>";
  html += "</form></body></html>";
  server.send(200, "text/html", html);
}

void handleSetTemp() // ファンの起動温度を更新する
{
  if (server.method() == HTTP_POST) {
    fanTemp = server.arg("temp").toInt();
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void sendSensorData(){
int ans ,miss;
ans = analogRead(34) ; // アナログ０番ピンからセンサー値を読込む
miss=ans-600;
ondo=miss/10;
Serial.println(ondo) ;


delay(500) ;
if ( ondo>fanTemp) {
  //fanTemp
digitalWrite(FAN1_1, HIGH );
digitalWrite(FAN1_2, LOW );
digitalWrite(FAN2_1, HIGH );
digitalWrite(FAN2_2, LOW );

delay( 1000 );
} else {
digitalWrite(FAN1_1, LOW );
digitalWrite(FAN1_2, LOW );
digitalWrite(FAN2_1, LOW );
digitalWrite(FAN2_2, LOW );


delay( 1000 );
}
}

void setup(){
Serial.begin(9600);
pinMode(FAN1_1, OUTPUT);
pinMode(FAN1_2, OUTPUT);
pinMode(FAN2_1, OUTPUT);
pinMode(FAN2_2, OUTPUT);

Wire.begin();
WiFi.softAP(ssid, password); // Wi-Fiホットスポットを開始
server.on("/", handleRoot);
server.on("/settemp", handleSetTemp);
server.begin();
Serial.println("Server started");
}

void loop()
{
server.handleClient();
sendSensorData();
}
