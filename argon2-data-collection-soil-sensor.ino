//Set Moisture Sensor to Analog 0 Pin
int Moisture = A1;
int analogMoisture = 0;
int mVoltage = 0;
int x = 0;

void setup() {

    pinMode(D7, OUTPUT);
    Particle.subscribe("toggle-led", toggleLed, ALL_DEVICES);
    
    //Set pinmode as INPUT so that we read the data from the Moisture sensor
    pinMode(Moisture, INPUT);
    
}



void loop() {
    
    if (Particle.connected() == false) {
        Particle.connect();
    }
    
        while (x < 50 && digitalRead(D7) == HIGH) {
            
            analogMoisture = analogRead(Moisture);
            mVoltage = (analogMoisture*3300)/4096;
            
            Particle.variable("mVoltage", mVoltage);
            
            if(mVoltage < 100){
        
            Particle.publish("mvoltage_reading", "Needs Water", PUBLIC);  
            
            }
            
            else{
                
                Particle.publish("mvoltage_reading", "Enough Water", PUBLIC);  
            }
            
            Particle.publish("mvoltage_reading", String(mVoltage), PUBLIC);  
            x++;
            
            delay(10000);
        }
    
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
