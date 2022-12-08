#include <ODriveArduino.h>
#include <ODriveEnums.h>
#include <Servo.h> 

#include <ODriveEnums.h>

#include <HardwareSerial.h>
#include <ODriveArduino.h>
// Printing with stream operator helper functions
template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }
HardwareSerial& odrive_serial1 = Serial1;
HardwareSerial& odrive_serial2 = Serial2;
ODriveArduino odrive1(odrive_serial1);
ODriveArduino odrive2(odrive_serial2);
Servo myservo1;
Servo myservo2;

int requested_state = AXIS_STATE_IDLE;
long previousmillis = 0;

void setup() {
  // put your setup code here, to run once:
  odrive_serial1.begin(115200);
  odrive_serial2.begin(115200);
  Serial.begin(115200);
  myservo1.attach(9);
  myservo2.attach(10);
  while (!Serial) ; // wait for Arduino Serial Monitor to open

  Serial.println("ODriveArduino");
  Serial.println("Setting parameters...");
  odrive_serial1 << "w axis0.config.motor.current_soft_max " << 1.0f <<'\n';
  odrive_serial2 << "w axis0.config.motor.current_soft_max " << 1.0f <<'\n';
  requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL;
  //odrive1.run_state(0,requested_state, false);
  //odrive2.run_state(0,requested_state, false);
  
}


void loop() {
  // put your main code here, to run repeatedly:
  //odrive.run_state(0,requested_state, false);
  /*unsigned long currentmillis = millis();
  //Serial.println(currentmillis);

  if(currentmillis - previousmillis > 1000){
    previousmillis=currentmillis;

    if(requested_state == AXIS_STATE_IDLE){
      Serial.println("On");
      requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL;
      odrive.run_state(0,requested_state, false);
    }
    else{
      Serial.println("off");
      requested_state = AXIS_STATE_IDLE;
      odrive.run_state(0,requested_state, false);
    }
  }*/
  Serial.println("On");
  //odrive_serial << "w axis0.config.motor.current_soft_max " << 1.0f <<'\n';
  //delay(1000);
  //odrive_serial << "w axis0.config.motor.current_soft_max " << 10.0f <<'\n';
  //odrive.SetPosition(0,0);
  //delay(500);
  //odrive.SetPosition(0,50);
  /*for (float ph = 0.0f; ph < 6.28318530718f; ph += 0.01f) {
        float pos_m0 = 2.0f * cos(ph);
        float pos_m1 = 2.0f * sin(ph);
        odrive.SetPosition(0, pos_m0);
        odrive.SetPosition(1, pos_m1);
        delay(5);
      }*/
      static const unsigned long duration = 10000;
      unsigned long start = millis();
      while(millis() - start < duration) {
        for (int motor = 0; motor < 1; ++motor) {
          Serial << odrive1.GetPosition(motor) << "    " << odrive2.GetPosition(motor) << '\t';
        }
        delay(10);
        Serial << '\n';
        myservo1.write(360*odrive1.GetPosition(0));
        myservo2.write(360*odrive2.GetPosition(0));

      }
      
  //Serial.println("Off");



}
