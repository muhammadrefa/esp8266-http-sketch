#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

const char* ssid = "SSID";
const char* password = "PASSWORD";

void setup()
{

    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }


    // Konek ke WiFi
    // WiFiMulti.addAP("SSID", "PASSWORD");
    WiFiMulti.addAP(ssid, password);

    // Jika terhubung
    while (!(WiFiMulti.run() == WL_CONNECTED)) {
      USE_SERIAL.println("Menghubungkan...");
      delay(1000);
    }
    // Cetak alamat IP
    Serial.print("Terhubung! IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
        http.begin("http://192.168.1.12/test.html"); //HTTP

        // Mengirim data POST
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpCode = http.POST("var1=data 1&var2=data2");
      
        // httpCode will be negative on error
        if(httpCode > 0) {
          // file found at server
          if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            USE_SERIAL.print(payload);
          }
        } else {
          USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
      
        http.end();
    }

    delay(10000);
}

