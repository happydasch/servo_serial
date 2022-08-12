#include <Arduino.h>
#include <Servo.h>

Servo myservo;
int val = 90;

void setup() {
    Serial.begin(115200);
    myservo.attach(5);
}

void loop() {
    while (Serial.available()) {
        String sval = Serial.readString();
        sval.trim();
        if (sval == "-") {
            val -= 10;
        } else if (sval == "+") {
            val += 10;
        } else if (sval != "") {
            if ((byte)sval[0] == 27) {
                if ((byte)sval[1] == 91) {
                    if ((byte)sval[2] == 68) {
                        val -= 1;
                    } else if ((byte)sval[2] == 66) {
                        val -= 5;
                    } else if ((byte)sval[2] == 67) {
                        val += 1;
                    } else if ((byte)sval[2] == 65) {
                        val += 5;
                    }
                }
            } else {
                val = sval.toInt();
            }
        }
        val = constrain(val, 0, 180);
        Serial.print("Setting servo to: ");
        Serial.println(val);
    }
    myservo.write(val);
    delay(20);
}
