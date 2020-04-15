#include <Arduino.h>
#include "config.h"
#include "led.h"
#include "driver.h"
#include "sensor.h"
#include "wifi_util.h"
#include "state_machine.h"

void setup() {
  drive_init();
  console_init();
  led_init();
  sensor_init();
  wifi_init();
  Serial.println("Started");
 }

void loop() {
  wifi_handle();


  if(drive_but_pressed()) {
    drive_set(HIGH);
    led_set_r(true);
    led_set_g(false);
  }else{
    if( sensor_get() && !st_is_holding()) {
      st_set_holding();
    }

    if(st_is_holding()) {
      // Serial.println("Drive");
      drive_set(HIGH);
      led_set_g(false);
      led_flash(LED_R, 500);

      
    }else{
      // Serial.println("Not Drive");
      led_set_r(false);
      led_flash(LED_G, 500);
      drive_set(LOW);
    }
  }
  
 }