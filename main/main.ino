#include <Servo.h>
#include <ArduinoJson.h>

Servo servos[6];

// {"motor_demands":[0.1, 0.1, 0.1, 0.1, 0.1, 0.1]}

void writeServos(float motor_demands[], Servo servos[]) {
    for(int i=0; i<6; i++) {
        servos[i].writeMicroseconds(motor_demands[i]);
    }
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);

  Serial.print("Setting up driver...\n");
   
  servos[0].attach(3);
  servos[1].attach(5);
  servos[2].attach(6);
  servos[3].attach(9);
  servos[4].attach(10);
  servos[5].attach(11);

  float init[6] = {1500, 1500, 1500, 1500, 1500, 1500};
  writeServos(init, servos);
  delay(3000);
  Serial.print("Driver ready\n");
}

void loop() {
    if (Serial.available() > 0) {
      
        String json = Serial.readString();
        Serial.println(json); 
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(json);

        float motor_demands[6];
        
        if (!root.success()) {
            Serial.println("parseObject() failed");
        }
        else {
            root.prettyPrintTo(Serial); 

            for(int i=0; i<6; i++) {
                double demand = root["motor_demands"][i];
                motor_demands[i] = demand*500 + 1500;     
            }
            writeServos(motor_demands, servos);
        }           
    }     
}










