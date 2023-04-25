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
