int x = 0;

void setup() {
    
    pinMode(D7, OUTPUT);
    Particle.subscribe("toggle-led", toggleLed, ALL_DEVICES);
    
    //Connect to a WiFi network check
    if (WiFi.ready() == false) {
        WiFi.setCredentials("Utsav", "thankyousir");
        WiFi.on(); WiFi.connect();
    }
    
    //Connect to Particle Clould check
    if (Particle.connected() == false) {
        Particle.connect();
    }
    Particle.subscribe("water your plant", water, ALL_DEVICES);
    
}

void loop() {
    
    if (digitalRead(D7) == LOW && x < 1) {
        delay(10000);
        Particle.publish("toggle-led", "on", PUBLIC);
        delay(2000);
        x++;
    }

}

String water(const char *event, const char *data) {
    return String(data);
}

//this function turns on LED
void toggleLed(const char *event, const char *data) {
    
    if (digitalRead(D7) == LOW && String(data).equals("on")) {
        digitalWrite(D7, HIGH);
    }
    else if (digitalRead(D7) == HIGH && String(data).equals("off")){
        digitalWrite(D7, LOW);
    }
}