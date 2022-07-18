#include <SoftwareSerial.h>
SoftwareSerial camera(8, 9); // RX, TX

#define I2C
#ifdef I2C
#include <Pixy2I2C.h>
Pixy2I2C pixy;
#else
#include <Pixy2.h>
Pixy2 pixy;
#endif

void setup() 
{
  Serial.begin(115200);
  camera.begin(115200);
  pixy.init();
  pixy.changeProg("line");
}

void loop() 
{
  char buf[128];
  pixy.line.getMainFeatures();
  camera.print(pixy.line.vectors->m_x0);
  camera.print(",");
  camera.println(pixy.line.vectors->m_x1);
  delay(10);  

}
