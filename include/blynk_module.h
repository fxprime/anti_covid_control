
/**
 * 
 * Blynk module 
 * 
 */
    #define BLYNK_PRINT Serial


    #include <BlynkSimpleEsp8266.h>

    /**
     * Note : virtual pin
     * V0 = temperature report
     * V1 = humidity report
     */
    char        auth[] = "nvsl8g2tK7EYD__11-AJ9919K7A0Fpl7";
    const char* domain = "blynk.iot-cm.com";
    uint16_t    port   = 8080;

/**
 * V6 = number of used
 * V1 = Manual override 
 * V2 = Motor status 
 * V3 = Accumulated time (min)
 * V4 = Time hold control
 * V5 = Time hold value
 * V7 = Accumulated time (sec)
 */



/**
 * V6 = number of used
 */
BLYNK_WRITE(V6) {
    if(!_number_used_inited) {
        _number_used_inited = true;
        _number_used = param.asInt();
        Serial.println("Inited number of used = " + String(_number_used));
    }
    
}

/**
 * V1 = maunual override
 */
BLYNK_WRITE(V1) {
    _run_by_app = param.asInt();
    Serial.println("Motor is running = " + String(_run_by_app));
}

/**
 * V3 = Accumulated time
 */
BLYNK_WRITE(V3) {
    if(!_accumulated_time_inited) {
        _accumulated_time_inited = true;
        _accumulated_time = param.asInt();
        Serial.println("Inited accumulated time = " + String(_accumulated_time));
    }
    
}

/**
 * V4 = Time hold control
 */
BLYNK_WRITE(V4) {
    HOLD_SEC = param.asInt();    
    Serial.println("Hold sec is set for = " + String(HOLD_SEC));
}


void blynk_init() {
    /**
     * เชื่อมต่ออินเตอร์เน็ตและ Blynk server
     */
    Serial.println("Blynk connecting..");
    Blynk.config(auth, domain, port);
    Blynk.connect(1000);
    Serial.println("Blynk connected!!");
    Blynk.syncAll();
}



static inline void blynk_accumulate_time() {
    static bool old_val = false;
    static uint32_t last_start = 0;
    uint32_t t_now = millis();

    
    if( !old_val && _is_running ) {
        old_val = true;
        last_start = t_now;
        _number_used++;
        Serial.println("Used +1 = " + String(_number_used));
    }

    if( old_val && !_is_running) {
        old_val = false;
        _accumulated_time += (t_now - last_start)/1000;
        Serial.println("Accumulate + " + String((t_now - last_start)/1000) + " ---> " + String(_accumulated_time) );
    }
}
static inline void blynk_update_data() {


    blynk_accumulate_time();
    
    static uint32_t last_update = millis();
    uint32_t t_now = millis();
    if( t_now - last_update > 1000 ) {
        last_update = t_now;


        Serial.println("Updated! is running = "+ String(_is_running));

        Blynk.virtualWrite(V6, _number_used);
        Blynk.virtualWrite(V2, _is_running);
        Blynk.virtualWrite(V3, _accumulated_time/60);
        Blynk.virtualWrite(V7, _accumulated_time);
        Blynk.virtualWrite(V5, HOLD_SEC);

        
    }

    
}