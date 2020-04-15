
/**
 * Pin out
 */
#define LED_R D6
#define LED_Y D0
#define LED_G D4
#define LED_ON HIGH
#define LED_OFF LOW

void led_init() {
    pinMode(LED_R, OUTPUT);
    pinMode(LED_Y, OUTPUT);
    pinMode(LED_G, OUTPUT);
    digitalWrite(LED_R, LED_OFF);
    digitalWrite(LED_Y, LED_OFF);
    digitalWrite(LED_G, LED_OFF);

}

static inline void led_set_r(const bool& val) {
    digitalWrite(LED_R, (val ? LED_ON : LED_OFF));
}
static inline void led_set_y(const bool& val) {
    digitalWrite(LED_Y, (val ? LED_ON : LED_OFF));
}
static inline void led_set_g(const bool& val) {
    digitalWrite(LED_G, (val ? LED_ON : LED_OFF));
}
static inline void led_flash(const int& pin, const int& interval) {
    bool     last_state = 0;
    uint32_t t_now = millis();
    
    last_state = ((t_now % (uint32_t)interval*2) < interval);
    digitalWrite(pin, last_state);
}