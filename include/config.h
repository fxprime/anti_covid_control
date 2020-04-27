
int HOLD_SEC = 30;

void console_init() {
    Serial.begin(115200);
}


int     _number_used = 0;
bool    _number_used_inited = false;
int     _accumulated_time = 0;
bool    _accumulated_time_inited = false;
bool    _run_by_app = false;
bool    _is_running = false;