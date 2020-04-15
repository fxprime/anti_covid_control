
#define SENS_PIN D5
#define SENS_DETECTED false
#define SENS_UNDETECTED true


void sensor_init() {
    pinMode(SENS_PIN, INPUT);
}

static inline bool sensor_get() {
    static int val_count = 0;
    bool val = digitalRead(SENS_PIN);
    if(val == SENS_DETECTED) {
        val_count ++;
    }else{
        val_count = 0;
    }
    if(val_count > 20) {
        val_count = 0;
        return true;
    }
    return false;
}