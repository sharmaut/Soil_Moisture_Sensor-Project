int sum = 0;
int temp = 0;
int average = 0;
int y = 1;
String value;

void setup() {
    pinMode(D7, OUTPUT);
    Particle.subscribe("mvoltage_reading", mVoltage, ALL_DEVICES);
    Particle.subscribe("toggle-led", toggleLed, ALL_DEVICES);
    
}

void loop() {
    //Connect to Particle Clould check
    if (Particle.connected() == false) {
        Particle.connect();
    }
    
    //For single device testing, set pin D7 to HIGH : digitalWrite(D7, HIGH);
    if (digitalRead(D7) == HIGH) {
        
        if (y > 20) {
            average = sum / y;
            if (average < 2000 && average > 0) {
                    digitalWrite(D7, HIGH);
                    delay(1000);
                    digitalWrite(D7, LOW);
                    Particle.publish("avg_voltage_reading", String(average));
                    Particle.publish("water-plant", "watered", PUBLIC);
                    Particle.publish("toggle-led", "off", PUBLIC);
                    average = 0;
            }
            if (average > 2000) {
                    digitalWrite(D7, HIGH);
                    delay(1000);
                    digitalWrite(D7, LOW);
                    Particle.publish("avg_voltage_reading", String(average));
                    Particle.publish("water-plant", "not watered", PUBLIC);
                    Particle.publish("toggle-led", "off", PUBLIC);
                    average = 0;
            }
            y = 0;
        }
       delay(10000);
    }
}
    
//this function sums the voltage values it recieves/collects
int mVoltage(const char *event, const char *data) {
    
    value = atoi(data);
    sum = sum + value.toInt();
    y++;
        
    return sum; 
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