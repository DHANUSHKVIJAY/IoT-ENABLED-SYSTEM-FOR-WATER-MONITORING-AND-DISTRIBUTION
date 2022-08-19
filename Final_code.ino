/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  =>
  =>          USB HOWTO: http://tiny.cc/BlynkUSB
  =>

  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT DebugSerial
#define ph A0



// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#include <BlynkSimpleStream.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "McsYWhMETW7g1FsDoLd6_pyDxo6Bls-6";

int echoPin = 3;
int trigPin  = 2;
int dist = 0;
int floatPin = 12;
int relayPin = 8;


void setup()
{
  // Debug console
  DebugSerial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(floatPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  pinMode(ph, INPUT);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
}

void loop()
{
  Blynk.run();
  ultra();
  fSwitch();
  getPH();
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void ultra() {
  dist = 0.01723 * readUltrasonicDistance(2, 3);
  Blynk.virtualWrite(V0, 1000-dist);
}


void fSwitch(){
  int floatVal = digitalRead(floatPin);
  if(floatVal){
    digitalWrite(relayPin, HIGH);
    Blynk.virtualWrite(V1, "Tank Empty");
  }
  else{
    digitalWrite(relayPin, LOW);
    Blynk.virtualWrite(V1, "Tank Full");
}
}

void getPH(){
  int phVal = analogRead(ph);
  Blynk.virtualWrite(V2, phVal);
}
