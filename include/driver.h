#define DRIVE_PIN 13
#define DRIVE_BUT D1

void drive_init() {
    pinMode(DRIVE_PIN, OUTPUT);
    pinMode(DRIVE_BUT, INPUT_PULLUP);
    digitalWrite(DRIVE_PIN, LOW);
}

static inline bool drive_but_pressed() {
    return !digitalRead(DRIVE_BUT);
}

static inline void drive_set(const bool& val ) {
    digitalWrite(DRIVE_PIN, val);
}