#include <AccelStepper.h>

#define dirM1 3    //7
#define stepM1 2   //6
#define dirM2 5    //5
#define stepM2 4   //4
#define dirM3 7   //3
#define stepM3 6   //2

AccelStepper stepper2(AccelStepper::DRIVER, stepM1, dirM1); 
AccelStepper stepper1(AccelStepper::DRIVER, stepM2, dirM2); 
AccelStepper stepper3(AccelStepper::DRIVER, stepM3, dirM3); 

int num,Speed1,Speed2,Speed3 = 0;
byte byteRead;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
unsigned long last_time,last_time2 = 0;

void setup()
{  
   Serial.begin(9600);
   Serial3.begin(9600);
   stepper1.setMaxSpeed(3000);
   stepper2.setMaxSpeed(3000);
   stepper3.setMaxSpeed(3000);

}

void loop()
{  
  while (Serial3.available()) 
  {
    byteRead = Serial3.read();
    if (byteRead > 47 && byteRead < 58) 
    {
        num = (num * 10) + (byteRead - 48);
      }
      else if (byteRead == 'a') 
      {
        Speed1 = num;
        num = 0;
      }
      else if (byteRead == 'b') 
      {
        Speed1 = -num;
        num = 0;
      }
      else if (byteRead == 'c') 
      {
        Speed2 = num;
        num = 0;
      }
      else if (byteRead == 'd') 
      {
        Speed2 = -num;
        num = 0;
      }
      else if (byteRead == 'e') 
      {
        Speed3 = num;
        num = 0;
      }
      else if (byteRead == 'f') 
      {
        Speed3 = -num;
        num = 0;
      }
  }

   stepper1.setSpeed(Speed1); 
   stepper2.setSpeed(Speed2); 
   stepper3.setSpeed(Speed3); 
   stepper1.runSpeed();
   stepper2.runSpeed();
   stepper3.runSpeed();

}
