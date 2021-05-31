#include "MQTT.h"
int led1 = D6;
int buzzer = A5;

void callback(char* topic, byte* payload, unsigned int length);

MQTT client("test.mosquitto.org", 1883, callback);

// recieve message
void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;

    //Motion Detected
    if (!strcmp(p, "true"))
        //Turn on Led and Buzzer
        digitalWrite(led1, HIGH);
        analogWrite(buzzer, 10);
        delay(2000);
        //Turn off Led and Buzzer
        digitalWrite(led1, LOW);
        analogWrite(buzzer, 0);
    delay(1000);
}


void setup() {
    pinMode(led1, OUTPUT);
    pinMode(buzzer, OUTPUT);

    // connect to the server
    client.connect(System.deviceID());

    // subscribe
    if (client.isConnected()) {
        client.subscribe("SecurityCamera/MotionDetected");
    }
}

void loop() {
    if (client.isConnected())
        client.loop();
}
