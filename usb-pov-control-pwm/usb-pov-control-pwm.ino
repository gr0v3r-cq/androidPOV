// The source for the Android application can be found at the following link: https://github.com/Lauszus/ArduinoBlinkLED
// The code for the Android application is heavily based on this guide: http://allaboutee.com/2011/12/31/arduino-adk-board-blink-an-led-with-your-phone-code-and-explanation/ by Miguel
#include <adk.h>

//
// CAUTION! WARNING! ATTENTION! VORSICHT! ADVARSEL! ¡CUIDADO! ВНИМАНИЕ!
//
// Pin 13 is occupied by the SCK pin on various Arduino boards,
// including Uno, Duemilanove, etc., so use a different pin for those boards.
//
// CAUTION! WARNING! ATTENTION! VORSICHT! ADVARSEL! ¡CUIDADO! ВНИМАНИЕ!
//
/*#if defined(LED_BUILTIN)
#define LED LED_BUILTIN // Use built in LED
#else
#define LED 3 // Set to something here that makes sense for your board.
#endif*/

#define LED 3 // Set to something here that makes sense for your board.

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#define COMMAND_LED 0x2
#define TARGET_PIN_2 0x2
#define VALUE_ON 0x1
#define VALUE_OFF 0x0

USB Usb;
ADK adk(&Usb, "Srichakram", // Manufacturer Name
              "ArduinoADK", // Model Name
              "Simple Led blink sketch for the USB Host Shield", // Description (user-visible string)
              "1.0", // Version
              "http://www.tkjelectronics.dk/uploads/ArduinoBlinkLED.apk", // URL (web page to visit if no installed apps support the accessory)
              "123456789"); // Serial Number (optional)

uint32_t timer;
bool connected;

int velocidad = 0;
int potenciometro = 0;
int InA1 = 7;
int InB1 = 8;
int PWM1 = 3;  //PWM1 connects to pin 3
//input nilai PWM 
//(1 = 220; 2 = 178; 3 = 151; 4 = 134; 5 = 120; 6 = 107; 7 = 98; 8 = 91; 9 = 81; 10 = 78)
int PWM1_val[] = {220,178,151,134,120,107,98,91,81,78}; 
void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print("\r\nOSCOKIRQ failed to assert");
    while (1); // halt
  }
  pinMode(LED, OUTPUT);
  
  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  
  Serial.print("\r\nArduino Blink LED Started");
}

void loop() {
  Usb.Task();

  if (adk.isReady()) {
    if (!connected) {
      connected = true;
      Serial.print(F("\r\nConnected to accessory"));
    }

    uint8_t msg[3];
    uint16_t len = sizeof(msg);
    uint8_t rcode = adk.RcvData(&len, msg);
    if (rcode && rcode != hrNAK) {
      Serial.print(F("\r\nData rcv: "));
      Serial.print(rcode, HEX);
    } else if (len > 0) {
      /*Serial.print(F("\r\nData Packet: "));
      Serial.print(msg[0]);
      digitalWrite(LED, msg[0] ? HIGH : LOW);*/

      if (msg[0] == COMMAND_LED) {
        if (msg[1] == TARGET_PIN_2){
          //get the switch state
          byte value = msg[2];
          //set output pin to according state
          Serial.println(value);
          if(value == (byte)1) {            
            digitalWrite(InA1, HIGH);
            digitalWrite(InB1, LOW);
            analogWrite(PWM1, PWM1_val[0]);
            Serial.println(PWM1_val[0]);
          }
          if(value == (byte)2) {
            digitalWrite(InA1, HIGH);
            digitalWrite(InB1, LOW);
            analogWrite(PWM1, PWM1_val[1]);
            Serial.println(PWM1_val[1]);
          }
          if(value == (byte)3) {
            digitalWrite(InA1, HIGH);
            digitalWrite(InB1, LOW);
            analogWrite(PWM1, PWM1_val[2]);
            Serial.println(PWM1_val[2]);
          }
          if(value == (byte)4) {
            digitalWrite(InA1, HIGH);
            digitalWrite(InB1, LOW);
            analogWrite(PWM1, PWM1_val[3]);
            Serial.println(PWM1_val[3]);
          }
          if(value == (byte)5) {
            digitalWrite(InA1, HIGH);
            digitalWrite(InB1, LOW);
            analogWrite(PWM1, PWM1_val[4]);
            Serial.println(PWM1_val[4]);
          }
          if(value == (byte)6) {
            digitalWrite(InA1, HIGH);
            digitalWrite(InB1, LOW);
            analogWrite(PWM1, PWM1_val[5]);
            Serial.println(PWM1_val[5]);
          }
          if(value == (byte)7) {
            digitalWrite(InA1, HIGH);
            digitalWrite(InB1, LOW);
            analogWrite(PWM1, PWM1_val[6]);
            Serial.println(PWM1_val[6]);
          }
          if(value == (byte)8) {
            digitalWrite(InA1, HIGH);
            digitalWrite(InB1, LOW);
            analogWrite(PWM1, PWM1_val[7]);
            Serial.println(PWM1_val[7]);
          }
          if(value == (byte)9) {
            digitalWrite(InA1, HIGH);
            digitalWrite(InB1, LOW);
            analogWrite(PWM1, PWM1_val[8]);
            Serial.println(PWM1_val[8]);
          }
          if(value == (byte)10) {
            digitalWrite(InA1, HIGH);
            digitalWrite(InB1, LOW);
            analogWrite(PWM1, PWM1_val[9]);
            Serial.println(PWM1_val[9]);
          }        
        }
      }      
    }

    if (millis() - timer >= 1000) { // Send data every 1s
      timer = millis();
      rcode = adk.SndData(sizeof(timer), (uint8_t*)&timer);
      if (rcode && rcode != hrNAK) {
        //Serial.print(F("\r\nData send: "));
        //Serial.print(rcode, HEX);
      } else if (rcode != hrNAK) {
        //Serial.print(F("\r\nTimer: "));
        //Serial.print(timer);
      }
    }
  } else {
    if (connected) {
      connected = false;
      Serial.print(F("\r\nDisconnected from accessory"));
      digitalWrite(LED, LOW);
    }
  }
}
