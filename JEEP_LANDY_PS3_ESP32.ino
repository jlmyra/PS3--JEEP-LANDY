

#include <Ps3Controller.h>

//****************Motor PWM******************************/

uint32_t freq = 30000;  //PWM Frequency
uint8_t driveMotorChannel = 14;//changed line 96 espservo.h to 2 servos max leaving channels 2-16 available for motors
uint8_t resolution = 8; //8 bit resolution PWM
int driveMotorPin = 25; //Cytron white wire (pwm) GPIO25, DOIT-D25, Wemos-I25
int driveMotorDirection = 27;

//****************END Motor PWM******************************/

//****************Winch Motor PWM******************************/

uint8_t winchPWMChannel_1 = 4;
uint8_t winchPWMChannel_2 = 2;

//int winchPWMPin = 26; //Winch Unwind  A1A
//int winchDirectionPin = 18; //Winch Rewind A1B

int winchDirection_1 = 26;
int winchDirection_2 = 18;

//****************END Winch Motor PWM******************************/

//****************Steering Servo******************************/
#include <ESP32Servo.h>  //changed line 96 espservo.h to 2 servos max leaving channels 2-16 availble for motors

Servo steerServo;  // create servo object to control a servo
                   // 2 servo objects can be created on the ESP32
 
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 4; //DOIT Pin - D4, Wemos Pin - I4 
//***JEEP***
//int servoMin = 1200;//1150 Drivers Side  range 700 - 1100-1765 offsets the centerpoint of the servo to get the steering centered.
//int servoMax = 2000;//1850 Passenger side
//***LANDY***
int servoMin = 1125;//1150   range 700 - 1100-1765 offsets the centerpoint of the servo to get the steering centered.
int servoMax = 1925;//1850 

//****************END Steering Servo******************************/

//*********************Motor Ramp Variables***********************/

float motorSpeedIncrement = 2;
float oldMotorSpeed = 0;
int oldMotorSpeedSlow = 0;
int motorSpeed = 0;
int motorSpeedSlow = 0;
float nitroSpeed = 0.6;
float normalSpeed = 0.45;
int oldJoystickPos = 0;
int joystickPos = 0;


//*********************End Motor Ramp Variables***********************/

//****************Battery Voltage Alarm******************************/
int batStatusLED = 0; //Variable to hold rover battery status on controller

float bitVoltage; //ADC converted voltage on batPin A0

float batteryVoltage; //computed battery voltage

int batRemPercent;

const int batPin =  32; //DOIT - D32, Wemos - I32 - ADC1_CH4 Variable that holds the GPIO Address 
unsigned long previousMillis = 0; //for timer reading A0
unsigned long interval = 1000; // millis between read A0
int rumbleCounter = 0;

//****************END Battery Voltage Alarm******************************/

  ESP32PWM pwm;

  void setup() {
 
  Serial.begin(250000);
 
  if (!Ps3.begin("b8:27:eb:37:85:b9")) {
    Serial.println("Initialization failed.");
    return;
  }
  Serial.println("Initialization finished.");
 
  Ps3.attach(onEvent);
  Ps3.attachOnConnect(onConnection);

//Battery Meter Setup
  pinMode(batPin, INPUT);
  analogSetPinAttenuation(batPin, ADC_0db);

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
//Drive Motor and Winch PWM Setup
  pinMode(driveMotorPin, OUTPUT); //Must have
  pinMode(driveMotorDirection, OUTPUT); //Must have
  
  pinMode(winchDirection_1, OUTPUT); //Must have
  pinMode(winchDirection_2, OUTPUT); //Must have

  
  ledcSetup(driveMotorChannel, freq, resolution);
  ledcAttachPin(driveMotorPin, driveMotorChannel); //GPIO25, DOIT D25, WEMOS I25

  ledcSetup(winchPWMChannel_1, freq, resolution);
  ledcAttachPin(winchDirection_1, winchPWMChannel_1);

  ledcSetup(winchPWMChannel_2, freq, resolution);
  ledcAttachPin(winchDirection_2, winchPWMChannel_2);

  //Servo Setup
 
  steerServo.setPeriodHertz(300);    // standard 50 hz servo
  steerServo.attach(servoPin, servoMin, servoMax); // attaches the servo on pin 4 to the servo object
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
  
}
 
void loop() {
  
  if(!Ps3.isConnected())
        return; 
          
  //computeBatteryVoltage();

  //vTaskDelete(NULL);
}
 



 
 



   
