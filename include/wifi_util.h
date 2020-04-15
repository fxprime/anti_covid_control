/***********************|
 * WiFI สำหรับ ESP8266   |
 ***********************/
    #include <ESP8266WiFi.h>
    #include <ESP8266mDNS.h>
    #include <WiFiUdp.h>
    #include <ArduinoOTA.h>


/************************|
 * รหัส WiFi ที่ต้องเชื่อมต่อ   |
 ************************/
    char* ssid      = "Kanuengnit_kiss2G";
    char* pwd       = "3213213213";
    #define ALWAY_CONNECT true


/************************|
 * ตั้งค่า Static IP ตรงนี้   |
 ************************/
    IPAddress local_IP(192, 168, 1, 56);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress primaryDNS(8, 8, 8, 8);


void wifi_ota_init() {

    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
        } else { // U_FS
        type = "filesystem";
        }

        // NOTE: if updating FS this would be the place to unmount FS using FS.end()
        Serial.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
        Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
        Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
        Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
        Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
        Serial.println("End Failed");
        }
    });
    ArduinoOTA.begin();
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
void wifi_init() {
    Serial.println("Checking wifi req.");
    pinMode(0, INPUT_PULLUP);
    led_set_y(true);
    delay(2000);
    
    if(digitalRead(0) == LOW || ALWAY_CONNECT) {
        Serial.println("WiFi requested.");
        WiFi.config(local_IP, primaryDNS, gateway, subnet);
        WiFi.begin(ssid, pwd);
        while(WiFi.status() != WL_CONNECTED) {
            led_set_y(false);
            delay(100);
            led_set_y(true);
            delay(100);
        }    
        Serial.println("WiFi started ! IP = " + WiFi.localIP().toString());
        wifi_ota_init();
    }else{
        Serial.println("WiFi not requested.");
    }
    led_set_y(false);
}
void wifi_handle() {
    ArduinoOTA.handle();
}