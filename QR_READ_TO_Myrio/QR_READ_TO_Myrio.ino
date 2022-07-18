
#include <SoftwareSerial.h>
#define qr_code 5
SoftwareSerial QR_code(9, 8); // RX, TXy
bool ch_scan = false, ch_send = false, once_time = true;
String dat;


unsigned long period = 4500;//5200
unsigned long last_time = 0;


void setup() {

  Serial.begin(9600);
  QR_code.begin(9600);
  pinMode(qr_code , OUTPUT);
  digitalWrite(qr_code, HIGH);// QR CODE TURN OFF

}

void loop() {

  if (QR_code.available()) {
    String txt = QR_code.readStringUntil("\n");
    //    Serial.println(txt+"   space  "+String(txt.length()));
    if (txt.length() == 2) {
      dat = txt.substring(0, 1);
      ch_send = true;
      //      Serial.println(txt + "  CH 2");
    } else if (txt.length() == 16) {
      dat = txt.substring(14, 15);
      ch_send = true;
      //      Serial.println(txt + "  CH 16");
    }
  }

  if (ch_send == true) {
    Serial.println(dat); delay(50);
    ch_scan = false;
  } else {
    Serial.println('4'); delay(50);
    ch_scan = false;
  }

  if (Serial.available()) {
    char tt = Serial.read();
    if (tt == 'A') {
      //      Serial.println("work A");
      ch_scan = true;
    } else if (tt == 'B') {
      ch_send = false;
      once_time = true;
      dat = "";
    }
  }
  if (ch_scan == true) {
    if (once_time == true) {
      //      Serial.println("work this once time");
      digitalWrite(qr_code, HIGH); delay(50);
      digitalWrite(qr_code, LOW);
      once_time = false;
      last_time = millis();
    } else {
      digitalWrite(qr_code, HIGH);
    }

    if (( millis() - last_time > period) && once_time == false) {
      //      Serial.println("work this");
      once_time = true;
      last_time = millis();
    }


  }

}

/*
  if (Serial.available()) {
    char a = Serial.read();

    QR_code.write(static_cast<byte>(0x7E));
    QR_code.write(static_cast<byte>(0x00));
    QR_code.write(static_cast<byte>(0x08));
    QR_code.write(static_cast<byte>(0x01));
    QR_code.write(static_cast<byte>(0x00));
    QR_code.write(static_cast<byte>(0x02));
    QR_code.write(static_cast<byte>(0x01));
    QR_code.write(static_cast<byte>(0xAB));
    QR_code.write(static_cast<byte>(0xCD));

  }
*/
