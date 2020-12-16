#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <stdio.h>
#include <DHT.h>
#include <Arduino.h>

#define wifi_name "1032_Family"
#define wifi_pass "Family1032"

        Timer -

    arduino - timer

                  temp sensor




    const char *host = "script.google.com";

const int httpsPort = 443;


WiFiClientSecure client;


arduino - timer timer

              DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  WiFi.begin(wifi_name, wifi_pass)


  try to connect for 5 seconds yell if no good // WiFi.begin(ssid, password);  

 set bandwidth through usb 

 port to computer // Serial Begin in baudrate [Serial.begin(115200)]

 set GPIO1,2,3,4 as INPUT // pinMode(16,INPUT)

 set timer every 20 sec do testSoil // timer.every(60000,testSoil) ////// timer.setInterval(60000,testSoil)

 set timer every 60 sec do measureTemp

 set timer every 120 sec do transmitData

 print done with setup // Serial.println("XXX")



 start digital conversation with the temp sensor // dht.begin();
}

void loop()
{

  run the timer // timer.run

      keep the wifi
}

void testSoil()
{

  turn on gpio4a // digitalWrite(9,HIGH);

  wait 0.2 sec //delay(200)

  float volts = for GPIO A0 what is voltageaa // float x = analogRead(A0)

  if change is more than 2% -->

    transmitData

    reset timer of transmitData

  turn off // digitalWrite(9,LOW);
}

void measureTemp()
{

  ask temp from digital adress 0x18 // dht.readTemperature();

          if change is more than 2 %
          -- >

      transmitData

          reset timer of transmitData
}

void transmitData()
{

  client.setInsecure();

  if (!client.connect(host, httpsPort))

  {

    Serial.println("connection failed");

    return;
  }

  String string_amp = String(Amps);

  String string_voltage = String(Voltage);

  String url = "/macros/s/" + GAS_ID + "/exec?Volts=" + string_voltage + "&Amps=" + string_amp;

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +

               "Host: " + host + "\r\n" +

               "User-Agent: BuildFailureDetectorESP8266\r\n" +

               "Connection: close\r\n\r\n");

  client.stop();
}