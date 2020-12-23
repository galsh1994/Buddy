#include <ESP8266WIFI.h>
#include <WiFiClientSecure.h>
#include <stdio.h>
#include <DHT.h>
#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>



#define DHTPIN 5 // Digital pin D1 connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11 - Temperature Sensor Type

// WiFi connection details
const char*   ssid=       "1032_Family";
const char*   wifi_pass=  "Family1032";


const int httpsPort = 443;
const char *host = "script.google.com";

//Current Temperature and Humidity, will be updated in the loop()
float t = 0.0;
float h = 0.0;
//Updating DHT readings every 10 seconds
const long interval = 10000;
// will store last time DHT was updated
unsigned long previousMillis = 0;

WiFiClientSecure client;
AsyncWebServer server(80);

DHT dht(DHTPIN, DHTTYPE);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP8266 DHT Server</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">°C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">%</sup>
  </p>
  <p>
      <script src="https://apps.elfsight.com/p/platform.js" defer></script>
<div class="elfsight-app-65e091b0-d33c-4191-81f3-be77c921660a"></div>
    </P>
  <p>
    <i class="fab fa-youtube" style="font-size:1.0rem;color:red;"></i>
    <span style="font-size:1.0rem;">Subscribe to </span>
    <a href="https://www.youtube.com/channel/UC49xSqiQ6gBrxUMQ9zvzO6A" target="_blank" style="font-size:1.0rem;">The IoT Projects YouTube Channel</a>
  </P>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(t);
  }
  else if(var == "HUMIDITY"){
    return String(h);
  }
  return String();
}

void setup()
{

  pinMode(1, INPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, wifi_pass);
  dht.begin();
  Serial.println();
  Serial.print("Connecting...");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(h).c_str());
  });

  // Start server
  server.begin();


set GPIO1,2,3,4 as INPUT // pinMode(16,INPUT)

  WiFi.begin(wifi_name, wifi_pass)


  try to connect for 5 seconds yell if no good // WiFi.begin(ssid, password);  

 set bandwidth through usb 

 port to computer // Serial Begin in baudrate [Serial.begin(115200)]

 set GPIO1,2,3,4 as INPUT // pinMode(16,INPUT)

 set timer every 20 sec do testSoil // timer.every(60000,testSoil) ////// timer.setInterval(60000,testSoil)
 timer.every(60000,testSoil)
 set timer every 60 sec do measureTemp
 set timer every 120 sec do transmitData
 print done with setup // Serial.println("XXX")
start digital conversation with the temp sensor // dht.begin();
}

void loop(){  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;
    // Read temperature as Celsius (the default)
    float newT = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    //float newT = dht.readTemperature(true);
    // if temperature read failed, don't change t value
    if (isnan(newT)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      t = newT;
      Serial.println(t);
    }
    // Read Humidity
    float newH = dht.readHumidity();
    // if humidity read failed, don't change h value 
    if (isnan(newH)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      h = newH;
      Serial.println(h);
    }
  }
}

// void testSoil()
// {

//   turn on gpio4a 
//   digitalWrite(9,HIGH);

//   wait 0.2 sec //delay(200)

//   float volts = for GPIO A0 what is voltageaa // float x = analogRead(A0)

//   if change is more than 2% -->

//     transmitData

//     reset timer of transmitData

//   turn off // digitalWrite(9,LOW);
// }

// void measureTemp()
// {

//   ask temp from digital adress 0x18 // dht.readTemperature();

//           if change is more than 2 %
//           -- >

//       transmitData

//           reset timer of transmitData
// }

// void transmitData()
// {

//   client.setInsecure();

//   if (!client.connect(host, httpsPort))

//   {

//     Serial.println("connection failed");

//     return;
//   }

//   String string_amp = String(Amps);

//   String string_voltage = String(Voltage);

//   String url = "/macros/s/" + GAS_ID + "/exec?Volts=" + string_voltage + "&Amps=" + string_amp;

//   client.print(String("GET ") + url + " HTTP/1.1\r\n" +

//                "Host: " + host + "\r\n" +

//                "User-Agent: BuildFailureDetectorESP8266\r\n" +

//                "Connection: close\r\n\r\n");

//   client.stop();
// }