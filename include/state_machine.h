


int32_t last_trig = -999000;


static inline void st_set_holding() {
    last_trig = millis();
}
static inline bool st_is_holding() {
    uint32_t t_now = millis();
    if( (int32_t)t_now - last_trig < HOLD_SEC*1000  ) {
        return true;
    }else{
        return false;
    }
}